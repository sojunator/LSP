#pragma once
#include "Thomas.h"
#include "graphics\Renderer.h"
#include "utils\Ocean\OceanSimulator.h"
using namespace thomas;
using namespace graphics;
class OceanPostProcess : public PostEffect
{
private:
	OceanPostProcess* CreateInstance(std::string name, Shader* shader)
	{
		return new OceanPostProcess(name, shader);
	}
public:
	OceanPostProcess(std::string shader) : PostEffect(shader) {}
	OceanPostProcess(std::string name, Shader* shader);
	void Update();
private:
	struct OceanProperties
	{
		math::Color waterColor;
		math::Color skyColor;
		float shininess;
		float uvScale;
		float uvOffset;
		float texelLengthX2;
		math::Vector3 bendParam;
		float g_PerlinSize;
		math::Vector3 g_PerlinAmplitude;
		float pad1;
		math::Vector3 g_PerlinOctave;
		float pad2;
		math::Vector3 g_PerlinGradient;
		float pad3;
		math::Vector2 perlinMovement;
		math::Vector2 pad4;
	};
	float time;
	OceanProperties m_oceanPropertiesStruct;
	utils::ocean::OceanParameter m_oceanSettings;
	utils::ocean::OceanSimulator* m_oceanSim;
};