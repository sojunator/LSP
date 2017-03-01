static const float PI = 3.14159265f;

cbuffer mvp : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
    matrix mvpMatrix;
    float3 camPosition;
};

struct VSInput
{
    float3 position : POSITION;
    float3 color : COLOR;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float3 positionWS : POSITION;
    float3 color : COLOR;
};

struct GSOutput
{
    float4 position : SV_POSITION;
    float3 positionWS : POSITION;
    float3 color : COLOR;
};

VSOutput VSmain(in VSInput vertexData : POSITION)
{
    VSOutput output;
    output.position = mul(float4(vertexData.position, 1), mvpMatrix);
    output.positionWS = mul(vertexData.position, (float3x3) worldMatrix);
    output.color = vertexData.color;
    return output;
}
[maxvertexcount(11)]
GSOutput GSmain(point VSOutput input[2], inout LineStream<GSOutput> OutputStream)
{
    float3 p0 = input[0].positionWS; //boat pos
    float3 p3 = input[1].positionWS; //aim pos

    float p1 = p0 /*+ exitVector*/; //vector defining starting direction of projectiles
    float p2 = p3 + float3(0, 1, 0)/* * scalar */;
    
    GSOutput output;
    for (float f = 0; f <= 1; f += 0.1f)
    {
        output.positionWS = (1 - f) * (1 - f) * (1 - f) * p0 + 3 * (1 - f) * (1 - f) * f * p1 + 3 * (1 - f) * f * f * p2 + f * f * f * p3;
        output.positionWS *= length(p3 - p0);
        output.position = output.positionWS;
        output.position = mul(output.position, viewMatrix);
        output.position = mul(output.position, projectionMatrix);
        output.color = lerp(input[0].color, input[1].color, f);
        OutputStream.Append(output);
    }
}