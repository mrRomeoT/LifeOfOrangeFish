#include "BadFish.h"

USING_NS_CC;

std::string BadFish::BAD_FISH_SPRITE_PATH = "sprites/game/badFish.png";

bool BadFish::init()
{
	if (!SimpleFish::init())
	{
		return false;
	}
	_sprite = Sprite::create(BAD_FISH_SPRITE_PATH);
	this->addChild(_sprite);

	return true;
}

void BadFish::moveToPoint(const cocos2d::Vec2 & point, float duration)
{
	lookAt(point);

	this->runAction(MoveTo::create(duration, point));
}

void BadFish::kill()
{
	auto tintBy = TintBy::create(0.1f, 120.0f, 232.0f, 254.0f);
	this->stopAllActions();

	_sprite->runAction(Sequence::create({ tintBy,
		CallFunc::create([&]()
		{
			SimpleFish::kill();
		})
	}));
}
