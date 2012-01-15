//
//  Gameplay.h
//  PuzzleGuess
//
//  Created by Francesco on 13/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PuzzleGuess_Gameplay_h
#define PuzzleGuess_Gameplay_h

#import "cocos2d.h"
#import "Puzzle.h"

class GameplayLayer : public cocos2d::CCLayer
{
	Puzzle *puzzle;
	
public:
	//methods
    virtual ~GameplayLayer();
    bool init();
    LAYER_NODE_FUNC(GameplayLayer);
	
	// overload methods for touches
	void registerWithTouchDispatcher();
	bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	
	void setupMenu();
	void guess_pressed(CCObject* pSender);
	string extractImageName();
};

class GameplayScene : public cocos2d::CCScene
{
public:
    GameplayScene():_layer(NULL) {};
    ~GameplayScene();
    bool init();
    SCENE_NODE_FUNC(GameplayScene);
	
    CC_SYNTHESIZE_READONLY(GameplayLayer*, _layer, Layer);
};

#endif
