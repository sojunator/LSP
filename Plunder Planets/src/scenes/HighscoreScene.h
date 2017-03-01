#pragma once
#include "Thomas.h"
#include "../gameobjects/HighscoreMenuObject.h"

class HighscoreScene : public thomas::Scene
{
public:
	HighscoreScene() : Scene("HighscoreScene")
	{
		/*if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_169)
		{
			thomas::graphics::Sprite::LoadTexture("Header", "../res/GUI/upgrade/upgrade.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuStart", "../res/GUI/upgrade/continue.png");
			thomas::graphics::Sprite::LoadTexture("CannonIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("CannonCost", "../res/GUI/upgrade/cost.png");
			thomas::graphics::Sprite::LoadTexture("CannonTalent1", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("CannonTalent2", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("CannonTalent3", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("CannonTalent4", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("CannonTalent5", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("MovementIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("MovementCost", "../res/GUI/upgrade/cost.png");
			thomas::graphics::Sprite::LoadTexture("MovementTalent1", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("MovementTalent2", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("MovementTalent3", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("MovementTalent4", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("MovementTalent5", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("ResourceIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("ResourceCost", "../res/GUI/upgrade/cost.png");
			thomas::graphics::Sprite::LoadTexture("ResourceTalent1", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("ResourceTalent2", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("ResourceTalent3", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("ResourceTalent4", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("ResourceTalent5", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("ShieldIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("ShieldCost", "../res/GUI/upgrade/cost.png");
			thomas::graphics::Sprite::LoadTexture("ShieldTalent1", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("ShieldTalent2", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("ShieldTalent3", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("ShieldTalent4", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("ShieldTalent5", "../res/GUI/upgrade/talent.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuExit", "../res/GUI/menu/exit.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuBackground", "../res/GUI/upgrade/background.jpg");

		}
		else if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_1610)
		{

		}
		else if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_43)
		{

		}
		else
		{
			thomas::graphics::Sprite::LoadTexture("Header", "../res/GUI/upgrade/upgrade.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuStart", "../res/GUI/upgrade/continue.png");
			thomas::graphics::Sprite::LoadTexture("CannonIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("CannonDamage", "../res/GUI/upgrade/damage.png");
			thomas::graphics::Sprite::LoadTexture("CannonSpread", "../res/GUI/upgrade/spread.png");
			thomas::graphics::Sprite::LoadTexture("CannonQuantity", "../res/GUI/upgrade/quantity.png");
			thomas::graphics::Sprite::LoadTexture("MovementIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("MovementSpeed", "../res/GUI/upgrade/Speed.png");
			thomas::graphics::Sprite::LoadTexture("ResourceIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("ShieldIcon", "../res/GUI/upgrade/icon.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuExit", "../res/GUI/menu/exit.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuBackground", "../res/GUI/upgrade/background.jpg");
		}*/

		LoadObject<HighscoreMenuObject>();

	};
};
