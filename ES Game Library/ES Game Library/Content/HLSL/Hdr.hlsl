sampler tex0 : register(s0);
float exposure;

float4 PS_P0_Main(float2 UV : TEXCOORD0) : COLOR0
{
    float4 color = tex2D(tex0, UV);
    color *= exp2(exposure);
    color /= 1.6f + color;

    return color;
}

technique ToneMap
{
    pass P0
    {
        VertexShader = NULL;
        PixelShader = compile ps_3_0 PS_P0_Main();
    }
}