
Texture2D backBufferTexture : register(t1);
SamplerState backBufferSamplerState : register(s1);

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

float4 PSMain(VS_OUT input): SV_Target
{
	return float4(1, 0, 0, 1);
}