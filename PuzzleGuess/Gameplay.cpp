//
//  Gameplay.cpp
//  PuzzleGuess
//
//  Created by Francesco on 13/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Gameplay.h"//zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz

using namespace cocos2d;

bool GameplayScene::init()
{
	if( CCScene::init() )
	{
		this->_layer = GameplayLayer::node();
		this->_layer->retain();
		this->addChild(_layer);
		
		return true;
	}
	else
	{
		return false;
	}
}

GameplayScene::~GameplayScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}

bool GameplayLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	
	//code here
	//touch
	this->setIsTouchEnabled(true);
	
	texcache = CCTextureCache::sharedTextureCache();
	texcache->addImage("cellempty.png");
	texcache->addImage("cellalpha.png");
	
	// set up Puzzle instance
	puzzle = new Puzzle(this, texcache->addImage("cellempty.png"), texcache->addImage("cellalpha.png"), 10);
	puzzle->setImage(texcache->addImage("image0.png"));
	puzzle->setTimings(4, 3.8);
	puzzle->start();
	// ______________________
	
	//set up menu
	setupMenu();
	
	return true;
}

GameplayLayer::~GameplayLayer()
{
	delete puzzle;
}

#define MENUITEM_GUESS		"menuItem_guess.png"
#define MENUITEM_GUESS_SEL	"menuItem_guess_sel.png"
void GameplayLayer::setupMenu()
{
	CCMenuItemImage *menuItem_guess = CCMenuItemImage::itemFromNormalImage("Icon-Small.png", "Icon-Small.png", this, menu_selector(GameplayLayer::guess_pressed));
	menuItem_guess->setUserData(this);
	
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	menuItem_guess->setPosition(ccp(winsize.width-16, winsize.height-16));
	
	CCMenu *ingameMenu = CCMenu::menuWithItems(menuItem_guess, NULL);
	ingameMenu->setPosition(CCPointZero);
	
	this->addChild(ingameMenu, 1);
}

void GameplayLayer::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GameplayLayer::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
	CCPoint location = touch->locationInView(touch->view());
    location = CCDirector::sharedDirector()->convertToGL(location);
	
	int index = puzzle->checkTouch(location);
	if (index != -1)
	{
		puzzle->makeCellVisible(index);
		return true;
	}
	
	return false;
}

void GameplayLayer::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{	
	
}

void GameplayLayer::guess_pressed(CCObject* pSender)
{
	GameplayLayer *pStart = (GameplayLayer*)((CCMenuItem*)pSender)->getUserData();
	pStart->puzzle->drawResultImage();
}
