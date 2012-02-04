//
//  Utility.cpp
//  PuzzleGuess
//
//  Created by Francesco on 24/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Utility.h"

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

CCSprite *maskedSpriteWithSprite(CCSprite *textureSprite, CCSprite *maskSprite)
{
	CCRenderTexture *rt = CCRenderTexture::renderTextureWithWidthAndHeight(maskSprite->getContentSizeInPixels().width, maskSprite->getContentSizeInPixels().height);
	
	int px = maskSprite->getContentSize().width/2;
	int py = maskSprite->getContentSize().height/2;
	maskSprite->setPosition(ccp(px,py));
	px = textureSprite->getContentSize().width/2;
	py = textureSprite->getContentSize().height/2;
	textureSprite->setPosition(ccp(px,py));
	
	maskSprite->setBlendFunc((ccBlendFunc){GL_ONE, GL_ZERO});
	textureSprite->setBlendFunc((ccBlendFunc){GL_DST_ALPHA, GL_ZERO});
	
	rt->begin();
	maskSprite->visit();
	textureSprite->visit();
	rt->end();
	
	CCSprite *retval = CCSprite::spriteWithTexture(rt->getSprite()->getTexture());
	retval->setFlipY(true);
	return retval;
}

string getImageNameFromLevel(int selectedlevel, int numalt, string *imagedb)
{
	char suffix[8];
	sprintf(suffix, "%d.png", arc4random() % numalt);
	string imagename = imagedb[selectedlevel];
	imagename.append(string(suffix));
	
	return imagename;
}

void coord::set(int _x, int _y)
{
	x = _x;
	y = _y;
}

bool coord::operator==(coord _b)
{
	if ((this->x == _b.x) && (this->y == _b.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}