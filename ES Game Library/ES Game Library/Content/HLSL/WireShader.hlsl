float4x4 wvp;

float red;

sampler m_Texture : register(s0);

struct VSINPUT
{
	float4 Pos          : POSITION;
	float2 Uv           : TEXCOORD0;
};

struct VSOUTPUT
{
	float4 Pos	  : POSITION;
	float2 Uv     : TEXCOORD0;
};

VSOUTPUT VS(VSINPUT vsin)
{
	VSOUTPUT vsout = (VSOUTPUT)0;
    
    vsout.Pos = mul(vsin.Pos, wvp);
	
	vsout.Uv  = vsin.Uv;

	return vsout;
}

float4 PS(VSOUTPUT psin) : COLOR
{
    float4 color = tex2D(m_Texture, psin.Uv);
	
    color.r += red;
	
    return color;
}

technique FixModel
{
	pass Pass0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader  = compile ps_3_0 PS();
	}
}
