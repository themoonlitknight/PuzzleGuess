//
//  Cell.cpp
//  testCocos2d-x
//
//  Created by Francesco on 25/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "Puzzle.h"
#import "Guess.h"
#import "Gameplay.h"

CCSprite *maskedSpriteWithSprite(CCSprite *textureSprite, CCSprite *maskSprite);

void block::set(int _x, int _y)
{
	x = _x;
	y = _y;
}

bool block::operator==(block _b)
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

Puzzle::Puzzle(CCLayer *l, CCTexture2D *texE, CCTexture2D *texM, int n)
{  
	Puzzle::canvasSize = CCDirector::sharedDirector()->getWinSize();
	Puzzle::canvasSize.height -= dimY;	//leave space at the top
	
	layer = l;
	tex_empty = texE;
	tex_cellmask = texM;
	numsprites = n;
	
	maskedempty = maskedSpriteWithSprite(CCSprite::spriteWithTexture(tex_empty), CCSprite::spriteWithTexture(tex_cellmask));
	cellframe = CCSpriteFrame::frameWithTexture(maskedempty->getTexture(), CCRectMake(0, 0, dimX, dimY));
	cellframe->retain();
	
	for (int i = 0; i < MAXCELLS; i++) {
		cell[i] = CCSprite::spriteWithSpriteFrame(cellframe);
		cell[i]->retain();
		cell[i]->setIsVisible(false);
		cell[i]->setAnchorPoint(ccp(0,0));
	}
	for (int i = 0; i < n; i++) {
		cell[i]->setIsVisible(true);
	}
	
	//calc number of cells
	numCellX = Puzzle::canvasSize.width / dimX;
	numCellY = Puzzle::canvasSize.height / dimY;
	
	extraction = new RandExtract(0, numCellX * numCellY - 1);	//pass max and min included
	
	taken = new CCPoint[numCellX * numCellY];
	numtaken = 0;
}

Puzzle::~Puzzle()
{
	for (int i = 0; i < MAXCELLS; i++)
		cell[i]->release();
	
	cellframe->release();
	
	delete extraction;
	delete taken;
}

void Puzzle::start()
{
	raiseBlocks(this->layer, this);
	
//	//schedule
//	CCFiniteTimeAction *scheduled_action = CCSequence::actions(CCDelayTime::actionWithDuration(t_raise - t_duration),
//															   CCCallFuncND::actionWithTarget(layer, callfuncND_selector(Puzzle::raiseBlocks), this),
//															   NULL);
//	layer->runAction(scheduled_action);
}

void Puzzle::raiseBlocks(CCNode* sender, void* pData)
{
	Puzzle *p = (Puzzle *)pData;
	
	if (p->extraction->max >= p->numsprites) {
		for (int i = 0; i < p->numsprites; i++)
		{
			int rnumb = p->extraction->extract();
			int randX = rnumb % p->numCellX;
			int randY = rnumb / p->numCellX;
			
			p->cellpos[i].set(randX, randY);
		}
		
		for (int i = 0; i < p->numsprites; i++) {
			p->cell[i]->setDisplayFrame(p->cellframe);
			p->cell[i]->setPosition(ccp(dimX*p->cellpos[i].x, dimY*p->cellpos[i].y));
			p->layer->addChild(p->cell[i]);
			
			//action transition
			p->cell[i]->setScale(0.1);
			CCScaleTo *scaleup = CCScaleTo::actionWithDuration(0.25, 1);
			CCAction *scaleup_ = CCEaseElasticOut::actionWithAction(scaleup);
			p->cell[i]->runAction(scaleup_);
		}
		
		//schedule
		CCFiniteTimeAction *scheduled_action = CCSequence::actions(CCDelayTime::actionWithDuration(p->t_duration),
																   CCCallFuncND::actionWithTarget(p->layer, callfuncND_selector(Puzzle::lowerBlocks), pData),
																   NULL);
		p->layer->runAction(scheduled_action);
	}
	else
	{
		p->drawResultImage();
		//cells over
	}
}

void Puzzle::drawResultImage()
{
	CCSprite *imageMask = spriteImageMask();
	CCSprite *imageResult = maskedSpriteWithSprite(CCSprite::spriteWithTexture(tex_image), imageMask);

	//create and set a new GuessScene
	GuessScene *guessScene = new GuessScene();
	guessScene->setImageResult(imageResult);
	guessScene->init();
	guessScene->autorelease();
	CCDirector::sharedDirector()->pushScene(guessScene);
}

void Puzzle::lowerBlocks(CCNode* sender, void* pData)
{
	Puzzle *p = (Puzzle *)pData;
	
	//remove cells from layer
	for (int i = 0; i < p->numsprites; i++)
	{
		p->layer->removeChild(p->cell[i], false);
	}
	
	//schedule next cells
	CCFiniteTimeAction *scheduled_action = CCSequence::actions(CCDelayTime::actionWithDuration(((Puzzle *)pData)->t_raise - ((Puzzle *)pData)->t_duration),
															   CCCallFuncND::actionWithTarget(((Puzzle *)pData)->layer, callfuncND_selector(Puzzle::raiseBlocks), pData),
															   NULL);
	((Puzzle *)pData)->layer->runAction(scheduled_action);
}

int Puzzle::checkTouch(CCPoint touchpos)
{
	for (int i = 0; i < numsprites; i++) {
		CCPoint cellpos = cell[i]->getPosition();
		CCRect cellrect = CCRectMake(cellpos.x, cellpos.y, dimX, dimY);
		
		if (CCRect::CCRectContainsPoint(cellrect, touchpos))
		{
			return i;
		}
	}
	
	return -1;
}

void Puzzle::makeCellVisible(int index)
{
	CCPoint cellpos = cell[index]->getPosition();
	CCSprite *cellonimage = CCSprite::spriteWithTexture(tex_image, CCRectMake(cellpos.x, Puzzle::canvasSize.height-dimY-cellpos.y,dimX,dimY));
	cellonimage->setFlipY(true);
	CCSprite *maskedimage = maskedSpriteWithSprite(cellonimage, CCSprite::spriteWithTexture(tex_cellmask));
	CCSpriteFrame *cellimageframe = CCSpriteFrame::frameWithTexture(maskedimage->getTexture(), CCRectMake(0, 0, dimX, dimY));
	cell[index]->setDisplayFrame(cellimageframe);
	
	//put touched cell's position in the array
	taken[numtaken] = cellpos;
	numtaken++;
}

void Puzzle::setTimings(float a, float b)
{
	t_raise = a;
	t_duration = b;
}

void Puzzle::setCellEmpty(CCTexture2D *tex)
{
	tex_empty = tex;
}

void Puzzle::setCellMask(CCTexture2D *tex)
{
	tex_cellmask = tex;
}

void Puzzle::setImage(CCTexture2D *tex)
{
	tex_image = tex;
}

void Puzzle::setNumCells(int n)
{
	numsprites = n;
}

CCSprite *Puzzle::spriteImageMask() {
	
    // 1: Create new CCRenderTexture
    CCRenderTexture *rt = CCRenderTexture::renderTextureWithWidthAndHeight(Puzzle::canvasSize.width, Puzzle::canvasSize.height);
	
    // 2: Call CCRenderTexture:begin
    rt->beginWithClear(0, 0, 0, 0);
	
    // 3: Draw into the texture
	CCPoint vertices[4];
	
	glColor4ub(255, 255, 255, 255);
	for (int i = 0; i < numtaken; i++) {
		vertices[0] = ccp(taken[i].x, taken[i].y);
		vertices[1] = ccp(taken[i].x, taken[i].y + dimY);
		vertices[2] = ccp(taken[i].x + dimX, taken[i].y + dimY);
		vertices[3] = ccp(taken[i].x + dimX, taken[i].y);
		
		ccDrawPoly(vertices, 4, true, true);
	}
	
    // 4: Call CCRenderTexture:end
    rt->end();
	
    // 5: Create a new Sprite from the texture
	CCSprite *ret = CCSprite::spriteWithTexture(rt->getSprite()->getTexture());
	ret->setFlipY(true);
    return ret;
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