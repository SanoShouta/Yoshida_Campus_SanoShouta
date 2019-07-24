//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef struct
{
	float4 position		: POSITION;
	float3 normal		: NORMAL;
	float2 uv			: TEXCOORD;
} InputVertex;

typedef struct
{
	float4 position		: POSITION;
	float3 normal		: NORMAL;
	float2 uv			: TEXCOORD;
} OutputVertex;

// =========================================================================
// 変数
// =========================================================================
float4x4 g_fMatrix;	// 合成用マトリクス
float4 g_fLightDir; // ライトの方向
float4 g_fColor; // ライトの方向
sampler g_MainTexture : register(s0);	// サンプラー(s)の0番を指定
sampler g_RampTexture : register(s1);	// サンプラー(s)の1番を指定

// =========================================================================
// 頂点関数
// =========================================================================
OutputVertex Vertex(InputVertex input)
{
	OutputVertex output = (OutputVertex)0;
	// 座標
	output.position = mul(input.position, g_fMatrix);
	// 法線
	output.normal = normalize(mul(input.normal, g_fMatrix));
	// UV
	output.uv = input.uv;

	return output;
}
// =========================================================================
// ピクセル関数
// =========================================================================
//float4 Pixel(OutputVertex input) : COLOR0
//{
//	// テクスチャ前提のシェーダにしたので、テクスチャがないと描画されません
//	// テクスチャを貼っていないモデルも描画したい場合、
//	// return input.color; のみの別シェーダを作り、
//	// model.cppで テクスチャがなかったらその別のシェーダを適用 などのプログラムを記述してください
//	// (※hlslでテクスチャのNULL判定は難しいです)
//	return tex2D(TextureSampler, input.uv) * input.color;
//}

float4 Pixel(OutputVertex input) : COLOR0
{
	float x = dot(input.normal, -g_fLightDir) * 0.5 + 0.5;
	float4 ramp = tex2D(g_RampTexture, float2(x, 0.5));
	float4 color = tex2D(g_MainTexture, input.uv) *  ramp * 1.7f*g_fColor;
	return color;
}
// =========================================================================
// テクニック宣言
// =========================================================================
technique StandardShader
{
	pass Pass0
	{
		vertexShader = compile vs_3_0 Vertex();
		pixelShader = compile ps_3_0 Pixel();
	}
}