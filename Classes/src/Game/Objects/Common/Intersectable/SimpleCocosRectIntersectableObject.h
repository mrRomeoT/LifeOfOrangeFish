#pragma once 
#ifndef _SIMPLE_COCOS_RECT_INTERSECTABLE_OBJECT_H_
#define _SIMPLE_COCOS_RECT_INTERSECTABLE_OBJECT_H_

#include "InteractableObjects.h"


class SimpleCocosRectIntersectableObject : public IntersectibleObject
{
public:

	virtual ~SimpleCocosRectIntersectableObject() = default;

	virtual bool containsPoint(const cocos2d::Vec2& location) override;

	virtual bool intersectWith(IntersectibleObject *object) override;
};

#endif //_SIMPLE_COCOS_RECT_INTERSECTABLE_OBJECT_H_