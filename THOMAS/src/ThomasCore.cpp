#include "ThomasCore.h"

#include "Input.h"
#include "object\Object.h"
#include "graphics\Texture.h"
#include "graphics\Renderer.h"
#include "graphics\Shader.h"
#include "graphics\Model.h"
#include "graphics\Material.h"
#include "graphics\PostEffect.h"
#include <assimp\Importer.hpp>
#include "Sound.h"
#include "graphics\Sprite.h"
#include "Scene.h"
#include "Physics.h"
#include "utils\DebugTools.h"
#include <AtlBase.h>
#include <atlconv.h>
#include "utils/d3d.h"
#include "graphics\ParticleSystem.h"
#include "Scene.h"

namespace thomas {
	ID3D11Debug* ThomasCore::s_debug;
	ID3D11Device* ThomasCore::s_device;
	ID3D11DeviceContext* ThomasCore::s_context;
	IDXGISwapChain* ThomasCore::s_swapchain;
	HINSTANCE ThomasCore::s_hInstance;
	bool ThomasCore::s_initialized;

	bool ThomasCore::Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, LONG windowWidth, LONG windowHeight, LPWSTR title)
	{
		srand(time(NULL));
		//#ifdef _DEBUG
		//		AllocConsole();
		//		freopen("CONOUT$", "w", stdout);
		//#endif
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		s_hInstance = hInstance;
		s_initialized = Window::Init(hInstance, nCmdShow, windowWidth, windowHeight, title);

		if (s_initialized)
			s_initialized = Input::Init();

		if (s_initialized)
			s_initialized = utils::D3d::Init(s_device, s_context, s_swapchain, s_debug);			

		if (s_initialized)
			s_initialized = graphics::Texture::Init();

		if (s_initialized)
			s_initialized = graphics::Renderer::Init();

		utils::DebugTools::Init();

		if (s_initialized)
			s_initialized = ThomasTime::Init();

		if (s_initialized)
			s_initialized = Sound::Init();

		if (s_initialized)
			s_initialized = graphics::PostEffect::Init();

		if(s_initialized)
			s_initialized = graphics::TextRender::Initialize();

		if (s_initialized)
			s_initialized = graphics::Sprite::Initialize();		
		if (s_initialized)
			s_initialized = Physics::Init();


		utils::DebugTools::Init();

		graphics::ParticleSystem::Init();
		
		return s_initialized;
	}

	HINSTANCE ThomasCore::GetHInstance()
	{
		return s_hInstance;
	}

	void ThomasCore::Update()
	{
		std::string title = "FPS: " + std::to_string(ThomasTime::GetFPS()) + " FrameTime: " + std::to_string(ThomasTime::GetFrameTime());
		SetWindowText(Window::GetWindowHandler(), CA2W(title.c_str()));


		if (Input::GetKeyDown(Input::Keys::F1))
			utils::DebugTools::ToggleVisibility();
		Scene::UpdateCurrentScene();
		Physics::Update();
		Scene::Render();
		Sound::Update();
	}

	void ThomasCore::Start()
	{


		if (s_initialized)
		{
			LOG("Thomas fully initiated, Chugga-chugga-whoo-whoo!");
			MSG msg = { 0 };
			ThomasTime::Update();

			while (WM_QUIT != msg.message)
			{
				// read messages
				if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					Input::Update();
					ThomasTime::Update();
					Update();
				}
			}
			Destroy();
			Window::Destroy();

		}
		else
		{
			LOG("Thomas failed to initiate :(");
			#ifdef _DEBUG
			system("pause");
			#endif // DEBUG

			
		}
			
	}
	bool ThomasCore::Initialized()
	{
		return s_initialized;
	}

	bool ThomasCore::Destroy()
	{
		Scene::UnloadScene();
		graphics::LightManager::Destroy();
		graphics::ParticleSystem::Destroy();
		graphics::Sprite::Destroy();
		graphics::TextRender::Destroy();
		graphics::Material::Destroy();
		graphics::Shader::Destroy();
		graphics::Texture::ReleaseSamplers();
		graphics::Texture::Destroy();
		graphics::Model::Destroy();
		graphics::Renderer::Destroy();
		utils::DebugTools::Destroy();
		object::Object::Destroy();
		s_swapchain->Release();
		s_context->Release();
		s_device->Release();

		
		s_swapchain = nullptr;
		s_context = nullptr;
		s_device = nullptr;
		

		#ifdef _DEBUG
		s_debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
		s_debug->Release();
		s_debug = nullptr;
		#endif // _DEBUG

		//Sound::Destroy();

		return true;
	}
	void ThomasCore::Exit()
	{
		Window::Destroy();
	}
	ID3D11Device * ThomasCore::GetDevice()
	{
		return s_device;
	}
	ID3D11DeviceContext* ThomasCore::GetDeviceContext()
	{
		return s_context;
	}
	IDXGISwapChain * ThomasCore::GetSwapChain()
	{
		return s_swapchain;
	}
}

