Texture2D displacementMap : register(t0);
SamplerState displacementSampler : register(s1);
cbuffer CollisionBuffer : register(b0)
{
	float2 UVs[2000];
}

RWStructuredBuffer<float> CollisionWrite : register(u0);

[numthreads(256, 1, 1)]
void CSMain(uint3 Gid : SV_GroupID, uint3 GTid : SV_GroupThreadID)
{
	float index = (Gid * 256) + GTid.x;
	float height = displacementMap.SampleLevel(displacementSampler, UVs[index], 0).z;

	CollisionWrite[index] = height;
}