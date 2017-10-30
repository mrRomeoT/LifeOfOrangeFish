#include "SimpleFish.h"
#include "base/ccUtils.h"

USING_NS_CC;

void SimpleFish::lookAt(const cocos2d::Vec2 &point, bool isTouchBegan)
{
	Vec2 curPos = this->getPosition();

	float dx = curPos.x - point.x;
	float dy = curPos.y - point.y;

	float angle = CC_RADIANS_TO_DEGREES(atan2f(dx, dy));

	if (isTouchBegan)
	{
		this->runAction(RotateTo::create(_rotationSpeed, angle));
	}
	else
	{
		this->setRotation(angle);
	}
}

float SimpleFish::getRotationSpeed() const
{
	return _rotationSpeed;
}

void SimpleFish::setRotationSpeed(float val)
{
	_rotationSpeed = val;
}

void SimpleFish::kill()
{
	this->removeFromParentAndCleanup(true);
}

cocos2d::Rect SimpleFish::getBox()
{
	return utils::getCascadeBoundingBox(this);
}