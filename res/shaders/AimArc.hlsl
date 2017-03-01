static const float PI = 3.14159265f;

cbuffer mvp : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

struct VSInput
{
    float3 position : POSITION;
    float3 color : COLOR;
};

struct VSOutput
{
    float4 positionWS : POSITION;
    float3 color : COLOR;
};

struct GSOutput
{
    float4 position : SV_POSITION;
    float4 positionWS : POSITION;
    float3 color : COLOR;
};

VSOutput VSMain(in VSInput vertexData)
{
    VSOutput output;
    output.positionWS = mul(float4(vertexData.position, 0), worldMatrix);
    output.color = vertexData.color;
    return output;
}
[maxvertexcount(11)] //dependent on for-loop iterations
GSOutput GSMain(point VSOutput input[2], inout LineStream<GSOutput> OutputStream)
{
    float4 p0 = input[0].positionWS; //boat pos
    float4 p3 = input[1].positionWS; //aim pos

    float4 p1 = p0 /*+ exitVector*/; //vector defining starting direction of projectiles
    float4 p2 = p3 + float4(0, 1, 0, 0)/* * scalar */;
    
    GSOutput output;
    for (float f = 0; f <= 1; f += 0.1f)
    {
        output.positionWS = (1 - f) * (1 - f) * (1 - f) * p0 + 3 * (1 - f) * (1 - f) * f * p1 + 3 * (1 - f) * f * f * p2 + f * f * f * p3;
        //output.positionWS *= length(p3 - p0);
        output.positionWS = mul(output.positionWS, worldMatrix);
        output.position = output.positionWS;
        output.position = mul(output.position, viewMatrix);
        output.position = mul(output.position, projectionMatrix);
        output.color = lerp(input[0].color, input[1].color, f);
        OutputStream.Append(output);
    }
}

float4 PSMain(GSOutput input)
{
    return float4(input.color, 1);
}