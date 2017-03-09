#include "Helper.h"
#include "EditorGameObject.h"


void TW_CALL Helper::AddSystem(void * clientData)
{
	thomas::Scene* scene = (thomas::Scene*)clientData;
	scene->LoadObject<EditorGameObject>();
}

void TW_CALL Helper::CloseSystem(void * clientData)
{
	EditorGameObject* editor = (EditorGameObject*)clientData;
	thomas::object::Object::Destroy(editor);
}

void TW_CALL Helper::PauseToggle(void * clientData)
{
	thomas::object::component::ParticleEmitterComponent* particle = (thomas::object::component::ParticleEmitterComponent*)clientData;
	particle->TogglePause();
}

void TW_CALL Helper::Restart(void * clientData)
{
	thomas::object::component::ParticleEmitterComponent* particle = (thomas::object::component::ParticleEmitterComponent*)clientData;
	particle->StopEmitting(true);
	particle->StartEmitting();
}

void TW_CALL Helper::ToggleModel(void * clientData)
{
	thomas::object::GameObject* model = (thomas::object::GameObject*)clientData;
	model->SetActive(!model->GetActive());
}

std::string Helper::WCHAR_TO_STRING(const wchar_t * wchar)
{
	std::string str = "";
	int index = 0;
	while (wchar[index] != 0)
	{
		str += (char)wchar[index];
		++index;
	}
	return str;
}

wchar_t * Helper::STRING_TO_WCHAR(const std::string & str)
{
	wchar_t wchar[260];
	unsigned int index = 0;
	while (index < str.size())
	{
		wchar[index] = (wchar_t)str[index];
		++index;
	}
	wchar[index] = 0;
	return wchar;
}

void TW_CALL Helper::SaveSystem(void * clientData)
{
	thomas::object::component::ParticleEmitterComponent* particle = (thomas::object::component::ParticleEmitterComponent*)clientData;

	std::string fResult;

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		//Windows File opening dialog system
		IFileSaveDialog* pFile;

		//What files to display
		LPCWSTR ps = L".thomasps";
		COMDLG_FILTERSPEC rgSpec = { ps, L"*.thomasps" };

		//Create instance
		hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_IFileSaveDialog, reinterpret_cast<void**>(&pFile));

		if (SUCCEEDED(hr))
		{
			//Set attributes
			pFile->SetDefaultExtension(L"thomasps");
			pFile->SetFileTypes(1, &rgSpec);

			//Display dialog system
			hr = pFile->Show(NULL);

			if (SUCCEEDED(hr))
			{
				//File chosen
				IShellItem* pItem;
				hr = pFile->GetResult(&pItem);

				if (SUCCEEDED(hr))
				{
					//Filepath from file
					LPWSTR fPath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &fPath);

					if (SUCCEEDED(hr))
					{
						fResult = WCHAR_TO_STRING(fPath);
						CoTaskMemFree(fPath);


					}
					pItem->Release();
				}
				pFile->Release();
			}
			CoUninitialize();
		}
	}

	if (fResult.size() <= 0)
	{
		//No file was selected
		int msg = MessageBox(
			NULL,
			L"No file specified! Export canceled.",
			L"Error",
			MB_ICONERROR | MB_OK);
		return;
	}
	else
	{
		particle->ExportEmitter(fResult);
	}
}

void TW_CALL Helper::LoadSystem(void * clientData)
{
	thomas::object::component::ParticleEmitterComponent* particle = (thomas::object::component::ParticleEmitterComponent*)clientData;

	std::string fResult;

	HRESULT hr = CoInitializeEx(NULL,
		COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		//Windows File opening dialog system
		IFileOpenDialog* pFile;

		//What files to display
		LPCWSTR ps = L".thomasps";
		COMDLG_FILTERSPEC rgSpec = { ps, L"*.thomasps" };

		//Create instance
		hr = CoCreateInstance(
			CLSID_FileOpenDialog,
			NULL,
			CLSCTX_ALL,
			IID_IFileOpenDialog,
			reinterpret_cast<void**>(&pFile));

		if (SUCCEEDED(hr))
		{
			//Event handling
			IFileDialogEvents* pfde = NULL;
			DWORD dwCookie = 0;

			hr = pFile->Advise(pfde, &dwCookie);



			//Set attributes
			pFile->SetDefaultExtension(L"thomasps");
			pFile->SetFileTypes(1, &rgSpec);

			//Display dialog system
			hr = pFile->Show(NULL);

			if (SUCCEEDED(hr))
			{
				//File chosen
				IShellItem* pItem;
				hr = pFile->GetResult(&pItem);

				if (SUCCEEDED(hr))
				{
					//Filepath from file
					LPWSTR fPath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &fPath);
					if (SUCCEEDED(hr))
					{
						fResult = WCHAR_TO_STRING(fPath);
						CoTaskMemFree(fPath);
					}
					pItem->Release();
				}
				pFile->Release();
			}

			CoUninitialize();
		}
	}

	if (fResult.size() <= 0)
	{
		//No file was selected
		int msg = MessageBox(
			NULL,
			L"No file selected! Import canceled.",
			L"Error",
			MB_ICONERROR | MB_OK);
		return;
	}

	//Test reading file
	std::ifstream file;
	file.open(fResult, std::ios::binary | std::ios::in);
	if (!file.is_open())
	{
		//Error in opening the file
		int msg = MessageBox(
			NULL,
			L"File was damaged or corrupt!",
			L"Error",
			MB_ICONERROR | MB_OK);
		file.close();
		return;
	}
	else
	{

		int textureSize;
		file.read((char*)&textureSize, sizeof(int));

		//Read texture name
		char* textureName = (char*)malloc(textureSize + 1);
		file.read(textureName, sizeof(char) * textureSize);
		textureName[textureSize] = 0;
		file.close();
		particle->ImportEmitter(fResult);
	}
}

void TW_CALL Helper::BrowseTextures(void * clientData)
{
	thomas::object::component::ParticleEmitterComponent* particle = (thomas::object::component::ParticleEmitterComponent*)clientData;

	std::string fResult;

	HRESULT hr = CoInitializeEx(NULL,
		COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		//Windows File opening dialog system
		IFileOpenDialog* pFile;

		//What files to display
		LPCWSTR ps = L".png";
		COMDLG_FILTERSPEC rgSpec[] = { { L".png", L"*.png" },{ L".jpg", L"*.jpg" },{ L".dds", L"*.dds" } };

		//Create instance
		hr = CoCreateInstance(
			CLSID_FileOpenDialog,
			NULL,
			CLSCTX_ALL,
			IID_IFileOpenDialog,
			reinterpret_cast<void**>(&pFile));

		if (SUCCEEDED(hr))
		{
			//Event handling
			IFileDialogEvents* pfde = NULL;
			DWORD dwCookie = 0;

			hr = pFile->Advise(pfde, &dwCookie);



			//Set attributes
			pFile->SetDefaultExtension(L"png");
			pFile->SetFileTypes(3, rgSpec);

			//Display dialog system
			hr = pFile->Show(NULL);

			if (SUCCEEDED(hr))
			{
				//File chosen
				IShellItem* pItem;
				hr = pFile->GetResult(&pItem);

				if (SUCCEEDED(hr))
				{
					//Filepath from file
					LPWSTR fPath;

					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &fPath);
					if (SUCCEEDED(hr))
					{
						fResult = WCHAR_TO_STRING(fPath);
						CoTaskMemFree(fPath);
					}
					pItem->Release();
				}
				pFile->Release();
			}

			CoUninitialize();
		}
	}

	if (fResult.size() <= 0)
	{
		//No file was selected
		int msg = MessageBox(
			NULL,
			L"No file selected! Import canceled.",
			L"Error",
			MB_ICONERROR | MB_OK);
		return;
	}
	else
	{
		TCHAR NPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, NPath);

		std::string relativeTexPath = GetRelativePath(fResult, WCHAR_TO_STRING(NPath));
		
		particle->SetTexture(relativeTexPath);

	}

}
