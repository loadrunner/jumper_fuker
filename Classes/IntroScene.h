#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "cocos2d.h"
#include "GameScene.h"

class IntroScene : public cocos2d::Scene {
public:
	IntroScene();
	~IntroScene();
	
	virtual bool init() override;
	
	void closeCallback(cocos2d::Ref* pSender);
	void playCallback(cocos2d::Ref* pSender);
	
	CREATE_FUNC(IntroScene);

private:
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

};

#endif // __MAINMENU_H__