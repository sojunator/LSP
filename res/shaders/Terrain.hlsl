
Texture2D diffuseTexture : register(t0);
SamplerState diffuseSampler : register(s0);

Texture2D specularTexture : register(t1);
SamplerState specularSampler : register(s1);

Texture2D normalTexture : register(t2);
SamplerState normalSampler : register(s2);



struct VSInput
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
	float3 normal: NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
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
    float4 ambientColor;
	float4 diffuseColor;
	float4 specularColor;
	float specularPower;
}

struct VSOutput
{
	float4 position : SV_POSITION;
	float3 positionWS : POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
    float WorldY : WORLDY;
};

float4 TerrainColour(float y)
{
    if (y < 0.5f * 2)
        return float4(0, 1.0f - y * 0.2, 1.0f, 1.0);
    else if (y < 1.1 * 2)
        return float4(0.749f, 0.749f, 0.749f - y * 0.2, 1.0f);
    else
        return float4(0.24f - y * 0.02, 0.74f - y * 0.02, 0.49f - y * 0.02, 1.0f);
}


VSOutput VSMain(in VSInput input)
{
	VSOutput output;

    output.position = mul(float4(input.position, 1), mvpMatrix);

	output.positionWS = mul(input.position, (float3x3)worldMatrix);

    output.tex = input.uv;

	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);
    output.WorldY = input.position.y;

	return output;
}



float4 PSMain(VSOutput input) : SV_TARGET
{
    return TerrainColour(input.WorldY);
}