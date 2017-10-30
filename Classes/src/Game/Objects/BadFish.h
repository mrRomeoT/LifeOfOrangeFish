#ifndef __BAD_FISH_H__
#define __BAD_FISH_H__

#include "cocos2d.h"
#include "SimpleFish.h"

class BadFish : public SimpleFish
{
public:
	CREATE_FUNC(BadFish);
	virtual bool init() override;

	void moveToPoint(const cocos2d::Vec2 &point, float duration);

	virtual void kill() override;

private:
	static std::string BAD_FISH_SPRITE_PATH;
	cocos2d::Sprite* _sprite = nullptr;
};
#endif // __BAD_FISH_H__