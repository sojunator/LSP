#include "ThomasCore.h"

#include "Input.h"
#include "object\Object.h"

#include <assimp\Importer.hpp>

namespace thomas {
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
		{
			s_initialized = utils::D3d::Init(windowWidth, windowHeight, s_device, s_context, s_swapchain, Window::GetWindowHandler());
		}

		if (s_initialized)
		{
			LOG("Thomas fully initiated, Chugga-chugga-whoo-whoo!");
		}
			
		else
		{
			LOG("Thomas failed to initiate :(");
		}
			
		return s_initialized;
	}

	HINSTANCE ThomasCore::GetHInstance()
	{
		return s_hInstance;
	}

	void ThomasCore::Update()
	{
		
	//	LOG("update");

		if (Input::GetButton(Input::Buttons::A))
			LOG("YAY");

		if (Input::GetKeyDown(Input::Keys::Escape))
			Window::Destroy();

		
		for (int i = 0; i < thomas::object::Object::GetObjects().size();i++)
		{
			thomas::object::Object::GetObjects()[i]->Update();
		}
		

		utils::D3d::PresentBackBuffer(s_context, s_swapchain);
	}

	void ThomasCore::Start()
	{

		if (s_initialized)
		{
			for (int i = 0; i < thomas::object::Object::GetObjects().size(); i++)
			{
				if (s_initialized)
				{
					s_initialized = thomas::object::Object::GetObjects()[i]->Start();
					LOG("initiating object: " << thomas::object::Object::GetObjects()[i]->GetName());
				}
				else
					break;

			}
		}


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
		utils::D3d::Destroy();
		s_swapchain->Release();
		s_context->Release();
		s_device->Release();

		s_swapchain = 0;
		s_context = 0;
		s_device = 0;
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
}


