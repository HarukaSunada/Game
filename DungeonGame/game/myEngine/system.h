#pragma once

#include "myEngine/Graphics/EffectManager.h"
#include "myEngine/Graphics/ModelDataManager.h"
extern LPDIRECT3D9				g_pD3D;		
extern LPDIRECT3DDEVICE9		g_pd3dDevice;
extern EffectManager*			g_effectManager;
extern ModelDataManager*		g_modelManager;

const int FRAME_BUFFER_WIDTH = 1280;
const int FRAME_BUFFER_HEIGHT = 720;