#pragma once
#include "Component.h"
#include "..\..\utils\math.h"
#include "..\..\graphics\Texture.h"
#include "..\..\graphics\Shader.h"
#include "..\..\graphics\ParticleSystem.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{
			class ParticleEmitterComponent : public Component
			{
			public:
				
				struct InitParticleBufferStruct
				{
					math::Vector3 position;
					float spread;

					math::Vector3 direction;
					float maxSpeed;

					float minSpeed;
					float maxDelay;
					float minDelay;
					float maxSize;

					float minSize;
					float maxLifeTime;
					float minLifeTime;
					float rand;

					float alpha;
					math::Vector3 pad;
				};

				struct ParticleStruct
				{
					math::Vector3 position;
					float spread;
					math::Vector3 direction;
					float speed;
					float delay;
					float size;
					float lifeTimeLeft;
					float alpha;
				};
			private:
				void CreateParticleUAVsandSRVs();
				void CreateInitBuffer();
				void InitialDispatch();

			public:
				ParticleEmitterComponent();
				
				void Destroy();

				void Start();
				void Update();

				void SetAll(_In_opt_ unsigned int nrOfParticles, _In_opt_ math::Vector3 particleDirection, _In_opt_ float minDelay, _In_opt_ float maxDelay, _In_opt_ float minSpeed, _In_opt_ float maxSpeed, 
					_In_opt_ float particleSpreadFactor, _In_opt_ float particleMinSize, _In_opt_ float particleMaxSize, _In_opt_ float particleMinLifeTime, _In_opt_ float particleMaxLifeTime, _In_opt_ float alpha);

				void SetPosition(math::Vector3 other);
				void SetSpread(float other);
				void SetDirection(math::Vector3 other);
				void SetMinSpeed(float other);
				void SetMaxSpeed(float other);
				void SetMinDelay(float other);
				void SetMaxDelay(float other);
				void SetMinSize(float other);
				void SetMaxSize(float other);
				void SetMinLifeTime(float other);
				void SetMaxLifeTime(float other);
				void SetAlpha(float other);
				

				void StartEmitting();
				void StopEmitting();
				
				bool IsEmitting() const;
				
				void SwapUAVsandSRVs(ID3D11UnorderedAccessView*& uav, ID3D11ShaderResourceView*& srv);//ping pong
				
				void SetShader(std::string shaderName);
				graphics::Shader* GetShader();
				void SetTexture(std::string texturePath);
				graphics::Texture* GetTexture();

				void SetNrOfParticles(unsigned int other);
				unsigned int GetNrOfParticles() const;
			private:
				
				graphics::Shader* m_shader;
				graphics::Texture* m_texture;
				ID3D11UnorderedAccessView* m_particleUAV1;
				ID3D11ShaderResourceView* m_particleSRV1;
				ID3D11Buffer* m_particleBuffer1;
				ID3D11UnorderedAccessView* m_particleUAV2;
				ID3D11ShaderResourceView* m_particleSRV2;
				ID3D11Buffer* m_particleBuffer2;
				bool m_booleanSwapUAVandSRV;

				ID3D11ComputeShader* s_particlesCS;
				ID3D11Buffer* m_particleBuffer;

				InitParticleBufferStruct m_particleBufferStruct;

				bool m_isEmitting;

				bool m_shouldUpdateResources;
				unsigned int m_nrOfParticles;
			};
		}
	}
}
