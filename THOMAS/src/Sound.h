#pragma once
#include "common.h"
#include <string>
#include <vector>
#include "../../DirectXTK-dec2016/Audio/SoundCommon.h"



namespace thomas
{
	class THOMAS_API Sound
	{
	public:
		enum class Effects
		{
			fMeow = 0,
			fSwoosh = 1,
		};
		enum class Music
		{
			mStress = 2,
			mThomas = 3,
		};
	public:
		static bool Init();
		static bool Play(std::string name, float volume);
		static void Pause();
		static void Resume();
		static void SetMasterVolume(float volume);
		static void SetFxVolume(float volume);
		static void SetMusicVolume(float volume);
		static bool LoadWaveBank(std::string name);
		static void Destroy();

	private:
		static float s_masterVolume;
		static float s_fxVolume;
		static float s_musicVolume;
		static std::unique_ptr<DirectX::SoundEffectInstance> s_mInstance;
		static std::unique_ptr<DirectX::SoundEffectInstance> s_aInstance;
		static std::unique_ptr<DirectX::WaveBank> s_bank;
		static std::unique_ptr<DirectX::AudioEngine> s_audioEngine;
	};
}