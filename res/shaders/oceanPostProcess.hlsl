
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


float3 GetWorldPositionFromDepth(float2 texCoord)
{
	float depth = depthBufferTexture.Load(float3(texCoord, 0)).r;
	float4 clipSpace;
	clipSpace.x = texCoord.x * 2.0 - 1.0;
	clipSpace.y = -texCoord.y * 2.0 - 1.0;
	clipSpace.z = depth * 2.0 - 1.0;
	clipSpace.w = 1.0;
	float4 viewSpace = mul(clipSpace, projectionMatrixInv);
	viewSpace /= viewSpace.w;

	float4 worldSpace = mul(viewSpace, viewMatrixInv);
	return worldSpace.xyz;
}

float4 PSMain(VS_OUT input) : SV_Target
{

	float waterLevel = 0.0;
	float waveAmplitude = 3.0;

	float3 color2 = backBufferTexture.Load(float3(input.Tex.xy, 0)).rgb;
	float3 color = color2;
	float3 position = GetWorldPositionFromDepth(input.Tex.xy);
	


	if(waterLevel >= camPosition.y)
		return float4(color2*float3(0,0,0.2), 1);
	

	if (position.y <= waterLevel+waveAmplitude)
	{
		float3 eyeVec = position - camPosition;
		float diff = waterLevel - position.y;
		float cameraDepth = camPosition.y - position.y;

		float3 eyeVecNorm = normalize(eyeVec);
		float t = (waterLevel - camPosition.y) / eyeVecNorm.y;
		float3 surfacePoint = camPosition + eyeVecNorm * t;
			

		float2 texCoord = (surfacePoint.xz * uvScale + uvOffset);

		//float2 texCoord;
		//for (int i = 0; i < 10; ++i)
		//{
		//	texCoord = (surfacePoint.xz + eyeVecNorm.xz * 0.1f);
			
		//	float bias = displacementTexture.Sample(displacementSampler, texCoord).rgb;
	
		//	bias *= 0.1f;
		//	waterLevel += bias * 1.0;
		//	t = (waterLevel - camPosition.y) / eyeVecNorm.y;
		//	surfacePoint = camPosition + eyeVecNorm * t;
		//}


		surfacePoint = displacementTexture.Sample(displacementSampler, texCoord).rgb;

		color = surfacePoint;

		//float depth = length(position - surfacePoint);
		//float depth2 = surfacePoint.y - position.y;
		//eyeVecNorm = normalize(camPosition - surfacePoint);

		//float3 normal = normalTexture.Sample(normalSampler, texCoord).rgb;
		
		//color = float3(1,0,0);
		//if(surfacePoint.y > waterLevel+waveAmplitude)
		//	color = color2;

		
	}

	if(position.y > waterLevel)
		color = color2;

	return float4(color, 1);
}