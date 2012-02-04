#include "Start.h"
#include "SimpleAudioEngine.h"
#import "MainMenu.h"
#import "Levels.h"

using namespace cocos2d;
using namespace CocosDenshion;

void initializeGame();

CCScene* Start::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	Start *layer = Start::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Start::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	//////////////////////////////
	// 2. insert code here
	this->setIsTouchEnabled(true);
	
	
	return true;
}

Start::~Start()
{
	
}

void Start::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}

//per ora appena al primo tocco parte GameplayScene
bool Start::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
	return true;
}

void Start::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{	
//	GameplayScene *gameplayScene = GameplayScene::node();
//	CCDirector::sharedDirector()->replaceScene(gameplayScene);
	
//	LevelsScene *levelsScene = LevelsScene::node();
//	CCDirector::sharedDirector()->replaceScene(levelsScene);
	
//	CategoryScene *categoryScene = CategoryScene::node();
//	CCDirector::sharedDirector()->replaceScene(categoryScene);
	
	initializeGame();
	
	MainMenuScene *mainMenuScene = MainMenuScene::node();
	CCDirector::sharedDirector()->replaceScene(mainMenuScene);
}

void initializeGame()
{
	// invece di inizializzarlo così leggere il valore da disco
	for (int i = 0; i < CATEGORIES; i++) {
		LevelsLayer::levelunlocked[i] = 0;
	}
}
