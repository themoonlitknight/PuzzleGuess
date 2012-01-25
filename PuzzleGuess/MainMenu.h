//
//  MainMenu.h
//  PuzzleGuess
//
//  Created by Francesco on 25/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PuzzleGuess_MainMenu_h
#define PuzzleGuess_MainMenu_h

#import "cocos2d.h"

class MainMenuLayer : public cocos2d::CCLayer
{	
public:
    virtual ~MainMenuLayer();
    bool init();
    LAYER_NODE_FUNC(MainMenuLayer);
};

class MainMenuScene : public cocos2d::CCScene
{	
public:
    MainMenuScene():_layer(NULL) {};
    ~MainMenuScene();
    bool init();
    SCENE_NODE_FUNC(MainMenuScene);
	
    CC_SYNTHESIZE_READONLY(MainMenuLayer*, _layer, Layer);
};

#endif
