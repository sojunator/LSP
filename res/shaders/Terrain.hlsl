
Texture2D sandTexture : register(t0);
SamplerState diffuseSampler : register(s0);

Texture2D grassTexture : register(t1);
SamplerState specularSampler : register(s1);

Texture2D hillsTexture : register(t2);
SamplerState normalSampler : register(s2);




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
};

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

    output.tex = input.uv; //Because texture is stretched

	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);

	return output;
}

float4 TerrainColour(VSOutput input)
{
    float slope, blendAmount;
    float2 tex = input.tex;
    tex*= 40;
    float4 sand = sandTexture.Sample(diffuseSampler, tex);
    float4 grass = grassTexture.Sample(specularSampler, tex);
    float4 hills = hillsTexture.Sample(normalSampler, tex);

	float sandGrassCutOff = 4.4f;
	float grassHillsCutOff = 8;

    // Determine which texture to use based on height.
    if (input.positionWS.y < sandGrassCutOff)
    {
        blendAmount = saturate((3 - input.positionWS.y) / (3 - sandGrassCutOff));
        return lerp(sand, grass, blendAmount);
    }
	
    if (input.positionWS.y < grassHillsCutOff)
    {
		blendAmount = saturate((sandGrassCutOff - input.positionWS.y) / (sandGrassCutOff - grassHillsCutOff));
        return lerp(grass, hills, blendAmount);
    }
    return hills;
}


float4 PSMain(VSOutput input) : SV_TARGET
{

    float4 textureColor = TerrainColour(input);
    float4 ambientColor = float4(0, 0, 0, 1);
    float4 outputColor = float4(0, 0, 0, 1);
	//input.normal = float3(input.normal.x, input.normal.y, -input.normal.z); //correct for lightdirCalcs, fucks specular

    float3 sunDir = normalize(-directionalLights[0].lightDir);

    ambientColor = (diffuseColor + textureColor) * 0.5f; //0.5 is a scalefactor for how strong the ambient will be
	//CURRENTLY NO NORMAL MAP
	/*float4 bumpMap = normalTexture.Sample(normalSampler, input.tex);

	bumpMap = (bumpMap * 2.0f) - 1.0f;

	float3 bumpNormal = (bumpMap.x*input.tangent) + (bumpMap.y*input.binormal) + (bumpMap.z*input.normal);
	bumpNormal = normalize(bumpNormal);*/
	//float lightIntensity = saturate(dot(bumpNormal, lightDir));

    for (uint i = 0; i < nrOfDirectionalLights; i++)
    {
		//float3 tempLightDir = float3(0, 0, 1); //for testing
        float lightIntensity = saturate(dot(input.normal, sunDir));
		//float lightIntensity = saturate(dot(input.normal, tempLightDir));

        float4 diffuse = saturate((diffuseColor + textureColor) * lightIntensity) * directionalLights[i].lightColor;

        float4 specular = float4(0, 0, 0, 0);
        if (lightIntensity > 0.0f)
        {
            float3 viewDirection = camPosition - input.positionWS;

			//float4 specularIntensity = specularTexture.Sample(specularSampler, input.tex); //specularTexture gives a 0,0,0,0 float4 somehow
            float3 reflection = normalize(directionalLights[i].lightDir + viewDirection);
			//float3 reflection = normalize(tempLightDir + viewDirection); //for testing
			//specular = pow(saturate(dot(bumpNormal, reflection)),specularPower)*lightIntensity; //NO WORKING NORMAL MEP YET
            specular = pow(saturate(dot(input.normal, reflection)), specularPower) * specularColor; // * lightIntensity; //specularPower = shiny
			//specular = specular * specularIntensity;
        }
        outputColor += diffuse + specular;
    }

    return float4((outputColor + ambientColor).rgb, 1);
}