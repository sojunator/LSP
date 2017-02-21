//Globals

Texture2D perlinTexture : register(t0);
SamplerState perlinSampler : register(s0);

Texture2D foamTexture : register(t1);
SamplerState foamSampler : register(s1);

Texture2D normalTexture : register(t2);
SamplerState normalSampler : register(s2);

Texture2D displacementTexture : register(t3);
SamplerState displacementSampler : register(s3);

TextureCube reflectionTexture : register(t4);
SamplerState reflectionSampler : register(s4);

Texture2D depthBufferTexture : register(t5);
SamplerState depthBufferSampler : register(s5);

#define PATCH_BLEND_BEGIN		500
#define PATCH_BLEND_END			6000000

cbuffer mvp : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix mvpMatrix;
	float3 camPosition;
	float buff;
	float3 camDirection;
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
	float pad;
	float3 perlinOctave;
	float pad2;
	float3 perlinGradient;
	float pad3;
	float2 perlinMovement;
	float2 pad4;
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
	float4 clip : POSITION0;
	float3 positionWS : POSITION1;
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
	float maxTessDistance = 1000;

	float tess = saturate((minTessDistance - d) / (minTessDistance - maxTessDistance));

	

	float minTessFactor = 32.0f;
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
	if (blendFactor < 1)
	{
		
		float2 perlinTC = output.tex * perlinSize + (pos.xy % 256) - 128;
		float perlin0 = perlinTexture.SampleLevel(perlinSampler, perlinTC * perlinOctave.x + perlinMovement, 0).w;
		float perlin1 = perlinTexture.SampleLevel(perlinSampler, perlinTC * perlinOctave.y + perlinMovement, 0).w;
		float perlin2 = perlinTexture.SampleLevel(perlinSampler, perlinTC * perlinOctave.z + perlinMovement, 0).w;
		perlin = perlin0 * perlinAmp.x + perlin1 * perlinAmp.y + perlin2 * perlinAmp.z;
		
	}

	float3 displacement = 0;
	if (blendFactor > 0)
	{
		displacement = displacementTexture.SampleLevel(displacementSampler, output.tex, 0).xyz;
	}
	displacement = lerp(float3(0, 0, perlin), displacement, blendFactor);


	pos.xyz += displacement.xyz;

	output.position = mul(pos.xzyw, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.positionWS = pos.xzy;

	output.clip = output.position;
	

	return output;
}


float fresnelTerm(float3 normal, float3 eyeVec)
{
	float angle = 1.0f - saturate(dot(normal, eyeVec));
	float fresnel = angle * angle;
	fresnel = fresnel * fresnel;
	fresnel = fresnel * angle;
	return saturate(fresnel * (1.0f - saturate(0.5)) + 0.5 - 0.5);
}

//Pixel shader

float4 PSMain(PSInput input) : SV_TARGET
{

	float2 ndc;
	ndc.x = (input.clip.x / input.clip.w) / 2.0 + 0.5;
	ndc.y = 1 - (input.clip.y / input.clip.w) / 2.0 + 0.5;


	float depth = depthBufferTexture.Sample(depthBufferSampler, ndc).r;
	float near = 0.1;
	float far = 3000.0;
	float floorDistance = (2 * near) / (far + near - depth * far - near);

	depth = input.position.z;

	float waterDistance = (2 * near) / (far + near - depth * far - near);

	float waterDepth = floorDistance - waterDistance;


	float3 sunDir = normalize(float3(-directionalLights[0].lightDir.x, -directionalLights[0].lightDir.y, directionalLights[0].lightDir.z)); //lightDir needs to be upside down for some reason


	float3 eyeVec = camPosition - input.positionWS;
	float3 eyeDir = normalize(eyeVec);

	float dist2d = length(eyeVec.xz);

	float blendFactor = (PATCH_BLEND_END - dist2d) / (PATCH_BLEND_END - PATCH_BLEND_BEGIN);
	blendFactor = saturate(blendFactor * blendFactor * blendFactor);


	float2 perlinTC = input.tex * perlinSize + (input.positionWS.xz) ;
	float perlin0 = perlinTexture.SampleLevel(perlinSampler, perlinTC * perlinOctave.x + perlinMovement, 0).w;
	float perlin1 = perlinTexture.SampleLevel(perlinSampler, perlinTC * perlinOctave.y + perlinMovement, 0).w;
	float perlin2 = perlinTexture.SampleLevel(perlinSampler, perlinTC * perlinOctave.z + perlinMovement, 0).w;
	float2 perlin = (perlin0 * perlinGradient.x + perlin1 * perlinGradient.y + perlin2 * perlinGradient.z);



	float2 fftTC = (blendFactor > 0) ? input.tex : 0;
	float2 grad = normalTexture.Sample(normalSampler, fftTC).xy;
	grad = lerp(perlin, grad, blendFactor);
	float3 normal = normalize(float3(grad, texelLengthX2));


	//return float4(normal, 1);
	//shading

	float3 shoreHardness = 1.0;
	float3 foamExistence = { 4.65f, 9.35f, 0.5f };
	// Colour of the water surface
	float3 depthColour = { 0.0078f, 0.5176f, 0.7f };
// Colour of the water depth
	float3 bigDepthColour = { 0.0039f, 0.00196f, 0.145f };
	float3 extinction = { 7.0f, 30.0f, 40.0f }; // Horizontal

	// How fast will colours fade out. You can also think about this
// values as how clear water is. Therefore use smaller values (eg. 0.05f)
// to have crystal clear water and bigger to achieve "muddy" water.
	float fadeSpeed = 0.15f;

	// Water transparency along eye vector.
	float visibility = 4.0f;

	float3 sunColor = directionalLights[0].lightColor.xyz;
	float sunScale = 3.0f;
	float3 reflectVec = reflect(-eyeDir, normal);

	float3 reflection = reflectionTexture.Sample(reflectionSampler, reflectVec).xyz;


	float fresnel = fresnelTerm(normal, camDirection * eyeDir);
	float2 tx = input.positionWS.xz / 100.0;
	tx += normal.xy * 0.1 + perlinMovement.xy / 5;


	float3 waterCol = saturate(length(sunColor) / sunScale);
	float depthN = waterDepth * fadeSpeed;
	
	float3 baseColor = lerp(depthColour * waterCol, bigDepthColour * waterCol, saturate(waterDepth / extinction));


	half3 specular = 0.0f;
	float3 lightDir = directionalLights[0].lightDir;
	half3 mirrorEye = (2.0f * dot(eyeDir, normal) * normal - eyeDir);
	half dotSpec = saturate(dot(mirrorEye.xyz, -lightDir) * 0.5f + 0.5f);
	specular = (1.0f - fresnel) * saturate(-lightDir.y) * ((pow(dotSpec, 512.0f)) * (shininess * 1.8f + 0.2f)) * sunColor;
	specular += specular * 25 * saturate(shininess - 0.05f) * sunColor;

	
	
	
	float3 foam = 0.0f;

	float2 texCoord = (input.positionWS.xz + eyeDir.xz * 0.1+perlinMovement) * 0.05;
	float3 foamColor = foamTexture.Sample(foamSampler, texCoord);
	
	float foamshit = clamp(waterDepth / 0.0005, 0, 1);

	foam = lerp(foamColor, 0.0f, foamshit);

	foam += (foamColor * 1.5f *
			saturate((input.positionWS.y - foamExistence.x)) / (foamExistence.y - foamExistence.z));
	


	float3 waterColor = lerp(baseColor, reflection, fresnel);

	waterColor = saturate(waterColor + max(specular, foam * sunColor));

	waterColor = lerp(waterColor, baseColor, saturate(depthN * shoreHardness));

	foamshit = clamp(waterDepth / 0.00005, 0, 1);



	waterColor = lerp(1.0, waterColor, foamshit);


	foamshit = saturate(1.0 - foamshit);

	float opacity = clamp(waterDepth / 0.01, 0.3, 1);
	return float4(waterColor, opacity + foamshit);
}