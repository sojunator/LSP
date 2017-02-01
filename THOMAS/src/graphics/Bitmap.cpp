#include "Bitmap.h"
#include "Texture.h"

namespace thomas
{
	namespace graphics
	{
		bool Bitmap::InitializeBuffers(ID3D11Device *)
		{





			VertexType* vertices;
			unsigned long* indices;
			D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
			D3D11_SUBRESOURCE_DATA vertexData, indexData;
			HRESULT result;
			int i;

			// Set the number of vertices in the vertex array.
			m_vertexCount = 6;

			// Set the number of indices in the index array.
			m_indexCount = m_vertexCount;

			// Create the vertex array.
			vertices = new VertexType[m_vertexCount];
			if (!vertices)
			{
				return false;
			}

			// Create the index array.
			indices = new unsigned long[m_indexCount];
			if (!indices)
			{
				return false;
			}

			// Initialize vertex array to zeros at first.
			memset(vertices, 0, (sizeof(VertexType) * m_vertexCount));

			// Load the index array with data.
			for (i = 0; i<m_indexCount; i++)
			{
				indices[i] = i;
			}

			// Set up the description of the static vertex buffer.
			vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			vertexBufferDesc.MiscFlags = 0;
			vertexBufferDesc.StructureByteStride = 0;

			// Give the subresource structure a pointer to the vertex data.
			vertexData.pSysMem = vertices;
			vertexData.SysMemPitch = 0;
			vertexData.SysMemSlicePitch = 0;

			// Now create the vertex buffer.
			result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
			if (FAILED(result))
			{
				return false;
			}

			// Set up the description of the static index buffer.
			indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
			indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexBufferDesc.CPUAccessFlags = 0;
			indexBufferDesc.MiscFlags = 0;
			indexBufferDesc.StructureByteStride = 0;

			// Give the subresource structure a pointer to the index data.
			indexData.pSysMem = indices;
			indexData.SysMemPitch = 0;
			indexData.SysMemSlicePitch = 0;

			// Create the index buffer.
			result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
			if (FAILED(result))
			{
				return false;
			}

			// Release the arrays now that the vertex and index buffers have been created and loaded.
			delete[] vertices;
			vertices = 0;

			delete[] indices;
			indices = 0;

			return true;
		}

		void Bitmap::ShutdownBuffers()
		{
		}
		
		void Bitmap::RenderBuffers(ID3D11DeviceContext *)
		{
		}
		bool Bitmap::LoadTexture(ID3D11Device *, WCHAR *)
		{
			return false;
		}
		void Bitmap::ReleaseTexture()
		{
		}
		Bitmap::Bitmap()
		{
		}


		Bitmap::~Bitmap()
		{
			m_data.m_indexBuffer->Release();
			m_data.m_vertexBuffer->Release();
		}

		Bitmap::Bitmap(const Bitmap &)
		{
		}

		bool Bitmap::Initialize(ID3D11Device* device, WCHAR* textureFilename, int bitmapWidth, int bitmapHeight)
		{
			bool result;

			m_screenWidth = m_window->GetWidth();
			m_screenHeight = m_window->GetHeight();

			m_bitmapWidth = bitmapWidth;
			m_bitmapHeight = bitmapHeight;

			// Initialize the previous rendering position to negative one.
			m_previousPosX = -1;
			m_previousPosY = -1;

			// Initialize the vertex and index buffers.
			result = InitializeBuffers(device);
			if (!result)
			{
				return false;
			}

			// Load the texture for this model.
			/*result = LoadTexture(device, textureFilename);
			if (!result)
			{
				return false;
			}*/


			return true;
		}

		void Bitmap::Shutdown()
		{
			//// Release the model texture.
			//ReleaseTexture();

			//// Shutdown the vertex and index buffers.
			//ShutdownBuffers();

			//return;
		}

		int Bitmap::GetIndexCount()
		{
			return m_data.m_indexCount;
		}

	}
}
