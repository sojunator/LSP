cbuffer cameraBuffer : register(b0)
{
	float3 cameraForward;
	float pad;
	float3 cameraUp;
	float pad2;
	float3 cameraRight;
	float pad3;
	float3 cameraPosition;
	float pad4;
};

struct quadStruct
{
	float3 quad[2][3];
};

RWStructuredBuffer<quadStruct> particle : register(u0);

[numthreads(1, 1, 1)]
void main( uint3 Gid : SV_GroupID )
{
	float3 right = cameraRight;
	float3 up = cameraUp;

	float3 particlePosWS = float3(10 * Gid.x,5,1);

	uint c = Gid.x;
	//tri 1
	particle[c].quad[0][0] = particlePosWS + up + right;
	particle[c].quad[0][1] = particlePosWS + up - right;
	particle[c].quad[0][2] = particlePosWS - up + right;
	//tri 2
	particle[c].quad[1][0] = particlePosWS - up + right;
	particle[c].quad[1][1] = particlePosWS + up - right;
	particle[c].quad[1][2] = particlePosWS - up - right;




}
