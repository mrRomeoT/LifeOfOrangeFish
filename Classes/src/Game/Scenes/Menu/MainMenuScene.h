#ifndef __MAIN_MENE_SCENE_H__
#define __MAIN_MENE_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

class MainMenuScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainMenuScene);	

private:
	static std::string BUTTON_NORMAL_SPRITE_PATH;
	static std::string BUTTON_SELECT_SPRITE_PATH;
	static std::string MENU_BACKGROUND_SPRITE_PATH;
	static float MAIN_GAME_SCENE_TRANSITION_TIME;

	void initBackground();

	void initPlayButton();
	void playButtonTouchEventListener(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	void startMainGameScene();
};

#endif // __MAIN_MENE_SCENE_H__