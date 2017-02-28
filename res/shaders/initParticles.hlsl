cbuffer InitBuffer : register(b0)
{
    float3 initPosition;
    float initSpread;
    float3 initDirection;
    float initMaxSpeed;

    float initMinSpeed;
    float initEndSpeed;
    float initMaxDelay;
    float initMinDelay;

    float initMaxSize;
    float initMinSize;
    float initEndSize;
    float initMaxLifeTime;

    float initMinLifeTime;
    float rand;
    float initRotationSpeed;
    bool initLooping;

    float4 initStartColor;
    float4 initEndColor;
};

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

RWStructuredBuffer<ParticleStruct> particlesWrite : register(u0);
RWStructuredBuffer<ParticleStruct> particlesWrite2 : register(u1);


uint rand_xorshift(uint rng_state)
{
	// Xorshift algorithm from George Marsaglia's paper
	rng_state ^= (rng_state << 13);
	rng_state ^= (rng_state >> 17);
	rng_state ^= (rng_state << 5);
	return rng_state;
}




[numthreads(256, 1, 1)]
void CSMain( uint3 Gid : SV_GroupID, uint3 GTid : SV_GroupThreadID )
{
    //INITIALIZE
    float index = (Gid.x * 256) + GTid.x;
	uint rng_state = index * rand;

	uint w1 = rand_xorshift(rng_state);
	uint w2 = rand_xorshift(w1);
	uint w3 = rand_xorshift(w2 * rand);
	uint w4 = rand_xorshift(w3);
	uint w5 = rand_xorshift(w4 * rand);
	
    float randClamp = (1.0 / 4294967296.0);
    
	
    float delay = (w1 * randClamp * (initMaxDelay - initMinDelay)) + initMinDelay;
    float speed = (w2 * randClamp * (initMaxSpeed - initMinSpeed)) + initMinSpeed;

    float size = (w4 * randClamp * (initMaxSize - initMinSize)) + initMinSize;
    float lifeTime = (w5 * randClamp * (initMaxSize - initMinLifeTime)) + initMinLifeTime;

    float randClampTimes2 = randClamp * 2;

    float x = (w3 * randClampTimes2) - 1;
    float y = (w4 * randClampTimes2) - 1;
    float z = (w5 * randClampTimes2) - 1;

    float3 rng = float3(x, y, z);
	normalize(rng);

	float3 proj = rng - (initDirection * dot(initDirection, rng));
    normalize(proj);
    proj *= initSpread;

	float3 dir = proj + initDirection;
    normalize(dir);

    particlesWrite[index].position = initPosition;
    particlesWrite[index].initPosition = initPosition;
    particlesWrite[index].spread = initSpread;
    particlesWrite[index].direction = dir;
	particlesWrite[index].speed = speed;
    particlesWrite[index].endSpeed = initEndSpeed;
    particlesWrite[index].delay = delay;
	particlesWrite[index].size = size;
    particlesWrite[index].endSize = initEndSize;
    particlesWrite[index].lifeTimeLeft = lifeTime;
    particlesWrite[index].timeElapsed = 0.0f;
    particlesWrite[index].rotationSpeed = initRotationSpeed;
    particlesWrite[index].looping = initLooping;
    particlesWrite[index].startColor = initStartColor;
    particlesWrite[index].endColor = initEndColor;

    particlesWrite2[index].position = initPosition;
    particlesWrite2[index].initPosition = initPosition;
    particlesWrite2[index].spread = initSpread;
    particlesWrite2[index].direction = dir;
    particlesWrite2[index].speed = speed;
    particlesWrite2[index].endSpeed = initEndSpeed;
    particlesWrite2[index].delay = delay;
    particlesWrite2[index].size = size;
    particlesWrite2[index].endSize = initEndSize;
    particlesWrite2[index].lifeTimeLeft = lifeTime;
    particlesWrite2[index].timeElapsed = 0.0f;
    particlesWrite2[index].rotationSpeed = initRotationSpeed;
    particlesWrite2[index].looping = initLooping;
    particlesWrite2[index].startColor = initStartColor;
    particlesWrite2[index].endColor = initEndColor;
}
