//
//  MainMenu.cpp
//  PuzzleGuess
//
//  Created by Francesco on 25/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "MainMenu.h"
#import "Category.h"

using namespace cocos2d;

//******** ResultScene ********
bool MainMenuScene::init()
{
	if( CCScene::init() )
	{
		this->_layer = MainMenuLayer::node();
		this->_layer->retain();
		this->addChild(_layer);
		
		return true;
	}
	else
	{
		return false;
	}
}

MainMenuScene::~MainMenuScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}

//******** ResultLayer ********
bool MainMenuLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	
	//code here
	setUpMainMenu();
	
	return true;
}


/* /\/\/\ MENU /\/\/\ */
void MainMenuLayer::setUpMainMenu()
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	
	CCMenu *menu = CCMenu::menuWithItems(NULL);
	
	// 'play' item
	CCMenuItemImage *menuItem_play;
	menuItem_play = CCMenuItemImage::itemFromNormalImage(MENUITEM_PLAY, MENUITEM_PLAY_SEL, this, menu_selector(MainMenuLayer::play_pressed));
	menu->addChild(menuItem_play, 0);
	
	// 'options' item
	CCMenuItemImage *menuItem_options;
	menuItem_options = CCMenuItemImage::itemFromNormalImage(MENUITEM_OPTIONS_SEL, MENUITEM_OPTIONS_SEL, this, menu_selector(MainMenuLayer::options_pressed));
	menu->addChild(menuItem_options, 0);

	
	//menu->setPosition(CCPointZero);
	menu->alignItemsVertically();
	
	this->addChild(menu, 1);
}

// 'play' has been pressed
void MainMenuLayer::play_pressed()
{
	CategoryScene *categoryScene = CategoryScene::node();
	CCDirector::sharedDirector()->replaceScene(categoryScene);
}

// 'options' has been pressed
void MainMenuLayer::options_pressed()
{
	
}

MainMenuLayer::~MainMenuLayer()
{
	
}
