#pragma once
class ParticleResources
{
public:
	ParticleResources();
	~ParticleResources();
	/*!
	*@brief	テクスチャのロード。
	*@details
	* 読み込み済みのテクスチャの場合はロードは行われず、</br>
	* 既存のテクスチャが返ってきます。
	*@param[in]	filePath	ロードするテクスチャのファイルパス。
	*@return	ロードしたテクスチャファイル。
	*/
	LPDIRECT3DTEXTURE9 LoadTexture(const char* filePath);
	/*!
	* @brief	リリース。
	*/
	void Release();
private:
	std::map<int, LPDIRECT3DTEXTURE9>		textureDictinary;	//!<テクスチャのインスタンスのディクショナリ。ファイルパスのハッシュ値をキーに持ち、CEffectのインスタンスを値に持つ。
};

//TextureManager* texManager;

 extern ParticleResources* parResource;