//
//  Result.cpp
//  PuzzleGuess
//
//  Created by Francesco on 17/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Result.h"

using namespace cocos2d;

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
	this->setIsTouchEnabled(true);

	
	return true;
}

ResultLayer::~ResultLayer()
{
	
}