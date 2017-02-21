//Globals

Texture2D perlinTexture : register(t0);
SamplerState perlinSampler : register(s0);

Texture1D fresnelTexture : register(t1);
SamplerState fresnelSampler : register(s1);

Texture2D normalTexture : register(t2);
SamplerState normalSampler : register(s2);

Texture2D displacementTexture : register(t3);
SamplerState displacementSampler : register(s3);

TextureCube reflectionTexture : register(t4);
SamplerState reflectionSampler : register(s4);


#define PATCH_BLEND_BEGIN		100
#define PATCH_BLEND_END			50000

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
	float4 baseWaterColor;
	float4 skyColor;
	float shininess;
	float uvScale;
	float uvOffset;
	float texelLengthX2;
	float3 bendParam;
	float perlinSize;
	float3 perlinAmp;
	float radius;
	float3 perlinOctave;
	float aiming;
	float3 perlinGradient;
	float pad3;
	float2 perlinMovement;
	float2 aimPos;

}

struct DirLight
{
	float4 lightColor;
	float3 lightDir;
	float padding;
};
//Struct coupled with LightManager
struct PointLight
{
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	float power;
	float4 lightColor;
	float3 position;
	float padding;
};
//Buffer coupled with LightManager
cbuffer lightBuffer : register(b2)
{
	uint nrOfDirectionalLights;
	uint nrOfPointLights;
	int padding1;
	int padding2;
	DirLight directionalLights[3];
	PointLight pointLights[20];
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

	output.position = mul(float4(input.position, 1), worldMatrix).xyz;


	float3 posW = output.position.xyz;
	float d = distance(camPosition, posW);


	float minTessDistance = 1;
	float maxTessDistance = 100;

	float tess = saturate((minTessDistance - d) / (minTessDistance - maxTessDistance));

	float minTessFactor = 16.0f;
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
[partitioning("pow2")]
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

	float4 pos = float4(vertexPosition.xzy, 1);

	output.tex = pos.xy * uvScale + uvOffset;

	float3 eyeVec = pos.xyz - camPosition;

	float dist2d = length(eyeVec.xy);

	float blendFactor = (PATCH_BLEND_END - dist2d) / (PATCH_BLEND_END - PATCH_BLEND_BEGIN);
	blendFactor = clamp(blendFactor, 0, 1);

	float perlin = 0;
	if(blendFactor < 1)
	{

		float2 perlinTC = output.tex * perlinSize + (pos.xy % 256) - 128;
		float perlin0 = perlinTexture.SampleLevel(perlinSampler, perlinTC * perlinOctave.x + perlinMovement, 0).w;
		float perlin1 = perlinTexture.SampleLevel(perlinSampler, perlinTC * perlinOctave.y + perlinMovement, 0).w;
		float perlin2 = perlinTexture.SampleLevel(perlinSampler, perlinTC * perlinOctave.z + perlinMovement, 0).w;
		perlin = perlin0 * perlinAmp.x + perlin1 * perlinAmp.y + perlin2 * perlinAmp.z;

	}

	float3 displacement = 0;
	if(blendFactor > 0)
	{
		displacement = displacementTexture.SampleLevel(displacementSampler, output.tex, 0).xyz;
	}
	displacement = lerp(float3(0, 0, perlin), displacement, blendFactor);


	pos.z += displacement.z;

	output.position = mul(pos.xzyw, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.positionWS = pos.xzy;



	return output;
}




//Pixel shader

float4 PSMain(PSInput input) : SV_TARGET
{

	float3 sunDir = normalize(float3(-directionalLights[0].lightDir.x, -directionalLights[0].lightDir.y, directionalLights[0].lightDir.z));//lightDir needs to be upside down for some reason


	float3 eyeVec = camPosition - input.positionWS;
	float3 eyeDir = normalize(eyeVec);

	float dist2d = length(eyeVec.xz);

	float blendFactor = (PATCH_BLEND_END - dist2d) / (PATCH_BLEND_END - PATCH_BLEND_BEGIN);
	blendFactor = saturate(blendFactor*blendFactor*blendFactor);

	float2 perlinTC = input.tex * perlinSize + (input.positionWS.xz % 256) - 128;
	float perlin0 = perlinTexture.SampleLevel(perlinSampler, perlinTC * perlinOctave.x + perlinMovement, 0).w;
	float perlin1 = perlinTexture.SampleLevel(perlinSampler, perlinTC * perlinOctave.y + perlinMovement, 0).w;
	float perlin2 = perlinTexture.SampleLevel(perlinSampler, perlinTC * perlinOctave.z + perlinMovement, 0).w;
	float2 perlin = (perlin0 * perlinGradient.x + perlin1 * perlinGradient.y + perlin2 * perlinGradient.z);



	float2 fftTC = (blendFactor > 0) ? input.tex: 0;
	float2 grad = normalTexture.Sample(normalSampler, fftTC).xy;
	grad = lerp(perlin, grad, blendFactor);
	float3 normal = normalize(float3(grad, texelLengthX2));


	float3 reflectVec = reflect(-eyeDir, normal);
	float cosAngle = dot(normal, eyeDir);

	float3 reflection = reflectionTexture.Sample(reflectionSampler, reflectVec).xyz;

	float reflectContrib = 0.15f;//hardcoded lerpfactor between watercolor and the sampled reflection

	float3 waterColor = lerp(baseWaterColor.rgb, reflection, reflectContrib);
	float distance = length(input.positionWS.xz - aimPos);
	if (distance < radius && aiming != 0.f)
	{
		waterColor = lerp(1, waterColor, 0.9);
	}
	
	else
	{
		float cosSpec = saturate(dot(reflectVec, sunDir));
		float sunSpot = pow(cosSpec, shininess); //shiny

		waterColor += float3(directionalLights[0].lightColor.xyz) * sunSpot;
	}


	return float4(waterColor, 1);
}
