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

struct ParticleStruct
{
	float3 position;
	float speed;
	float3 direction;
	float angle;
};

struct BillboardStruct
{
	float3 quad[2][3];
	float pad;
	float2 uvs[2][3];
	float pad2;
	float pad3;
};

StructuredBuffer<ParticleStruct> particlesRead : register(t0);
RWStructuredBuffer<ParticleStruct> particlesWrite : register(u0);
RWStructuredBuffer<BillboardStruct> billboards : register(u1);





[numthreads(1, 1, 1)]
void main( uint3 Gid : SV_GroupID )
{
	uint seed = Gid.x;
	seed = (seed ^ 61) ^ (seed >> 16);
	seed *= 9;
	seed = seed ^ (seed >> 4);
	seed *= 668265261;
	seed = seed ^ (seed >> 15);
	seed = seed * 2 - 1;
	float3 dir = float3(seed,seed,seed);//float3(seed, seed, seed);
	normalize(dir);
	//ANIMATE
	float3 particlePosWS = particlesRead[Gid.x].position + dir * 0.1;
	particlesWrite[Gid.x].position = particlePosWS;
	particlesWrite[Gid.x].direction = dir;
	particlesWrite[Gid.x].angle = particlesRead[Gid.x].angle + 0.5f;
	particlesWrite[Gid.x].speed = particlesRead[Gid.x].speed;

	//BILLBOARD
	float3 right = cameraRight * 1;
	float3 up = cameraUp * 1;

	//tri 1
	billboards[Gid.x].quad[0][0] = particlePosWS + up + right;
	billboards[Gid.x].quad[0][1] = particlePosWS + up - right;
	billboards[Gid.x].quad[0][2] = particlePosWS - up + right;
	billboards[Gid.x].uvs[0][0] = float2(1, 1);
	billboards[Gid.x].uvs[0][1] = float2(1, 0);
	billboards[Gid.x].uvs[0][2] = float2(0, 1);
	//tri 2
	billboards[Gid.x].quad[1][0] = particlePosWS - up + right;
	billboards[Gid.x].quad[1][1] = particlePosWS + up - right;
	billboards[Gid.x].quad[1][2] = particlePosWS - up - right;

	billboards[Gid.x].uvs[1][0] = float2(0, 1);
	billboards[Gid.x].uvs[1][1] = float2(1, 0);
	billboards[Gid.x].uvs[1][2] = float2(0, 0);

}
