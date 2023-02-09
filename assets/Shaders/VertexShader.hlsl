cbuffer VS_CONSTANT_BUFFER : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
    float4 lightDir;
}

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float2 text : TEXCOORD0;
};

struct VS_INPUT
{
    float4 pos : POSITION;
    float2 text : TEXCOORD0;
    
};
    


PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    output.text = input.text;
	return output;
}