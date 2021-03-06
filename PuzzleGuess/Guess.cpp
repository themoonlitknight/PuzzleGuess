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
int GuessScene::num_instance;

//******** GuessScene ********
bool GuessScene::init()
{
	if( CCScene::init() )
	{
		GuessScene::num_instance++;
		
		// create the GuessLayer
		this->_layer = GuessLayer::node();
		this->_layer->retain();
		this->addChild(_layer);
		
		//add the image to the GuessLayer
		this->imageResult->setAnchorPoint(ccp(0,0));
		this->imageResult->setPosition(ccp(0,0));
		this->_layer->addChild(imageResult);
		
		// create the ChoiceLayer
		this->choiceLayer = new ChoiceLayer();
		this->choiceLayer->setAlternatives();
		
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
	
	delete this->choiceLayer;
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
	
	setupMenu();
	
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
	
	//action transition
	GuessScene::instance->choiceLayer->altMenu->setScale(0.1);
	CCScaleTo *scaleup = CCScaleTo::actionWithDuration(0.25, 1);
	CCAction *scaleup_ = CCEaseElasticOut::actionWithAction(scaleup);
	GuessScene::instance->choiceLayer->altMenu->runAction(scaleup_);
	
	return true;
}

void GuessLayer::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event)
{	
	
}

/* /\/\/\ MENU /\/\/\ */
void GuessLayer::setupMenu()
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	
	CCMenu *ingameMenu = CCMenu::menuWithItems(NULL);
	
	// 'menu' item
	CCMenuItemImage *menuItem_menu = CCMenuItemImage::itemFromNormalImage(MENUITEM_MENU, MENUITEM_MENU, this, menu_selector(GuessLayer::menu_pressed));
	menuItem_menu->setUserData(this);
	menuItem_menu->setPosition(ccp(winsize.width-80, winsize.height-MENUMARGIN/2));
	ingameMenu->addChild(menuItem_menu, 0);
	
	if (GuessScene::num_instance < ATTEMPTS)
	{
		// 'fill' item
		CCMenuItemImage *menuItem_fill = CCMenuItemImage::itemFromNormalImage(MENUITEM_FILL, MENUITEM_FILL, this, menu_selector(GuessLayer::fill_pressed));
		menuItem_fill->setPosition(ccp(winsize.width-MENUMARGIN/2, winsize.height-MENUMARGIN/2));
		ingameMenu->addChild(menuItem_fill, 0);
	}
	
	ingameMenu->setPosition(CCPointZero);
	
	this->addChild(ingameMenu, 1);
}

void GuessLayer::fill_pressed(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();
}

void GuessLayer::menu_pressed(CCObject* pSender)
{
	
}

//******** ChoiceLayer ********
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
//		alt[i] = CCSprite::spriteWithTexture(CCTextureCache::sharedTextureCache()->addImage(s.c_str()));
		alt[i] = CCMenuItemImage::itemFromNormalImage(s.c_str(), s.c_str(), GuessScene::instance, menu_selector(GuessScene::didChoice));
		alt[i]->setTag(i);
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
	
	altMenu = CCMenu::menuWithItems(NULL);
	
	for (int i = 0; i < NUMALT; i++) 
	{
		alt[i]->setScale(0.40);
		alt[i]->setPosition(centers[i]);
		altMenu->addChild(alt[i], 1);
	}
	
	altMenu->setPosition(CCPointZero);
	GuessScene::instance->addChild(altMenu, 1);
}

// method called when alternative is selected
void GuessScene::didChoice(CCObject* pSender)
{
	int choice = ((CCMenuItem*)pSender)->getTag();
	ResultScene *resultScene = new ResultScene();
	resultScene->setSuccess(choice == Puzzle::currentImageIndex);
	resultScene->init();
	resultScene->autorelease();
	CCDirector::sharedDirector()->popScene();
	CCDirector::sharedDirector()->replaceScene(resultScene);
}
