#include "Bubble.h"

std::string Bubble::BUUBLE_SPRITE_PATH = "sprites/game/bubble.png";

cocos2d::Rect Bubble::getBox()
{
	return Sprite::getBoundingBox();
}

bool Bubble::init()
{
	if (!Sprite::initWithFile(BUUBLE_SPRITE_PATH))
	{
		return false;
	}

	return true;
}

void Bubble::kill()
{
	this->removeFromParentAndCleanup(true);
}