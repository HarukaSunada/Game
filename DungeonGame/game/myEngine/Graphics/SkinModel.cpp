#include "stdafx.h"
#include "myEngine/Graphics/SkinModel.h"
#include "myEngine/Graphics/SkinModelData.h"
#include "myEngine/Graphics/Light.h"

extern UINT                 g_NumBoneMatricesMax;
extern D3DXMATRIXA16*       g_pBoneMatrices ;
namespace {
	void DrawMeshContainer(
		IDirect3DDevice9* pd3dDevice, 
		LPD3DXMESHCONTAINER pMeshContainerBase, 
		LPD3DXFRAME pFrameBase,
		ID3DXEffect* pEffect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		D3DXMATRIX* viewMatrix,
		D3DXMATRIX* projMatrix,
		Light* light,
		LPDIRECT3DTEXTURE9 normalMap,
		bool isDrawShadowMap,
		bool isRecieveShadow
	)
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
		D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
		UINT iAttrib;
		LPD3DXBONECOMBINATION pBoneComb;

		D3DXMATRIXA16 matTemp;
		D3DCAPS9 d3dCaps;
		pd3dDevice->GetDeviceCaps(&d3dCaps);
		D3DXMATRIX viewProj;
		D3DXMatrixMultiply(&viewProj, viewMatrix, projMatrix);
		
		//�e�N�j�b�N��ݒ�B
		{
			//�X�L�����f��
			if (pMeshContainer->pSkinInfo != NULL) {
				if (isDrawShadowMap) {
					//�V���h�E�}�b�v�ւ̏������݃e�N�j�b�N
					pEffect->SetTechnique("SkinModelRenderToShadowMap");
				}
				else {
					pEffect->SetTechnique("SkinModel");
				}
			}
			else {
				if (isDrawShadowMap) {
					pEffect->SetTechnique("NoSkinModelRenderToShadowMap");
				}
				else {
					pEffect->SetTechnique("NoSkinModel");
				}
			}
		}
		//���ʂ̒萔���W�X�^��ݒ�
		{
			//�r���[�v���W�F�N�V����
			pEffect->SetMatrix("g_mViewProj", &viewProj);
			//�V���h�E���V�[�o�[�t���O��]���B
			pEffect->SetInt("g_isShadowReciever", isRecieveShadow);
			//���C�g
			pEffect->SetValue(
				"g_light",
				light,
				sizeof(Light)
			);

			//�V���h�E���V�[�o�[
			if (isRecieveShadow) {
				pEffect->SetTexture("g_shadowMapTexture", g_shadowMap->GetTexture());
				pEffect->SetMatrix("g_lightViewMatrix", &g_shadowMap->GetLightViewMatrix());
				pEffect->SetMatrix("g_lightProjectionMatrix", &g_shadowMap->GetLightProjectionMatrix());
			}
		}

		if (normalMap != NULL) {
			//�@���}�b�v���V�F�[�_�ɓ]��
			pEffect->SetTexture("g_nomalTexture", normalMap);

			//�@���}�b�v����
			pEffect->SetBool("g_isHasNomalMap", true);
		}
		else {
			//�@���}�b�v�Ȃ�
			pEffect->SetBool("g_isHasNomalMap", false);
		}

		if (pMeshContainer->pSkinInfo != NULL)
		{
			//�X�L�����L��B
			pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
			for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
			{
				// first calculate all the world matrices
				for (DWORD iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
				{
					DWORD iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
					if (iMatrixIndex != UINT_MAX)
					{
						D3DXMatrixMultiply(
							&g_pBoneMatrices[iPaletteEntry],
							&pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
							pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]
						);
						//D3DXMatrixMultiply(&g_pBoneMatrices[iPaletteEntry], &matTemp, &g_matView);
					}
				}
			
				
				pEffect->SetMatrixArray("g_mWorldMatrixArray", g_pBoneMatrices, pMeshContainer->NumPaletteEntries);
				pEffect->SetInt("g_numBone", pMeshContainer->NumInfl);
				// �f�B�t���[�Y�e�N�X�`���B
				pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);

				// �{�[�����B
				pEffect->SetInt("CurNumBones", pMeshContainer->NumInfl - 1);

				pEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
				pEffect->BeginPass(0);

				pEffect->CommitChanges();
				// draw the subset with the current world matrix palette and material state
				pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
				pEffect->EndPass();
				pEffect->End();

			}
		}
		else {
						
			D3DXMATRIX mWorld;
			if (pFrame != NULL) {
				mWorld = pFrame->CombinedTransformationMatrix;
			}
			else {
				mWorld = *worldMatrix;
			}
			
			pEffect->SetMatrix("g_worldMatrix", &mWorld);
			pEffect->SetMatrix("g_rotationMatrix", rotationMatrix);

			pEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
			pEffect->BeginPass(0);

			for (DWORD i = 0; i < pMeshContainer->NumMaterials; i++) {
				pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[i]);
				pEffect->CommitChanges();
				pMeshContainer->MeshData.pMesh->DrawSubset(i);
			}
			pEffect->EndPass();
			pEffect->End();
		}
	}
	void DrawFrame(
		IDirect3DDevice9* pd3dDevice, 
		LPD3DXFRAME pFrame, 
		ID3DXEffect* pEffect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		D3DXMATRIX* viewMatrix, 
		D3DXMATRIX* projMatrix,
		Light* light,
		LPDIRECT3DTEXTURE9 normalMap,
		bool isDrawShadowMap, 
		bool isRecieveShadow)
	{
		LPD3DXMESHCONTAINER pMeshContainer;

		pMeshContainer = pFrame->pMeshContainer;
		while (pMeshContainer != NULL)
		{
			DrawMeshContainer(
				pd3dDevice, 
				pMeshContainer, 
				pFrame, 
				pEffect,
				worldMatrix,
				rotationMatrix,
				viewMatrix,
				projMatrix,
				light,
				normalMap,
				isDrawShadowMap,
				isRecieveShadow
				);

			pMeshContainer = pMeshContainer->pNextMeshContainer;
		}

		if (pFrame->pFrameSibling != NULL)
		{
			DrawFrame(
				pd3dDevice, 
				pFrame->pFrameSibling, 
				pEffect,
				worldMatrix,
				rotationMatrix,
				viewMatrix,
				projMatrix,
				light,
				normalMap,
				isDrawShadowMap,
				isRecieveShadow
				);
		}

		if (pFrame->pFrameFirstChild != NULL)
		{
			DrawFrame(
				pd3dDevice, 
				pFrame->pFrameFirstChild, 
				pEffect,
				worldMatrix,
				rotationMatrix,
				viewMatrix,
				projMatrix,
				light,
				normalMap,
				isDrawShadowMap,
				isRecieveShadow
				);
		}
	}
}
SkinModel::SkinModel() :
	skinModelData(nullptr),
	light(nullptr),
	pEffect(nullptr)
{
}
SkinModel::~SkinModel()
{

}

void SkinModel::Init(SkinModelData* modelData)
{
	pEffect = g_effectManager->LoadEffect("Assets/Shader/Model.fx");
	skinModelData = modelData;
}
void SkinModel::Update(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale)
{
	if (isShadowCaster) {
		//�V���h�E�L���X�^�[�o�^
		SkinModel* caster = this;
		g_shadowMap->Entry(this);
	}
	D3DXMATRIX mTrans, mScale;
	D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&mTrans, trans.x, trans.y, trans.z);
	D3DXMatrixRotationQuaternion(&rotationMatrix, &rot);

	worldMatrix = mScale * rotationMatrix * mTrans;

	if (skinModelData) {
		skinModelData->UpdateBoneMatrix(worldMatrix);	//�{�[���s����X�V�B
	}
}

void SkinModel::Draw(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix ,bool isDrawShadowMap)
{
	if (skinModelData) {
		DrawFrame(
			g_pd3dDevice, 
			skinModelData->GetFrameRoot(), 
			pEffect,
			&worldMatrix,
			&rotationMatrix,
			viewMatrix,
			projMatrix,
			light,
			normalMap,
			isDrawShadowMap,
			isRecieveShadow
		);
	}
}
LPD3DXMESH SkinModel::GetOrgMeshFirst()
{
	if(skinModelData != nullptr){
		return skinModelData->GetOrgMeshFirst();
	}
	return nullptr;
}