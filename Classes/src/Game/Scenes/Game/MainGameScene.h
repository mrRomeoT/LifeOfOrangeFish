#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "cocos2d.h"
#include "base/CCEventDispatcher.h"

class OrangeFish;
class SimpleFish;

class MainGameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(MainGameScene);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *ev) override;
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *ev) override;
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *ev) override;	

	virtual void update(float delta) override;
	
private:
	static std::string MENU_BACKGROUND_SPRITE_PATH;
	static float MAIN_MENU_SCENE_TRANSITION_TIME;
	static float CHARACTERS_SCALE;

	void initBackground();
	void gameOver();
	
	void initTouchEventListher();
	void initOrangeFish();
	cocos2d::Vec2 gerRundomPositionArroundTheScreen();
	
	void spawnEnemyFish(float delta);
	SimpleFish* createBadFish();

	void initEnemyCounterLabel();

	OrangeFish* _orangeFish = nullptr;
	cocos2d::Vec2 _centerOfScreen;
	
	float _enemyFishSpawnTimer = 5.0f;
	float _enemyFishSpawnTime = 5.0f;

	bool _gameOver = false;

	cocos2d::Label *_enemyCounterLabel = nullptr;

	int _killsCount = 0;
};

#endif // __MAIN_GAME_SCENE_H__