
cbuffer camera : register(b0)
{
	matrix viewProjection;
};

struct VS_IN
{
	float3 Pos : POSITION;
	float3 Color : COLOR0;
};

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Color : COLOR0;
};


VS_OUT VSMain(VS_IN input)
{
	VS_OUT output = (VS_OUT) 0;
	
	output.Pos = mul(float4(input.Pos,1), viewProjection);
	output.Color = input.Color;

	return output;
}

float4 PSMain(VS_OUT input) : SV_Target
{
	return float4(input.Color,1);
}