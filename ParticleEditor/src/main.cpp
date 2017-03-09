#include "ParticleEditorScene.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	MSG msg = { 0 };
	thomas::ThomasCore::Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, 1920, 1080, L"Thomas Particle Editor");

	thomas::Scene* menuScene = thomas::Scene::LoadScene<ParticleEditorScene>();


	//start
	thomas::ThomasCore::Start();

	return (int)msg.wParam;
}