#include "cocos2d.h"
#include "IntroScene.h"

class LoadingScene : public cocos2d::Scene {
public:
	LoadingScene();
	~LoadingScene();
	
	CREATE_FUNC(LoadingScene);
	void onEnter() override;

private:
	void loadingCallBack();
};