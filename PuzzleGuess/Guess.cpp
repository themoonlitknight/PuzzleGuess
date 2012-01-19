//
//  Guess.cpp
//  PuzzleGuess
//
//  Created by Francesco on 14/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Guess.h"
#import "Puzzle.h"
#import "Result.h"

using namespace cocos2d;

GuessScene *GuessScene::instance;

//******** GuessScene ********
bool GuessScene::init()
{
	if( CCScene::init() )
	{
		// create the GuessLayer
		this->_layer = GuessLayer::node();
		this->_layer->retain();
		this->addChild(_layer);
		
		//add the image to the GuessLayer
		this->imageResult->setAnchorPoint(ccp(0,0));
		this->imageResult->setPosition(ccp(0,0));
		this->_layer->addChild(imageResult);
		
		// create the ChoiceLayer
		this->choiceLayer = ChoiceLayer::node();
		this->choiceLayer->setAlternatives();
		this->addChild(this->choiceLayer, 1);
		
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
	GuessScene::instance->choiceLayer->viewChoice();
	GuessScene::instance->choiceLayer->setIsTouchEnabled(true);
	
	//action transition
	GuessScene::instance->choiceLayer->setScale(0.1);
	CCScaleTo *scaleup = CCScaleTo::actionWithDuration(0.25, 1);
	CCAction *scaleup_ = CCEaseElasticOut::actionWithAction(scaleup);
	GuessScene::instance->choiceLayer->runAction(scaleup_);
	
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
		alt[i]->setTag(i+10);	// index = tag - 10
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
		alt[i]->setScale(0.40);
		alt[i]->setPosition(centers[i]);
		this->addChild(alt[i]);
	}
	
}

// method called when alternative is selected
void ChoiceLayer::didChoice()
{
	ResultScene *resultScene = ResultScene::node();
	resultScene ->getLayer()->success = choice == Puzzle::currentImageIndex;	
	CCDirector::sharedDirector()->replaceScene(resultScene);
}

void ChoiceLayer::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}

bool ChoiceLayer::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{	
	
	return true;
}

void ChoiceLayer::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{	
	
}
