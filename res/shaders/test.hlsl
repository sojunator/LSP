
struct VSInput
{
	float4 position : POSITION;
	float2 uv : TEXCOORD;
	float3 normal: NORMAL;
};

struct VSOutput
{
	float4 position : SV_POSITION;
};


VSOutput VSMain(in VSInput input)
{
	VSOutput output;
	output.position = input.position;
	return output;
}


float4 PSMain(VSOutput input) : SV_TARGET
{
	return float4(1,0,1,1);
}