
//Globals

Texture2D diffuseTexture : register(t0);
SamplerState diffuseSampler : register(s0);

Texture2D specularTexture : register(t1);
SamplerState specularSampler : register(s1);

Texture2D normalTexture : register(t2);
SamplerState normalSampler : register(s2);

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
}

struct PSInput
{
	float4 position : SV_POSITION;
	float3 positionWS : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};

float4 PSMain(PSInput input) : SV_TARGET
{

	float3 lightDir = normalize(float3(1, 0, -1)); //TEMP


	float4 textureColor = diffuseTexture.Sample(diffuseSampler, input.tex);

	float4 bumpMap = normalTexture.Sample(normalSampler, input.tex);
	bumpMap = (bumpMap * 2.0f) - 1.0f;

	float3 bumpNormal = (bumpMap.x * input.tangent) + (bumpMap.y * input.binormal) + (bumpMap.z * input.normal);

	bumpNormal = normalize(bumpNormal);

	lightDir = -lightDir;
	float lightIntensity = saturate(dot(bumpNormal, lightDir));

	float4 diffuse = saturate(diffuseColor * lightIntensity);
	float4 specular = float4(0, 0, 0, 0);
	if (lightIntensity > 0.0f)
	{

		float3 viewDirection = camPosition - input.positionWS;

		float4 specularIntensity = specularTexture.Sample(specularSampler, input.tex);
		float3 reflection = normalize(lightDir + viewDirection);
		specular = pow(saturate(dot(bumpNormal, reflection)), specularPower) * lightIntensity;
		specular = specular * specularIntensity;
	}
	return textureColor;
	return ambientColor * textureColor * 0.05f + diffuse * textureColor + specular * specularColor;
}