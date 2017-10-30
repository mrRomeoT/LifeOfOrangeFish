#include "OrangeFish.h"
#include "Bubble.h"

USING_NS_CC;

std::string OrangeFish::ORANGE_FISH_SPRITE_PATH = "sprites/game/fish.png";
std::string OrangeFish::ORANGE_FISH_BUBLE_SPRITE_PATH = "sprites/game/fishBubble.png";

bool OrangeFish::init()
{
	if (!SimpleFish::init())
	{
		return false;
	}

	_fishSprite = Sprite::create(ORANGE_FISH_SPRITE_PATH);
	_fishSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_fishSprite->setPosition(Vec2::ZERO);

	_fishBubbleSprite = Sprite::create(ORANGE_FISH_BUBLE_SPRITE_PATH);
	_fishBubbleSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_fishBubbleSprite->setPosition(Vec2::ZERO);

	_fishBubbleSprite->setVisible(false);

	this->addChild(_fishSprite, 0);
	this->addChild(_fishBubbleSprite, 1);

	return true;
}

bool OrangeFish::isTouchAnyEnemyFish(cocos2d::Vec2 location)
{
	for (SimpleFish* fish : _enemies)
	{
		if (fish->containsPoint(location))
		{
			return true;
		}
	}

	return false;
}

void OrangeFish::bubbleShot(const cocos2d::Vec2 &position)
{
	if (_canShot == true)
	{
		if (isTouchAnyEnemyFish(position))
		{
			Node* bubble = createBubble();

			_fishSprite->setVisible(false);
			_fishBubbleSprite->setVisible(true);

			this->runAction(Sequence::create({ DelayTime::create(0.2f), CallFunc::create([&]()
			{
				_fishBubbleSprite->setVisible(false);
				_fishSprite->setVisible(true);
			}) }));

			bubble->runAction(MoveTo::create(0.5f, position));

			_canShot = false;
		}
	}
}

std::vector<Bubble*> OrangeFish::getBubbles()
{
	return _bubbles;
}

void OrangeFish::killBubble(Bubble * bubble)
{
	_bubbles.erase(std::remove(_bubbles.begin(), _bubbles.end(), bubble), _bubbles.end());
	bubble->kill();
}

void OrangeFish::setCanShot(bool val)
{
	_canShot = val;
}

void OrangeFish::addEnemy(SimpleFish* fish)
{
	_enemies.push_back(fish);
}

void OrangeFish::update(float delta)
{
	if (_isAlive == true)
	{
		checkBubblesIntersectWithEnemies();
		checkIsIntersectWithEnemies();
	}
}

void OrangeFish::checkBubblesIntersectWithEnemies()
{
	std::vector<std::pair<SimpleFish*, Bubble*>> bubbleEmenyKills;

	for (Bubble* bubble : _bubbles)
	{
		for (SimpleFish* enemyFish : _enemies)
		{
			if (enemyFish->intersectWith(bubble))
			{
				bubbleEmenyKills.push_back(std::make_pair(enemyFish, bubble));
			}
		}
	}

	if (!bubbleEmenyKills.empty())
	{
		for (auto& pairForKill : bubbleEmenyKills)
		{
			killEnemy(pairForKill.first);
			killBubble(pairForKill.second);

			if (onBubbleKillEnemy != nullptr)
			{
				onBubbleKillEnemy();
			}
		}
	}
}

void OrangeFish::checkIsIntersectWithEnemies()
{
	for (SimpleFish* enemiFish : _enemies)
	{		
		if (this->intersectWith(enemiFish))
		{
			_isAlive = false;
			if (onEnemyTouchMe != nullptr)
			{
				onEnemyTouchMe();
			}
		}
	}
}

bool OrangeFish::getIsAlive() const
{
	return _isAlive;
}

Node* OrangeFish::createBubble()
{
	auto bubble = Bubble::create();
	bubble->setScale(this->getScale());
	bubble->setPosition(this->getPosition());

	_bubbles.push_back(bubble);
	getParent()->addChild(bubble);
	return bubble;
}

void OrangeFish::killEnemy(SimpleFish* fish)
{
	_enemies.erase(std::remove(_enemies.begin(), _enemies.end(), fish), _enemies.end());
	fish->kill();
}