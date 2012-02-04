//
//  Levels.cpp
//  PuzzleGuess
//
//  Created by Francesco on 23/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Levels.h"
#import "Gameplay.h"
#import "Utility.h"
#import "Category.h"

using namespace cocos2d;

void setImageDb();

int LevelsLayer::levelunlocked[CATEGORIES]; //al posto di inizializzarlo qui, leggere il valore su disco
int LevelsLayer::selectedCategory;
string LevelsLayer::imageName;
int LevelsLayer::selectedLevel;
string LevelsLayer::imagedb[LEVELS];


//******** LevelsScene ********
bool LevelsScene::init()
{
	if( CCScene::init() )
	{		
		this->_layer = LevelsLayer::node();
		this->_layer->retain();
		this->addChild(_layer);
		
		return true;
	}
	else
	{
		return false;
	}
}

LevelsScene::~LevelsScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}

//******** LevelsLayer ********
bool LevelsLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	
	//code here
	this->setIsTouchEnabled(true);
	
	// fill data structures with image file name
	setImageDb();

	setUpLevelsMenu();
	
	return true;
}

/* /\/\/\ MENU /\/\/\ */
void LevelsLayer::setUpLevelsMenu()
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	
	CCMenu *levelsMenu = CCMenu::menuWithItems(NULL);
	
	// 'back' item
	CCMenuItemImage *menuItem_back;
	menuItem_back = CCMenuItemImage::itemFromNormalImage(MENUITEM_BACK, MENUITEM_BACK, this, menu_selector(LevelsLayer::back_pressed));
	menuItem_back->setPosition(ccp(35, 35));
	levelsMenu->addChild(menuItem_back, 0);
	
	// 'level' items
	CCMenuItemImage *menuItem_level[LEVELS];
	CCPoint positions[LEVELS];
	calcMenuItemPoints(positions, LEVELS, 3, 80, 150, 50);
	for (int i = 0; i < LEVELS; i++) {
		if (i <= LevelsLayer::levelunlocked[LevelsLayer::selectedCategory])
		{
			menuItem_level[i] = CCMenuItemImage::itemFromNormalImage(MENUITEM_UNLOCKED, MENUITEM_UNLOCKED, this, menu_selector(LevelsLayer::levelSelected));
		}
		else
		{
			menuItem_level[i] = CCMenuItemImage::itemFromNormalImage(MENUITEM_LOCKED, MENUITEM_LOCKED, this, menu_selector(LevelsLayer::levelSelected));
		}
		menuItem_level[i]->setPosition(positions[i]);
		menuItem_level[i]->setTag(i);
		levelsMenu->addChild(menuItem_level[i], 0);
	}
	
	levelsMenu->setPosition(CCPointZero);
	
	this->addChild(levelsMenu, 1);
}

LevelsLayer::~LevelsLayer()
{
	
}

void LevelsLayer::setImageDb()
{
	switch (LevelsLayer::selectedCategory) {
		case 0:
			imagedb[0] = "image";
			imagedb[1] = "image";
			imagedb[2] = "image";
			imagedb[3] = "image";
			imagedb[4] = "image";
			imagedb[5] = "image";
			imagedb[6] = "image";
			imagedb[7] = "image";
			imagedb[8] = "image";
			imagedb[9] = "image";
			imagedb[10] = "image";
			imagedb[11] = "image";
			break;
		
		case 1:
			imagedb[0] = "image";
			imagedb[1] = "image";
			imagedb[2] = "image";
			imagedb[3] = "image";
			imagedb[4] = "image";
			imagedb[5] = "image";
			imagedb[6] = "image";
			imagedb[7] = "image";
			imagedb[8] = "image";
			imagedb[9] = "image";
			imagedb[10] = "image";
			imagedb[11] = "image";
			break;

		case 2:
			imagedb[0] = "image";
			imagedb[1] = "image";
			imagedb[2] = "image";
			imagedb[3] = "image";
			imagedb[4] = "image";
			imagedb[5] = "image";
			imagedb[6] = "image";
			imagedb[7] = "image";
			imagedb[8] = "image";
			imagedb[9] = "image";
			imagedb[10] = "image";
			imagedb[11] = "image";
			break;

		case 3:
			imagedb[0] = "image";
			imagedb[1] = "image";
			imagedb[2] = "image";
			imagedb[3] = "image";
			imagedb[4] = "image";
			imagedb[5] = "image";
			imagedb[6] = "image";
			imagedb[7] = "image";
			imagedb[8] = "image";
			imagedb[9] = "image";
			imagedb[10] = "image";
			imagedb[11] = "image";
			break;

			
		default:
			break;
	}
}

// method called when a level is selected
void LevelsLayer::levelSelected(CCObject* pSender)
{
	LevelsLayer::selectedLevel = ((CCMenuItem*)pSender)->getTag();
	
	//TEMP
	printf(">>> %d\n",LevelsLayer::selectedLevel);
	
	LevelsLayer::imageName = getImageNameFromLevel(LevelsLayer::selectedLevel, NUMALT, LevelsLayer::imagedb);
	
	GameplayScene *gameplayScene = GameplayScene::node();
	CCDirector::sharedDirector()->replaceScene(gameplayScene);
}

void LevelsLayer::back_pressed(CCObject* pSender)
{
	CategoryScene *categoryScene = CategoryScene::node();
	CCDirector::sharedDirector()->replaceScene(categoryScene);
}
