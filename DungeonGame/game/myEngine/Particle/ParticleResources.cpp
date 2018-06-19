#include "stdafx.h"
#include "ParticleResources.h"
#include "myEngine/Util.h"

ParticleResources::ParticleResources()
{
}


ParticleResources::~ParticleResources()
{
}

LPDIRECT3DTEXTURE9 ParticleResources::LoadTexture(const char* filePath)
{

	LPDIRECT3DTEXTURE9 texture = nullptr;
	int hash = CUtil::MakeHash(filePath);

	auto it = textureDictinary.find(hash);
	if (it == textureDictinary.end()) {
		//�V�K�B
		HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice, filePath, &texture);

		
		if (FAILED(hr)) {
			//MessageBox(nullptr, reinterpret_cast<char*>(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
			//�ǂݍ��ݎ��s�B
			std::abort();
		}

		std::pair<int, LPDIRECT3DTEXTURE9> node(hash, texture);
		textureDictinary.insert(node);
	}
	else {
		//�o�^�ς݁B
		texture = it->second;
	}
	return texture;
}
/*!
* @brief	�����[�X�B
*/
void ParticleResources::Release()
{
	for (auto p : textureDictinary) {
		p.second->Release();;
	}
	textureDictinary.clear();
}