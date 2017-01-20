#include "ThomasCore.h"
#include "Input.h"

namespace thomas {
	HINSTANCE ThomasCore::s_hInstance;
	bool ThomasCore::s_initialized;

	bool ThomasCore::Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, LONG windowWidth, LONG windowHeight, LPWSTR title)
	{
		s_hInstance = hInstance;
		s_initialized = Window::Init(hInstance, nCmdShow, windowWidth, windowHeight, title);
		if (s_initialized)
			s_initialized = Input::Init();
		return s_initialized;
	}

	HINSTANCE ThomasCore::GetHInstance()
	{
		return s_hInstance;
	}

	void ThomasCore::Update()
	{

		if (Input::GetKeyDown(Input::Keys::Escape))
			Window::Destroy();

		
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
					Input::Update();
					Update();
				}
			}
			Window::Destroy();
		}
	}
	bool ThomasCore::Initialized()
	{
		return s_initialized;
	}
}


