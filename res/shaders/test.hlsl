
struct VSInput
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
	float3 normal: NORMAL;
};


cbuffer mvp
{
	matrix mvpMatrix;
};

struct VSOutput
{
	float4 position : SV_POSITION;
};


VSOutput VSMain(in VSInput input)
{
	VSOutput output;
    output.position = mul(float4(input.position, 1), mvpMatrix);
	return output;
}


float4 PSMain(VSOutput input) : SV_TARGET
{
	return float4(0,1,0,1);
}