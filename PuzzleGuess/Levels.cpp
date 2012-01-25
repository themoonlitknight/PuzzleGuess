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

using namespace cocos2d;

void setImageDb();

int LevelsLayer::levelunlocked = 0; //al posto di inizializzarlo qui, leggere il valore su disco
int LevelsLayer::numcategory;
string LevelsLayer::imageName;


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

#define MENUITEM_UNLOCKED		"levelunlocked.png"
#define MENUITEM_UNLOCKED_SEL	"levelunlocked_sel.png"
#define MENUITEM_LOCKED		"levellocked.png"
#define MENUITEM_LOCKED_SEL	"levellocked_sel.png"
void LevelsLayer::setUpLevelsMenu()
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	
	CCMenu *levelsMenu = CCMenu::menuWithItems(NULL);
	
	CCMenuItemImage *menuItem_level[LEVELS];
	CCPoint positions[LEVELS];
	calcMenuItemPoints(positions, LEVELS, 3, 80, 150, 50);
	
	for (int i = 0; i < LEVELS; i++) {
		if (i <= LevelsLayer::levelunlocked)
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
	switch (LevelsLayer::numcategory) {
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
	int selectedlevel = ((CCMenuItem*)pSender)->getTag();
	
	//TEMP
	printf(">>> %d\n",selectedlevel);
	
	char suffix[8];
	sprintf(suffix, "%d.png", arc4random() % NUMALT);
	string imagename = imagedb[selectedlevel];
	imagename.append(string(suffix));
	
	LevelsLayer::imageName = imagename;
	
	GameplayScene *gameplayScene = GameplayScene::node();
	CCDirector::sharedDirector()->replaceScene(gameplayScene);
}
