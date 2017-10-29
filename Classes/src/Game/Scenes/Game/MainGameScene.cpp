#include "MainGameScene.h"

USING_NS_CC;

std::string MainGameScene::MENU_BACKGROUND_SPRITE_PATH = "sprites/game/background.png";

cocos2d::Scene* MainGameScene::createScene()
{
	return MainGameScene::create();
}

bool MainGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	initBackground();

	return true;
}

void MainGameScene::initBackground()
{
	auto backgroundSprite = Sprite::create(MENU_BACKGROUND_SPRITE_PATH);

	backgroundSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	backgroundSprite->setPosition(Vec2::ZERO);

	addChild(backgroundSprite, 0);
}