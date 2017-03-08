#pragma once


#include "Thomas.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <shobjidl.h>
#include "Win32InputBox.h"

class Helper
{
public:

	static std::string s_texturePath;
	
	static void TW_CALL AddSystem(void* clientData);

	static void TW_CALL CloseSystem(void *clientData);

	static void TW_CALL PauseToggle(void *clientData);

	static void TW_CALL Restart(void *clientData);

	static void TW_CALL ToggleModel(void *clientData);

	static std::string WCHAR_TO_STRING(const wchar_t *wchar);

	static wchar_t* STRING_TO_WCHAR(const std::string &str);

	static void TW_CALL SaveSystem(void *clientData);

	static void TW_CALL LoadSystem(void* clientData);

	static inline bool StringsEqual_i(const std::string& lhs, const std::string& rhs)
	{
		return _stricmp(lhs.c_str(), rhs.c_str()) == 0;
	}

	static void SplitPath(const std::string& in_path, std::vector<std::string>& split_path)
	{
		size_t start = 0;
		size_t dirsep;
		do
		{
			dirsep = in_path.find_first_of("\\/", start);
			if (dirsep == std::string::npos)
				split_path.push_back(std::string(&in_path[start]));
			else
				split_path.push_back(std::string(&in_path[start], &in_path[dirsep]));
			start = dirsep + 1;
		} while (dirsep != std::string::npos);
	}

	/**
	* Get the relative path from a base location to a target location.
	*
	* \param to The target location.
	* \param from The base location. Must be a directory.
	* \returns The resulting relative path.
	*/
	static std::string GetRelativePath(const std::string& to, const std::string& from)
	{
		std::vector<std::string> to_dirs;
		std::vector<std::string> from_dirs;

		SplitPath(to, to_dirs);
		SplitPath(from, from_dirs);

		std::string output;
		output.reserve(to.size());

		std::vector<std::string>::const_iterator to_it = to_dirs.begin(),
			to_end = to_dirs.end(),
			from_it = from_dirs.begin(),
			from_end = from_dirs.end();

		while ((to_it != to_end) && (from_it != from_end) && StringsEqual_i(*to_it, *from_it))
		{
			++to_it;
			++from_it;
		}

		while (from_it != from_end)
		{
			output += "..\\";
			++from_it;
		}

		while (to_it != to_end)
		{
			output += *to_it;
			++to_it;

			if (to_it != to_end)
				output += "\\";
		}

		return output;
	}

	static void TW_CALL BrowseTextures(void *clientData);
};
