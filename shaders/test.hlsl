
struct VSInput
{
	float4 position : POSITION;
	float2 uv : TEXCOORD;
};

struct VSOutput
{
	float4 positionCS : SV_POSITION;
	float4 position : POSITION;
	float2 uv : TEXCOORD;
};

cbuffer TEST : register(b0)
{
	float test1;
	float test2;
	float test3;
	float test4;
};

float4 VSMain(in VSInput input): SV_POSITION
{
	return float4(test1, test2, test3, test4);
}


float4 PSMain(in VSInput input) : SV_TARGET
{
	return float4(1,1,1,1);
}