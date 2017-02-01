#pragma once
#include "Math.h"

namespace thomas
{
	namespace utils
	{
		class OceanSimulator
		{
		public:
			struct OceanSettings
			{
				// Must be power of 2.
				int mapDimension;
				// Typical value is 1000 ~ 2000
				float patchLength;

				// Adjust the time interval for simulation.
				float timeScale;
				// Amplitude for transverse wave. Around 1.0
				float waveAmplitude;
				// Wind direction. Normalization not required.
				math::Vector2 windDir;
				// Around 100 ~ 1000
				float windSpeed;
				// This value damps out the waves against the wind direction.
				// Smaller value means higher wind dependency.
				float windDependency;
				// The amplitude for longitudinal wave. Must be positive.
				float choppyScale;

				//Gravity in cm/s^2
				float gravity = 981 
			};

		private:
			void InitHeightMap(math::Vector2* outH0, float* outOmega);

			// Generating gaussian random number with mean 0 and standard deviation 1.
			float Gauss();

			// Phillips Spectrum
			// K: normalized wave vector, W: wind direction, v: wind velocity, a: amplitude constant
			float Phillips(math::Vector2 k, math::Vector2 w, float v, float a, float dir_depend);

		public:
			OceanSimulator(OceanSettings& settings);
			OceanSimulator();

			void Update();

			ID3D11ShaderResourceView* GetDisplacementMap();
			ID3D10ShaderResourceView* GetNormalMap();

			OceanSettings& GetSettings();
		private:
			OceanSettings m_settings;

			//Displacement map
			ID3D11Texture2D* m_displacementMap;
			ID3D11ShaderResourceView* m_displacmentSRV;
			ID3D11RenderTargetView* m_displacementRTV;

			//Normal map
			ID3D11Texture2D* m_normalMap;			// (RGBA16F)
			ID3D11ShaderResourceView* m_normalSRV;
			ID3D11RenderTargetView* m_normalRTV;

			ID3D11SamplerState* m_pointSamplerState;

			//--------------------CS Simulation data--------------------

			//H(0) Philliphs spectrum & Gauss distribution
			ID3D11Buffer* m_bufferH0;
			ID3D11UnorderedAccessView* m_uavH0;
			ID3D11ShaderResourceView* m_srvH0;

			//Angular frequency
			ID3D11Buffer* m_bufferOmega;
			ID3D11UnorderedAccessView* m_uavOmega;
			ID3D11ShaderResourceView* m_srvOmega;

			//H(t), Dx(t) & Dy(t) in freq domain. Updated each frame
			ID3D11Buffer* m_bufferHT;
			ID3D11UnorderedAccessView* m_uavHT;
			ID3D11ShaderResourceView* m_srvHT;

			//Height and choppy buffer in space domain, corresponding to H(t), Dx(t) & Dy(t)
			ID3D11Buffer* m_bufferDxyz;
			ID3D11UnorderedAccessView* m_uavDxyz;
			ID3D11ShaderResourceView* m_srvDxyz;

			ID3D11Buffer* m_pQuadVertexBuffer;
			
			//Shaders, layouts and constants
			ID3D11ComputeShader* m_updateSpectrumCS;

			ID3D11VertexShader* m_quadVS;
			ID3D11PixelShader* m_updateDisplacementPS;
			ID3D11PixelShader* m_genNormalsPS;

			ID3D11InputLayout* m_quadLayout;

			ID3D11Buffer* m_immutableCB;
			ID3D11Buffer* m_perFrameCB;

			// FFT wrap-up
		//	CSFFT512x512_Plan m_fft_plan;

		};
	}
}