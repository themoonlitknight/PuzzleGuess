//
//  Utility.h
//  PuzzleGuess
//
//  Created by Francesco on 24/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PuzzleGuess_Utility_h
#define PuzzleGuess_Utility_h

#import "cocos2d.h"

using namespace cocos2d;

void calcMenuItemPoints(CCPoint *p, int numitems, int numrows, int padX, int padY, int deltaY);
CCSprite *maskedSpriteWithSprite(CCSprite *textureSprite, CCSprite *maskSprite);

#endif
