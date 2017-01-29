
//Hull shader

struct VSOutput
{
	float4 positionWS : SV_POSITION;
	float2 tex : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
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


[domain("tri")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("HSPatch")]

HSOutput HSMain(InputPatch<VSOutput, 3> patch, uint pointId : SV_OutputControlPointID, uint patchId : SV_PrimitiveID)
{
	HSOutput output;

	output.position = patch[pointId].positionWS.xyz;
	output.tex = patch[pointId].tex;
	output.normal = patch[pointId].normal;
	output.tangent = patch[pointId].tangent;
	output.binormal = patch[pointId].binormal;

	return output;

}

HSPatchOutput HSPatch(InputPatch<VSOutput, 3> inputPatch, uint patchId : SV_PrimitiveID)
{
	HSPatchOutput output;


	// Set the tessellation factors for the three edges of the triangle.
	output.edges[0] = 4;
	output.edges[1] = 4;
	output.edges[2] = 4;

	// Set the tessellation factor for tessallating inside the triangle.
	output.inside = 4;

	return output;
}