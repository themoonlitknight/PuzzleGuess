//
//  Category.h
//  PuzzleGuess
//
//  Created by Francesco on 24/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PuzzleGuess_Category_h
#define PuzzleGuess_Category_h

#import "cocos2d.h"
#import "settings.h"

class CategoryLayer : public cocos2d::CCLayer
{	
	void setUpCategoryMenu();
	void categorySelected(CCObject* pSender);
	
public:
    virtual ~CategoryLayer();
    bool init();
    LAYER_NODE_FUNC(CategoryLayer);
	
	// overload methods for touches
	//	void registerWithTouchDispatcher();
	//	bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	//	void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
};

class CategoryScene : public cocos2d::CCScene
{	
public:
    CategoryScene():_layer(NULL) {};
    ~CategoryScene();
    bool init();
    SCENE_NODE_FUNC(CategoryScene);
	
    CC_SYNTHESIZE_READONLY(CategoryLayer*, _layer, Layer);
};


#endif
