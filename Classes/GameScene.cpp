#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	
	// add layer as a child to scene
	scene->addChild(layer);
	
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}
	
	this->setKeypadEnabled(true);
	
	mScreenSize = Director::getInstance()->getWinSize();
	mVisibleSize = Director::getInstance()->getVisibleSize();
	mOrigin = Director::getInstance()->getVisibleOrigin();
	
	cocos2d::log("size %f, %f", mScreenSize.width, mScreenSize.height);
	cocos2d::log("visible size %f, %f", mVisibleSize.width, mVisibleSize.height);
	cocos2d::log("offset %f, %f", mOrigin.x, mOrigin.y);
	
	boundsVerticesFull[0] = cocos2d::Vec2(0, 0);
	boundsVerticesFull[1] = cocos2d::Vec2(mScreenSize.width, 0);
	boundsVerticesFull[2] = cocos2d::Vec2(mScreenSize.width, mScreenSize.height);
	boundsVerticesFull[3] = cocos2d::Vec2(0, mScreenSize.height);
	
	float border = mScreenSize.width * 0.01f;
	
	boundsVerticesEdge[0] = cocos2d::Vec2(border, border);
	boundsVerticesEdge[1] = cocos2d::Vec2(mScreenSize.width - border, border);
	boundsVerticesEdge[2] = cocos2d::Vec2(mScreenSize.width - border, mScreenSize.height - border);
	boundsVerticesEdge[3] = cocos2d::Vec2(border, mScreenSize.height - border);
	
	SpriteFrameCache* frameCache = Loader::getFrameCache();
	
//	mBackgroundSpriteBatch = SpriteBatchNode::createWithTexture(frameCache->spriteFrameByName("bg0000.png")->getTexture());
//	this->addChild(mBackgroundSpriteBatch);
	
	createPools();
	
	// Register Touch Event
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	this->schedule(schedule_selector(GameScene::update), 0.02f);
	
	return true;
}

void GameScene::update(float dt)
{
	/*
	int i, n;
	Node* target = this->hero;
	AbstractObject* projectile;
	cocos2d::Rect targetRect = hero->getCollisionRect();
	
	n = mObstacles.size();
	for (i = 0; i < n; i++)
	{
		projectile = mObstacles.at(i);
		
		if (targetRect.intersectsRect(projectile->getCollisionRect()))
		{
			cocos2d::log("collissiosndasdas with obstacle");
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("crash.ogg");
			mHeroHitDisabled = true;
			mHeroHitTimer = 3;
			
			this->hero->hit(3);
			
			mLives--;
			__String * value = __String::createWithFormat("%i", mLives);
			mLivesView->setString(value->getCString());
			
			break;
		}
	}
	*/
}
/*
void GameScene::addObstacle()
{
	cocos2d::log("add meteor!!");
	timeFromLastMeteor = 0;
	
	Obstacle* meteor = (Obstacle*) mMeteorPool->objectAtIndex(mMeteorPoolIndex);
	mMeteorPoolIndex++;
	if (mMeteorPoolIndex == mMeteorPool->count()) {
		mMeteorPoolIndex = 0;
	}
	
	int meteor_x = rand() % (int) mScreenSize.width;
	int meteor_target_x = rand() % (int) mScreenSize.width;
	meteor->reset();
	meteor->setPosition(Vec2(meteor_x, mScreenSize.height + meteor->boundingBox().size.height * 0.5));
	meteor->setVisible(true);
	meteor->resume();
	meteor->moveAction = ObjectMoveTo::create(4, Vec2(meteor_target_x, 0), CC_CALLBACK_0(GameScene::removeObstacle, this, meteor));
	meteor->runAction(meteor->moveAction);
	mObstacles.pushBack(meteor);
}

void GameScene::removeObstacle(Obstacle* obstacle)
{
	obstacle->setVisible(false);
	obstacle->pause();
	if (obstacle->moveAction != nullptr)
		obstacle->stopAction(obstacle->moveAction);
	
	mObstacles.eraseObject(obstacle, true);
}
*/

void GameScene::createPools()
{
	/*
	Obstacle* obstacle;
	mMeteorPool = cocos2d::__Array::createWithCapacity(50);
	mMeteorPool->retain();
	mMeteorPoolIndex = 0;
	for (int i = 0; i < 50; i++) {
		obstacle = Meteor::create();
		obstacle->setVisible(false);
		obstacle->pause();
		obstacle->setScale(2);
		mObstacleSpriteBatch->addChild(obstacle/*, kMiddleground, kSpriteMeteor*//*);
		mMeteorPool->addObject(obstacle);
	}
	*/
}

void GameScene::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);
}

bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	cocos2d::log("You touched %f, %f", touch->getLocationInView().x, touch->getLocationInView().y);
	
	return true;
}

void GameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	cocos2d::log("You moved %f, %f", touch->getLocationInView().x, touch->getLocationInView().y);
	
}

void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	cocos2d::log("You released %f, %f", touch->getLocationInView().x, touch->getLocationInView().y);
	
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	cocos2d::log("button press %d", keyCode);
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		exitGame();
	}
}

void GameScene::exitGame()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif
	
	Director::getInstance()->end();
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}