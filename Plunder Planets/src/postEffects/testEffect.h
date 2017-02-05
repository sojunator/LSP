#pragma once
#include "Thomas.h"
#include "graphics\Renderer.h"
using namespace thomas;
using namespace graphics;

class TestEffect : public PostEffect
{
private:
	PostEffect* CreateInstance(std::string name, Shader* shader)
	{
		return new TestEffect(name, shader);
	}
public:
	TestEffect(std::string shader) : PostEffect(shader) {}
	TestEffect(std::string name, Shader* shader) : PostEffect(name, shader)
	{
		m_textures.push_back(Texture::CreateTexture(Texture::SamplerState::WRAP, 1, "depthBuffer", Renderer::GetDepthBufferSRV()));
	}
};