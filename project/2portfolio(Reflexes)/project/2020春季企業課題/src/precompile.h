//===========================================================================
//!
//!	@file	stdafx.h
//!	@brief	�v���R���p�C���w�b�_�[
//!
//===========================================================================
#pragma once

#include <SDKDDKVer.h>

//===========================================================================
// Windows�w�b�_�[�t�@�C��
//===========================================================================
#define NOMINMAX

#include <windows.h>

#include <wrl/client.h>

template<typename T>
using com_ptr = Microsoft::WRL::ComPtr<T>;

//===========================================================================
// C�����^�C���w�b�_�[�t�@�C��
//===========================================================================
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//===========================================================================
// STL�֘A
//===========================================================================
#include <algorithm>
#include <array>
#include <exception>
#include <malloc.h>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>
#include <tuple>

//---- VisualStudio2010 ��stdint.h��intsafe.h���Փ˂��邽�߂̌x���΍�
#pragma warning(push)
#pragma warning(disable : 4005)
#include <stdint.h>
#include <intsafe.h>
#pragma warning(pop)

//===========================================================================
// DirectX�֘A
//===========================================================================
#include <d3d11.h>
#include <d3dcompiler.h>

// ���C�u�����t�@�C���̃����N�w��
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//---- DirectX Math
#include <DirectXMath.h>

//---- DirectX Tex
//
//#include <OpenSource/DirectXTex/DirectXTex/DirectXTex.h>
//
//#ifdef _DEBUG
//	#pragma comment(lib, "../OpenSource/DirectXTex/DirectXTex/Bin/Desktop_2013/Win32/Debug/DirectXTex.lib")
//#else
//	#pragma comment(lib, "../OpenSource/DirectXTex/DirectXTex/Bin/Desktop_2013/Win32/Release/DirectXTex.lib")
//#endif

//---- DirectX ToolKit
//#include <OpenSource/DirectXTK/Inc/Audio.h>
#include <OpenSource/DirectXTK/Inc/CommonStates.h>
#include <OpenSource/DirectXTK/Inc/DDSTextureLoader.h>
#include <OpenSource/DirectXTK/Inc/DirectXHelpers.h>
#include <OpenSource/DirectXTK/Inc/Effects.h>
#include <OpenSource/DirectXTK/Inc/GeometricPrimitive.h>
#include <OpenSource/DirectXTK/Inc/Model.h>
#include <OpenSource/DirectXTK/Inc/PrimitiveBatch.h>
#include <OpenSource/DirectXTK/Inc/ScreenGrab.h>
#include <OpenSource/DirectXTK/Inc/SimpleMath.h>
#include <OpenSource/DirectXTK/Inc/SpriteBatch.h>
#include <OpenSource/DirectXTK/Inc/SpriteFont.h>
#include <OpenSource/DirectXTK/Inc/VertexTypes.h>
#include <OpenSource/DirectXTK/Inc/WICTextureLoader.h>

#ifdef _DEBUG
#pragma comment(lib, "../OpenSource/DirectXTK/Bin/Desktop_2017/x64/Debug/DirectXTK.lib")
#else
#pragma comment(lib, "../OpenSource/DirectXTK/Bin/Desktop_2017/x64/Release/DirectXTK.lib")
#endif

using namespace DirectX;

//===========================================================================
//	imgui
//===========================================================================
#include <OpenSource/imgui/imgui.h>
#include <OpenSource/imgui/examples/imgui_impl_win32.h>
#include <OpenSource/imgui/examples/imgui_impl_dx11.h>

//===========================================================================
//
//===========================================================================
#include "gmTypedef.h"

#include "Vector.h"
#include "Matrix.h"

#include "Handle.h"        // �n���h���Ǘ�
#include "FileWatcher.h"   // �t�@�C���Ď�

#include "Resource.h"   // ���\�[�X���

#include "GpuBuffer.h"        // �o�b�t�@
#include "GpuTexture.h"       // �e�N�X�`��
#include "GpuInputLayout.h"   // ���̓��C�A�E�g
#include "GpuShader.h"        // �V�F�[�_�[
#include "GpuCommand.h"       // GPU�R�}���h
#include "Primitive.h"        // �v���~�e�B�u�`��
#include "Camera.h"           // �J����
#include "CameraDebug.h"      // �f�o�b�O�J����
#include "Shadowmap.h"        // �V���h�E�}�b�v�Ǘ�
#include "GBuffer.h"          // GBuffer�Ǘ�

#include "FilterGlare.h"   // �O���A�t�B���^�[

#include "Pass.h"            // �����_�����O�p�X
#include "PassShadow.h"      // �V���h�E�����p�X
#include "PassGbuffer.h"     // Gbuffer�����p�X
#include "PassLighting.h"    // �Ɩ��p�X
#include "PassFilterHDR.h"   // HDR�t�B���^�[
#include "SystemRender.h"    // �����_�����O�V�X�e��

#include "ModelMQO.h"   // MQO���f��
#include "ModelFBX.h"   // FBX���f��

#include "Scene.h"   // �V�[�����
#include "SceneRender.h"

#include "main.h"

//===========================================================================
//	END OF FILE
//===========================================================================
