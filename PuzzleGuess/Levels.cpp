//
//  Levels.cpp
//  PuzzleGuess
//
//  Created by Francesco on 23/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Levels.h"
#import "Gameplay.h"
#import "Guess.h"

using namespace cocos2d;

void setImageDb();
void calcMenuItemPoints(CCPoint *p, int numitems, int numrows, int padX, int padY, int deltaY);

int LevelsLayer::numlevel = 0; //al posto di inizializzarlo qui, leggere il valore su disco
int LevelsLayer::numcategory = 0; // "
string LevelsLayer::imageName;
string imagedb[CATEGORIES][LEVELS];

void setImageDb()
{
	imagedb[0][0] = "image"; 
	//...
}

//******** LevelsScene ********
bool LevelsScene::init()
{
	if( CCScene::init() )
	{
		// fill data structures with image file name
		setImageDb();
		
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
		if (i <= LevelsLayer::numlevel)
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

// method called when a level is selected
void LevelsLayer::levelSelected(CCObject* pSender)
{
	int selectedlevel = ((CCMenuItem*)pSender)->getTag();
	
	//TEMP
	printf(">>> %d\n",selectedlevel);
	
	char suffix[8];
	sprintf(suffix, "%d.png", arc4random() % NUMALT);
	string imagename = imagedb[numcategory][selectedlevel];
	imagename.append(string(suffix));
	
	LevelsLayer::imageName = imagename;
	
	GameplayScene *gameplayScene = GameplayScene::node();
	CCDirector::sharedDirector()->replaceScene(gameplayScene);
}

void calcMenuItemPoints(CCPoint *p, int numitems, int numrows, int padX, int padY, int deltaY)
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	int n = (ceilf)((float)numitems / (float)numrows);
	int deltaC = (int)((winsize.width - 2*padX) / (float)(n - 1));
	
	int y = winsize.height - padY;
	for (int i = 0; i < numrows; i++) {
		for (int j = 0; j < (i != numrows-1 ? n : (numitems%n == 0 ? n : numitems%n)); j++) {
			p[i*n+j] = ccp(padX + deltaC*j, y);
		}
		y -= deltaY;
	}
}
