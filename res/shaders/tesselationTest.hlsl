//Globals
Texture2D displacementTexture : register(t3);
SamplerState displacementSampler : register(s3);

TextureCube reflectionTexture : register(t4);
SamplerState reflectionSampler : register(s4);



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
	float uvScale;
	float uvOffset;
	float texelLengthX2;
}



struct VSInput
{
	float3 position : POSITION;
};


struct HSInput
{
	float3 position : POSITION;
	float tessFactor : TESS;
};

struct DSinput
{
	float3 position : POSITION;
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
};

//Vertex shader

HSInput VSMain(in VSInput input)
{
	HSInput output;
	
	output.position = input.position.xyz;


	float3 posW = mul(input.position, (float3x3) worldMatrix);
	float d = distance(camPosition, posW);


	float minTessDistance = 1;
	float maxTessDistance = 10;

	float tess = saturate((minTessDistance - d) / (minTessDistance - maxTessDistance));

	float minTessFactor = 64.0f;
	float maxTessFactor = 1.0f;

	output.tessFactor = minTessFactor + (tess * (maxTessFactor - minTessFactor));

	return output;
}

//Hull shader

HSConstantData PatchConstantFunction(InputPatch<HSInput, 3> patch, uint patchId : SV_PrimitiveID)
{
	HSConstantData output;


	// Set the tessellation factors for the three edges of the triangle.
	output.edges[0] = 0.5f * (patch[1].tessFactor + patch[2].tessFactor);
	output.edges[1] = 0.5f * (patch[2].tessFactor + patch[0].tessFactor);
	output.edges[2] = 0.5f * (patch[0].tessFactor + patch[1].tessFactor);

	// Set the tessellation factor for tessallating inside the triangle.
	output.inside = output.edges[0];

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

	vertexPosition = uvwCoord.x * patch[0].position + uvwCoord.y * patch[1].position + uvwCoord.z * patch[2].position;

	float4 pos = float4(vertexPosition.xz, 0, 1);

	output.tex = pos.xy * uvScale + uvOffset;

	float3 displacement = displacementTexture.SampleLevel(displacementSampler, output.tex, 0).xyz;

	pos.xyz += displacement;

	output.position = mul(pos.xzyw, mvpMatrix);
	output.positionWS = mul(pos.xzy, (float3x3) worldMatrix);

	

	return output;
}


//Pixel shader

float4 PSMain(PSInput input) : SV_TARGET
{
	float3 sunDir = normalize(float3(0, 0, -1));

	float3 eyeVec = camPosition - input.positionWS;
	float3 eyeDir = normalize(eyeVec);


	float2 grad = normalTexture.Sample(normalSampler, input.tex).xy;
	float3 normal = normalize(float3(grad, texelLengthX2));


	float3 reflectVec = reflect(-eyeDir, normal);
	float3 cosAngle = dot(normal, eyeDir);

	float3 reflection = reflectionTexture.Sample(reflectionSampler, reflectVec).xyz;

	float3 waterColor = lerp(float3(0.0, 0.1, 0.9), reflection, 0.1);

	float cosSpec = clamp(dot(reflectVec, sunDir), 0, 1);
	float sunSpot = pow(cosSpec, 400); //shiny

	waterColor += float3(0.9, 0.7, 0.07) * sunSpot;
	
	return float4(waterColor, 1);
}