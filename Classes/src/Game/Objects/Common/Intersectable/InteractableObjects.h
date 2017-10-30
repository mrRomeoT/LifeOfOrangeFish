#ifndef _INTERSECTABLE_OBJECT_H_
#define _INTERSECTABLE_OBJECT_H_

#include "cocos2d.h"

USING_NS_CC;

class IntersectibleObject
{
public:
	virtual ~IntersectibleObject() = default;

	virtual bool containsPoint(const cocos2d::Vec2& location) = 0;

	virtual bool intersectWith(IntersectibleObject* object) = 0;

	virtual cocos2d::Rect getBox() = 0;
};

#endif // _INTERSECTABLE_OBJECT_H_