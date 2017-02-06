
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



float4 PSMain(VS_OUT input) : SV_Target
{

	float waterLevel = 0.0;
	float waveAmplitude = 1.0;

	float3 color = backBufferTexture.Sample(backBufferSampler, input.Tex).rgb;
	
	float depth = depthBufferTexture.Sample(depthBufferSampler, input.Tex).r;

	float near = 0.1;
	float far = 1000.0;

	depth = depth * 2.0 - 1.0;

	depth = 2.0 * near * far / (far + near - depth * (far - near));
	depth /= far;


	color = lerp(color, float3(0.5, 0.5, 0.5), depth);

	return float4(color, 1);
}