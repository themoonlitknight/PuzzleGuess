//
//  RandExtract.cpp
//  PuzzleGuess
//
//  Created by Francesco on 04/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "RandExtract.h"
#import "cocos2d.h"

RandExtract::RandExtract(int a, int b)
{
	max = b - a + 1;	//maximum index+1
	randarray = new int[max];
	
	int x = a;
	for (int i = 0; i < max; i++) {
		randarray[i] = x;
		x++;
	}
}

RandExtract::~RandExtract()
{
	delete randarray;
}

int RandExtract::extract()
{
	int index = arc4random() % max;
	int number = randarray[index];
	randarray[index] = randarray[max-1];
	max--;
	return number;
}
