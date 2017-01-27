#pragma once
#include "common.h"
#include <string>
#include "utils/directXTK/Audio.h"

namespace thomas
{
	class THOMAS_API Sound
	{
	private:
		Sound(std::string fileName, std::string name, int type, DirectX::SoundEffect* sound, DirectX::AudioEngine* audioEngine);
	public:
		static bool Init();
		static Sound* CreateSound(std::string fileName, std::string name, std::string type); //types: "music" or "effect"
		std::string GetFileName();
		bool Play();
		void Pause();
		void Update();

	private:
		struct Data
		{
			std::string fileName;
			std::string name;
			int type; //1 is music, 0 is effect
			DirectX::SoundEffect* sound;
			DirectX::AudioEngine* audioEngine;
		};

		static Data s_data;
		static std::vector<Sound*> s_music;
		static std::vector<Sound*> s_soundEffect;
	};
}