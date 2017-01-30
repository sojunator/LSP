
Texture2D diffuseTexture : register(t0);
SamplerState diffuseSampler : register(s0);

Texture2D specularTexture : register(t1);
SamplerState specularSampler : register(s1);

Texture2D normalTexture : register(t2);
SamplerState normalSampler : register(s2);



struct VSInput
{
	float3 position : POSITION;
	float2 uv : TEXCOORD;
	float3 normal: NORMAL;
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
};

struct DirLight
{
	float4 ambientColor;
	float4 diffuseColor;
	float4 specularColor;
	float3 lightDir;
	float padding;
};

cbuffer lightBuffer : register(b2)
{
	DirLight lighttt;
	
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

    output.position = mul(float4(input.position, 1), mvpMatrix);

	output.positionWS = mul(input.position, (float3x3)worldMatrix);

    output.tex = input.uv;

	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);

	output.tangent = mul(input.tangent, (float3x3)worldMatrix);
	output.tangent = normalize(output.tangent);

	output.binormal = mul(input.binormal, (float3x3)worldMatrix);
	output.binormal = normalize(output.binormal);

	return output;
}


float4 PSMain(VSOutput input) : SV_TARGET
{


	float3 lightDir = normalize(float3(1, 0, -1)); //TEMP


    float4 textureColor = diffuseTexture.Sample(diffuseSampler, input.tex);

	float4 bumpMap = normalTexture.Sample(normalSampler, input.tex);
	bumpMap = (bumpMap * 2.0f) - 1.0f;

	float3 bumpNormal = (bumpMap.x*input.tangent) + (bumpMap.y*input.binormal) + (bumpMap.z*input.normal);

	bumpNormal = normalize(bumpNormal);

	lightDir = -lightDir;
	float lightIntensity = saturate(dot(bumpNormal, lighttt.lightDir));

	float4 diffuseColor = float4(0.5, 0, 0, 1);

	float4 diffuse = saturate(diffuseColor*lightIntensity);
	float4 specular = float4(0,0,0,0);
	if (lightIntensity > 0.0f)
	{

		float3 viewDirection = camPosition - input.positionWS;

		float4 specularIntensity = specularTexture.Sample(specularSampler, input.tex);
		float3 reflection = normalize(lightDir + viewDirection);
		specular = pow(saturate(dot(bumpNormal, reflection)),specularPower)*lightIntensity;
		specular = specular * specularIntensity;
	}

	return lighttt.ambientColor*textureColor*0.05f + diffuse*textureColor + specular*specularColor;
}