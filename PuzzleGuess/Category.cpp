//
//  Category.cpp
//  PuzzleGuess
//
//  Created by Francesco on 24/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Category.h"
#import "Levels.h"
#import "Utility.h"
#import "MainMenu.h"

using namespace cocos2d;

//******** CategoryScene ********
bool CategoryScene::init()
{
	if( CCScene::init() )
	{
		this->_layer = CategoryLayer::node();
		this->_layer->retain();
		this->addChild(_layer);
		
		return true;
	}
	else
	{
		return false;
	}
}

CategoryScene::~CategoryScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}

//******** CategoryLayer ********
bool CategoryLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	
	//code here
	this->setIsTouchEnabled(true);
	
	setUpCategoryMenu();
	
	return true;
}


/* /\/\/\ MENU /\/\/\ */
void CategoryLayer::setUpCategoryMenu()
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	
	CCMenu *categoryMenu = CCMenu::menuWithItems(NULL);
	
	// 'back' item
	CCMenuItemImage *menuItem_back;
	menuItem_back = CCMenuItemImage::itemFromNormalImage(MENUITEM_BACK, MENUITEM_BACK, this, menu_selector(CategoryLayer::back_pressed));
	menuItem_back->setPosition(ccp(35, 35));
	categoryMenu->addChild(menuItem_back, 0);
	
	// 'category' items
	CCMenuItemImage *menuItem_level[CATEGORIES];
	CCPoint positions[CATEGORIES];
	calcMenuItemPoints(positions, CATEGORIES, 2, 80, 150, 50);
	for (int i = 0; i < CATEGORIES; i++) {
		menuItem_level[i] = CCMenuItemImage::itemFromNormalImage(MENUITEM_CATEGORY, MENUITEM_CATEGORY, this, menu_selector(CategoryLayer::categorySelected));
		menuItem_level[i]->setPosition(positions[i]);
		menuItem_level[i]->setTag(i);
		categoryMenu->addChild(menuItem_level[i], 0);
	}
	
	categoryMenu->setPosition(CCPointZero);
	
	this->addChild(categoryMenu, 1);
}


CategoryLayer::~CategoryLayer()
{
	
}

// method called when a level is selected
void CategoryLayer::categorySelected(CCObject* pSender)
{
	LevelsLayer::selectedCategory = ((CCMenuItem*)pSender)->getTag();
	
	//TEMP
	printf(">>> %d\n",LevelsLayer::selectedCategory);
	
	LevelsScene *levelsScene = LevelsScene::node();
	CCDirector::sharedDirector()->replaceScene(levelsScene);
}

void CategoryLayer::back_pressed(CCObject* pSender)
{
	MainMenuScene *mainMenuScene = MainMenuScene::node();
	CCDirector::sharedDirector()->replaceScene(mainMenuScene);
}
