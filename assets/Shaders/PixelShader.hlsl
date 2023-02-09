Texture2D tex : register(t1);
SamplerState TexSampler : register(s0);

cbuffer VS_CONSTANT_BUFFER : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
    float4 lightDir;
}


struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 text : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    return tex.Sample(TexSampler, input.text) * float4(1, 1, 1, 1);
}