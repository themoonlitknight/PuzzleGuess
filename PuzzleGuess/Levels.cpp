//
//  Levels.cpp
//  PuzzleGuess
//
//  Created by Francesco on 23/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Levels.h"

using namespace cocos2d;

void calcMenuItemPoints(CCPoint *p, int numitems, int numrows, int padX, int padY, int deltaY);

int LevelsLayer::numlevel = 0; //al posto di inizializzarlo qui, leggere il valore su disco
string LevelsLayer::category;

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
	
	setUpLevelsMenu();
	
	return true;
}

void LevelsLayer::setUpLevelsMenu()
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	
	CCMenu *levelsMenu = CCMenu::menuWithItems(NULL);
	
	CCMenuItemImage *menuItem_level[LEVELS];
	CCPoint positions[LEVELS];
	calcMenuItemPoints(positions, LEVELS, 3, 80, 150, 50);
	
	for (int i = 0; i < LEVELS; i++) {
		menuItem_level[i] = CCMenuItemImage::itemFromNormalImage("levelunlocked.png", "levelunlocked.png", this, menu_selector(LevelsLayer::levelSelected));
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
	
	printf(">>> %d\n",selectedlevel);
}

void calcMenuItemPoints(CCPoint *p, int numitems, int numrows, int padX, int padY, int deltaY)
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	int n = numitems / numrows;
	int deltaC = (int)((winsize.width - 2*padX) / (float)(n - 1));
	
	int y = winsize.height - padY;
	for (int i = 0; i < numrows; i++) {
		for (int j = 0; j < (i != numrows-1 ? n : (numitems%n == 0 ? n : numitems%n)); j++) {
			p[i*n+j] = ccp(padX + deltaC*j, y);
		}
		y -= deltaY;
	}
}
