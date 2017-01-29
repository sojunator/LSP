


//Globals

Texture2D diffuseTexture : register(t0);
SamplerState diffuseSampler : register(s0);

Texture2D specularTexture : register(t1);
SamplerState specularSampler : register(s1);

Texture2D normalTexture : register(t2);
SamplerState normalSampler : register(s2);

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
}



//Vertex shader

struct VSInput
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
	float3 normal: NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};



struct VSOutput
{
	float3 position : POSITION;
	float2 tex : TEXCOORD;
	float3 normal: NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};


VSOutput VSMain(in VSInput input)
{
	VSOutput output;
	
	output.position = input.position;
	output.tex = input.uv;
	output.normal = input.normal;
	output.tangent = input.tangent;
	output.binormal = input.binormal;

	return output;
}

//Hull shader

struct ConstantOutputType
{
	float edges[3]: SV_TessFactor;
	float inside : SV_InsideTessFactor;
};


ConstantOutputType ColorPatchConstantFunction(InputPatch<VSOutput, 3> InputPatch, uint patchId : SV_PrimitiveID)
{
	ConstantOutputType output;


	// Set the tessellation factors for the three edges of the triangle.
	output.edges[0] = 2;
	output.edges[1] = 2;
	output.edges[2] = 2;

	// Set the tessellation factor for tessallating inside the triangle.
	output.inside = 2;

	return output;
}

[domain("tri")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("ColorPatchConstantFunction")]

VSOutput HSMain(InputPatch<VSOutput, 3> patch, uint pointId : SV_OutputControlPointID, uint pathcId, SV_PrimitiveID)
{
	VSOutput output;

	output.position = patch[pointId].position;
	output.tex = patch[pointId].uv;
	output.normal = patch[pointId].normal;
	output.tangent = patch[pointId].tangent;
	output.binormal = patch[pointId].binormal;

	return output;

}


//Domain shader
struct PSInput
{
	float4 position : SV_POSITION;
	float3 positionWS : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};
[domain("tri")]

PSInput DSMain(ConstantOutputType input, float3 uvwCoord : SV_DomainLocation, const OutputPatch<VSOutput, 3> patch)
{
	float3 vertexPosition;
	float3 normal;
	float3 tangent;
	float3 binormal;
	PSInput output;

	vertexPosition = uvwCoord.x * patch[0].position + uvwCoord.y * patch[1].position + uvwCoord.z * patch[2].position;
	output.position = mul(float4(vertexPosition, 1), mvpMatrix);

	normal = uvwCoord.x * patch[0].normal + uvwCoord.y * patch[1].normal + uvwCoord.z * patch[2].normal;
	output.normal = mul(normal, (float3x3)worldMatrix);

	tangent = uvwCoord.x * patch[0].tangent + uvwCoord.y * patch[1].tangent + uvwCoord.z * patch[2].tangent;
	output.tangent = mul(tangent, (float3x3)worldMatrix);

	binormal = uvwCoord.x * patch[0].binormal + uvwCoord.y * patch[1].binormal + uvwCoord.z * patch[2].binormal;
	output.binormal = mul(binormal, (float3x3)worldMatrix);

	output.tex = patch[0].tex;

	return output;
}


float4 PSMain(VSOutput input) : SV_TARGET
{


	float3 lightDir = normalize(float3(1, 0, -1)); //TEMP


	float4 textureColor = diffuseTexture.Sample(diffuseSampler, input.tex);

	float4 bumpMap = normalTexture.Sample(normalSampler, input.tex);
	bumpMap = (bumpMap * 2.0f) - 1.0f;

	float3 bumpNormal = (bumpMap.x*input.tangent) + (bumpMap.y*input.binormal) + (bumpMap.z*input.normal);

	bumpNormal = normalize(bumpNormal);

	lightDir = -lightDir;
	float lightIntensity = saturate(dot(bumpNormal, lightDir));

	float4 diffuse = saturate(diffuseColor*lightIntensity);
	float4 specular = float4(0,0,0,0);
	if (lightIntensity > 0.0f)
	{

		float3 viewDirection = camPosition - input.positionWS;

		float4 specularIntensity = specularTexture.Sample(specularSampler, input.tex);
		float3 reflection = normalize(lightDir + viewDirection);
		specular = pow(saturate(dot(bumpNormal, reflection)),specularPower)*lightIntensity;
		specular = specular * specularIntensity;
	}

	return ambientColor*textureColor*0.05f + diffuse*textureColor + specular*specularColor;
}