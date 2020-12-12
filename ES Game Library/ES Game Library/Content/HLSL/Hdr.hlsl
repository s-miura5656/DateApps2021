sampler tex0 : register(s0);
float exposure;

float4 PS_P0_Main(float2 UV : TEXCOORD0) : COLOR0
{
    float4 color = tex2D(tex0, UV);
    color *= exp2(exposure);
    color = max(color - 0.004, 0.0);
    color = (color * (6.2 * color + 0.5)) / (color * (6.2 * color + 1.7) + 0.06);

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