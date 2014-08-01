#include <algorithm>

#include "AppDelegate.h"

USING_NS_CC;

const int AppDelegate::BASE_WIDTH = 160;
const int AppDelegate::BASE_HEIGHT = 120;
const float AppDelegate::SCALE_L_RES = 3.0;   //scale 0.250000
const float AppDelegate::SCALE_M_RES = 4.0;   //scale 0.333333
const float AppDelegate::SCALE_H_RES = 6.0;   //scale 0.500000
const float AppDelegate::SCALE_XH_RES = 8.0;  //scale 0.666666
const float AppDelegate::SCALE_XXH_RES = 12.0;//scale 1.000000

AppDelegate::AppDelegate()
{
	
}

AppDelegate::~AppDelegate()
{
	
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLView::createWithRect("Space Survivor", Rect(0, 0, 960, 700), 1);
		director->setOpenGLView(glview);
	}
	
	glview->setDesignResolutionSize(AppDelegate::BASE_WIDTH, AppDelegate::BASE_HEIGHT, ResolutionPolicy::NO_BORDER);
	CCSize frameSize = glview->getFrameSize();
	
	cocos2d::log("frame size %f, %f", frameSize.width, frameSize.height);
	
	std::vector<std::string> searchPath;
	
	if (frameSize.width >= 1920) {
		this->resolutionScale = AppDelegate::SCALE_XXH_RES;
		searchPath.push_back("gfx/xxh_res");
	} else if (frameSize.width >= 1280) {
		this->resolutionScale = AppDelegate::SCALE_XH_RES;
		searchPath.push_back("gfx/xh_res");
	} else if (frameSize.width >= 960) {
		this->resolutionScale = AppDelegate::SCALE_H_RES;
		searchPath.push_back("gfx/h_res");
	} else if (frameSize.width >= 640) {
		this->resolutionScale = AppDelegate::SCALE_M_RES;
		searchPath.push_back("gfx/m_res");
	} else {
		this->resolutionScale = AppDelegate::SCALE_L_RES;
		searchPath.push_back("gfx/l_res");
	}
	searchPath.push_back("sfx");
	FileUtils::getInstance()->setSearchPaths(searchPath);
	
	cocos2d::log("resolution scale %f, %f", resolutionScale, (AppDelegate::BASE_WIDTH * this->resolutionScale) / AppDelegate::BASE_WIDTH);
	
//	float scale = std::min(
//			frameSize.width / (frameSize.width * resolutionScale),
//			frameSize.height / (frameSize.height * resolutionScale)
//	);
	
	director->setContentScaleFactor(this->resolutionScale);
	
	// turn on display FPS
	director->setDisplayStats(true);
	
	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);
	
	// create a scene. it's an autorelease object
	auto scene = LoadingScene::create();
	
	// run
	director->runWithScene(scene);
	
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
	
	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
	
	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
