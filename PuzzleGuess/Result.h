//
//  Result.h
//  PuzzleGuess
//
//  Created by Francesco on 17/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PuzzleGuess_Result_h
#define PuzzleGuess_Result_h

#import "cocos2d.h"

class ResultLayer : public cocos2d::CCLayer
{	
	void setUpMenu();
	void nextlevel_pressed(CCObject* pSender);
	void retrylevel_pressed(CCObject* pSender);
	void returnlevels_pressed(CCObject* pSender);
	void returnmain_pressed(CCObject* pSender);
	
public:
    virtual ~ResultLayer();
    bool init();
    LAYER_NODE_FUNC(ResultLayer);
	
	
	
	// overload methods for touches
//	void registerWithTouchDispatcher();
//	bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
//	void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
};

class ResultScene : public cocos2d::CCScene
{	
	bool success;
	
public:
    ResultScene():_layer(NULL) {instance = this;};
    ~ResultScene();
    bool init();
    //SCENE_NODE_FUNC(ResultScene);
	
    CC_SYNTHESIZE_READONLY(ResultLayer*, _layer, Layer);
	
	void setSuccess(bool _success) {success = _success;};
	bool getSuccess() {return success;};
	
	static ResultScene *instance;
};

#endif
