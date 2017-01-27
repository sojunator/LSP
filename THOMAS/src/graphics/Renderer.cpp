#include "Renderer.h"
#include "Model.h"
#include "../object/GameObject.h"

namespace thomas
{
	namespace graphics
	{

		ID3D11RenderTargetView* Renderer::s_backBuffer;
		ID3D11RasterizerState* Renderer::s_rasterState;
		ID3D11DepthStencilState* Renderer::s_depthStencilState;
		ID3D11DepthStencilView* Renderer::s_depthStencilView;
		ID3D11Texture2D* Renderer::s_depthBuffer;
		D3D11_VIEWPORT Renderer::s_viewport;

		ID3D11Buffer* Renderer::s_matrixBuffer;
		Renderer::MatrixStruct Renderer::s_objectMatrix;

		bool thomas::graphics::Renderer::Init()
		{
			if (utils::D3d::InitRenderer(s_backBuffer, s_rasterState, s_depthStencilState, s_depthStencilView, s_depthBuffer))
			{
				s_viewport = utils::D3d::CreateViewport(0, 0, Window::GetWidth(), Window::GetHeight());

				s_matrixBuffer = utils::D3d::CreateBufferFromStruct(s_objectMatrix, D3D11_BIND_CONSTANT_BUFFER);
				
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

			Clear();
		//	ThomasCore::GetDeviceContext()->OMSetDepthStencilState(s_depthStencilState, 1);
			ThomasCore::GetDeviceContext()->OMSetRenderTargets(1, &s_backBuffer, s_depthStencilView);
			ThomasCore::GetDeviceContext()->RSSetViewports(1, &s_viewport);
			ThomasCore::GetDeviceContext()->RSSetState(s_rasterState);

			std::vector<Shader*> loadedShaders = Shader::GetLoadedShaders();

			loadedShaders[0]->Bind();
			for (object::GameObject* gameObject : object::GameObject::FindGameObjectsWithComponent<object::component::RenderComponent>())
			{
				object::component::RenderComponent* renderComponent = gameObject->GetComponent<object::component::RenderComponent>();

				object::component::Camera* camera = GetCameras()[0];

				s_objectMatrix.matrix = gameObject->m_transform->GetWorldMatrix() * camera->GetViewProjMatrix();
				s_objectMatrix.matrix = s_objectMatrix.matrix.Transpose();
				utils::D3d::FillBuffer(s_matrixBuffer, s_objectMatrix);
				thomas::graphics::Shader::GetCurrentBoundShader()->BindBuffer(s_matrixBuffer, thomas::graphics::Shader::ResourceType::MVP_MATRIX);

				for (Mesh* mesh : renderComponent->GetModel()->GetMeshes())
				{
					mesh->GetMaterial()->Bind();
					mesh->Bind();
					mesh->Draw();
				}

			}

			//for (Shader* shader : loadedShaders)
			//{
			//	shader->Bind();

			//	for (material::Material* mat : material::Material::GetMaterialsByShader(shader))
			//	{
			//		mat->Bind();
			//		for (object::GameObject* gameObject : object::GameObject::FindGameObjectsWithComponent<object::component::RenderComponent>())
			//		{
			//			object::component::RenderComponent* renderComponent = gameObject->GetComponent<object::component::RenderComponent>();

			//			for (object::component::Camera* camera : GetCameras()) //Render for every camera;
			//			{
			//				//Fill matrix buffer with gameObject info
			//				s_objectMatrix.matrix = gameObject->m_transform->GetWorldMatrix() * camera->GetViewProjMatrix();
			//				s_objectMatrix.matrix = s_objectMatrix.matrix.Transpose();
			//				utils::D3d::FillBuffer(s_matrixBuffer, s_objectMatrix);
			//				thomas::graphics::Shader::GetCurrentBoundShader()->BindBuffer(s_matrixBuffer, thomas::graphics::Shader::ResourceType::MVP_MATRIX);

			//				//Draw every mesh of gameObjects model
			//				for (Mesh* mesh : renderComponent->GetModel()->GetMeshesByMaterial(mat))
			//				{
			//					mesh->Bind();
			//					mesh->Draw();
			//				}
			//			}


			//		}
			//		mat->Unbind();
			//	}
			//	shader->Unbind();
			//}

			ThomasCore::GetSwapChain()->Present(0, 0);
		}

		bool Renderer::Destroy()
		{

			s_backBuffer->Release();
			s_rasterState->Release();
			s_depthStencilState->Release();
			s_depthStencilView->Release();
			s_depthBuffer->Release();
			s_matrixBuffer->Release();

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
	}
}

