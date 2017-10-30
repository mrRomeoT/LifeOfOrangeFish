#include "MainGameScene.h"
#include "../../Objects/OrangeFish.h"
#include "../../Objects/Bubble.h"
#include "../../Objects/BadFish.h"
#include "../Menu/MainMenuScene.h"

USING_NS_CC;

std::string MainGameScene::MENU_BACKGROUND_SPRITE_PATH = "sprites/game/background.png";

float MainGameScene::MAIN_MENU_SCENE_TRANSITION_TIME = 1.0f;

float MainGameScene::CHARACTERS_SCALE = 0.2f;

cocos2d::Vec2 MainGameScene::gerRundomPositionArroundTheScreen()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	int degree = cocos2d::RandomHelper::random_int<int>(0, 360);

	float radian = CC_DEGREES_TO_RADIANS(degree);

	float x = cos(radian);
	float y = sin(radian);

	Vec2 spawnPoint = Vec2(x, y) * visibleSize.width;

	return spawnPoint;
}

cocos2d::Scene* MainGameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainGameScene::create();
	scene->addChild(layer);

	return scene;
}

bool MainGameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	_centerOfScreen = visibleSize / 2.0f;

	initBackground();
	initOrangeFish();

	initTouchEventListher();
	this->scheduleUpdate();

	return true;
}

SimpleFish* MainGameScene::createBadFish()
{
	auto badFish = BadFish::create();

	badFish->setScale(CHARACTERS_SCALE);

	badFish->setPosition(gerRundomPositionArroundTheScreen());

	this->addChild(badFish);

	badFish->moveToPoint(_centerOfScreen, cocos2d::RandomHelper::random_real<float>(3.0f, 6.0f));

	return badFish;
}

void MainGameScene::initEnemyCounterLabel()
{
	_enemyCounterLabel = Label::createWithTTF(std::to_string(_killsCount), "fonts/Marker Felt.ttf", 24.0f);

	_enemyCounterLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	const Size& labelSize = _enemyCounterLabel->getBoundingBox().size;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	_enemyCounterLabel->setPosition(Vec2(20, (visibleSize.height - labelSize.height)));

	this->addChild(_enemyCounterLabel);	
}

bool MainGameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *ev)
{
	cocos2d::Vec2 location = touch->getLocation();

	_orangeFish->lookAt(location, true);
	_orangeFish->bubbleShot(location);

	return true;
}

void MainGameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *ev)
{
	_orangeFish->setCanShot(true);
}

void MainGameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *ev)
{
	cocos2d::Vec2 location = touch->getLocation();

	_orangeFish->lookAt(location);
	_orangeFish->bubbleShot(location);
}

void MainGameScene::update(float delta)
{
	if (_gameOver == false)
	{
		spawnEnemyFish(delta);

		_orangeFish->update(delta);
	}
}

void MainGameScene::spawnEnemyFish(float delta)
{
	_enemyFishSpawnTimer += delta;

	if (_enemyFishSpawnTimer >= _enemyFishSpawnTime)
	{
		_enemyFishSpawnTimer = 0.0f;
		_enemyFishSpawnTime = cocos2d::RandomHelper::random_real<float>(1.0f, 3.0f);

		_orangeFish->addEnemy(createBadFish());
	}
}

void MainGameScene::gameOver()
{
	_gameOver = true;
	TransitionScene* fadeMainGameScene = TransitionFade::create(MAIN_MENU_SCENE_TRANSITION_TIME, MainMenuScene::createScene(), Color3B::WHITE);
	Director::getInstance()->replaceScene(fadeMainGameScene);
}

void MainGameScene::initBackground()
{
	auto backgroundSprite = Sprite::create(MENU_BACKGROUND_SPRITE_PATH);

	backgroundSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	backgroundSprite->setPosition(Vec2::ZERO);

	addChild(backgroundSprite, 0);
}

void MainGameScene::initTouchEventListher()
{
	auto touchEventListner = EventListenerTouchOneByOne::create();

	touchEventListner->setSwallowTouches(true);
	touchEventListner->onTouchBegan = CC_CALLBACK_2(MainGameScene::onTouchBegan, this);
	touchEventListner->onTouchEnded = CC_CALLBACK_2(MainGameScene::onTouchEnded, this);
	touchEventListner->onTouchMoved = CC_CALLBACK_2(MainGameScene::onTouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchEventListner, this);
}

void MainGameScene::initOrangeFish()
{
	_orangeFish = OrangeFish::create();

	_orangeFish->setScale(CHARACTERS_SCALE);

	const Size& orangeFishHalfContentSize = _orangeFish->getBoundingBox().size / 2.0f;

	_orangeFish->setPosition(Vec2(_centerOfScreen.x - orangeFishHalfContentSize.width, _centerOfScreen.y + orangeFishHalfContentSize.height));

	_orangeFish->onEnemyTouchMe = [&]()
	{
		gameOver();
	};

	this->addChild(_orangeFish);

	initEnemyCounterLabel();

	_orangeFish->onBubbleKillEnemy = [&]()
	{
		++_killsCount;
		_enemyCounterLabel->setString(std::to_string(_killsCount));
	};
}