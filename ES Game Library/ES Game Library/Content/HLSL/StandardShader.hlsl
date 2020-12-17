float4x4 wvp;

float3 model_ambient;
float3 light_dir;
float3 eye_pos;
float3 limit_color;

sampler _Texture : register(s0);

texture m_Texture;
sampler s1 = sampler_state
{
	Texture = <m_Texture>;

	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = NONE;

	AddressU = WRAP;
	AddressV = WRAP;
};

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
    float3 EyePos : TEXCOORD1;
};

VSOUTPUT VS(VSINPUT vsin)
{
	VSOUTPUT vsout = (VSOUTPUT)0;
    
    vsout.Pos = mul(vsin.Pos, wvp);
	
    vsout.Normal = vsin.Normal;
	
    vsout.Uv = vsin.Uv;

    vsout.EyePos = normalize(eye_pos - vsin.Pos.xyz);

	return vsout;
}

float4 S0_PS(VSOUTPUT psin) : COLOR
{
    float3 N = psin.Normal;
    float3 L = -light_dir;
    float3 H = normalize(L + psin.EyePos);
	
    float4 color = tex2D(_Texture, psin.Uv);
	
    color.rgb *= max(model_ambient, dot(psin.Normal, -light_dir)) + pow(max(0, dot(N, H)), 10);
	
    return color;
}

float4 S1_PS(VSOUTPUT psin) : COLOR
{
    float3 N = psin.Normal;
    float3 L = -light_dir;
    float3 H = normalize(L + psin.EyePos);
	
    float4 color = tex2D(s1, psin.Uv);
	
    color.rgb *= max(model_ambient, dot(psin.Normal, -light_dir)) + pow(max(0, dot(N, H)), 10);
    
    return color;
}

float4 S1_PS_Limit(VSOUTPUT psin) : COLOR
{
    float3 N = psin.Normal;
    float3 L = -light_dir;
    float3 H = normalize(L + psin.EyePos);
	
    float4 color = tex2D(s1, psin.Uv);
	
    color.rgb *= max(model_ambient, dot(psin.Normal, -light_dir)) + pow(max(0, dot(N, H)), 10);
    color.rgb += limit_color;
    
    return color;
}

technique FixModel_S0
{
	pass Pass0
	{
		VertexShader = compile vs_3_0 VS();
        PixelShader  = compile ps_3_0 S0_PS();
    }
}

technique FixModel_S1
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 VS();
        PixelShader  = compile ps_3_0 S1_PS();
    }
}

technique FixLimitModel_S1
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 VS();
        PixelShader  = compile ps_3_0 S1_PS_Limit();
    }
}