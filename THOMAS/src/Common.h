#pragma once
#include <iostream>
#include <comdef.h>

#define THOMAS_API 


#define LOG(msg) std::cout <<__FUNCTION__  << ": "<< msg << std::endl;

#define LOG_HR(hr) 	_com_error err(hr); LPCTSTR  errMsg = err.ErrorMessage(); std::cout <<__FUNCTION__  << ": "; std::wcout << errMsg << std::endl;


#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }


#define THOMAS_AA_COUNT 1
#define THOMAS_AA_QUALITY 0