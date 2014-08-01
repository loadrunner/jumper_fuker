#include "IntroScene.h"


IntroScene::IntroScene()
{
	cocos2d::log("intro scene constructed");
}

IntroScene::~IntroScene()
{
	cocos2d::log("intro scene destructed");
}

bool IntroScene::init()
{
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	
	cocos2d::SpriteFrameCache* frameCache = Loader::getFrameCache();
	
	auto bg = cocos2d::LayerColor::create(cocos2d::Color4B::BLUE);
	this->addChild(bg);
	
	auto playBtn  = cocos2d::MenuItemSprite::create(
			cocos2d::Sprite::createWithSpriteFrame(frameCache->getSpriteFrameByName("play_btn.png")), NULL,
			CC_CALLBACK_1(IntroScene::playCallback, this));
	playBtn->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
	
	auto closeBtn = cocos2d::MenuItemSprite::create(
			cocos2d::Sprite::createWithSpriteFrame(frameCache->spriteFrameByName("close_normal.png")),
			cocos2d::Sprite::createWithSpriteFrame(frameCache->spriteFrameByName("close_selected.png")),
			CC_CALLBACK_1(IntroScene::closeCallback, this));
	closeBtn->setPosition(origin.x + visibleSize.width - closeBtn->getContentSize().width / 2, origin.y + closeBtn->getContentSize().height / 2);
	
	auto menu = cocos2d::Menu::create(playBtn, closeBtn, NULL);
	menu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(menu, 1);
	
	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(IntroScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(IntroScene::onKeyReleased, this);
	
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
	return true;
}

void IntroScene::playCallback(cocos2d::Ref* pSender)
{
	auto scene = GameScene::createScene();
//	cocos2d::TransitionScene *transition = cocos2d::TransitionFade::create(1, scene);
	cocos2d::Director::getInstance()->replaceScene(scene);
}

void IntroScene::closeCallback(cocos2d::Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif
	
	cocos2d::Director::getInstance()->end();
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void IntroScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{
	cocos2d::log("pressed");
	CC_UNUSED_PARAM(keyCode);
	CC_UNUSED_PARAM(unused_event);
}

void IntroScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{
	cocos2d::log("button press %d", keyCode);
	cocos2d::log("released");
//	CC_UNUSED_PARAM(unused_event);
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		closeCallback(nullptr);
	}
}
