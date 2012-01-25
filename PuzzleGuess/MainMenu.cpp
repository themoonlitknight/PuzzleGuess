//
//  MainMenu.cpp
//  PuzzleGuess
//
//  Created by Francesco on 25/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "MainMenu.h"

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
	
	return true;
}

MainMenuLayer::~MainMenuLayer()
{
	
}
