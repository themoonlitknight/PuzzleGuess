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

#define MENUITEM_CATEGORY		"levelunlocked.png"
#define MENUITEM_CATEGORY_SEL	"levelunlocked.png"
void CategoryLayer::setUpCategoryMenu()
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	
	CCMenu *categoryMenu = CCMenu::menuWithItems(NULL);
	
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
	int selectedcategory = ((CCMenuItem*)pSender)->getTag();
	
	//TEMP
	printf(">>> %d\n",selectedcategory);
	
	LevelsLayer::numcategory = selectedcategory;
	
	LevelsScene *levelsScene = LevelsScene::node();
	CCDirector::sharedDirector()->replaceScene(levelsScene);
}
