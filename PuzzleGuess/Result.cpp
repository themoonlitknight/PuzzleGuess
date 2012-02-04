//
//  Result.cpp
//  PuzzleGuess
//
//  Created by Francesco on 17/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Result.h"
#import "settings.h"
#import "MainMenu.h"
#import "Levels.h"
#import "Utility.h"
#import "Gameplay.h"

using namespace cocos2d;

ResultScene *ResultScene::instance;

//******** ResultScene ********
bool ResultScene::init()
{
	if( CCScene::init() )
	{
		this->_layer = ResultLayer::node();
		this->_layer->retain();
		this->addChild(_layer);
		
		return true;
	}
	else
	{
		return false;
	}
}

ResultScene::~ResultScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}

//******** ResultLayer ********
bool ResultLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	
	//code here
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	
	setUpMenu();
	
	// set (image) label for success or failure
	string successSpriteFile = string(ResultScene::instance->getSuccess() ? IMG_LEVELCOMPLETED : IMG_LEVELFAILED);
	CCSprite *successSprite = CCSprite::spriteWithFile(successSpriteFile.c_str());
	this->addChild(successSprite);
	successSprite->setPosition(ccp(winsize.width/2, winsize.height*0.3));

	// unlock next level if succeded
	if ( (ResultScene::instance->getSuccess())
		&& (LevelsLayer::selectedLevel == LevelsLayer::levelunlocked[LevelsLayer::selectedCategory])
		&& (LevelsLayer::selectedLevel < LEVELS) )
	{
		LevelsLayer::levelunlocked[LevelsLayer::selectedCategory]++;
	}
	
	return true;
}

ResultLayer::~ResultLayer()
{
	
}

/* /\/\/\ MENU /\/\/\ */
void ResultLayer::setUpMenu()
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	
	CCMenu *menu = CCMenu::menuWithItems(NULL);
	
	if (ResultScene::instance->getSuccess())
	{
		// 'nextlevel' item
		CCMenuItemImage *menuItem_nextlevel;
		menuItem_nextlevel = CCMenuItemImage::itemFromNormalImage(MENUITEM_NEXTLEVEL, MENUITEM_NEXTLEVEL, this, menu_selector(ResultLayer::nextlevel_pressed));
		menu->addChild(menuItem_nextlevel, 0);	
	}
	else
	{
		// 'retrylevel' item
		CCMenuItemImage *menuItem_retrylevel;
		menuItem_retrylevel = CCMenuItemImage::itemFromNormalImage(MENUITEM_RETRYLEVEL, MENUITEM_RETRYLEVEL, this, menu_selector(ResultLayer::retrylevel_pressed));
		menu->addChild(menuItem_retrylevel, 0);
	}
	
	// 'returnlevels' item
	CCMenuItemImage *menuItem_returnlevels;
	menuItem_returnlevels = CCMenuItemImage::itemFromNormalImage(MENUITEM_RETURNLEVELS, MENUITEM_RETURNLEVELS, this, menu_selector(ResultLayer::returnlevels_pressed));
	menu->addChild(menuItem_returnlevels, 0);
	
	// 'returnmain' item
	CCMenuItemImage *menuItem_returnmain;
	menuItem_returnmain = CCMenuItemImage::itemFromNormalImage(MENUITEM_RETURNMAIN, MENUITEM_RETURNMAIN, this, menu_selector(ResultLayer::returnmain_pressed));
	menu->addChild(menuItem_returnmain, 0);
	
	
	//menu->setPosition(CCPointZero);
	menu->alignItemsVertically();
	
	this->addChild(menu, 1);
}

void ResultLayer::nextlevel_pressed(CCObject* pSender)
{
	LevelsLayer::selectedLevel++;
	
	LevelsLayer::imageName = getImageNameFromLevel(LevelsLayer::selectedLevel, NUMALT, LevelsLayer::imagedb);
	
	GameplayScene *gameplayScene = GameplayScene::node();
	CCDirector::sharedDirector()->replaceScene(gameplayScene);
}

void ResultLayer::retrylevel_pressed(CCObject* pSender)
{
	GameplayScene *gameplayScene = GameplayScene::node();
	CCDirector::sharedDirector()->replaceScene(gameplayScene);
}

void ResultLayer::returnlevels_pressed(CCObject* pSender)
{
	LevelsScene *levelsScene = LevelsScene::node();
	CCDirector::sharedDirector()->replaceScene(levelsScene);
}

void ResultLayer::returnmain_pressed(CCObject* pSender)
{
	MainMenuScene *mainMenuScene = MainMenuScene::node();
	CCDirector::sharedDirector()->replaceScene(mainMenuScene);
}
