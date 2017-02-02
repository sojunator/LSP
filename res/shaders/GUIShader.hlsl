
SamplerState ObjSamplerState : register(s0);
Texture2D myTexture : register (t0);

struct VSInput
{
	float3 position : POSITION;
	float2 texCoord : TEXCOORD;
};

cbuffer mvp : register(b0)
{
	matrix orthMatrix;
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

VSOutput VSMain(in VSInput input)
{
	VSOutput output;

	output.position = mul(float4(input.position, 1), orthMatrix);
	output.texCoord = input.texCoord;

	return output;
}

float4 PSMain(VSOutput input) : SV_TARGET
{
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);
	return myTexture.Sample(ObjSamplerState, input.texCoord);
}