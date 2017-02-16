/*cbuffer cameraBuffer : register(b1)
{
	float3 cameraForward;
	float3 cameraUp;
	float3 cameraRight;
	float3 cameraPosition;
};
*/
cbuffer matrixBuffer : register(b0)
{
	matrix viewProjMatrix;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
};

struct quadStruct
{
	float3 quad[2][3];
};

StructuredBuffer<quadStruct> particle : register(t0);

VS_OUT  VSMain(uint id : SV_VERTEXID)
{
	VS_OUT output = (VS_OUT) 0;

	uint particleIndex = (uint)id/6.0f;
	uint triangleIndex = (uint)id/3.0f;
	uint vertexIndex = id % 3;

	output.pos = mul(float4(particle[particleIndex].quad[triangleIndex][vertexIndex], 1.0), viewProjMatrix);

return output;
}


float4 PSMain(VS_OUT input) : SV_Target
{

	return float4(1,0,0,1);

}
