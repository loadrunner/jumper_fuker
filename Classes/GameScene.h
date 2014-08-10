#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"

#include "Loader.h"
#include "Terrain.h"
#include "Hero.h"

class GameScene : public cocos2d::Layer, public b2ContactListener
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init() override;
	
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	
	CREATE_FUNC(GameScene);
	
private:
	cocos2d::Size mScreenSize;
	cocos2d::Size mVisibleSize;
	cocos2d::Vec2 mOrigin;
	
	Terrain* mTerrain;
	b2World* mWorld;
	Hero* mHero;
	bool mTapDown;
	
//	cocos2d::Vector<Obstacle*> mObstacles;
	
//	int mMeteorPoolIndex;
//	cocos2d::__Array *mMeteorPool;
	
//	cocos2d::SpriteBatchNode* mBackgroundSpriteBatch;
	
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	
	void update(float dt);
	
	void createPools();
	
//	void addObstacle();
//	void removeObstacle(Obstacle* obstacle);
	
	void exitGame();
	
	cocos2d::Vec2 boundsVerticesFull[4];
	cocos2d::Vec2 boundsVerticesEdge[4];
};

#endif // __GAMESCENE_H__
