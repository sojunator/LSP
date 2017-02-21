Texture2D diffuseTexture : register(t0);
SamplerState diffuseSampler : register(s0);

Texture2D specularTexture : register(t1); //Gör ingenting
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
	float4 materialProperty;
	float specularPower; //shiny
}

//Struct coupled with LightManager
struct DirLight
{
	float4 lightColor;
	float3 lightDir;
	float padding;
};
//Struct coupled with LightManager
struct PointLight
{
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	float power;
	float4 lightColor;
	float3 position;
	float padding;
};
//Buffer coupled with LightManager
cbuffer lightBuffer : register(b2)
{
	uint nrOfDirectionalLights;
	uint nrOfPointLights;
	int padding1;
	int padding2;
	DirLight directionalLights[3];
	PointLight pointLights[20];
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
	float3 textureColor = float3(1,1,1);
	if(materialProperty.x >= 1)
		textureColor = diffuseTexture.Sample(diffuseSampler, input.tex).rgb;

	float3 ambientColor = float3(0,0,0);
	float3 outputColor = float3(0,0,0);

	ambientColor = (diffuseColor.rgb * textureColor) * 0.5f; //0.5 is a scalefactor for how strong the ambient will be

	float4 bumpMap = normalTexture.Sample(normalSampler, input.tex);

	bumpMap = (bumpMap * 2.0f) - 1.0f;

	float3 bumpNormal = (bumpMap.x*input.tangent) + (bumpMap.y*input.binormal) + (bumpMap.z*input.normal);
	bumpNormal = normalize(bumpNormal);

	for (uint i = 0; i < nrOfDirectionalLights; i++)
	{
		DirLight light = directionalLights[i];
		float3 lightColor = light.lightColor.rgb;
		float lightStrenght = light.lightColor.w;

		float3 sunDir = normalize(-light.lightDir);

		float lightIntensity = saturate(dot(input.normal, sunDir));
		if(materialProperty.z >= 1)
			lightIntensity = saturate(dot(bumpNormal, sunDir));

		float3 diffuse = saturate(diffuseColor.rgb * textureColor * lightIntensity * lightColor * lightStrenght);

		float3 specular = float3(0,0,0);
		if (lightIntensity > 0.0f)
		{
			float3 viewDirection = camPosition - input.positionWS;

			//float4 specularIntensity = specularTexture.Sample(specularSampler, input.tex); //specularTexture gives a 0,0,0,0 float4 somehow
			
			float3 reflection = normalize(reflect(-viewDirection, input.normal));
			if (materialProperty.z >= 1)
				reflection = normalize(reflect(-viewDirection, bumpNormal));

			float specularPower2 = specularPower;
			specularPower2 += 0.000000001f; //because we can't pow with a value of 0
			specular = pow(saturate(dot(input.normal, reflection)), specularPower2) * specularColor.rgb; //specularPower = shiny
			if (materialProperty.z >= 1)
				specular = pow(saturate(dot(bumpNormal, reflection)), specularPower2) * specularColor.rgb;
			//specular = specular * specularIntensity; //specularIntensity returns 0,0,0,0
		}
		outputColor = saturate(outputColor + diffuse + specular);
	}
	outputColor = saturate(outputColor + ambientColor);
	return float4(outputColor,1);
}