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
    float initLifeTime;
    float3 pad;
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

RWStructuredBuffer<ParticleStruct> particlesWrite : register(u0);



uint rand_xorshift(uint rng_state)
{
	// Xorshift algorithm from George Marsaglia's paper
	rng_state ^= (rng_state << 13);
	rng_state ^= (rng_state >> 17);
	rng_state ^= (rng_state << 5);
	return rng_state;
}




[numthreads(256, 1, 1)]
void main( uint3 Gid : SV_GroupID, uint3 GTid : SV_GroupThreadID )
{
    //INITIALIZE
    float index = (Gid.x * 256) + GTid.x;
	uint rng_state = index;

	uint w1 = rand_xorshift(rng_state);
	uint w2 = rand_xorshift(w1);
	uint w3 = rand_xorshift(w2);
	uint w4 = rand_xorshift(w3);
	uint w5 = rand_xorshift(w4);
	


	
	float delay = (w1 * (1.0 / 4294967296.0) * (initMaxDelay - initMinDelay)) + initMinDelay;
	float speed = (w2 * (1.0 / 4294967296.0) * (initMaxSpeed - initMinSpeed)) + initMinSpeed;

	float x = (w3 * (1.0 / 4294967296.0) * 2) - 1;
	float y = (w4 * (1.0 / 4294967296.0) * 2) - 1;
	float z = (w5 * (1.0 / 4294967296.0) * 2) - 1;

    float3 rng = float3(x, y, z);
	normalize(rng);

	float3 proj = rng - (initDirection * dot(initDirection, rng));
    normalize(proj);
    proj *= initSpread;

	float3 dir = proj + initDirection;
    


    particlesWrite[index].position = initPosition;
    particlesWrite[index].spread = initSpread;
    particlesWrite[index].direction = dir;
	particlesWrite[index].speed = speed;
    particlesWrite[index].delay = delay;
	particlesWrite[index].size = initSize;
    particlesWrite[index].lifeTimeLeft = initLifeTime;

}
