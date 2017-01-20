#include "ThomasCore.h"

namespace thomas {
	HINSTANCE ThomasCore::m_hInstance;
	bool ThomasCore::m_initialized;

	bool ThomasCore::Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, LONG windowWidth, LONG windowHeight, LPWSTR title)
	{
		m_hInstance = hInstance;
		m_initialized = Window::Init(hInstance, nCmdShow, windowWidth, windowHeight, title);
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


