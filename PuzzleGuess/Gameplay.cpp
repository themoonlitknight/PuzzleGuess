//
//  Gameplay.cpp
//  PuzzleGuess
//
//  Created by Francesco on 13/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Gameplay.h"
#import "Guess.h"

using namespace cocos2d;

string Puzzle::currentImageName;
int Puzzle::currentImageIndex;
CCSize Puzzle::canvasSize;

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
	
	// code here
	//touch
	this->setIsTouchEnabled(true);
	
	
	CCTextureCache *texcache = CCTextureCache::sharedTextureCache();
	
	// choose and load images
	string imageName = extractImageName();		// choose randomly an image from the pool
	int i_dot =  imageName.find_last_of('.');	// index corresponding to the dot of *.png
	string s = imageName;
	for (int i = 0; i < NUMALT; i++) {			// put the set of images in cache
		s[i_dot-1] = i + 48;					// ascii number to char conversion
		texcache->addImage(s.c_str());
	}
	int imageIndex = (int)(imageName[i_dot-1] - 48); // ascii char to number conversion
	// ______________________
	
	texcache->addImage("cellempty.png");
	texcache->addImage("cellalpha.png");
	
	// set up Puzzle instance
	puzzle = new Puzzle(this, texcache->addImage("cellempty.png"), texcache->addImage("cellalpha.png"), 140);
	puzzle->setImage(texcache->addImage(imageName.c_str()));
	Puzzle::currentImageName = imageName;
	Puzzle::currentImageIndex = imageIndex;
	puzzle->setTimings(60, 59.8);
	puzzle->start();
	// ______________________
	
	// set up menu
	setupMenu();
	
	return true;
}

GameplayLayer::~GameplayLayer()
{
	delete puzzle;
}

string GameplayLayer::extractImageName()
{
	string s = "image1.png";
	return s;
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
