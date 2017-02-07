
Texture2D backBufferTexture : register(t0);
SamplerState backBufferSampler : register(s0);

Texture2D depthBufferTexture : register(t1);
SamplerState depthBufferSampler : register(s1);

Texture2D displacementTexture : register(t2);
SamplerState displacementSampler : register(s2);

Texture2D normalTexture : register(t3);
SamplerState normalSampler : register(s3);

TextureCube reflectionTexture : register(t4);
SamplerState reflectionSampler : register(s4);

Texture2D foamTexture : register(t5);
SamplerState foamSampler : register(s5);


cbuffer mvp : register(b0)
{
	matrix viewMatrixInv;
	matrix projectionMatrixInv;
	float3 cameraPos;
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

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};



float fresnelTerm(float3 normal, float3 eyeVec)
{
	float R0 = 0.5f;
	float refractionStrength = 0.0f;

	float angle = 1.0f - saturate(dot(normal, eyeVec));
	float fresnel = angle * angle;
	fresnel = fresnel * fresnel;
	fresnel = fresnel * angle;
	return saturate(fresnel * (1.0f - saturate(R0)) + R0 - refractionStrength);
}


float3 GetWorldPositionFromDepth(float2 texCoord)
{
	float depth = depthBufferTexture.Sample(depthBufferSampler, texCoord).r;
	float4 clipSpace = float4(texCoord.x * 2 - 1, (1 - texCoord.y) * 2 - 1, depth, 1);
	float4 viewSpace = mul(clipSpace, projectionMatrixInv);
	viewSpace /= viewSpace.w;

	float4 worldSpace = mul(viewSpace, viewMatrixInv);
	return worldSpace.xyz;
}

float4 PSMain(VS_OUT input) : SV_Target
{
	// Level at which water surface begins
	float waterLevel = 1.0f;


// How fast will colours fade out. You can also think about this
// values as how clear water is. Therefore use smaller values (eg. 0.05f)
// to have crystal clear water and bigger to achieve "muddy" water.
	float fadeSpeed = 0.05f;

// Timer
	float timer = pad;

// Normals scaling factor
	float normalScale = 1.0f;

// R0 is a constant related to the index of refraction (IOR).
// It should be computed on the CPU and passed to the shader.

// Maximum waves amplitude
	float maxAmplitude = 1.35;

// Direction of the light
	float3 lightDir = directionalLights[0].lightDir;

// Colour of the sun
	float3 sunColor = directionalLights[0].lightColor.rgb;
		
// The smaller this value is, the more soft the transition between
// shore and water. If you want hard edges use very big value.
// Default is 1.0f.
	float shoreHardness = 0.8f;

// This value modifies current fresnel term. If you want to weaken
// reflections use bigger value. If you want to empasize them use
// value smaller then 0. Default is 0.0f.

//float refractionStrength = -0.3f;


// Describes at what depth foam starts to fade out and
// at what it is completely invisible. The fird value is at
// what height foam for waves appear (+ waterLevel).
	float3 foamExistence = { 0.65f, 1.35f, 0.9f };

	float sunScale = 3.0f;

	float shiny = 0.7f;
	float specular_intensity = 0.32;

// Colour of the water surface
	float3 depthColour = { 0.0078f, 0.5176f, 0.7f };
// Colour of the water depth
	float3 bigDepthColour = { 0.0039f, 0.00196f, 0.145f };
	float3 extinction = { 7.0f, 30.0f, 40.0f }; // Horizontal

// Water transparency along eye vector.
	float visibility = 200.0f;

	float refractionScale = 0.005f;

	float2 scale = { 0.5f, 0.5f };

	float wind = 100;

	float level = waterLevel;

	float3 color2 = backBufferTexture.Sample(backBufferSampler, input.Tex).rgb;
	float3 color = color2;
	float3 position = GetWorldPositionFromDepth(input.Tex.xy);
	float depth = 0.0f;
	float2 texCoorda = position.xz * uvScale + uvOffset;

		// If we are underwater let's leave out complex computations
	if (level >= cameraPos.y)
		return float4(color2, 1.0f);
	
	if (position.y <= level + maxAmplitude)
	{
		
		float3 eyeVec = position - cameraPos;
		float diff = level - position.y;
		float cameraDepth = cameraPos.y - position.y;
		
		// Find intersection with water surface
		float3 eyeVecNorm = normalize(eyeVec);
		float t = (level - cameraPos.y) / eyeVecNorm.y;
		float3 surfacePoint = cameraPos + eyeVecNorm * t;
		
		eyeVecNorm = normalize(eyeVecNorm);
		
		float2 texCoord;
		float3 d;
		float samSize = 10;
		for (int i = 0; i < samSize; ++i)
		{
			texCoord = ((surfacePoint.xz + eyeVecNorm.xz * 0.1) * uvScale + uvOffset);
			
			d = displacementTexture.SampleLevel(displacementSampler, texCoord, 0).rgb;
		//	return float4(d, 1);
			float bias = d.g;
	
			bias *= 1/samSize;
			level += bias * maxAmplitude;
			t = (level - cameraPos.y) / eyeVecNorm.y;
			surfacePoint = cameraPos + eyeVecNorm * t;
		//	surfacePoint += float3(d.r * 1 / samSize, 0, d.b * 1 / samSize);
		}
		
		color = d;

		depth = length(position - surfacePoint);
		float depth2 = surfacePoint.y - position.y;
		
		eyeVecNorm = normalize(cameraPos - surfacePoint);

		float3 normal = normalTexture.Sample(normalSampler, texCoord).rgb;
		normal = normalize(float3(normal.xy, texelLengthX2));

		texCoord = input.Tex;
		texCoord.x += sin(timer * 0.002f + 3.0f * abs(position.y)) * (refractionScale * min(depth2, 1.0f));
		float3 refraction = backBufferTexture.Sample(backBufferSampler, texCoord);

		
		if (GetWorldPositionFromDepth(texCoord).y > level)
			refraction = color2;
		
	//	float4x4 matTextureProj = mul(matViewProj, matReflection);
				
		float3 reflectVector = reflect(eyeVecNorm, normal);
		reflectVector.z = max(0, reflectVector.z);

		float3 waterPosition = surfacePoint.xyz;
		waterPosition.y -= (level - waterLevel);
		//float4 texCoordProj = mul(float4(waterPosition, 1.0f), matTextureProj);
		
		//float4 dPos;
		//dPos.x = texCoordProj.x + displace * normal.x;
		//dPos.z = texCoordProj.z + displace * normal.z;
		//dPos.yw = texCoordProj.yw;
		//texCoordProj = dPos;
		
		float3 reflection = reflectionTexture.Sample(reflectionSampler, reflectVector).rgb;
		
		float fresnel = fresnelTerm(normal, eyeVecNorm);
		
		float3 depthN = depth * fadeSpeed;
		float3 waterCol = saturate(length(sunColor) / sunScale);
		refraction = lerp(lerp(refraction, depthColour * waterCol, saturate(depthN / visibility)),
						  bigDepthColour * waterCol, saturate(depth2 / extinction));

		float foam = 0.0f;

		texCoord = (surfacePoint.xz + eyeVecNorm.xz * 0.1) * 0.05 + timer * 0.0001f + sin(timer * 0.001 + position.x) * 0.005;
		float2 texCoord2 = (surfacePoint.xz + eyeVecNorm.xz * 0.1) * 0.05 + timer * 0.001f + sin(timer * 0.001 + position.z) * 0.005;
		
		float3 f1 = foamTexture.Sample(foamSampler, texCoord).rgb;
		float3 f2 = foamTexture.Sample(foamSampler, texCoord2).rgb;

		if (depth2 < foamExistence.x)
			foam = (f1 + f2) * 0.5f;
		else if (depth2 < foamExistence.y)
		{
			foam = lerp((f1 + f2) * 0.5f, 0.0f,
						 (depth2 - foamExistence.x) / (foamExistence.y - foamExistence.x));
			
		}
		
		if (maxAmplitude - foamExistence.z > 0.0001f)
		{
			foam += (f1 + f2) * 0.5f *
				saturate((level - (waterLevel + foamExistence.z)) / (maxAmplitude - foamExistence.z));
		}

		
		float3 specular = 0.0f;

		float cosSpec = clamp(dot(reflectVector, lightDir), 0, 1);
		float sunSpot = pow(cosSpec, shininess); //shiny

		specular = sunColor * sunSpot;
		
		color = lerp(refraction, reflection, fresnel);
		color = saturate(color + max(specular, foam * sunColor));
		
		color = lerp(refraction, color, saturate(depth * shoreHardness));
	}
	
	if (position.y > level)
		color = color2;
	return float4(color, 1);
}