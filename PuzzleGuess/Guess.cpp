//
//  Guess.cpp
//  PuzzleGuess
//
//  Created by Francesco on 14/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Guess.h"
#import "Puzzle.h"

using namespace cocos2d;

//******** GuessScene ********
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

void GuessScene::setImageResult(cocos2d::CCSprite *i)
{
	imageResult = i;
}


//******** GuessLayer ********
bool GuessLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	
	//code here
	this->setIsTouchEnabled(true);
	
	ChoiceLayer *choiceLayer = ChoiceLayer::node();
	this->addChild(choiceLayer);
	choiceLayer->setAlternatives();
	
	return true;
}

GuessLayer::~GuessLayer()
{

}

void GuessLayer::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GuessLayer::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{	
	return true;
}

void GuessLayer::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{	
	
}


//******** ChoiceLayer ********
bool ChoiceLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	
	//code here
	
	
	return true;
}

void ChoiceLayer::setAlternatives()
{
	string currentImageName = Puzzle::getCurrentImageName();
	
	int i_dot =  currentImageName.find_last_of('.');	// index corresponding to the dot of *.png
	string s = currentImageName;
	
	//set images as the four choices
	for (int i = 0; i < NUMALT; i++) {
		s[i_dot-1] = i + 48;
		alt[i] = CCSprite::spriteWithTexture(CCTextureCache::sharedTextureCache()->addImage(s.c_str()));
	}
}

void viewChoice()
{
	//funzione che viene chiamata quando si tocca il GuessLayer
	
	
}
