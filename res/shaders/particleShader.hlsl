cbuffer matrixBuffer : register(b0)
{
	matrix viewProjMatrix;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

struct quadStruct
{
	float3 quad[2][3];
};

StructuredBuffer<quadStruct> particle : register(t0);

VS_OUT  VSMain(uint id : SV_VERTEXID)
{
	VS_OUT output = (VS_OUT) 0;
	output.color = float4(1,0,0,1);

	uint particleIndex = (uint)(id/6);
	uint triangleIndex = (uint)((id % 6)/3);
	uint vertexIndex = id % 3;

	output.pos = mul(float4(particle[particleIndex].quad[triangleIndex][vertexIndex], 1.0), viewProjMatrix);

	return output;
}


float4 PSMain(VS_OUT input) : SV_Target
{

	return input.color;

}
