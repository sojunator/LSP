
struct VSInput
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
	float3 normal: NORMAL;
};


cbuffer test
{
	matrix worldMatrix;
};

struct VSOutput
{
	float4 position : SV_POSITION;
};


VSOutput VSMain(in VSInput input)
{
	VSOutput output;
    output.position = float4(input.position, 1);
	return output;
}


float4 PSMain(VSOutput input) : SV_TARGET
{
	return float4(0,1,0,1);
}