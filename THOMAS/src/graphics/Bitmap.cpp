#include "Bitmap.h"
#include "Texture.h"

namespace thomas
{
	namespace graphics
	{
		bool Bitmap::InitializeBuffers()
		{
			VertexType* vertices;
			unsigned long* indices;
			D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
			D3D11_SUBRESOURCE_DATA vertexData, indexData;
			HRESULT result;
			int i;

			// Set the number of vertices in the vertex array.
			m_data.vertexCount = 4;

			// Set the number of indices in the index array.
			m_data.indexCount = m_data.vertexCount;

			// Create the vertex array.
			vertices = new VertexType[m_data.vertexCount];
			if (!vertices)
			{
				return false;
			}

			// Create the index array.
			indices = new unsigned long[m_data.indexCount];
			if (!indices)
			{
				return false;
			}

			// Initialize vertex array to zeros at first.
			memset(vertices, 0, (sizeof(VertexType) * m_data.vertexCount));

			// Load the index array with data.
			for (i = 0; i< m_data.indexCount; i++)
			{
				indices[i] = i;
			}

			// Set up the description of the static vertex buffer.
			vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_data.vertexCount;
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			vertexBufferDesc.MiscFlags = 0;
			vertexBufferDesc.StructureByteStride = 0;

			// Give the subresource structure a pointer to the vertex data.
			vertexData.pSysMem = vertices;
			vertexData.SysMemPitch = 0;
			vertexData.SysMemSlicePitch = 0;

			// Now create the vertex buffer.
			result = ThomasCore::GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_data.vertexBuffer);
			if (FAILED(result))
			{
				return false;
			}

			// Set up the description of the static index buffer.
			indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_data.indexCount;
			indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexBufferDesc.CPUAccessFlags = 0;
			indexBufferDesc.MiscFlags = 0;
			indexBufferDesc.StructureByteStride = 0;

			// Give the subresource structure a pointer to the index data.
			indexData.pSysMem = indices;
			indexData.SysMemPitch = 0;
			indexData.SysMemSlicePitch = 0;

			// Create the index buffer.
			result = ThomasCore::GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_data.indexBuffer);
			if (FAILED(result))
			{
				return false;
			}

			// Release the arrays now that the vertex and index buffers have been created and loaded.
			delete[] vertices;
			vertices = 0;

			delete[] indices;
			indices = 0;

			m_data.constantBuffer = utils::D3d::CreateBufferFromStruct(m_constBuffer, D3D11_BIND_CONSTANT_BUFFER);

			return true;
		}

		bool Bitmap::UpdateBuffers(int positionX, int positionY)
		{
			float left, right, top, bottom;
			VertexType* vertices;
			D3D11_MAPPED_SUBRESOURCE mappedResource;
			VertexType* verticesPtr;
			HRESULT result;

			// If the position we are rendering this bitmap to has not changed then don't update the vertex buffer since it
			// currently has the correct parameters.
			if ((positionX == m_previousPosX) && (positionY == m_previousPosY))
			{
				return true;
			}

			// If it has changed then update the position it is being rendered to.
			m_previousPosX = positionX;
			m_previousPosY = positionY;

			// Calculate the screen coordinates of the left side of the bitmap.
			left = (float)((m_screenWidth / 2) * -1) + (float)positionX;

			// Calculate the screen coordinates of the right side of the bitmap.
			right = left + (float)m_bitmapWidth;

			// Calculate the screen coordinates of the top of the bitmap.
			top = (float)(m_screenHeight / 2) - (float)positionY;

			// Calculate the screen coordinates of the bottom of the bitmap.
			bottom = top - (float)m_bitmapHeight;

			// Create the vertex array.
			vertices = new VertexType[m_data.vertexCount];
			if (!vertices)
			{
				return false;
			}

			// Load the vertex array with data.
			// First triangle.
			vertices[1].position = math::Vector3(left, top, 0.0f);  // Top left.
			vertices[1].texture = math::Vector2(0.0f, 0.0f);

			vertices[2].position = math::Vector3(right, bottom, 0.0f);  // Bottom right.
			vertices[2].texture = math::Vector2(1.0f, 1.0f);

			vertices[0].position = math::Vector3(left, bottom, 0.0f);  // Bottom left.
			vertices[0].texture = math::Vector2(0.0f, 1.0f);

			vertices[3].position = math::Vector3(right, top, 0.0f);  // Top right.
			vertices[3].texture = math::Vector2(1.0f, 0.0f);

			// Lock the vertex buffer so it can be written to.
			result = ThomasCore::GetDeviceContext()->Map(m_data.vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			if (FAILED(result))
			{
				return false;
			}

			// Get a pointer to the data in the vertex buffer.
			verticesPtr = (VertexType*)mappedResource.pData;

			// Copy the data into the vertex buffer.
			memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * m_data.vertexCount));

			// Unlock the vertex buffer.
			ThomasCore::GetDeviceContext()->Unmap(m_data.vertexBuffer, 0);

			// Release the vertex array as it is no longer needed.
			delete[] vertices;
			vertices = 0;

			return true;
		}

		void Bitmap::CreateDepthStencilState()
		{
			m_data.depthStencilState = utils::D3d::CreateDepthStencilState(D3D11_COMPARISON_LESS, false);
		}

		bool Bitmap::LoadTexture(std::string path)
		{
			m_data.texture = Texture::CreateTexture(Texture::SamplerState::WRAP, Texture::TextureType::DIFFUSE, path);
			return true;
		}

		void Bitmap::CreateRasterizer()
		{
			m_data.rasterizerState = utils::D3d::CreateRasterizer(D3D11_FILL_SOLID, D3D11_CULL_FRONT);
		}

		Bitmap::Bitmap(std::string path, std::string shaderName, int bitmapWidth, int bitmapHeight)
		{
			Initialize(bitmapWidth, bitmapHeight);
			InitializeBuffers();
			LoadTexture(path);
			CreateRasterizer();
			CreateDepthStencilState();
			m_data.shader = Shader::GetShaderByName(shaderName);
		}

		Bitmap::~Bitmap()
		{
			m_data.indexBuffer->Release();
			m_data.vertexBuffer->Release();
			m_data.rasterizerState->Release();
			m_data.depthStencilState->Release();
			delete m_data.texture;
		}

		bool Bitmap::Initialize(int bitmapWidth, int bitmapHeight)
		{
			bool result;

			m_screenWidth = Window::GetWidth();
			m_screenHeight = Window::GetHeight();

			m_bitmapWidth = bitmapWidth;
			m_bitmapHeight = bitmapHeight;

			// Initialize the previous rendering position to negative one.
			m_previousPosX = -1;
			m_previousPosY = -1;
			return true;
		}

		int Bitmap::GetIndexCount()
		{
			return m_data.indexCount;
		}

		void Bitmap::Draw()
		{
			thomas::ThomasCore::GetDeviceContext()->DrawIndexed(GetIndexCount(), 0, 0);
		}

		bool Bitmap::Bind(int positionX, int positionY)
		{
			m_data.shader->Bind();

			UpdateBuffers(positionX, positionY);
			bool v = m_data.shader->BindVertexBuffer(m_data.vertexBuffer, sizeof(VertexType), 0);
			bool i = m_data.shader->BindIndexBuffer(m_data.indexBuffer);
			m_orthographic = math::Matrix::CreateOrthographic(Window::GetWidth(), Window::GetHeight(), 0.1f, 1000.f);
			m_constBuffer.orthMatrix = m_orthographic;
			utils::D3d::FillBuffer(m_data.constantBuffer, m_constBuffer);

			ThomasCore::GetDeviceContext()->RSSetState(m_data.rasterizerState);
			ThomasCore::GetDeviceContext()->OMSetDepthStencilState(m_data.depthStencilState, 1);

			m_data.shader->BindBuffer(m_data.constantBuffer, Shader::ResourceType::GAME_OBJECT);
			m_data.shader->BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			m_data.texture->Bind();

			Draw();

			return v && i;
		}

		bool Bitmap::Unbind()
		{
			bool v = Shader::GetCurrentBoundShader()->BindVertexBuffer(NULL, sizeof(VertexType), 0);
			bool i = Shader::GetCurrentBoundShader()->BindIndexBuffer(NULL);

			ThomasCore::GetDeviceContext()->RSSetState(NULL);
			ThomasCore::GetDeviceContext()->OMSetDepthStencilState(NULL, 1);

			m_data.texture->Unbind();
			m_data.shader->Unbind();

			return v && i;
		}
	}
}
