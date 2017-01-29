
Texture2D diffuseTexture : register(t0);
SamplerState diffuseSampler : register(s0);

Texture2D specularTexture : register(t0);
SamplerState specularSampler : register(s0);

Texture2D normalTexture : register(t0);
SamplerState normalSampler : register(s0);



struct VSInput
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
	float3 normal: NORMAL;
};


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
    float4 ambient;
}

struct VSOutput
{
	float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};


VSOutput VSMain(in VSInput input)
{
	VSOutput output;
    output.position = mul(float4(input.position, 1), mvpMatrix);
    output.tex = input.uv;
	return output;
}


float4 PSMain(VSOutput input) : SV_TARGET
{
    float4 textureColor = testTexture.Sample(SampleType, input.tex);
	return ambient*textureColor;
}