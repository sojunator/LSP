//Globals

Texture2D diffuseTexture : register(t0);
SamplerState diffuseSampler : register(s0);

Texture2D specularTexture : register(t1);
SamplerState specularSampler : register(s1);

Texture2D normalTexture : register(t2);
SamplerState normalSampler : register(s2);

Texture2D heightTexture : register(t3);
SamplerState heightSampler : register(s3);

cbuffer mvp : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix mvpMatrix;
	float3 camPosition;
};

cbuffer material : register(b1)
{
	float4 ambientColor;
	float4 diffuseColor;
	float4 specularColor;
	float specularPower;
	float tess;
}


struct VSInput
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};


struct HSInput
{
	float3 position : POSITION;
	float2 tex : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};

struct DSinput
{
	float3 position : POSITION;
	float2 tex : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};

struct HSConstantData
{
	float edges[3] : SV_TessFactor;
	float inside : SV_InsideTessFactor;
};


struct PSInput
{
	float4 position : SV_POSITION;
	float3 positionWS : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};

//Vertex shader

DSinput VSMain(in VSInput input)
{
	DSinput output;
	
	output.position = input.position.xyz;
	output.tex = input.uv;
	output.normal = input.normal;
	output.tangent = input.tangent;
	output.binormal = input.binormal;

	return output;
}

//Hull shader

HSConstantData PatchConstantFunction(InputPatch<HSInput, 3> inputPatch, uint patchId : SV_PrimitiveID)
{
	HSConstantData output;


	// Set the tessellation factors for the three edges of the triangle.
	output.edges[0] = tess;
	output.edges[1] = tess;
	output.edges[2] = tess;

	// Set the tessellation factor for tessallating inside the triangle.
	output.inside = tess;

	return output;
}

[domain("tri")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("PatchConstantFunction")]
DSinput HSMain(InputPatch<HSInput, 3> patch, uint pointId : SV_OutputControlPointID, uint patchId : SV_PrimitiveID)
{
	DSinput output;

	output.position = patch[pointId].position;
	output.tex = patch[pointId].tex;
	output.normal = patch[pointId].normal;
	output.tangent = patch[pointId].tangent;
	output.binormal = patch[pointId].binormal;

	return output;

}

//Domain shader

[domain("tri")]
PSInput DSMain(HSConstantData input, float3 uvwCoord : SV_DomainLocation, const OutputPatch<DSinput, 3> patch)
{
	float3 vertexPosition;
	float3 normal;
	float3 tangent;
	float3 binormal;
	PSInput output;


	output.tex = uvwCoord.x * patch[0].tex + uvwCoord.y * patch[1].tex + uvwCoord.z * patch[2].tex;

	normal = uvwCoord.x * patch[0].normal + uvwCoord.y * patch[1].normal + uvwCoord.z * patch[2].normal;
	normal = normalize(normal);
	output.normal = mul(normal, (float3x3) worldMatrix);

	float h = heightTexture.SampleLevel(heightSampler, output.tex, 0).r;

	vertexPosition = uvwCoord.x * patch[0].position + uvwCoord.y * patch[1].position + uvwCoord.z * patch[2].position;

	vertexPosition += (5.0f * (h - 1.0)) * normal;

	output.position = mul(float4(vertexPosition, 1), mvpMatrix);
	output.positionWS = mul(vertexPosition, (float3x3) worldMatrix);

	

	tangent = uvwCoord.x * patch[0].tangent + uvwCoord.y * patch[1].tangent + uvwCoord.z * patch[2].tangent;
	output.tangent = mul(tangent, (float3x3) worldMatrix);

	binormal = uvwCoord.x * patch[0].binormal + uvwCoord.y * patch[1].binormal + uvwCoord.z * patch[2].binormal;
	output.binormal = mul(binormal, (float3x3) worldMatrix);

	

	return output;
}


//Pixel shader

float4 PSMain(PSInput input) : SV_TARGET
{
	float3 lightDir = normalize(float3(1, 0, -1)); //TEMP


	float4 textureColor = diffuseTexture.Sample(diffuseSampler, input.tex);

	float4 bumpMap = normalTexture.Sample(normalSampler, input.tex);
	bumpMap = (bumpMap * 2.0f) - 1.0f;

	float3 bumpNormal = (bumpMap.x * input.tangent) + (bumpMap.y * input.binormal) + (bumpMap.z * input.normal);

	bumpNormal = normalize(bumpNormal);

	lightDir = -lightDir;
	float lightIntensity = saturate(dot(bumpNormal, lightDir));

	float4 diffuse = saturate(diffuseColor * lightIntensity);
	float4 specular = float4(0, 0, 0, 0);
	if (lightIntensity > 0.0f)
	{

		float3 viewDirection = camPosition - input.positionWS;

		float4 specularIntensity = specularTexture.Sample(specularSampler, input.tex);
		float3 reflection = normalize(lightDir + viewDirection);
		specular = pow(saturate(dot(bumpNormal, reflection)), specularPower) * lightIntensity;
		specular = specular * specularIntensity;
	}
	return heightTexture.Sample(heightSampler, input.tex);
	return ambientColor * textureColor * 0.05f + diffuse * textureColor + specular * specularColor;
}