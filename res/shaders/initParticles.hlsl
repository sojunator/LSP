cbuffer InitBuffer : register(b0)
{
    float3 initPosition;
    float initSpread;
    float3 initDirection;
    float initMaxSpeed;
    float initMinSpeed;
    float initMaxDelay;
    float initMinDelay;
    float initSize;
};

struct ParticleStruct
{
    float3 position;
    float spread;
    float3 direction;
    float speed;
    float delay;
	float size;
    float2 padding;
};

RWStructuredBuffer<ParticleStruct> particlesWrite : register(u0);

[numthreads(256, 1, 1)]
void main( uint3 Gid : SV_GroupID, uint3 GTid : SV_GroupThreadID )
{
    //INITIALIZE
    float index = (Gid.x * 256) + GTid.x;

    float seed1 = frac(sin(dot(float2(index, index), float2(12.9898, 78.233))) * 43758.5453);
    float r1 = (seed1 * 2) - 1;
	float seed2 = frac(sin(dot(float2(index, seed1), float2(12.9898, 78.233))) * 43758.5453);
    float r2 = (seed2 * 2) - 1;
    float seed3 = frac(sin(dot(float2(seed2, index), float2(12.9898, 78.233))) * 43758.5453);
    float r3 = (seed3 * 2) - 1;

	float rcubed = seed1 * seed2 * seed3;
	float factor = pow(rcubed, 0.333333f);
	
	float delay = (factor * (initMaxDelay - initMinDelay)) + initMinDelay;
	float speed = (factor * (initMaxSpeed - initMinSpeed)) + initMinSpeed;

    float3 dir = initDirection + float3(r1,r2,r3) * initSpread;
    normalize(dir);


    particlesWrite[index].position = initPosition;
    particlesWrite[index].spread = initSpread;
    particlesWrite[index].direction = dir;
    particlesWrite[index].speed = speed;
    particlesWrite[index].delay = delay;
	particlesWrite[index].size = initSize;


}
