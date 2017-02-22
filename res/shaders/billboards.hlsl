cbuffer cameraBuffer : register(b0)
{
	float3 cameraForward;
	float deltaTime;
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
	float spread;
	float3 direction;
	float speed;
	float delay;
	float size;
    float lifeTimeLeft;
    float pad;
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





[numthreads(256, 1, 1)]
void main(uint3 Gid : SV_GroupID, uint3 GTid : SV_GroupThreadID)
{
	float index = (Gid.x * 256) + GTid.x;

    //ANIMATE
    if (particlesRead[index].delay < 0.0f)
    {
        float3 particlePosWS = particlesRead[index].position + particlesRead[index].direction * particlesRead[index].speed * deltaTime;
        particlesWrite[index].position = particlePosWS;
        particlesWrite[index].direction = particlesRead[index].direction;
        particlesWrite[index].delay = particlesRead[index].delay;
        particlesWrite[index].speed = particlesRead[index].speed;
        particlesWrite[index].spread = particlesRead[index].spread;
        particlesWrite[index].size = particlesRead[index].size;
        particlesWrite[index].lifeTimeLeft = particlesRead[index].lifeTimeLeft;

        float scale = particlesRead[index].size;
        if (particlesRead[index].lifeTimeLeft < 0.0f)
        {
            scale = 0.0f;
        }
        else
        {
            particlesWrite[index].lifeTimeLeft = particlesRead[index].lifeTimeLeft - deltaTime;
        }
        //BILLBOARD
        float3 right = cameraRight * scale;
        float3 up = cameraUp * scale;	

         //tri 1
        billboards[index].quad[0][0] = particlePosWS + up + right;
        billboards[index].quad[0][1] = particlePosWS + up - right;
        billboards[index].quad[0][2] = particlePosWS - up + right;
        billboards[index].uvs[0][0] = float2(0, 0);
        billboards[index].uvs[0][1] = float2(1, 0);
        billboards[index].uvs[0][2] = float2(0, 1);
        //tri 2
        billboards[index].quad[1][0] = particlePosWS - up + right;
        billboards[index].quad[1][1] = particlePosWS + up - right;
        billboards[index].quad[1][2] = particlePosWS - up - right;

        billboards[index].uvs[1][0] = float2(0, 1);
        billboards[index].uvs[1][1] = float2(1, 0);
        billboards[index].uvs[1][2] = float2(1, 1);
    }
    else
    {
        particlesWrite[index].delay = particlesRead[index].delay - deltaTime;
    }
}
