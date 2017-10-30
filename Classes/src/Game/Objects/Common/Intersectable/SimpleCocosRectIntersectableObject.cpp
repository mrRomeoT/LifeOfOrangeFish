#include "SimpleCocosRectIntersectableObject.h"

bool SimpleCocosRectIntersectableObject::containsPoint(const cocos2d::Vec2& location)
{
	return this->getBox().containsPoint(location);
}

bool SimpleCocosRectIntersectableObject::intersectWith(IntersectibleObject* object)
{
	return this->getBox().intersectsRect(object->getBox());
}