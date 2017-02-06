
Texture2D backBufferTexture : register(t0);
SamplerState backBufferSampler : register(s0);

Texture2D depthBufferTexture : register(t1);
SamplerState depthBufferSampler : register(s1);

Texture2D displacementTexture : register(t2);
SamplerState displacementSampler : register(s2);

Texture2D normalTexture : register(t3);
SamplerState normalSampler : register(s3);

cbuffer mvp : register(b0)
{
	matrix viewMatrixInv;
	matrix projectionMatrixInv;
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
	float pad;
	float3 perlinOctave;
	float pad2;
	float3 perlinGradient;
	float pad3;
	float2 perlinMovement;
	float2 pad4;
}

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};




// Level at which water surface begins
float waterLevel = 0.0f;


// How fast will colours fade out. You can also think about this
// values as how clear water is. Therefore use smaller values (eg. 0.05f)
// to have crystal clear water and bigger to achieve "muddy" water.
float fadeSpeed = 0.15f;

// Timer
float timer;

// Normals scaling factor
float normalScale = 1.0f;

// R0 is a constant related to the index of refraction (IOR).
// It should be computed on the CPU and passed to the shader.
float R0 = 0.5f;

// Maximum waves amplitude
float maxAmplitude = 1.0f;

// Direction of the light
float3 lightDir = { 0.0f, 1.0f, 0.0f };

// Colour of the sun
float3 sunColor = { 1.0f, 1.0f, 1.0f };

// The smaller this value is, the more soft the transition between
// shore and water. If you want hard edges use very big value.
// Default is 1.0f.
float shoreHardness = 1.0f;

// This value modifies current fresnel term. If you want to weaken
// reflections use bigger value. If you want to empasize them use
// value smaller then 0. Default is 0.0f.
float refractionStrength = 0.0f;
//float refractionStrength = -0.3f;


// Describes at what depth foam starts to fade out and
// at what it is completely invisible. The fird value is at
// what height foam for waves appear (+ waterLevel).
float3 foamExistence = { 0.65f, 1.35f, 0.5f };

float sunScale = 3.0f;

float shiny = 0.7f;
float specular_intensity = 0.32;

// Colour of the water surface
float3 depthColour = { 0.0078f, 0.5176f, 0.7f };
// Colour of the water depth
float3 bigDepthColour = { 0.0039f, 0.00196f, 0.145f };
float3 extinction = { 7.0f, 30.0f, 40.0f }; // Horizontal

// Water transparency along eye vector.
float visibility = 4.0f;

float refractionScale = 0.005f;


float fresnelTerm(float3 normal, float3 eyeVec)
{
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

	float level = waterLevel;

	float3 color2 = backBufferTexture.Sample(backBufferSampler, input.Tex).rgb;
	float3 color = color2;
	float3 position = GetWorldPositionFromDepth(input.Tex.xy);
	float depth = 0.0f;

	if (level >= camPosition.y)
		return float4(color2, 1);

	if (position.y <= level + maxAmplitude)
	{
		float3 eyeVec = position - camPosition;
		float diff = waterLevel - position.y;
		float cameraDepth = camPosition.y - position.y;

		float3 eyeVecNorm = normalize(eyeVec);
		float t = (waterLevel - camPosition.y) / eyeVecNorm.y;
		float3 surfacePoint = camPosition + eyeVecNorm * t;
		
		
		

		float2 texCoord = (surfacePoint.xz) * uvScale + uvOffset;

		surfacePoint += displacementTexture.Sample(displacementSampler, texCoord).rgb;
		level = surfacePoint.y;

		//for (int i = 0; i < 10; ++i)
		//{
		//	texCoord = (surfacePoint.xz + eyeVecNorm.xz * 0.1f)  * uvScale + uvOffset;
			
		//	float bias = displacementTexture.Load(float3(texCoord, 0)).g;
	
		//	bias *= 0.1f;
		//	level += bias * waveAmplitude;
		//	t = (level - camPosition.y) / eyeVecNorm.y;
		//	surfacePoint = camPosition + eyeVecNorm * t;
		//}

		float depth = length(position - surfacePoint);
		float depth2 = surfacePoint.y - position.y;
		eyeVecNorm = normalize(camPosition - surfacePoint);

		float2 grad = normalTexture.Sample(normalSampler, texCoord);
		
		float3 normal = normalize(float3(grad, texelLengthX2));

		texCoord = input.Tex;

		float3 reflect = float3(0.3, 0.2, 0.5);

		texCoord.x += (sin(3 * abs(position.y)) * 0.005 * min(depth2, 1.0));
		float3 refraction = backBufferTexture.Sample(backBufferSampler, texCoord).rgb;
		if(GetWorldPositionFromDepth(texCoord).y > level)
			refraction = color2;

		float fresnel = fresnelTerm(normal, eyeVecNorm);
		float depthN = depth * fadeSpeed;
		float3 waterCol = saturate(length(sunColor) / sunScale);

		refraction = lerp(lerp(refraction, depthColour * waterCol, saturate(depthN / visibility)),
						  bigDepthColour * waterCol, saturate(depth2 / extinction));


		color = lerp(refraction, reflect, fresnel);

		color = lerp(refraction, color, saturate(depth * shoreHardness));


	}

	if(position.y > waterLevel)
		color = color2;

	return float4(color, 1);
}