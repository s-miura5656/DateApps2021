
float4x4 wvp;

sampler m_Texture : register(s0);

//texture m_Texture;
//sampler s0 = sampler_state
//{
//    Texture = <m_Texture>;
//    MipFilter = LINEAR;
//    MinFilter = LINEAR;
//    MagFilter = NONE;

//	AddressU = WRAP;
//	AddressV = WRAP;
//};



struct VSINPUT
{
	float4 Pos          : POSITION;
    float3 Normal		: NORMAL;
	float2 Uv           : TEXCOORD0;
};

struct VSOUTPUT
{
	float4 Pos	  : POSITION;
    float3 Normal : NORMAL;
	float2 Uv     : TEXCOORD0;
};

VSOUTPUT VS(VSINPUT vsin)
{
	VSOUTPUT vsout = (VSOUTPUT)0;
    
    vsout.Pos = mul(vsin.Pos, wvp);
    
    vsout.Normal = vsin.Normal;
	
	vsout.Uv  = vsin.Uv;

	return vsout;
}

float4 PS(VSOUTPUT psin) : COLOR
{
    return tex2D(m_Texture, psin.Uv);
}

technique FixModel
{
	pass Pass0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader  = compile ps_3_0 PS();
	}
}