#include "ParticleEmitterComponent.h"
#include <cstdlib>
#include <ctime>

namespace thomas
{
	namespace object
	{
		namespace component
		{
			thomas::object::component::ParticleEmitterComponent::ParticleEmitterComponent() : Component("ParticleEmitterComponent")
			{

			}

			void ParticleEmitterComponent::Start()
			{
				m_shouldUpdateResources = true;
				m_emissionDuration = 1.0;
				m_emissionTimeLeft = m_emissionDuration;
				m_emissionTimer = 0;
				m_emissionRate = 1.0;
				m_looping = false;
				m_maxNrOfParticles = 0;//256 * 100 + 254;
				m_isEmitting = false;

				m_particleBufferStruct.position = math::Vector3(0, 0, 0);
				m_particleBufferStruct.spread = 1.0f;
				m_particleBufferStruct.directionMatrix = math::Matrix::CreateLookAt(math::Vector3(0,0,0),math::Vector3(1, 0, 0),math::Vector3::Up).Transpose();
				m_particleBufferStruct.maxSpeed = 0.0f;
				m_particleBufferStruct.minSpeed = 0.0f;
				m_particleBufferStruct.endSpeed = 0.0f;
				m_particleBufferStruct.maxDelay = 0.0f;
				m_particleBufferStruct.minDelay = 0.0f;
				m_particleBufferStruct.maxSize = 1.0f;
				m_particleBufferStruct.minSize = 1.0f;
				m_particleBufferStruct.endSize = 1.0f;
				m_particleBufferStruct.maxLifeTime = 1.0f;
				m_particleBufferStruct.minLifeTime = 1.0f;
				m_particleBufferStruct.rotationSpeed = 0.0f;
				m_particleBufferStruct.rotation = math::PI / 2;
				m_particleBufferStruct.startColor = math::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
				m_particleBufferStruct.endColor = math::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
				m_particleBufferStruct.currentParticleStartIndex = 0;

				m_particleBufferStruct.rand = (std::rand() % 1000) / 1000.f;

				m_shader = graphics::Shader::GetShaderByName("particleShader");
				m_texture = graphics::Texture::CreateTexture(thomas::graphics::Texture::SamplerState::WRAP, thomas::graphics::Texture::TextureType::DIFFUSE, "../res/textures/standardParticle.png");
				m_d3dData.swapUAVandSRV = true;


				CalculateMaxNrOfParticles();
				CreateInitBuffer();
			}

			void ParticleEmitterComponent::Update()
			{

				if (m_emissionTimeLeft < 0.0f)
					StopEmitting();

				if (m_isEmitting)
				{
					if (!m_looping)
						m_emissionTimeLeft -= Time::GetDeltaTime();

					m_emissionTimer += Time::GetDeltaTime();
					UINT numberOfParticlesToEmit = m_emissionTimer / (1.0f / m_emissionRate);
					if (numberOfParticlesToEmit > 0)
					{
						m_emissionTimer = 0;
						if (m_shouldUpdateResources)
						{
							m_shouldUpdateResources = false;
							CreateParticleUAVsandSRVs();
						}
						m_particleBufferStruct.position = m_gameObject->m_transform->GetPosition();
						m_particleBufferStruct.rand = (std::rand() % 1000) / 1000.f;
						utils::D3d::FillDynamicBufferStruct(m_d3dData.particleBuffer, m_particleBufferStruct);
						graphics::ParticleSystem::SpawnParticles(this, numberOfParticlesToEmit);
						m_particleBufferStruct.currentParticleStartIndex = (m_particleBufferStruct.currentParticleStartIndex + numberOfParticlesToEmit) % m_maxNrOfParticles;
					}
				}





			}

			void thomas::object::component::ParticleEmitterComponent::Destroy()
			{
				SAFE_RELEASE(m_d3dData.particleBuffer1);
				SAFE_RELEASE(m_d3dData.particleBuffer2);
				SAFE_RELEASE(m_d3dData.particleUAV1);
				SAFE_RELEASE(m_d3dData.particleUAV2);
				SAFE_RELEASE(m_d3dData.particleSRV1);
				SAFE_RELEASE(m_d3dData.particleSRV2);
				SAFE_RELEASE(m_d3dData.billboardBuffer);
				SAFE_RELEASE(m_d3dData.billboardsSRV);
				SAFE_RELEASE(m_d3dData.billboardsUAV);
			}

			void ParticleEmitterComponent::SetSpread(float const other)
			{
				m_particleBufferStruct.spread = other;
			}
			void ParticleEmitterComponent::SetDirection(math::Vector3 other)
			{
				other.x += 0.0000001;
				m_particleBufferStruct.directionMatrix = math::Matrix::CreateLookAt(math::Vector3(0, 0, 0), -other, math::Vector3::Up).Invert().Transpose();
			}
			void ParticleEmitterComponent::SetDirection(float const x, float const y, float const z)
			{
				SetDirection(math::Vector3(x, y, z));
			}
			void ParticleEmitterComponent::SetSpeed(float const min, float const max)
			{
				SetMinSpeed(min);
				SetMaxSpeed(max);
			}
			void ParticleEmitterComponent::SetSpeed(float const speed)
			{
				SetSpeed(speed, speed);
				SetEndSpeed(speed);
			}
			void ParticleEmitterComponent::SetMaxSpeed(float const other)
			{
				m_particleBufferStruct.maxSpeed = other;
			}
			void ParticleEmitterComponent::SetMinSpeed(float const other)
			{
				m_particleBufferStruct.minSpeed = other;
			}
			void ParticleEmitterComponent::SetEndSpeed(float const other)
			{
				m_particleBufferStruct.endSpeed = other;
			}
			void ParticleEmitterComponent::SetDelay(float const min, float const max)
			{
				SetMinDelay(min);
				SetMaxDelay(max);
			}
			void ParticleEmitterComponent::SetDelay(float const delay)
			{
				SetDelay(delay, delay);

			}
			void ParticleEmitterComponent::SetMaxDelay(float const other)
			{
				m_particleBufferStruct.maxDelay = other;
				CalculateMaxNrOfParticles();
			}
			void ParticleEmitterComponent::SetMinDelay(float const other)
			{
				m_particleBufferStruct.minDelay = other;
			}
			void ParticleEmitterComponent::SetSize(float const min, float const max)
			{
				SetMinSize(min);
				SetMaxSize(max);
			}
			void ParticleEmitterComponent::SetSize(float const size)
			{
				SetSize(size, size);
				SetEndSize(size);
			}
			void ParticleEmitterComponent::SetMaxSize(float const other)
			{
				m_particleBufferStruct.maxSize = other;
			}
			void ParticleEmitterComponent::SetMinSize(float const other)
			{
				m_particleBufferStruct.minSize = other;
			}
			void ParticleEmitterComponent::SetEndSize(float const other)
			{
				m_particleBufferStruct.endSize = other;
			}
			void ParticleEmitterComponent::SetLifeTime(float const min, float const max)
			{
				SetMinLifeTime(min);
				SetMaxLifeTime(max);
			}
			void ParticleEmitterComponent::SetLifeTime(float lifeTime)
			{
				SetLifeTime(lifeTime, lifeTime);

			}
			void ParticleEmitterComponent::SetMinLifeTime(float const other)
			{
				m_particleBufferStruct.minLifeTime = other;
			}
			void ParticleEmitterComponent::SetMaxLifeTime(float const other)
			{
				m_particleBufferStruct.maxLifeTime = other;
				CalculateMaxNrOfParticles();
			}
			void ParticleEmitterComponent::SetRotationSpeed(float const other)
			{
				m_particleBufferStruct.rotationSpeed = other;
			}
			void ParticleEmitterComponent::SetRotation(float const other)
			{
				m_particleBufferStruct.rotation = other;
			}
			void ParticleEmitterComponent::SetLooping(bool const other)
			{
				m_looping = other;
			}
			void ParticleEmitterComponent::SetStartColor(math::Vector4 const other)
			{
				m_particleBufferStruct.startColor = other;
			}
			void ParticleEmitterComponent::SetEndColor(math::Vector4 const other)
			{
				m_particleBufferStruct.endColor = other;
			}

			void ParticleEmitterComponent::StartEmitting()
			{
				m_isEmitting = true;
				m_emissionTimeLeft = m_emissionDuration;

			}

			void ParticleEmitterComponent::StopEmitting()
			{
				m_isEmitting = false;
			}

			bool ParticleEmitterComponent::IsEmitting() const
			{
				return m_isEmitting;
			}


			void ParticleEmitterComponent::SetShader(std::string shaderName)
			{
				m_shader = graphics::Shader::GetShaderByName(shaderName);
			}

			graphics::Shader * ParticleEmitterComponent::GetShader()
			{
				return m_shader;
			}

			void ParticleEmitterComponent::SetTexture(std::string texturePath)
			{
				m_texture = graphics::Texture::CreateTexture(thomas::graphics::Texture::SamplerState::WRAP, thomas::graphics::Texture::TextureType::DIFFUSE, texturePath);
			}

			graphics::Texture * ParticleEmitterComponent::GetTexture()
			{
				return m_texture;
			}

			void ParticleEmitterComponent::CreateParticleUAVsandSRVs()
			{
				SAFE_RELEASE(m_d3dData.particleBuffer1);
				SAFE_RELEASE(m_d3dData.particleBuffer2);
				SAFE_RELEASE(m_d3dData.particleUAV1);
				SAFE_RELEASE(m_d3dData.particleUAV2);
				SAFE_RELEASE(m_d3dData.particleSRV1);
				SAFE_RELEASE(m_d3dData.particleSRV2);
				SAFE_RELEASE(m_d3dData.billboardBuffer);
				SAFE_RELEASE(m_d3dData.billboardsSRV);
				SAFE_RELEASE(m_d3dData.billboardsUAV);
				UINT bytewidth = sizeof(ParticleStruct) * m_maxNrOfParticles;
				UINT structurebytestride = sizeof(ParticleStruct);
				utils::D3d::CreateBufferAndUAV(NULL, bytewidth, structurebytestride, m_d3dData.particleBuffer1, m_d3dData.particleUAV1, m_d3dData.particleSRV1);
				utils::D3d::CreateBufferAndUAV(NULL, bytewidth, structurebytestride, m_d3dData.particleBuffer2, m_d3dData.particleUAV2, m_d3dData.particleSRV2);
				graphics::ParticleSystem::CreateBillboardUAVandSRV(m_maxNrOfParticles, m_d3dData.billboardBuffer, m_d3dData.billboardsUAV, m_d3dData.billboardsSRV);
			}

			void ParticleEmitterComponent::CreateInitBuffer()
			{
				m_d3dData.particleBuffer = thomas::utils::D3d::CreateDynamicBufferFromStruct(m_particleBufferStruct, D3D11_BIND_CONSTANT_BUFFER);
			}


			void ParticleEmitterComponent::CalculateMaxNrOfParticles()
			{
				m_maxNrOfParticles = (m_particleBufferStruct.maxLifeTime + m_particleBufferStruct.maxDelay)*m_emissionRate;
				m_maxNrOfParticles += m_emissionRate + 1; //add some padding :)
				m_shouldUpdateResources = true;
				
			}

			void ParticleEmitterComponent::SetEmissionRate(float emissionRate)
			{
				m_emissionRate = emissionRate;
				CalculateMaxNrOfParticles();
			}

			void ParticleEmitterComponent::SetEmissionDuration(float duration)
			{
				m_emissionDuration = duration;
				m_emissionTimeLeft = m_emissionDuration;
			}

			float ParticleEmitterComponent::GetEmissionRate()
			{
				return m_emissionRate;
			}

			unsigned int ParticleEmitterComponent::GetNrOfMaxParticles() const
			{
				return m_maxNrOfParticles;
			}

			ParticleEmitterComponent::D3DData * ParticleEmitterComponent::GetD3DData()
			{
				return &m_d3dData;
			}


		}
	}
}