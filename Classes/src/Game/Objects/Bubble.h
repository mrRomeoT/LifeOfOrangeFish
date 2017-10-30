#ifndef __BUBBLE_FISH_H__
#define __BUBBLE_FISH_H__

#include "cocos2d.h"
#include "Common/Intersectable/SimpleCocosRectIntersectableObject.h"

class Bubble : public cocos2d::Sprite, public SimpleCocosRectIntersectableObject
{
public:	
	virtual bool init() override;

	CREATE_FUNC(Bubble);

	void kill();

	virtual cocos2d::Rect getBox() override;

private:
	static std::string BUUBLE_SPRITE_PATH;
};

#endif // __BUBBLE_FISH_H__