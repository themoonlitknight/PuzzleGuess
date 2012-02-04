//
//  Levels.h
//  PuzzleGuess
//
//  Created by Francesco on 23/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PuzzleGuess_Levels_h
#define PuzzleGuess_Levels_h

#import "cocos2d.h"
#import "settings.h"

class LevelsLayer : public cocos2d::CCLayer
{	
	void setImageDb();
	void setUpLevelsMenu();
	void levelSelected(CCObject* pSender);
	void back_pressed(CCObject* pSender);
	
public:
    virtual ~LevelsLayer();
    bool init();
    LAYER_NODE_FUNC(LevelsLayer);

	// overload methods for touches
	//	void registerWithTouchDispatcher();
	//	bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	//	void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	
	static int levelunlocked[CATEGORIES];
	static int selectedCategory;
	static int selectedLevel;
	static string imageName;
	static string imagedb[LEVELS];
};

class LevelsScene : public cocos2d::CCScene
{	
public:
    LevelsScene():_layer(NULL) {};
    ~LevelsScene();
    bool init();
    SCENE_NODE_FUNC(LevelsScene);
	
    CC_SYNTHESIZE_READONLY(LevelsLayer*, _layer, Layer);
};

#endif
