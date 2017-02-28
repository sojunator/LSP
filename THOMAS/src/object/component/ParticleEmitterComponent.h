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
					float spread;//This is a hack

					math::Vector3 direction;
					float maxSpeed;

					float minSpeed;
					float endSpeed;
					float maxDelay;
					float minDelay;

					float maxSize;
					float minSize;
					float endSize;
					float maxLifeTime;

					float minLifeTime;
					float rand;
					float rotationSpeed;
					float rotation;

					math::Vector4 startColor;

					math::Vector4 endColor;

					bool looping;
					math::Vector3 pad;
				};

				struct ParticleStruct
				{
					math::Vector3 position;
					float spread;

					math::Vector3 direction;
					float speed;

					float endSpeed;
					float delay;
					float size;
					float endSize;

					float lifeTimeLeft;
					float timeElapsed;
					float rotationSpeed;
					float rotation;

					math::Vector4 startColor;

					math::Vector4 endColor;

					math::Vector3 initPosition;
					bool looping;
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

				void SetPosition(math::Vector3 const other);
				void SetSpread(float const other);
				void SetDirection(math::Vector3 const other);
				void SetMaxSpeed(float const other);
				void SetMinSpeed(float const other);
				void SetEndSpeed(float const other);
				void SetMaxDelay(float const other);
				void SetMinDelay(float const other);
				void SetMaxSize(float const other);
				void SetMinSize(float const other);
				void SetEndSize(float const other);
				void SetMaxLifeTime(float const other);
				void SetMinLifeTime(float const other);
				void SetRotationSpeed(float const other);
				void SetRotation(float const other);
				void SetLooping(bool const other);
				void SetStartColor(math::Vector4 const other);
				void SetEndColor(math::Vector4 const other);
				
				

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

				graphics::Shader* m_particlesCS;
				ID3D11Buffer* m_particleBuffer;

				InitParticleBufferStruct m_particleBufferStruct;

				bool m_isEmitting;

				bool m_shouldUpdateResources;
				unsigned int m_nrOfParticles;
			};
		}
	}
}
