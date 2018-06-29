/*!
 * @brief	�V�[���`�F���W�B
 */

struct VS_INPUT{
	float4		pos		: POSITION;
	float2		uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4		pos		: POSITION;
	float2		uv		: TEXCOORD0;
};

float4 g_screenParams;		//�����_�����O�^�[�Q�b�g�̕��ƍ���
float g_FadeRate;			//�t�F�[�h�J�E���g��

texture g_tex;
sampler TextureSampler = 
sampler_state
{
    Texture = <g_tex>;
    MipFilter = NONE;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};


VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	Out.pos = In.pos;
	Out.uv	= In.uv;
	return Out;
}
float4 PSMain( VS_OUTPUT In ) : COLOR0
{
	float4 color = tex2D( TextureSampler, In.uv );
	
	float4 c;
	float fadeSize;
	float visible;
	//���؂ꍞ�݃t�F�[�h
	fadeSize = 80.0; //�t�F�[�h�̑傫��
	visible = 1.0 - floor(frac(In.uv.x / (fadeSize / g_screenParams.x)) + g_FadeRate);
	c = float4(color.rgb * visible, 1.0);
	return c;
}

technique Default
{
	pass p0
	{
		VertexShader 	= compile vs_3_0 VSMain();
		PixelShader		= compile ps_3_0 PSMain();
	}
}
