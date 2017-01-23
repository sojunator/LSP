
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


VSOutput VSMain(in VSInput input)
{
	VSOutput output;
	float4 pos = input.position;
	pos.z = 1.0f;
	output.positionCS = pos;
	output.position = mul(pos, invViewProjMatrix);
	output.uv = input.uv;
	return output;
}

