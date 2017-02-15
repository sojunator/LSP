
cbuffer mvp : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix mvpMatrix;
	float3 camPosition;
	float padding;
};



struct quadStruct
{
	float3 quad[2][3];
};

RWStructuredBuffer<quadStruct> particle : register(u0);

[numthreads(1, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
/*
	particle[0].quad[0][0] = float3(-0.5, 0.5, 0);
	particle[0].quad[0][1] = float3(0.5, -0.5, 0);
	particle[0].quad[0][2] = float3(-1, -0.5, 0);
	particle[0].quad[1][0] = float3(0.0, 1, 0);
	particle[0].quad[1][1] = float3(1, -1, 0);
	particle[0].quad[1][2] = float3(-1, -1, 0);*/

	float3 posTest = float3(0,0,0);
	float3 camTest = float3(-1,0,-1);
	float3 particlePosWS = float3(0,0,-1000);//mul(posTest, (float3x3)worldMatrix);

	float3 particleLookAtCam =	camTest - posTest; //camPosition - particlePosWS;

	float3 forward = normalize(particleLookAtCam);
	float3 right = cross( float3(0,1,0), particleLookAtCam);
	float3 up = cross(forward, right);

	//tri 1
	particle[0].quad[0][0] = particlePosWS + up - right;
	particle[0].quad[0][1] = particlePosWS + up + right;
	particle[0].quad[0][2] = particlePosWS - up + right;
	//tri 2
	/*particle[0].quad[1][0] = particlePosWS + up - right;
	particle[0].quad[1][1] = particlePosWS - up + right;
	particle[0].quad[1][2] = particlePosWS - up - right;*/

	particle[0].quad[1][0] = float3(0.0, 0.1, 0);
	particle[0].quad[1][1] = float3(0.1, -0.1, 0);
	particle[0].quad[1][2] = float3(-0.1, -0.1, 0);
}
