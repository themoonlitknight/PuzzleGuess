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
	
	choiceLayer = ChoiceLayer::node();
	this->addChild(choiceLayer, 1);
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
	choiceLayer->viewChoice();
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

ChoiceLayer::~ChoiceLayer()
{
	for (int i = 0; i < NUMALT; i++)
	{
		alt[i]->release();
	}
}

void ChoiceLayer::setAlternatives()
{
	string _currentImageName = Puzzle::currentImageName;
	
	int i_dot =  _currentImageName.find_last_of('.');	// index corresponding to the dot of *.png
	string s = _currentImageName;
	
	// set images as the four choices
	for (int i = 0; i < NUMALT; i++) {
		s[i_dot-1] = i + 48;
		alt[i] = CCSprite::spriteWithTexture(CCTextureCache::sharedTextureCache()->addImage(s.c_str()));
		alt[i]->retain();
	}
}

void ChoiceLayer::viewChoice()
{
	//funzione che viene chiamata quando si tocca il GuessLayer

	CCSize csize = Puzzle::canvasSize;
	CCPoint centers[4];
	centers[0] = ccp(csize.width/4, csize.height*3/4);
	centers[1] = ccp(csize.width*3/4, csize.height*3/4);
	centers[2] = ccp(csize.width/4, csize.height/4);
	centers[3] = ccp(csize.width*3/4, csize.height/4);
	
	for (int i = 0; i < NUMALT; i++) {
		alt[i]->setScale(0.45);
		alt[i]->setPosition(centers[i]);
		this->addChild(alt[i]);
	}
	
}
