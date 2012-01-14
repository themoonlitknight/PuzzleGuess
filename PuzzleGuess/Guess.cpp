//
//  Guess.cpp
//  PuzzleGuess
//
//  Created by Francesco on 14/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Guess.h"

using namespace cocos2d;

bool GuessScene::init()
{
	if( CCScene::init() )
	{
		this->_layer = GuessLayer::node();
		this->_layer->retain();
		this->addChild(_layer);
		
		//add the image to the layer
		this->imageResult->setAnchorPoint(ccp(0,0));
		this->imageResult->setPosition(ccp(0,0));
		this->_layer->addChild(imageResult);
		
		return true;
	}
	else
	{
		return false;
	}
}

GuessScene::~GuessScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}

bool GuessLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	
	//code here

	
	return true;
}

GuessLayer::~GuessLayer()
{

}
