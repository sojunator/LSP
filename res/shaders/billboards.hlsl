cbuffer cameraBuffer : register(b0)
{
    float3 cameraUp;
	float deltaTime;
	float3 cameraRight;
	float pad;
};

cbuffer emitterPos : register(b1)
{
    float3 emitterposition;
    float pad2;
}

struct ParticleStruct
{
    float3 position;
    float spread;

    float3 direction;
    float speed;

    float endSpeed;
    float delay;
    float size;
    float endSize;

    float lifeTimeLeft;
    float timeElapsed;
    float rotationSpeed;
    bool looping;

    float4 startColor;

    float4 endColor;

    float3 initPosition;
    float paddd;
};

struct BillboardStruct
{
	float3 quad[2][3];
    float2 pad2;
	float2 uvs[2][3];
    float4 colorFactor;
};

StructuredBuffer<ParticleStruct> particlesRead : register(t0);
RWStructuredBuffer<ParticleStruct> particlesWrite : register(u0);
RWStructuredBuffer<BillboardStruct> billboards : register(u1);


[numthreads(256, 1, 1)]
void CSMain(uint3 Gid : SV_GroupID, uint3 GTid : SV_GroupThreadID)
{
	float index = (Gid.x * 256) + GTid.x;

    
    if (particlesRead[index].delay < 0.0f)
    {
        //ANIMATE
        float3 particlePosWS = particlesRead[index].position + particlesRead[index].direction * particlesRead[index].speed * deltaTime;
        particlesWrite[index].position = particlePosWS;
        
        particlesWrite[index].delay = particlesRead[index].delay;
        particlesWrite[index].speed = particlesRead[index].speed;
        
        particlesWrite[index].size = particlesRead[index].size;
        
        particlesWrite[index].lifeTimeLeft = particlesRead[index].lifeTimeLeft;
        particlesWrite[index].timeElapsed = particlesRead[index].timeElapsed;
        
        float scale = particlesRead[index].size;

        if (particlesRead[index].lifeTimeLeft < 0.0f)
        {
            if (particlesRead[index].looping)
            {
                particlesWrite[index].position = particlesRead[index].initPosition;
                particlesWrite[index].lifeTimeLeft = particlesRead[index].timeElapsed;
                particlesWrite[index].timeElapsed = 0.0f;
            }
            else
            {
                scale = particlesRead[index].endSize;
            }
        }
        else
        {
            particlesWrite[index].lifeTimeLeft = particlesRead[index].lifeTimeLeft - deltaTime;
            particlesWrite[index].timeElapsed = particlesRead[index].timeElapsed + deltaTime;
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

        float a = particlesRead[index].lifeTimeLeft + particlesRead[index].timeElapsed;
        float b = particlesRead[index].lifeTimeLeft / a;
        float c = 1 - b;
        billboards[index].colorFactor = particlesRead[index].startColor * b + particlesRead[index].endColor * c;
        particlesWrite[index].size = particlesRead[index].size * b + particlesRead[index].endSize * c;
    }
    else
    {
        particlesWrite[index].position = emitterposition;
        particlesWrite[index].delay = particlesRead[index].delay - deltaTime;
    }
}
