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
			class EmitterComponent : public Component
			{
			public:
				
				struct InitParticleBufferStruct
				{
					math::Vector3 initPosition;
					float initSpread;
					math::Vector3 initDirection;
					float initMaxSpeed;
					float initMinSpeed;
					float initMaxDelay;
					float initMinDelay;
					float initSize;
					float initLifeTime;
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
					float pad;
				};
			private:
				void CreateParticleUAVsandSRVs();
				void CreateInitBuffer();
				void InitialDispatch();

			public:
				EmitterComponent();
				void Init(unsigned int nrOfParticles, bool emitterState, math::Vector3 particleDirection, float minDelay, float maxDelay, float minSpeed, float maxSpeed, 
					math::Vector3 emitterPosition, float particleSpreadFactor, float particleSize, float particleLifeTime, std::string shaderName, std::string texturePath);
				void Destroy();
				void Update(unsigned int nrOfParticles, math::Vector3 particleDirection, float minDelay, float maxDelay, float minSpeed, float maxSpeed,
					float particleSpreadFactor, float particleSize, float particleLifeTime);
				void Emit();
				void Stop();
				unsigned int GetNrOfParticles() const;
				bool IsEmitting() const;
				
				void SwapUAVsandSRVs(ID3D11UnorderedAccessView*& uav, ID3D11ShaderResourceView*& srv);//ping pong
				
				graphics::Shader* GetShader();
				graphics::Texture* GetTexture();
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

				ID3D11ComputeShader* s_initParticlesCS;
				ID3D11Buffer* m_initParicleBuffer;

				std::string m_name;
				InitParticleBufferStruct m_initParticleBufferStruct;

				bool m_isEmitting;

				unsigned int m_nrOfParticles;
			};
		}
	}
}
