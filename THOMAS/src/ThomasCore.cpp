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
#include "Scene.h"

#include <AtlBase.h>
#include <atlconv.h>

namespace thomas {
	ID3D11Debug* ThomasCore::s_debug;
	ID3D11Device* ThomasCore::s_device;
	ID3D11DeviceContext* ThomasCore::s_context;
	IDXGISwapChain* ThomasCore::s_swapchain;
	HINSTANCE ThomasCore::s_hInstance;
	bool ThomasCore::s_initialized;

	bool ThomasCore::Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, LONG windowWidth, LONG windowHeight, LPWSTR title)
	{
		#ifdef _DEBUG
				AllocConsole();
				freopen("CONOUT$", "w", stdout);
		#endif

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

		if (s_initialized)
			s_initialized = Time::Init();

		if (s_initialized)
			s_initialized = Sound::Init();

		if (s_initialized)
			s_initialized = graphics::PostEffect::Init();

		return s_initialized;
	}

	HINSTANCE ThomasCore::GetHInstance()
	{
		return s_hInstance;
	}

	void ThomasCore::Update()
	{

		std::string title = "FPS: " + std::to_string(Time::GetFPS()) + " FrameTime: " + std::to_string(Time::GetFrameTime());
		SetWindowText(Window::GetWindowHandler(), CA2W(title.c_str()));

		if (Input::GetKeyDown(Input::Keys::Escape))
			Window::Destroy();

		Scene::UpdateCurrentScene();
		
		for (object::Object* object : thomas::object::Object::GetObjects())
		{
 			if(object)
				object->Update();
		}

		//graphics::Renderer::Render();
		Scene::Render();
	}

	void ThomasCore::Start()
	{


		if (s_initialized)
		{
			LOG("Thomas fully initiated, Chugga-chugga-whoo-whoo!");
			MSG msg = { 0 };


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
					Time::Update();
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
		graphics::Material::Destroy();
		graphics::Shader::Destroy();
		graphics::Texture::Destroy();
		graphics::Model::Destroy();
		graphics::Renderer::Destroy();
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

