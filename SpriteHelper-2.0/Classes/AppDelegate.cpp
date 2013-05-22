#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    
    
    
    
    float scrWidth = CCEGLView::sharedOpenGLView()->getFrameSize().width;
    float scrHeight= CCEGLView::sharedOpenGLView()->getFrameSize().height;
    
    std::vector<std::string> res;
    
    if(scrWidth == 480 || scrHeight == 480){//very old iphones
        
        res.push_back("sd");
        
        CCFileUtils::sharedFileUtils()->setSearchPaths(res);
        CCDirector::sharedDirector()->setContentScaleFactor(1.0f);
    }
    else if(scrWidth == 640 || scrHeight == 640){ //check for both iphone4/4S and iphone5
        res.push_back("hd");
        
        CCFileUtils::sharedFileUtils()->setSearchPaths(res);
        CCDirector::sharedDirector()->setContentScaleFactor(2.0f);
    }
    else if(scrWidth == 1024 || scrHeight == 1024){ //ipad mini and old ipads
        
        res.push_back("ipad");
        CCFileUtils::sharedFileUtils()->setSearchPaths(res);
        CCDirector::sharedDirector()->setContentScaleFactor(1.0f);
    }
    else if(scrWidth == 2048 || scrHeight == 2048){ //ipad retina and mac platform
        
        res.push_back("ipadhd");
        
        CCFileUtils::sharedFileUtils()->setSearchPaths(res);
        CCDirector::sharedDirector()->setContentScaleFactor(2.0f);
    }
    
    
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
