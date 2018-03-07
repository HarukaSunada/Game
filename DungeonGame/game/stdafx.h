#pragma once
#include <d3d9.h>
#include <d3dx9effect.h>
#pragma warning( disable : 4996 ) 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <cstdlib>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>

#include <xaudio2.h>
#include <x3daudio.h>
#include <xaudio2fx.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"xaudio2.lib")

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

#include "myEngine/System.h"

#include "myEngine/Graphics/Camera.h"
#include "myEngine/Graphics/SkinModel.h"
#include "myEngine/Graphics/SkinModelData.h"
#include "myEngine/Graphics/ShadowMap.h"
#include "myEngine/Graphics/Animation.h"
#include "myEngine/Graphics/Light.h"
#include "myEngine/HID/Pad.h"
#include "myEngine/Sound/SoundSource.h"

extern RenderTarget* mainRenderTarget;	//!<18-2 ���C�������_�����O�^�[�Q�b�g�B
extern void DrawQuadPrimitive();
extern void ChangeEffect(int ef);

const float		frameDeltaTime = 1.0f / 60.0f;		//1�t���[���̌o�ߎ��ԁB