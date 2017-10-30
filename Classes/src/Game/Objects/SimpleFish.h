#ifndef __SIMPLE_FISH_H__
#define __SIMPLE_FISH_H__

#include "cocos2d.h"
#include "Common/Intersectable/SimpleCocosRectIntersectableObject.h"

class SimpleFish : public cocos2d::Node, public SimpleCocosRectIntersectableObject
{
public:	
	void lookAt(const cocos2d::Vec2 &point, bool isTouchBegan = false);

	float getRotationSpeed() const;
	void setRotationSpeed(float val);

	virtual void kill();

	virtual cocos2d::Rect getBox() override;	

protected:
	float _rotationSpeed = 0.1f;

};
#endif // __SIMPLE_FISH_H__