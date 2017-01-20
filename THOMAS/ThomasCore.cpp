#include "ThomasCore.h"
#include "Input.h"

namespace thomas {
	HINSTANCE ThomasCore::m_hInstance;
	bool ThomasCore::m_initialized;

	bool ThomasCore::Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, LONG windowWidth, LONG windowHeight)
	{
		m_hInstance = hInstance;
		m_initialized = Window::Init(hInstance, nCmdShow, windowWidth, windowHeight, L"Thomas test window");
		if (m_initialized)
			m_initialized = Input::Init();
		return m_initialized;
	}

	HINSTANCE ThomasCore::GetHInstance()
	{
		return m_hInstance;
	}

	void ThomasCore::Update()
	{

		if (thomas::Input::IsKeyDown(Input::Keys::Space))
			OutputDebugString(L"space! ");

		
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
					Input::Update();
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


