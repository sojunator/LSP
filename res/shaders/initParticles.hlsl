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
	proj *= initSpread;
	float3 dir = (proj + initDirection) - initPosition;

	
	/*
	float3 dir = initDirection;

	float theta = initSpread * w3;
	float theta2 = initSpread;
	float theta3 = initSpread;
	
	float c = cos(theta);
	float s = sin(theta);
	float c2 = cos(theta2);
	float s2 = sin(theta2);
	float c3 = cos(theta3);
	float s3 = sin(theta3);

	//rotate
	dir.x = dir.x * c - dir.y * s;
	dir.y = dir.x * s + dir.y * c;
	dir.x = dir.x * c2 + dir.z * s2;
	dir.z = -dir.x * s2 + dir.z * c2;
	dir.y = dir.y * c3 - dir.z * s3;
	dir.z = dir.y * s3 + dir.z * c3;
	*/
	

    particlesWrite[index].position = initPosition;
    particlesWrite[index].spread = initSpread;
    particlesWrite[index].direction = dir;
	particlesWrite[index].speed = speed;
    particlesWrite[index].delay = delay;
	particlesWrite[index].size = initSize;


}
