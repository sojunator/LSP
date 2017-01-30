
//Hull shader

struct VSOutput
{
	float3 position : POSITION;
	float2 tex : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};

struct HSConstantDataOutput
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




HSConstantDataOutput PatchConstantFunction(InputPatch<VSOutput, 3> inputPatch, uint patchId : SV_PrimitiveID)
{
	HSConstantDataOutput output;


	// Set the tessellation factors for the three edges of the triangle.
	output.edges[0] = 1.0f;
	output.edges[1] = 1.0f;
	output.edges[2] = 1.0f;

	// Set the tessellation factor for tessallating inside the triangle.
	output.inside = 1.0f;

	return output;
}

[domain("tri")]
[partitioning("fractional_even")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("PatchConstantFunction")]
HSOutput HSMain(InputPatch<VSOutput, 3> patch, uint pointId : SV_OutputControlPointID, uint patchId : SV_PrimitiveID)
{
	HSOutput output;

	output.position = patch[pointId].position;
	output.tex = patch[pointId].tex;
	output.normal = patch[pointId].normal;
	output.tangent = patch[pointId].tangent;
	output.binormal = patch[pointId].binormal;

	return output;

}

