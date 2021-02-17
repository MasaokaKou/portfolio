//===========================================================================
//!
//!	@file	stdafx.h
//!	@brief	プリコンパイルヘッダー
//!
//===========================================================================
#pragma once

#include <SDKDDKVer.h>

//===========================================================================
// Windowsヘッダーファイル
//===========================================================================
#define NOMINMAX

#include <windows.h>

#include <wrl/client.h>

template<typename T>
using com_ptr = Microsoft::WRL::ComPtr<T>;

//===========================================================================
// Cランタイムヘッダーファイル
//===========================================================================
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//===========================================================================
// STL関連
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

//---- VisualStudio2010 のstdint.hとintsafe.hが衝突するための警告対策
#pragma warning(push)
#pragma warning(disable : 4005)
#include <stdint.h>
#include <intsafe.h>
#pragma warning(pop)

//===========================================================================
// DirectX関連
//===========================================================================
#include <d3d11.h>
#include <d3dcompiler.h>

// ライブラリファイルのリンク指定
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

#include "Handle.h"        // ハンドル管理
#include "FileWatcher.h"   // ファイル監視

#include "Resource.h"   // リソース基底

#include "GpuBuffer.h"        // バッファ
#include "GpuTexture.h"       // テクスチャ
#include "GpuInputLayout.h"   // 入力レイアウト
#include "GpuShader.h"        // シェーダー
#include "GpuCommand.h"       // GPUコマンド
#include "Primitive.h"        // プリミティブ描画
#include "Camera.h"           // カメラ
#include "CameraDebug.h"      // デバッグカメラ
#include "Shadowmap.h"        // シャドウマップ管理
#include "GBuffer.h"          // GBuffer管理

#include "FilterGlare.h"   // グレアフィルター

#include "Pass.h"            // レンダリングパス
#include "PassShadow.h"      // シャドウ生成パス
#include "PassGbuffer.h"     // Gbuffer生成パス
#include "PassLighting.h"    // 照明パス
#include "PassFilterHDR.h"   // HDRフィルター
#include "SystemRender.h"    // レンダリングシステム

#include "ModelMQO.h"   // MQOモデル
#include "ModelFBX.h"   // FBXモデル

#include "Scene.h"   // シーン基底
#include "SceneRender.h"

#include "main.h"

//===========================================================================
//	END OF FILE
//===========================================================================
