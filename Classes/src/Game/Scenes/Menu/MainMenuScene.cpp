#include "MainMenuScene.h"
#include "..\Game\MainGameScene.h"

USING_NS_CC;

std::string MainMenuScene::BUTTON_NORMAL_SPRITE_PATH = "sprites/menu/buttonRed.png";

std::string MainMenuScene::BUTTON_SELECT_SPRITE_PATH = "sprites/menu/buttonRedPressed.png";

std::string MainMenuScene::MENU_BACKGROUND_SPRITE_PATH = "sprites/menu/menuBackground.png";

float MainMenuScene::MAIN_GAME_SCENE_TRANSITION_TIME = 0.5f;

cocos2d::Scene* MainMenuScene::createScene()
{
	return MainMenuScene::create();
}

bool MainMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	initBackground();
	initPlayButton();

	return true;
}

void MainMenuScene::initBackground()
{
	auto backgroundSprite = Sprite::create(MENU_BACKGROUND_SPRITE_PATH);

	backgroundSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	backgroundSprite->setPosition(Vec2::ZERO);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto contentSize = backgroundSprite->getContentSize();

	backgroundSprite->setScaleX(visibleSize.width / contentSize.width);
	backgroundSprite->setScaleY(visibleSize.height / contentSize.width);

	addChild(backgroundSprite, 0);
}

void MainMenuScene::initPlayButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto playButton = ui::Button::create(BUTTON_NORMAL_SPRITE_PATH, BUTTON_SELECT_SPRITE_PATH);
	playButton->setScale9Enabled(true);	
	playButton->setTitleText("Play game!");
	playButton->setTitleFontSize(24.0f);

	Size borders = Size(15.0f, 10.0f);

	playButton->setContentSize(playButton->getTitleLabel()->getContentSize() + borders);
	playButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::playButtonTouchEventListener, this));

	const Size& playButtonHalfContentSize = playButton->getVirtualRendererSize() / 2.0f;

	Vec2 centerScreen = visibleSize / 2.0f;

	playButton->setPosition(Vec2(centerScreen.x - playButtonHalfContentSize.width, centerScreen.y + playButtonHalfContentSize.height));

	this->addChild(playButton, 1);
}

void MainMenuScene::playButtonTouchEventListener(Ref *sender, ui::Widget::TouchEventType type)
{
	switch (type) {
	case ui::Widget::TouchEventType::ENDED:		
		auto button = static_cast<ui::Button*>(sender);
		button->setEnabled(false);

		startMainGameScene();

		break;
	}
}

void MainMenuScene::startMainGameScene()
{
	TransitionScene* fadeMainGameScene = TransitionFade::create(MAIN_GAME_SCENE_TRANSITION_TIME, MainGameScene::createScene());
	Director::getInstance()->replaceScene(fadeMainGameScene);
}