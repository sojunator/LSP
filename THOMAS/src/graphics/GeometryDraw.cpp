#include "GeometryDraw.h"
#include "../object/component/Camera.h"
namespace thomas
{
	namespace graphics
	{
		GeometryDraw::GeometryDraw(math::Matrix worldMatrix)
		{
			m_inputLayout = nullptr;
			m_vertexShader = nullptr;
			m_geometryShader = nullptr;
			m_pixelShader = nullptr;
			VertexData a;
			a.position = math::Vector3(1, 0, 0);
			a.color = math::Vector3(1, 1, 1);
			m_data.push_back(a); //Line start
			m_data.push_back(a); //Line end
			m_vertexBuffer = utils::D3d::CreateDynamicBufferFromVector(m_data, D3D11_BIND_VERTEX_BUFFER);
			m_constantBuffer = utils::D3d::CreateDynamicBufferFromStruct(m_cbData, D3D11_BIND_CONSTANT_BUFFER);
			//m_cbData.worldMatrix = worldMatrix;
		}
		void GeometryDraw::SetShaders(std::string path, std::string shaderModel, std::string VSEntryPoint, std::string GSEntryPoint, std::string PSEntryPoint)
		{
			//Create VS
			//ID3D10Blob* blob = Shader::Compile(path, "vs" + shaderModel, VSEntryPoint);
			ID3D10Blob* blob = Shader::Compile("../res/thomasShaders/lineShader.hlsl", "vs_4_0", "VSMain");
			if (blob)
				ThomasCore::GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &m_vertexShader);

			//Create input layout
			std::vector<D3D11_INPUT_ELEMENT_DESC> layoutDesc;
			layoutDesc =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};
			ThomasCore::GetDevice()->CreateInputLayout(&layoutDesc.front(), layoutDesc.size(), blob->GetBufferPointer(), blob->GetBufferSize(), &m_inputLayout);

			//If GSEntryPoint Create GS
			if (GSEntryPoint != "")
			{
				SAFE_RELEASE(blob);
				blob = Shader::Compile(path, "gs" + shaderModel, GSEntryPoint);
				if (blob)
					ThomasCore::GetDevice()->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &m_geometryShader);
			}

			//Create PS
			SAFE_RELEASE(blob);
			blob = Shader::Compile("../res/thomasShaders/lineShader.hlsl", "ps_4_0", "PSMain");
			if (blob)
				ThomasCore::GetDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &m_pixelShader);
			SAFE_RELEASE(blob);
		}
		void GeometryDraw::DrawLine(math::Vector3 from, math::Vector3 to, math::Vector3 fromColor, math::Vector3 toColor)
		{
			DirectX::CommonStates states(ThomasCore::GetDevice());
			ThomasCore::GetDeviceContext()->OMSetBlendState(states.Opaque(), nullptr, 0xFFFFFFFF);
			ThomasCore::GetDeviceContext()->OMSetDepthStencilState(states.DepthDefault(), 0);
			ThomasCore::GetDeviceContext()->RSSetState(states.CullNone());

			ThomasCore::GetDeviceContext()->IASetInputLayout(m_inputLayout);
			ThomasCore::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

			ThomasCore::GetDeviceContext()->VSSetShader(m_vertexShader, NULL, 0);
			ThomasCore::GetDeviceContext()->GSSetShader(NULL, NULL, 0);
			if(m_geometryShader)
				ThomasCore::GetDeviceContext()->GSSetShader(m_geometryShader, NULL, 0);
			ThomasCore::GetDeviceContext()->PSSetShader(m_pixelShader, NULL, 0);


			m_data[0].position = math::Vector3(from.x, from.y, from.z);
			m_data[0].color = math::Vector3(fromColor.x, fromColor.y, fromColor.z);

			m_data[1].position = math::Vector3(to.x, to.y, to.z);
			m_data[1].color = math::Vector3(toColor.x, toColor.y, toColor.z);

			UINT stride = sizeof(VertexData);
			utils::D3d::FillDynamicBufferVector(m_vertexBuffer, m_data);

			UINT offset = 0;
			ThomasCore::GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_constantBuffer);
			ThomasCore::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

			ThomasCore::GetDeviceContext()->Draw(2, 0);

			ThomasCore::GetDeviceContext()->VSSetShader(NULL, NULL, 0);
			if (m_geometryShader)
				ThomasCore::GetDeviceContext()->GSSetShader(NULL, NULL, 0);
			ThomasCore::GetDeviceContext()->PSSetShader(NULL, NULL, 0);
		}
		void GeometryDraw::Update(object::component::Camera* camera)
		{
			m_cbData.viewProjectionMatrix = camera->GetViewProjMatrix().Transpose();
			utils::D3d::FillDynamicBufferStruct(m_constantBuffer, m_cbData);
		}
	}
}
