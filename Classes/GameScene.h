#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Loader.h"
#include "SimpleAudioEngine.h"

class GameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init() override;
	
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	
	CREATE_FUNC(GameScene);
	
private:
	cocos2d::Size mScreenSize;
	cocos2d::Size mVisibleSize;
	cocos2d::Vec2 mOrigin;
	
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