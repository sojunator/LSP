
SamplerState ObjSamplerState : register(s0);
TextureCube SkyMap : register (t0);

struct VSInput
{
	float3 position : POSITION;
};

cbuffer mvp : register(b0)
{
	matrix mvpMatrix;
};

struct VSOutput
{
	float4 position : SV_POSITION;
	float3 texCoord : TEXCOORD;
};

VSOutput VSMain(in VSInput input)
{
	VSOutput output;

    output.position = mul(float4(input.position, 1), mvpMatrix).xyww;
	output.texCoord = input.position;

	return output;
}

float4 PSMain(VSOutput input) : SV_TARGET
{
	return SkyMap.Sample(ObjSamplerState, input.texCoord);
}