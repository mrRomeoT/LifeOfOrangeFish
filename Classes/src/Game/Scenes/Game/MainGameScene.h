#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "cocos2d.h"

class MainGameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();


	CREATE_FUNC(MainGameScene);

private:
	static std::string MENU_BACKGROUND_SPRITE_PATH;
	void initBackground();
};

#endif // __MAIN_GAME_SCENE_H__