#include "Renderer.h"
#include "Model.h"
#include "../object/GameObject.h"
#include "../object/component/Light.h"
#include "PostEffect.h"
#include "LightManager.h"

namespace thomas
{
	namespace graphics
	{

		ID3D11RenderTargetView* Renderer::s_backBuffer = NULL;
		ID3D11ShaderResourceView* Renderer::s_backBufferSRV = NULL;
		ID3D11RasterizerState* Renderer::s_rasterState = NULL;
		ID3D11RasterizerState* Renderer::s_wireframeRasterState = NULL;
		ID3D11DepthStencilState* Renderer::s_depthStencilState = NULL;
		ID3D11DepthStencilView* Renderer::s_depthStencilView = NULL;
		ID3D11ShaderResourceView* Renderer::s_depthBufferSRV = NULL;

		ID3D11Buffer* Renderer::s_objectBuffer;
		Renderer::GameObjectBuffer Renderer::s_objectBufferStruct;

		bool thomas::graphics::Renderer::Init()
		{

			if (utils::D3d::InitRenderer(s_backBuffer,s_backBufferSRV, s_depthStencilState, s_depthStencilView, s_depthBufferSRV))
			{
				s_objectBuffer = utils::D3d::CreateBufferFromStruct(s_objectBufferStruct, D3D11_BIND_CONSTANT_BUFFER);
				s_rasterState = utils::D3d::CreateRasterizer(D3D11_FILL_SOLID, D3D11_CULL_BACK);
				s_wireframeRasterState = utils::D3d::CreateRasterizer(D3D11_FILL_WIREFRAME, D3D11_CULL_BACK);
				return true;

			}
			return false;
		}

		void thomas::graphics::Renderer::Clear()
		{
			float color[4] = { 0.3f, 0.4f, 0.3f, 1.0f };
			ThomasCore::GetDeviceContext()->ClearRenderTargetView(s_backBuffer, color);
			ThomasCore::GetDeviceContext()->ClearDepthStencilView(s_depthStencilView, D3D11_CLEAR_DEPTH, 1, 0);

		}

		void thomas::graphics::Renderer::Render()
		{




			//TODO: Find out if this is the fastest order of things.

			for (object::component::Camera* camera : GetCameras()) //Render for every camera;
			{
				Clear();

				ThomasCore::GetDeviceContext()->OMSetRenderTargets(1, &s_backBuffer, s_depthStencilView);
				ThomasCore::GetDeviceContext()->RSSetViewports(1, camera->GetViewport().Get11());

				ThomasCore::GetDeviceContext()->OMSetDepthStencilState(s_depthStencilState, 1);


				std::vector<Shader*> loadedShaders = Shader::GetLoadedShaders();

				ThomasCore::GetDeviceContext()->RSSetState(s_rasterState);

				for (Material* mat : Material::GetLoadedMaterials())
				{
					mat->Update();
				}

				for (PostEffect* fx : PostEffect::GetLoadedPostEffects())
				{
					fx->Update();
				}

				if (Input::GetKey(Input::Keys::X))
				{
					ThomasCore::GetDeviceContext()->RSSetState(s_wireframeRasterState);
				}
				else
				{
					ThomasCore::GetDeviceContext()->RSSetState(s_rasterState);
				}

				//For every shader
				for (Shader* shader : loadedShaders)
				{

					shader->Bind();

					LightManager::BindAllLights();
					camera->BindReflection();
					//Get the materials that use the shader
					for (Material* mat : Material::GetMaterialsByShader(shader))
					{
						mat->Bind(); //Bind material specific buffers/textures
										//Get all gameObjects that have a rendererComponent


						for (object::GameObject* gameObject : object::GameObject::FindGameObjectsWithComponent<object::component::RenderComponent>())
						{
							object::component::RenderComponent* renderComponent = gameObject->GetComponent<object::component::RenderComponent>();
							Model* model = renderComponent->GetModel();

							BindGameObjectBuffer(camera, gameObject);
							//Draw every mesh of gameObjects model that has
							if (model)
							{
								for (Mesh* mesh : model->GetMeshesByMaterial(mat))
								{
									mesh->Bind(); //bind vertex&index buffer
									mesh->Draw();
								}
							}
							UnBindGameObjectBuffer();

						}
						mat->Unbind();
					}

					LightManager::Unbind();

					shader->Unbind();
				}
				camera->BindSkybox();
				camera->UnbindSkybox();

				PostEffect::Render(s_backBufferSRV, s_backBuffer, camera);

				ThomasCore::GetSwapChain()->Present(0, 0);
			}

		}

		bool Renderer::Destroy()
		{
			SAFE_RELEASE(s_backBuffer);
			SAFE_RELEASE(s_rasterState);
			SAFE_RELEASE(s_depthStencilState);
			SAFE_RELEASE(s_depthStencilView);
			SAFE_RELEASE(s_objectBuffer);

			return true;

		}
		std::vector<object::component::Camera*> Renderer::GetCameras()
		{
			std::vector<object::component::Camera*> cameras;
			for (object::GameObject* gameObject : object::GameObject::FindGameObjectsWithComponent<object::component::Camera>())
			{
				cameras.push_back(gameObject->GetComponent<object::component::Camera>());
			}
			return cameras;
		}
		void Renderer::BindGameObjectBuffer(object::component::Camera * camera, object::GameObject * gameObject)
		{
			//Fill matrix buffer with gameObject info

			s_objectBufferStruct.worldMatrix = gameObject->m_transform->GetWorldMatrix().Transpose();
			s_objectBufferStruct.viewMatrix = camera->GetViewMatrix().Transpose();
			s_objectBufferStruct.projectionMatrix = camera->GetProjMatrix().Transpose();
			s_objectBufferStruct.mvpMatrix = s_objectBufferStruct.projectionMatrix * s_objectBufferStruct.viewMatrix * s_objectBufferStruct.worldMatrix;
			s_objectBufferStruct.camPos = camera->GetPosition();

			utils::D3d::FillBuffer(s_objectBuffer, s_objectBufferStruct);

			//Bind gameObject specific buffers
			thomas::graphics::Shader::GetCurrentBoundShader()->BindBuffer(s_objectBuffer, thomas::graphics::Shader::ResourceType::GAME_OBJECT);
		}
		ID3D11ShaderResourceView * Renderer::GetDepthBufferSRV()
		{
			return s_depthBufferSRV;
		}
		void Renderer::UnBindGameObjectBuffer()
		{
			thomas::graphics::Shader::GetCurrentBoundShader()->BindBuffer(NULL, thomas::graphics::Shader::ResourceType::GAME_OBJECT);
		}
	}
}

