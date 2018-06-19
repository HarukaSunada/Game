#pragma once
class ParticleResources
{
public:
	ParticleResources();
	~ParticleResources();
	/*!
	*@brief	�e�N�X�`���̃��[�h�B
	*@details
	* �ǂݍ��ݍς݂̃e�N�X�`���̏ꍇ�̓��[�h�͍s��ꂸ�A</br>
	* �����̃e�N�X�`�����Ԃ��Ă��܂��B
	*@param[in]	filePath	���[�h����e�N�X�`���̃t�@�C���p�X�B
	*@return	���[�h�����e�N�X�`���t�@�C���B
	*/
	LPDIRECT3DTEXTURE9 LoadTexture(const char* filePath);
	/*!
	* @brief	�����[�X�B
	*/
	void Release();
private:
	std::map<int, LPDIRECT3DTEXTURE9>		textureDictinary;	//!<�e�N�X�`���̃C���X�^���X�̃f�B�N�V���i���B�t�@�C���p�X�̃n�b�V���l���L�[�Ɏ����ACEffect�̃C���X�^���X��l�Ɏ��B
};

//TextureManager* texManager;

 extern ParticleResources* parResource;