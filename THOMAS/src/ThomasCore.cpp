#include "ThomasCore.h"

#include "Input.h"
#include "object\Object.h"
#include "Sound.h"

#include <assimp\Importer.hpp>

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
			s_initialized = Time::Init();

		if (s_initialized)
			s_initialized = Sound::Init();

		Sound* bajs = Sound::CreateSound("../res/sounds/thomas.wav", "Meow", Sound::Type::Music);
		
		if (!bajs->Play())
			LOG("Sound error");

		return s_initialized;
	}

	HINSTANCE ThomasCore::GetHInstance()
	{
		return s_hInstance;
	}

	void ThomasCore::Update()
	{
		
		utils::D3d::Clear();
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
					
					thomas::object::Object* obj = thomas::object::Object::GetObjects()[i];
					if(obj->GetType() == "GameObject")
						LOG("initiating " << obj->GetType() << ":" << obj->GetName());

					s_initialized = obj->Start();
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
		utils::D3d::Destroy();
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

		Sound::Destroy();

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

