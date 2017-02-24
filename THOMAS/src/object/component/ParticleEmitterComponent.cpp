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
				std::srand(time(NULL));
				m_shouldUpdateResources = false;
				m_nrOfParticles = 255;//256 * 100 + 254;
				m_isEmitting = false;

				m_particleBufferStruct.direction = math::Vector3(1, 0, 0);
				m_particleBufferStruct.maxDelay = 1.0f;
				m_particleBufferStruct.minDelay = 1.0f;
				m_particleBufferStruct.maxSpeed = 1.0f;
				m_particleBufferStruct.minSpeed = 1.0f;
				m_particleBufferStruct.position = math::Vector3(0, 0, 0);
				m_particleBufferStruct.spread = 1.0f;
				m_particleBufferStruct.maxSize = 1.0f;
				m_particleBufferStruct.minSize = 1.0f;
				m_particleBufferStruct.maxLifeTime = 1.0f;
				m_particleBufferStruct.minLifeTime = 1.0f;
				m_particleBufferStruct.alpha = 1.0f;

				m_particleBufferStruct.rand = (std::rand() % 1000) / 1000.f;

				m_shader = graphics::Shader::GetShaderByName("particleShader");
				m_texture = graphics::Texture::CreateTexture(thomas::graphics::Texture::SamplerState::WRAP, thomas::graphics::Texture::TextureType::DIFFUSE, "../res/textures/standardParticle.png");
				m_booleanSwapUAVandSRV = true;

				ID3DBlob* shaderBlob = thomas::graphics::Shader::Compile("../res/shaders/initParticles.hlsl", "cs_5_0", "main");
				HRESULT hr = ThomasCore::GetDevice()->CreateComputeShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &s_particlesCS);
				if (FAILED(hr))
				{
					LOG_HR(hr);
				}

				CreateParticleUAVsandSRVs();
				CreateInitBuffer();
				InitialDispatch();
			}

			void ParticleEmitterComponent::Update()
			{
				if (m_shouldUpdateResources)
				{
					m_particleBufferStruct.rand = (std::rand() % 1000) / 1000.f;
					utils::D3d::FillDynamicBufferStruct(m_particleBuffer, m_particleBufferStruct);
					InitialDispatch();
					m_shouldUpdateResources = false;
				}
			}

			void thomas::object::component::ParticleEmitterComponent::Destroy()
			{

			}

			void thomas::object::component::ParticleEmitterComponent::SetAll(_In_opt_ unsigned int nrOfParticles, _In_opt_ math::Vector3 particleDirection, _In_opt_ float minDelay, _In_opt_ float maxDelay, _In_opt_ float minSpeed,
				_In_opt_ float maxSpeed, _In_opt_ float particleSpreadFactor, _In_opt_ float particleMinSize, _In_opt_ float particleMaxSize, _In_opt_ float particleMinLifeTime, _In_opt_ float particleMaxLifeTime, _In_opt_ float alpha)
			{
				if (nrOfParticles)
					m_nrOfParticles = nrOfParticles;//256 * 100 + 254;
				if (particleDirection != math::Vector3(NULL, NULL, NULL))
					m_particleBufferStruct.direction = particleDirection;
				if (minDelay)
					m_particleBufferStruct.maxDelay = maxDelay;
				if (maxDelay)
					m_particleBufferStruct.minDelay = minDelay;
				if (minSpeed)
					m_particleBufferStruct.maxSpeed = maxSpeed;
				if (maxSpeed)
					m_particleBufferStruct.minSpeed = minSpeed;
				if (particleSpreadFactor)
					m_particleBufferStruct.spread = particleSpreadFactor;
				if (particleMinSize)
					m_particleBufferStruct.minSize = particleMinSize;
				if (particleMaxSize)
					m_particleBufferStruct.maxSize = particleMaxSize;
				if (particleMinLifeTime)
					m_particleBufferStruct.minLifeTime = particleMinLifeTime;
				if (particleMaxLifeTime)
					m_particleBufferStruct.maxLifeTime = particleMaxLifeTime;
				if (alpha)
					m_particleBufferStruct.alpha;

				m_shouldUpdateResources = true;
			}

			void ParticleEmitterComponent::SetPosition(math::Vector3 other)
			{
				m_particleBufferStruct.position = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetSpread(float other)
			{
				m_particleBufferStruct.spread = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetDirection(math::Vector3 other)
			{
				m_particleBufferStruct.direction = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMinSpeed(float other)
			{
				m_particleBufferStruct.minSpeed = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMaxSpeed(float other)
			{
				m_particleBufferStruct.maxSpeed = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMinDelay(float other)
			{
				m_particleBufferStruct.minDelay = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMaxDelay(float other)
			{
				m_particleBufferStruct.maxDelay = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMinSize(float other)
			{
				m_particleBufferStruct.minSize = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMaxSize(float other)
			{
				m_particleBufferStruct.maxSize = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMinLifeTime(float other)
			{
				m_particleBufferStruct.minLifeTime = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMaxLifeTime(float other)
			{
				m_particleBufferStruct.maxLifeTime = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetAlpha(float other)
			{
				m_particleBufferStruct.alpha = other;
				m_shouldUpdateResources = true;
			}

			void ParticleEmitterComponent::StartEmitting()
			{
				m_isEmitting = true;

			}

			void ParticleEmitterComponent::StopEmitting()
			{
				m_isEmitting = false;
			}

			bool ParticleEmitterComponent::IsEmitting() const
			{
				return m_isEmitting;
			}


			void ParticleEmitterComponent::SwapUAVsandSRVs(ID3D11UnorderedAccessView*& uav, ID3D11ShaderResourceView*& srv)//ping pong
			{
				if (m_booleanSwapUAVandSRV)
				{
					m_booleanSwapUAVandSRV = false;
				}
				else
				{
					m_booleanSwapUAVandSRV = true;
				}

				if (m_booleanSwapUAVandSRV)
				{
					uav = m_particleUAV1;
					srv = m_particleSRV2;
				}
				else
				{
					uav = m_particleUAV2;
					srv = m_particleSRV1;
				}
			}

			void ParticleEmitterComponent::SetNrOfParticles(unsigned int other)
			{
				m_nrOfParticles = other;
				m_shouldUpdateResources = true;
			}

			void ParticleEmitterComponent::SetShader(std::string shaderName)
			{
				m_shader = graphics::Shader::GetShaderByName(shaderName);
				m_shouldUpdateResources = true;
			}

			graphics::Shader * ParticleEmitterComponent::GetShader()
			{
				return m_shader;
			}

			void ParticleEmitterComponent::SetTexture(std::string texturePath)
			{
				m_texture = graphics::Texture::CreateTexture(thomas::graphics::Texture::SamplerState::WRAP, thomas::graphics::Texture::TextureType::DIFFUSE, texturePath);
				m_shouldUpdateResources = true;
			}

			graphics::Texture * ParticleEmitterComponent::GetTexture()
			{
				return m_texture;
			}

			void ParticleEmitterComponent::CreateParticleUAVsandSRVs()
			{
				UINT bytewidth = sizeof(ParticleStruct) * m_nrOfParticles;
				UINT structurebytestride = sizeof(ParticleStruct);
				utils::D3d::CreateBufferAndUAV(NULL, bytewidth, structurebytestride, m_particleBuffer1, m_particleUAV1, m_particleSRV1);
				utils::D3d::CreateBufferAndUAV(NULL, bytewidth, structurebytestride, m_particleBuffer2, m_particleUAV2, m_particleSRV2);
			}

			void ParticleEmitterComponent::CreateInitBuffer()
			{
				m_particleBuffer = thomas::utils::D3d::CreateDynamicBufferFromStruct(m_particleBufferStruct, D3D11_BIND_CONSTANT_BUFFER);
			}

			void thomas::object::component::ParticleEmitterComponent::InitialDispatch()
			{
				ID3D11UnorderedAccessView* nulluav[1] = { NULL };
				ThomasCore::GetDeviceContext()->CSSetShader(s_particlesCS, 0, NULL);

				ThomasCore::GetDeviceContext()->CSSetConstantBuffers(0, 1, &m_particleBuffer);

				ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &m_particleUAV2, NULL);
				ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(1, 1, &m_particleUAV1, NULL);

				ThomasCore::GetDeviceContext()->Dispatch(GetNrOfParticles() / 256 + 1, 1, 1);

				ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, nulluav, NULL);
				ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(1, 1, nulluav, NULL);
			}

			unsigned int thomas::object::component::ParticleEmitterComponent::GetNrOfParticles() const
			{
				return m_nrOfParticles;
			}

			
		}
	}
}