#ifndef __HERO_H__
#define __HERO_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Terrain.h"

using namespace cocos2d;

#define NUM_PREV_VELS 9

class Hero:public Sprite {
	b2World *_world;
	b2Body *_body;
	bool _awake;
	b2Vec2 _prevVels[NUM_PREV_VELS];
	int _nextVel;
	
	CCAnimation *_normalAnim;
	CCRepeatForever *_normalAnimate;
	
	void createBody();
public:
	bool initWithWorld(b2World* world);
	void update();
	void wake();
	void dive();
	void limitVelocity();
	bool getAwake() { return _awake; }
	bool setAwake(bool awake) { _awake = awake; }
	void nodive();
	void runForceAnimation();
	void runNormalAnimation();
};

#endif
