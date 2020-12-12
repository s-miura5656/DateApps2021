static const int MAX_MATRICES = 26;
float4x3 WorldMatrixArray[MAX_MATRICES];
int NumBones;

float4x4 vp;

//sampler m_Texture : register(s0);
float3 model_ambient;
float3 light_dir;
float3 eye_pos;

texture m_Texture;
sampler s0 = sampler_state
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
    float4 BlendWeights : BLENDWEIGHT;
    float4 BlendIndices : BLENDINDICES;
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
    
    int IndexArray[4] = (int[4]) vsin.BlendIndices;
    float BlendWeightsArray[4] = (float[4]) vsin.BlendWeights;

    float LastWeight = 0;
    
    for (int iBone = 0; iBone < NumBones - 1; iBone++)
    {
        vsout.Pos.xyz += mul(vsin.Pos,
                                 WorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
        
        vsout.Normal += mul(float4(vsin.Normal, 1.0f),
                                 WorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];

        LastWeight += BlendWeightsArray[iBone];
    }
    
    LastWeight = 1.0f - LastWeight;
    
    vsout.Pos.xyz += (mul(vsin.Pos, WorldMatrixArray[IndexArray[NumBones - 1]])
                      * LastWeight);

    vsout.Normal += (mul(float4(vsin.Normal, 1.0f), WorldMatrixArray[IndexArray[NumBones - 1]])
                     * LastWeight);
    
    vsout.Normal = normalize(vsout.Normal);
    
    vsout.Pos.w = 1.0f;
    vsout.Pos = mul(vsout.Pos, vp);
	
	vsout.Uv  = vsin.Uv;
    
    vsout.EyePos = normalize(eye_pos - vsout.Pos.xyz);
    
	return vsout;
}

float4 PS(VSOUTPUT psin) : COLOR
{
    float3 N = psin.Normal;
    float3 L = -light_dir;
    float3 H = normalize(L + psin.EyePos);
	
    float4 color = tex2D(s0, psin.Uv);
	
    color.rgb *= max(model_ambient, dot(psin.Normal, -light_dir)) + pow(max(0, dot(N, H)), 10);
	
    return color;
}

float4 DAMAGE_PS(VSOUTPUT psin) : COLOR
{
    float3 N = psin.Normal;
    float3 L = -light_dir;
    float3 H = normalize(L + psin.EyePos);
	
    float4 color = tex2D(s0, psin.Uv);
	
    color.rgb *= max(model_ambient, dot(psin.Normal, -light_dir)) + pow(max(0, dot(N, H)), 10);
	
    color += float4(1.0f, 0.0f, 0.0f, 1.0f);
    
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

technique DamageModel
{
    pass Pass0
    {
        VertexShader = compile vs_3_0 VS();
        PixelShader  = compile ps_3_0 DAMAGE_PS();
    }
}