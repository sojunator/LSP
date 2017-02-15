
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

/*	uint particleIndex = (uint)id/6.0f;
	uint triangleIndex = (uint)id/3.0f;
	uint vertexIndex = id % 3;

	output.pos = float4(particle[particleIndex].quad[triangleIndex][vertexIndex], 1.0);*/

	if (id == 0)
				output.pos = float4(particle[0].quad[0][0], 1.0);
		else if (id == 1)
				output.pos = float4(particle[0].quad[0][1], 1.0);
		else if (id == 2)
				output.pos = float4(particle[0].quad[0][2], 1.0);
		else if (id == 3)
				output.pos = float4(particle[0].quad[1][0], 1.0);
		else if (id == 4)
				output.pos = float4(particle[0].quad[1][1], 1.0);
		else if (id == 5)
				output.pos = float4(particle[0].quad[1][2], 1.0);


return output;
}


float4 PSMain(VS_OUT input) : SV_Target
{

	return float4(1,0,0,1);

}
