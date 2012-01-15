//
//  Guess.h
//  PuzzleGuess
//
//  Created by Francesco on 14/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PuzzleGuess_Guess_h
#define PuzzleGuess_Guess_h

#import "cocos2d.h"

#define NUMALT 4

class GuessLayer : public cocos2d::CCLayer
{
public:
    virtual ~GuessLayer();
    bool init();
    LAYER_NODE_FUNC(GuessLayer);
	
	cocos2d::CCSprite *imageResult;
	
	// overload methods for touches
	void registerWithTouchDispatcher();
	bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
};

class ChoiceLayer : public cocos2d::CCLayer
{
	cocos2d::CCSprite *alt[NUMALT];
	
public:
    //virtual ~ChoiceLayer();
    bool init();
    LAYER_NODE_FUNC(ChoiceLayer);
	
	void setAlternatives();
	void viewChoice();
	
	// overload methods for touches
	//	void registerWithTouchDispatcher();
	//	bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	//	void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
};

class GuessScene : public cocos2d::CCScene
{
	cocos2d::CCSprite *imageResult;
	
public:
    GuessScene():_layer(NULL) {};
    ~GuessScene();
    bool init();
    SCENE_NODE_FUNC(GuessScene);
	
    CC_SYNTHESIZE_READONLY(GuessLayer*, _layer, Layer);
	
	void setImageResult(cocos2d::CCSprite *i);
};

#endif
