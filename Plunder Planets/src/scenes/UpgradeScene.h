#pragma once
#include "Thomas.h"
#include "../gameobjects/UpgradeMenuObject.h"
class UpgradeScene : public thomas::Scene
{
public:
	UpgradeScene() : Scene("UpgradeScene")
	{
		LoadShader("particleShader", thomas::graphics::Shader::InputLayouts::NONE, "../res/shaders/particleShader.hlsl");
		if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_169)
		{
			thomas::graphics::Sprite::LoadTexture("CannonInfo", "../res/GUI/upgrade/cannoninfo.png");
			thomas::graphics::Sprite::LoadTexture("MovementInfo", "../res/GUI/upgrade/movementinfo.png");
			thomas::graphics::Sprite::LoadTexture("ResourceInfo", "../res/GUI/upgrade/resourceinfo.png");
			thomas::graphics::Sprite::LoadTexture("ShieldInfo", "../res/GUI/upgrade/shieldinfo.png");
			thomas::graphics::Sprite::LoadTexture("HealthInfo", "../res/GUI/upgrade/healthinfo.png");
			thomas::graphics::Sprite::LoadTexture("PlunderInfo", "../res/GUI/upgrade/plunderinfo.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuStart", "../res/GUI/upgrade/continue.png");
			thomas::graphics::Sprite::LoadTexture("CannonIcon", "../res/GUI/upgrade/cannon.png");
			thomas::graphics::Sprite::LoadTexture("Talent", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("MovementIcon", "../res/GUI/upgrade/speed.png");
			thomas::graphics::Sprite::LoadTexture("ResourceIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("ShieldIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("RepairIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("PlunderIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuExit", "../res/GUI/menu/exit.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuBackground", "../res/GUI/upgrade/background.jpg");
			//Upgrade icons
			thomas::graphics::Sprite::LoadTexture("CannonIcon1", "../res/GUI/upgrade/cannon1.png");
			thomas::graphics::Sprite::LoadTexture("CannonIcon2", "../res/GUI/upgrade/cannon2.png");
			thomas::graphics::Sprite::LoadTexture("CannonIcon3", "../res/GUI/upgrade/cannon3.png");
			thomas::graphics::Sprite::LoadTexture("CannonIcon4", "../res/GUI/upgrade/cannon4.png");
			thomas::graphics::Sprite::LoadTexture("CannonIcon5", "../res/GUI/upgrade/cannon5.png");
			thomas::graphics::Sprite::LoadTexture("MovementIcon1", "../res/GUI/upgrade/speed1.png");
			thomas::graphics::Sprite::LoadTexture("MovementIcon2", "../res/GUI/upgrade/speed2.png");
			thomas::graphics::Sprite::LoadTexture("MovementIcon3", "../res/GUI/upgrade/speed3.png");
			thomas::graphics::Sprite::LoadTexture("MovementIcon4", "../res/GUI/upgrade/speed4.png");
			thomas::graphics::Sprite::LoadTexture("MovementIcon5", "../res/GUI/upgrade/speed5.png");
		}
		else if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_1610) //FIX FITTING LATER
		{
			thomas::graphics::Sprite::LoadTexture("CannonInfo", "../res/GUI/upgrade/cannoninfo.png");
			thomas::graphics::Sprite::LoadTexture("MovementInfo", "../res/GUI/upgrade/movementinfo.png");
			thomas::graphics::Sprite::LoadTexture("ResourceInfo", "../res/GUI/upgrade/resourceinfo.png");
			thomas::graphics::Sprite::LoadTexture("ShieldInfo", "../res/GUI/upgrade/shieldinfo.png");
			thomas::graphics::Sprite::LoadTexture("HealthInfo", "../res/GUI/upgrade/healthinfo.png");
			thomas::graphics::Sprite::LoadTexture("PlunderInfo", "../res/GUI/upgrade/plunderinfo.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuStart", "../res/GUI/upgrade/continue.png");
			thomas::graphics::Sprite::LoadTexture("CannonIcon", "../res/GUI/upgrade/cannon.png");
			thomas::graphics::Sprite::LoadTexture("Talent", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("MovementIcon", "../res/GUI/upgrade/speed.png");
			thomas::graphics::Sprite::LoadTexture("ResourceIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("ShieldIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("RepairIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("PlunderIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuExit", "../res/GUI/menu/exit.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuBackground", "../res/GUI/upgrade/background.jpg");
		}
		else if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_43)
		{
			thomas::graphics::Sprite::LoadTexture("CannonInfo", "../res/GUI/upgrade/cannoninfo.png");
			thomas::graphics::Sprite::LoadTexture("MovementInfo", "../res/GUI/upgrade/movementinfo.png");
			thomas::graphics::Sprite::LoadTexture("ResourceInfo", "../res/GUI/upgrade/resourceinfo.png");
			thomas::graphics::Sprite::LoadTexture("ShieldInfo", "../res/GUI/upgrade/shieldinfo.png");
			thomas::graphics::Sprite::LoadTexture("HealthInfo", "../res/GUI/upgrade/healthinfo.png");
			thomas::graphics::Sprite::LoadTexture("PlunderInfo", "../res/GUI/upgrade/plunderinfo.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuStart", "../res/GUI/upgrade/continue.png");
			thomas::graphics::Sprite::LoadTexture("CannonIcon", "../res/GUI/upgrade/cannon.png");
			thomas::graphics::Sprite::LoadTexture("Talent", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("MovementIcon", "../res/GUI/upgrade/speed.png");
			thomas::graphics::Sprite::LoadTexture("ResourceIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("ShieldIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("RepairIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("PlunderIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuExit", "../res/GUI/menu/exit.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuBackground", "../res/GUI/upgrade/background.jpg");
		}
		else
		{
			thomas::graphics::Sprite::LoadTexture("CannonInfo", "../res/GUI/upgrade/cannoninfo.png");
			thomas::graphics::Sprite::LoadTexture("MovementInfo", "../res/GUI/upgrade/movementinfo.png");
			thomas::graphics::Sprite::LoadTexture("ResourceInfo", "../res/GUI/upgrade/resourceinfo.png");
			thomas::graphics::Sprite::LoadTexture("ShieldInfo", "../res/GUI/upgrade/shieldinfo.png");
			thomas::graphics::Sprite::LoadTexture("HealthInfo", "../res/GUI/upgrade/healthinfo.png");
			thomas::graphics::Sprite::LoadTexture("PlunderInfo", "../res/GUI/upgrade/plunderinfo.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuStart", "../res/GUI/upgrade/continue.png");
			thomas::graphics::Sprite::LoadTexture("CannonIcon", "../res/GUI/upgrade/cannon.png");
			thomas::graphics::Sprite::LoadTexture("Talent", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("MovementIcon", "../res/GUI/upgrade/speed.png");
			thomas::graphics::Sprite::LoadTexture("ResourceIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("ShieldIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("RepairIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("PlunderIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuExit", "../res/GUI/menu/exit.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuBackground", "../res/GUI/upgrade/background.jpg");
		}
		thomas::graphics::TextRender::LoadFont("Pirate", "../res/font/pirate.spritefont");
		LoadObject<UpgradeMenuObject>();

	};
};