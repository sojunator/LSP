#include "ThomasCore.h"
#include "utils/d3d.h"

#include "assimpincludes\assimp\Importer.hpp"

namespace thomas {
	HINSTANCE ThomasCore::s_hInstance;
	bool ThomasCore::s_initialized;

	bool ThomasCore::Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, LONG windowWidth, LONG windowHeight, LPWSTR title)
	{
		s_hInstance = hInstance;
		s_initialized = Window::Init(hInstance, nCmdShow, windowWidth, windowHeight, title);
		return s_initialized;
	}

	HINSTANCE ThomasCore::GetHInstance()
	{
		return s_hInstance;
	}

	void ThomasCore::Update()
	{
		utils::D3d::PresentBackBuffer(s_context, s_swapchain);
	}

	void ThomasCore::Start()
	{
		if (s_initialized)
		{
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
					Update();
				}
			}
			Destroy();
			Window::Destroy();

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
}


