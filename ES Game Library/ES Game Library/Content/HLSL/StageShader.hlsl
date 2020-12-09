float4x4 wvp;

float3 model_ambient;
float3 light_dir;
float3 eye_pos;

sampler m_Texture : register(s0);

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
	
	vsout.Uv  = vsin.Uv;

    vsout.EyePos = normalize(eye_pos - vsin.Pos.xyz);
	
	return vsout;
}

float4 PS(VSOUTPUT psin) : COLOR
{
    float3 N = psin.Normal;
    float3 L = -light_dir;
    float3 H = normalize(L + psin.EyePos);
	
    float4 color = tex2D(m_Texture, psin.Uv);
	
    color.rgb *= max(model_ambient, dot(psin.Normal, -light_dir)) + pow(max(0, dot(N, H)), 10);
	
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
