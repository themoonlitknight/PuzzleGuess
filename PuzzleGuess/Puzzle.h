//
//  Cell.h
//  testCocos2d-x
//
//  Created by Francesco on 25/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef testCocos2d_x_Cell_h
#define testCocos2d_x_Cell_h

#import "cocos2d.h"
#import "RandExtract.h"

using namespace cocos2d;

#define MAXCELLS 10
#define dimX 32
#define dimY 32

class block {
public:
	int x;
	int y;
	
	void set(int _x, int _y);
	bool operator==(block _b);
};

static string currentImageName;
static int currentImageIndex;

class Puzzle {
	CCLayer *layer;
	CCSprite *cell[MAXCELLS], *maskedempty;
	CCSpriteFrame *cellframe;
	int numsprites;
	CCTexture2D *tex_empty, *tex_image, *tex_cellmask;
	int t_raise, t_duration;
	int numCellX, numCellY;
	block cellpos[MAXCELLS];
	CCSize winsize;
	RandExtract *extraction;
	
	CCPoint *taken;	//array of cells touched by the player
	int numtaken;
	
public:
	Puzzle(CCLayer *l, CCTexture2D *texE, CCTexture2D *texM, int n);
	~Puzzle();
	void start();
	void raiseBlocks(CCNode* sender, void* pData);
	void lowerBlocks(CCNode* sender, void* pData);
	int checkTouch(CCPoint touchpos); 
	void makeCellVisible(int index);
	
	void setCellEmpty(CCTexture2D *tex);
	void setCellMask(CCTexture2D *tex);
	void setImage(CCTexture2D *tex);
	void setNumCells(int n);
	void setTimings(float a, float b);
	static void setCurrentImageName(string name) {currentImageName = name;};
	static string getCurrentImageName() {return currentImageName;};
	static void setCurrentImageIndex(int index) {currentImageIndex = index;};
	static int getCurrentImageIndex() {return currentImageIndex;};
	
	CCSprite *spriteImageMask();
	void drawResultImage();
};

#endif
