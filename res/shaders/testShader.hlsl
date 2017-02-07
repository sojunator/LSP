
Texture2D displacementTexture : register(t0);
SamplerState displacementSampler : register(s0);

Texture2D normalTexture : register(t2);
SamplerState normalSampler : register(s2);

TextureCube reflectionTexture : register(t4);
SamplerState reflectionSampler : register(s4);

struct VSInput
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};


cbuffer mvp : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix mvpMatrix;
	float3 camPosition;
};

cbuffer material : register(b1)
{
	float4 ambientColor;
	float4 diffuseColor;
	float4 specularColor;
	float specularPower;
	float uvScale;
	float uvOffset;
	float texelLengthX2;
}

struct VSOutput
{
	float4 position : SV_POSITION;
	float3 positionWS : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};


VSOutput VSMain(in VSInput input)
{
	VSOutput output;

	float4 pos = float4(input.position,1 );

	output.tex = input.uv;

	float3 displacement = displacementTexture.SampleLevel(displacementSampler, output.tex, 0).xyz;

	pos.xyz += displacement;

	output.positionWS = mul(pos, worldMatrix).xyz;

	output.position = mul(pos, mvpMatrix);

	output.normal = mul(input.normal, (float3x3) worldMatrix);
	output.normal = normalize(output.normal);

	output.tangent = mul(input.tangent, (float3x3) worldMatrix);
	output.tangent = normalize(output.tangent);

	output.binormal = mul(input.binormal, (float3x3) worldMatrix);
	output.binormal = normalize(output.binormal);

	return output;
}


float4 PSMain(VSOutput input) : SV_TARGET
{

	float3 sunDir = normalize(float3(0, 0, -1));

	float3 eyeVec = camPosition - input.positionWS;
	float3 eyeDir = normalize(eyeVec);


	float2 grad = normalTexture.Sample(normalSampler, input.tex).xy;
	float3 normal = normalize(float3(grad, texelLengthX2));


	float3 reflectVec = reflect(-eyeDir, normal);
	float3 cosAngle = dot(normal, eyeDir);

	float3 reflection = reflectionTexture.Sample(reflectionSampler, reflectVec).xyz;

	float3 waterColor = lerp(float3(0.0, 0.1, 0.9), reflection, 0.5);

	float cosSpec = clamp(dot(reflectVec, sunDir), 0, 1);
	float sunSpot = pow(cosSpec, 400); //shiny

	waterColor += float3(0.9, 0.7, 0.07) * sunSpot;
	
	return float4(normal, 1);
}