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
};

StructuredBuffer<ParticleStruct> particlesRead : register(t0);
RWStructuredBuffer<ParticleStruct> particlesWrite : register(u0);
RWStructuredBuffer<BillboardStruct> billboards : register(u1);


[numthreads(1, 1, 1)]
void main( uint3 Gid : SV_GroupID )
{
	//ANIMATE
	float3 particlePosWS = particlesRead[Gid.x].position + float3(0.01, 0, 0);
	particlesWrite[Gid.x].position = particlePosWS;
	particlesWrite[Gid.x].direction = particlesRead[Gid.x].direction;
	particlesWrite[Gid.x].angle = particlesRead[Gid.x].angle + 0.5f;
	particlesWrite[Gid.x].speed = particlesRead[Gid.x].speed;

	//BILLBOARD
	float3 right = cameraRight;
	float3 up = cameraUp;

	//tri 1
	billboards[Gid.x].quad[0][0] = particlePosWS + up + right;
	billboards[Gid.x].quad[0][1] = particlePosWS + up - right;
	billboards[Gid.x].quad[0][2] = particlePosWS - up + right;
	//tri 2
	billboards[Gid.x].quad[1][0] = particlePosWS - up + right;
	billboards[Gid.x].quad[1][1] = particlePosWS + up - right;
	billboards[Gid.x].quad[1][2] = particlePosWS - up - right;

}
