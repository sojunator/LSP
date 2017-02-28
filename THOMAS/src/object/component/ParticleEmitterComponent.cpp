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
				m_shouldUpdateResources = false;
				m_nrOfParticles = 255;//256 * 100 + 254;
				m_isEmitting = false;

				m_particleBufferStruct.position = math::Vector3(0, 0, 0);
				m_particleBufferStruct.spread = 1.0f;
				m_particleBufferStruct.direction = math::Vector3(1, 0, 0);
				m_particleBufferStruct.maxSpeed = 1.0f;
				m_particleBufferStruct.minSpeed = 1.0f;
				m_particleBufferStruct.endSpeed = 1.0f;
				m_particleBufferStruct.maxDelay = 1.0f;
				m_particleBufferStruct.minDelay = 1.0f;
				m_particleBufferStruct.maxSize = 1.0f;
				m_particleBufferStruct.minSize = 1.0f;
				m_particleBufferStruct.endSize = 1.0f;
				m_particleBufferStruct.maxLifeTime = 1.0f;
				m_particleBufferStruct.minLifeTime = 1.0f;
				m_particleBufferStruct.rotationSpeed = 0.5f;
				m_particleBufferStruct.looping = false;
				m_particleBufferStruct.startColor = math::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
				m_particleBufferStruct.endColor = math::Vector4(1.0f, 1.0f, 1.0f, 1.0f);

				m_particleBufferStruct.rand = (std::rand() % 1000) / 1000.f;

				m_shader = graphics::Shader::GetShaderByName("particleShader");
				m_texture = graphics::Texture::CreateTexture(thomas::graphics::Texture::SamplerState::WRAP, thomas::graphics::Texture::TextureType::DIFFUSE, "../res/textures/standardParticle.png");
				m_booleanSwapUAVandSRV = true;

				m_particlesCS = graphics::Shader::GetShaderByName("InitParticleCS");

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


			void ParticleEmitterComponent::SetPosition(math::Vector3 const other)
			{
				m_particleBufferStruct.position = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetSpread(float const other)
			{
				m_particleBufferStruct.spread = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetDirection(math::Vector3 const other)
			{
				m_particleBufferStruct.direction = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMaxSpeed(float const other)
			{
				m_particleBufferStruct.maxSpeed = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMinSpeed(float const other)
			{
				m_particleBufferStruct.minSpeed = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetEndSpeed(float const other)
			{
				m_particleBufferStruct.endSpeed = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMaxDelay(float const other)
			{
				m_particleBufferStruct.maxDelay = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMinDelay(float const other)
			{
				m_particleBufferStruct.minDelay = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMaxSize(float const other)
			{
				m_particleBufferStruct.maxSize = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMinSize(float const other)
			{
				m_particleBufferStruct.minSize = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetEndSize(float const other)
			{
				m_particleBufferStruct.endSize = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMinLifeTime(float const other)
			{
				m_particleBufferStruct.minLifeTime = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetMaxLifeTime(float const other)
			{
				m_particleBufferStruct.maxLifeTime = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetRotationSpeed(float const other)
			{
				m_particleBufferStruct.rotationSpeed = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetLooping(bool const other)
			{
				m_particleBufferStruct.looping = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetStartColor(math::Vector4 const other)
			{
				m_particleBufferStruct.startColor = other;
				m_shouldUpdateResources = true;
			}
			void ParticleEmitterComponent::SetEndColor(math::Vector4 const other)
			{
				m_particleBufferStruct.endColor = other;
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
				m_particlesCS->Bind();
				m_particlesCS->BindBuffer(m_particleBuffer, 0);
				m_particlesCS->BindUAV(m_particleUAV2, 0);
				m_particlesCS->BindUAV(m_particleUAV1, 1);

				ThomasCore::GetDeviceContext()->Dispatch(GetNrOfParticles() / 256 + 1, 1, 1);

				m_particlesCS->BindUAV(NULL, 0);
				m_particlesCS->BindUAV(NULL, 0);
				m_particlesCS->BindBuffer(NULL, 0);
				m_particlesCS->Unbind();
			}

			unsigned int thomas::object::component::ParticleEmitterComponent::GetNrOfParticles() const
			{
				return m_nrOfParticles;
			}

			
		}
	}
}