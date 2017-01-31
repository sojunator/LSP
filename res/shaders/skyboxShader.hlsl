
SamplerState ObjSamplerState : register(s4);
TextureCube SkyMap : register (t4);

struct VSInput
{
	float3 position : POSITION;
};

cbuffer mvp : register(b0)
{
	matrix mvpMatrix;
	matrix viewMatrix;
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
	output.texCoord = mul(input.position,(float3x3)viewMatrix);

	return output;
}

float4 PSMain(VSOutput input) : SV_TARGET
{
	return SkyMap.Sample(ObjSamplerState, input.texCoord);
}