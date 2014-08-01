#include "LoadingScene.h"

LoadingScene::LoadingScene()
{
	cocos2d::log("loading scene constructed");
}

LoadingScene::~LoadingScene()
{
	cocos2d::log("loading scene destructed");
}

void LoadingScene::onEnter()
{
	cocos2d::Scene::onEnter();
	
	cocos2d::LayerColor* bg = cocos2d::LayerColor::create(cocos2d::Color4B::WHITE);
	this->addChild(bg);
	
	auto logo = cocos2d::Sprite::create("logo.png");
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	logo->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
	this->addChild(logo);
	
	// start ansyc method load the atlas.png
	//Director::getInstance()->getTextureCache()->addImageAsync("atlas.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	
	Loader::loadEverything(CC_CALLBACK_0(LoadingScene::loadingCallBack, this));
}

void LoadingScene::loadingCallBack()
{
	
	auto scene = IntroScene::create();
	cocos2d::TransitionScene *transition = cocos2d::TransitionFade::create(1, scene);
	cocos2d::Director::getInstance()->replaceScene(transition);
}
