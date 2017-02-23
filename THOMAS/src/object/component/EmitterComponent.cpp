#include "EmitterComponent.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{
			thomas::object::component::EmitterComponent::EmitterComponent() : Component("EmitterComponent")
			{

			}

			void thomas::object::component::EmitterComponent::Init(unsigned int nrOfParticles, bool emitterState, math::Vector3 particleDirection, float minDelay, float maxDelay, float minSpeed, float maxSpeed, 
				math::Vector3 emitterPosition, float particleSpreadFactor, float particleMinSize, float particleMaxSize, float particleMinLifeTime, float particleMaxLifeTime, std::string shaderName, std::string texturePath)
			{
				m_nrOfParticles = nrOfParticles;//256 * 100 + 254;
				m_isEmitting = emitterState;

				m_initParticleBufferStruct.initDirection = particleDirection;
				m_initParticleBufferStruct.initMaxDelay = maxDelay;
				m_initParticleBufferStruct.initMinDelay = minDelay;
				m_initParticleBufferStruct.initMaxSpeed = maxSpeed;
				m_initParticleBufferStruct.initMinSpeed = minSpeed;
				m_initParticleBufferStruct.initPosition = emitterPosition;
				m_initParticleBufferStruct.initSpread = particleSpreadFactor;
				m_initParticleBufferStruct.initMaxSize = particleMaxSize;
				m_initParticleBufferStruct.initMinSize = particleMinSize;
				m_initParticleBufferStruct.initMaxLifeTime = particleMaxLifeTime;
				m_initParticleBufferStruct.initMinLifeTime = particleMinLifeTime;
				m_initParticleBufferStruct.rand = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

				m_shader = graphics::Shader::GetShaderByName(shaderName);
				m_texture = graphics::Texture::CreateTexture(thomas::graphics::Texture::SamplerState::WRAP, thomas::graphics::Texture::TextureType::DIFFUSE, texturePath);
				m_booleanSwapUAVandSRV = true;

				ID3DBlob* shaderBlob = thomas::graphics::Shader::Compile("../res/shaders/initParticles.hlsl", "cs_5_0", "main");
				HRESULT hr = ThomasCore::GetDevice()->CreateComputeShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &s_initParticlesCS);
				if (FAILED(hr))
				{
					LOG_HR(hr);
				}

				CreateParticleUAVsandSRVs();
				CreateInitBuffer();
				InitialDispatch();

				return;
			}

			void thomas::object::component::EmitterComponent::Destroy()
			{

			}

			void thomas::object::component::EmitterComponent::Update(_In_opt_ unsigned int nrOfParticles, _In_opt_ math::Vector3 particleDirection, _In_opt_ float minDelay, _In_opt_ float maxDelay, _In_opt_ float minSpeed,
				_In_opt_ float maxSpeed, _In_opt_ float particleSpreadFactor, _In_opt_ float particleMinSize, _In_opt_ float particleMaxSize, _In_opt_ float particleMinLifeTime, _In_opt_ float particleMaxLifeTime)
			{
				if (nrOfParticles)
					m_nrOfParticles = nrOfParticles;//256 * 100 + 254;
				if (particleDirection != math::Vector3(NULL, NULL, NULL))
					m_initParticleBufferStruct.initDirection = particleDirection;
				if (minDelay)
					m_initParticleBufferStruct.initMaxDelay = maxDelay;
				if (maxDelay)
					m_initParticleBufferStruct.initMinDelay = minDelay;
				if (minSpeed)
					m_initParticleBufferStruct.initMaxSpeed = maxSpeed;
				if (maxSpeed)
					m_initParticleBufferStruct.initMinSpeed = minSpeed;
				if (particleSpreadFactor)
					m_initParticleBufferStruct.initSpread = particleSpreadFactor;
				if (particleMinSize)
					m_initParticleBufferStruct.initMinSize = particleMinSize;
				if (particleMaxSize)
					m_initParticleBufferStruct.initMaxSize = particleMaxSize;
				if (particleMinLifeTime)
					m_initParticleBufferStruct.initMinLifeTime = particleMinLifeTime;
				if (particleMaxLifeTime)
					m_initParticleBufferStruct.initMaxLifeTime = particleMaxLifeTime;

				ThomasCore::GetDeviceContext()->UpdateSubresource(m_initParicleBuffer, 0, 0, &m_initParticleBufferStruct, 0, 0);
				InitialDispatch();
			}

			void thomas::object::component::EmitterComponent::Emit()
			{
				m_isEmitting = true;

			}

			bool thomas::object::component::EmitterComponent::IsEmitting() const
			{
				return m_isEmitting;
			}


			void EmitterComponent::SwapUAVsandSRVs(ID3D11UnorderedAccessView*& uav, ID3D11ShaderResourceView*& srv)//ping pong
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

			graphics::Shader * EmitterComponent::GetShader()
			{
				return m_shader;
			}

			graphics::Texture * EmitterComponent::GetTexture()
			{
				return m_texture;
			}

			void thomas::object::component::EmitterComponent::CreateParticleUAVsandSRVs()
			{
				UINT bytewidth = sizeof(ParticleStruct) * m_nrOfParticles;
				UINT structurebytestride = sizeof(ParticleStruct);
				thomas::utils::D3d::CreateBufferAndUAV(NULL, bytewidth, structurebytestride, m_particleBuffer1, m_particleUAV1, m_particleSRV1);
				thomas::utils::D3d::CreateBufferAndUAV(NULL, bytewidth, structurebytestride, m_particleBuffer2, m_particleUAV2, m_particleSRV2);
			}

			void thomas::object::component::EmitterComponent::CreateInitBuffer()
			{
				m_initParicleBuffer = thomas::utils::D3d::CreateBufferFromStruct(m_initParticleBufferStruct, D3D11_BIND_CONSTANT_BUFFER);
			}

			void thomas::object::component::EmitterComponent::InitialDispatch()
			{
				ID3D11UnorderedAccessView* nulluav[1] = { NULL };
				ThomasCore::GetDeviceContext()->CSSetShader(s_initParticlesCS, 0, NULL);

				ThomasCore::GetDeviceContext()->CSSetConstantBuffers(0, 1, &m_initParicleBuffer);

				ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &m_particleUAV2, NULL);
				ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(1, 1, &m_particleUAV1, NULL);

				ThomasCore::GetDeviceContext()->Dispatch(GetNrOfParticles() / 256 + 1, 1, 1);

				ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, nulluav, NULL);
				ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(1, 1, nulluav, NULL);
			}

			void thomas::object::component::EmitterComponent::Stop()
			{
				m_isEmitting = false;
			}

			unsigned int thomas::object::component::EmitterComponent::GetNrOfParticles() const
			{
				return m_nrOfParticles;
			}

			
		}
	}
}