
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

    output.tex = input.uv * 30.0f; //Because texture is stretched

	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);

	return output;
}

float4 TerrainColour(VSOutput input)
{
    float slope, blendAmount;
    float2 tex = input.tex;
    float4 sand = sandTexture.Sample(diffuseSampler, tex);
    float4 grass = grassTexture.Sample(specularSampler, tex);
    float4 hills = hillsTexture.Sample(normalSampler, tex);
	/*float4 sand = float4(1.0f, 0.0f, 0.0f, 1.0f);
	float4 grass = float4(0.0f, 1.0f, 0.0f, 1.0f);
	float4 hills = float4(0.0f, 0.0f, 1.0f, 1.0f);*/
    slope = 1.0f - input.normal.y;

        // Determine which texture to use based on height.
    if (input.positionWS.y < 1.1 * 4)
    {
        blendAmount = slope / 0.3f;
        return lerp(sand, grass, blendAmount); //lerp not working as wanted
		//return sand;
    }
	
    if (input.positionWS.y < 2.0 * 4)
    {
        blendAmount = (slope - 0.2f) * (1.0f / (0.7f - 0.2f));
		//blendAmount = slope / 0.3f;
        return lerp(grass, hills, blendAmount);
		//return grass;
    }

    return hills;
    //if (y < 1.1 * 4)

    //    return float4(0.749f, 0.749f, 0.749f - y * 0.2, 1.0f);
    //else if (y < 2.0 * 4)
    //    return float4(0.24f - y * 0.02, 0.74f - y * 0.02, 0.49f - y * 0.02, 1.0f);
    //else
    //    return float4(0.8 - 0.002 * y, 0.8 - 0.002 * y, 0.8 - 0.002 * y, 1.0);
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