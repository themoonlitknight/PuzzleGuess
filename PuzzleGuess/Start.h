#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#import "cocos2d.h"

using namespace cocos2d;

class Start : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(Start);

//	// overload methods for touches
	void registerWithTouchDispatcher();
	bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

	~Start();
};

#endif // __START_SCENE_H__
