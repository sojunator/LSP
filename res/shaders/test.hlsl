
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

//Struct coupled with LightManager
struct DirLight
{
	float4 ambientColor;
	float4 diffuseColor;
	float4 specularColor;
	float4 lightDir;
};
//Struct coupled with LightManager
struct PointLight
{
	float4 ambientColor;
	float4 diffuseColor;
	float4 specularColor;
	float4 position;
};
//Buffer coupled with LightManager
cbuffer lightBuffer : register(b2)
{
	uint nrOfDirectionalLights;
	uint nrOfPointLights;
	int padding1;
	int padding2;
	DirLight directionalLights[3];
	PointLight pointLights[3];
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

    float4 textureColor = diffuseTexture.Sample(diffuseSampler, input.tex);

	float4 bumpMap = normalTexture.Sample(normalSampler, input.tex);
	bumpMap = (bumpMap * 2.0f) - 1.0f;
	float3 bumpNormal = (bumpMap.x*input.tangent) + (bumpMap.y*input.binormal) + (bumpMap.z*input.normal);
	bumpNormal = normalize(bumpNormal);

	float4 outputTest = float4(0,0,0,0);

	for (uint i = 0; i < nrOfDirectionalLights; i++)
	{
		float lightIntensity = saturate(dot(bumpNormal, -directionalLights[i].lightDir.xyz));


		float4 diffuse = saturate(directionalLights[i].diffuseColor*lightIntensity);
		float4 specular = float4(0,0,0,0);

		if (lightIntensity > 0.0f)
		{

			float3 viewDirection = camPosition - input.positionWS;

			float4 specularIntensity = specularTexture.Sample(specularSampler, input.tex);
			float3 reflection = normalize(-directionalLights[i].lightDir.xyz + viewDirection);
			specular = pow(saturate(dot(bumpNormal, reflection)),specularPower)*lightIntensity;
			specular = specular * specularIntensity;
		}
	
		outputTest += directionalLights[i].ambientColor*textureColor*0.05f + diffuse*textureColor + specular*directionalLights[i].specularColor;

	}
	for (uint p = 0; p < nrOfPointLights; p++)
	{
		float4 temppl = pointLights[p].position;// mul(pointLights[p].position, worldMatrix);
		float3 pointlightdir = temppl.xyz - input.positionWS;
		normalize(pointlightdir);
		float lightIntensity = saturate(dot(bumpNormal, pointlightdir));

		float4 diffuse = saturate(pointLights[p].diffuseColor*lightIntensity);
		float4 specular = float4(0, 0, 0, 0);

		if (lightIntensity > 0.0f)
		{

			float3 viewDirection = camPosition - input.positionWS;

			float4 specularIntensity = specularTexture.Sample(specularSampler, input.tex);
			float3 reflection = normalize(temppl.xyz + viewDirection);
			specular = pow(saturate(dot(bumpNormal, reflection)), specularPower)*lightIntensity;
			specular = specular * specularIntensity;
		}

		outputTest += pointLights[p].ambientColor*textureColor*0.05f + diffuse*textureColor + specular*pointLights[p].specularColor;
	}

	return outputTest;
}