#ifndef __ORANGE_FISH_H__
#define __ORANGE_FISH_H__

#include "cocos2d.h"
#include "SimpleFish.h"

class Bubble;

class OrangeFish : public SimpleFish
{
public:
	CREATE_FUNC(OrangeFish);
	virtual bool init() override;	

	void bubbleShot(const cocos2d::Vec2 &position);
	std::vector<Bubble*> getBubbles();
	
	void setCanShot(bool val);

	void addEnemy(SimpleFish* fish);

	virtual void update(float delta) override;
	
	bool getIsAlive() const;

	std::function<void()> onEnemyTouchMe = nullptr;
	std::function<void()> onBubbleKillEnemy = nullptr;
	
private:
	Node* createBubble();

	void killBubble(Bubble * second);
	void killEnemy(SimpleFish* fish);

	void checkBubblesIntersectWithEnemies();
	void checkIsIntersectWithEnemies();
	bool isTouchAnyEnemyFish(cocos2d::Vec2 location);

	static std::string ORANGE_FISH_SPRITE_PATH;
	static std::string ORANGE_FISH_BUBLE_SPRITE_PATH;

	cocos2d::Sprite* _fishSprite = nullptr;
	cocos2d::Sprite* _fishBubbleSprite = nullptr;

	std::vector<Bubble*> _bubbles;
	std::vector<SimpleFish*> _enemies;

	bool _canShot = true;
	bool _isAlive = true;
};
#endif // __ORANGE_FISH_H__