
cbuffer mvp : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix mvpMatrix;
	float3 camPosition;
};


struct HSPatchOutput
{
	float edges[3] : SV_TessFactor;
	float inside : SV_InsideTessFactor;
};

struct HSOutput
{
	float3 position : POSITION;
	float2 tex : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};

struct PSInput
{
	float4 position : SV_POSITION;
	float3 positionWS : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};

[domain("tri")]

PSInput DSMain(HSPatchOutput input, float3 uvwCoord : SV_DomainLocation, const OutputPatch<HSOutput, 3> patch)
{
	float3 vertexPosition;
	float3 normal;
	float3 tangent;
	float3 binormal;
	PSInput output;

	vertexPosition = 
	uvwCoord.x * patch[0].position+
	uvwCoord.y * patch[1].position+
	uvwCoord.z * patch[2].position;
	output.position = mul(float4(vertexPosition, 1), mvpMatrix);
	output.positionWS = vertexPosition;

	normal = uvwCoord.x * patch[0].normal + uvwCoord.y * patch[1].normal + uvwCoord.z * patch[2].normal;
	output.normal = mul(normal, (float3x3) worldMatrix);

	tangent = uvwCoord.x * patch[0].tangent + uvwCoord.y * patch[1].tangent + uvwCoord.z * patch[2].tangent;
	output.tangent = mul(tangent, (float3x3) worldMatrix);

	binormal = uvwCoord.x * patch[0].binormal + uvwCoord.y * patch[1].binormal + uvwCoord.z * patch[2].binormal;
	output.binormal = mul(binormal, (float3x3) worldMatrix);

	output.tex = patch[0].tex;

	return output;
}