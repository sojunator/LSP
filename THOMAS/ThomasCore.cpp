#include "ThomasCore.h"
#include "utils/d3d.h"

namespace thomas {
	HINSTANCE ThomasCore::m_hInstance;
	bool ThomasCore::m_initialized;
	ID3D11Device* ThomasCore::s_device;
	ID3D11DeviceContext* ThomasCore::s_context;
	IDXGISwapChain* ThomasCore::s_swapchain;

	bool ThomasCore::Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, LONG windowWidth, LONG windowHeight)
	{
		m_hInstance = hInstance;
		m_initialized = Window::Init(hInstance, nCmdShow, windowWidth, windowHeight, L"Thomas test window");
		if (m_initialized)
		{
			m_initialized = utils::D3d::Init(windowWidth, windowHeight, s_device, s_context, s_swapchain, Window::GetWindowHandler());
		}
		return m_initialized;
	}

	HINSTANCE ThomasCore::GetHInstance()
	{
		return m_hInstance;
	}

	void ThomasCore::Update()
	{

	}

	void ThomasCore::Start()
	{
		if (m_initialized)
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
			Window::Destroy();
		}
	}
	bool ThomasCore::Initialized()
	{
		return m_initialized;
	}
}


