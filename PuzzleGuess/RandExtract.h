//
//  RandExtract.h
//  PuzzleGuess
//
//  Created by Francesco on 04/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef PuzzleGuess_RandExtract_h
#define PuzzleGuess_RandExtract_h

class RandExtract {
	int *randarray;
	
public:
	int max;
	
	RandExtract(int a, int b);
	~RandExtract();
	int extract();
};

#endif
