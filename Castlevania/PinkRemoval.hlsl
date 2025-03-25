Texture2D tex : register(t0);
SamplerState samp : register(s0);


static const float3 PinkColor = float3(1.0f, 0.0f, 1.0f);

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float2 texCoord : TEXCOORD;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    float4 color = tex.Sample(samp, input.texCoord);
    if (color.r == PinkColor.r && color.g == PinkColor.g && color.b == PinkColor.b)
    {
        discard;
    }
    
    return color;
}

