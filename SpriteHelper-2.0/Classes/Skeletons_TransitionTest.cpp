//
//  Skeletons_AnimationTest.cpp
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#include "Skeletons_TransitionTest.h"
#include "HelloWorldScene.h"
#include "GameDevHelper.h"
using namespace cocos2d;

Skeletons_TransitionTest::~Skeletons_TransitionTest()
{
	// cpp don't need to call super dealloc
	// virtual destructor will do this
}

Skeletons_TransitionTest::Skeletons_TransitionTest()
{
}

CCScene* Skeletons_TransitionTest::scene()
{
	CCScene * scene = NULL;
	do
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
        
		// 'layer' is an autorelease object
		Skeletons_TransitionTest *layer = Skeletons_TransitionTest::create();
		CC_BREAK_IF(! layer);
        
		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);
    
	// return the scene
	return scene;
}

std::string Skeletons_TransitionTest::initTest()
{
    skeleton = NULL;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    
    GHSkeletalAnimationCache* cache = GHSkeletalAnimationCache::sharedSkeletalAnimationCache();
    cache->addSkeletalAnimationWithFile("skeletons/animations/BallPlay.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/Bow.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/Death.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/HatWave.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/HolsterGun.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/Idle.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/Push.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/Shoot.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/SoftWalk.plist");
    cache->addSkeletalAnimationWithFile("skeletons/animations/StrongWalk.plist");
    
    
    
    this->executeTestCodeAtPosition(ccp(s.width/2, s.height/2));
    
    return "Demonstrate transitioninig to new skeleton animation.\nTap on the screen to transition to another animation.\nTransition time is set high for demonstrating the effect.\nIn general you should use a small time.\nYou should only transition animations that are related (e.g from walk to run).\nIf you are not careful this may create unrealistic movement.\n";

    
//    return "Demonstrate skeletal animations.\nTap to change animation.\nWatch console for notifications.";
}

void Skeletons_TransitionTest::executeTestCodeAtPosition(CCPoint p)
{
    
    if(skeleton == NULL)
    {
        skeleton = GHSkeleton::createWithFile("skeletons/Officer_Officer.plist");
        
        skeleton->setPosition(p);
        this->addChild(skeleton);
    }
    
    if(skeleton){
        skeleton->playAnimationWithName("SoftWalk");
    }
}

void Skeletons_TransitionTest::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    changeAnimation();
}

void Skeletons_TransitionTest::changeAnimation(){
    
    
    std::vector<std::string> animNames;
    animNames.push_back("BallPlay");
    animNames.push_back("Bow");
    animNames.push_back("Death");
    animNames.push_back("HatWave");
    animNames.push_back("HolsterGun");
    animNames.push_back("Idle");
    animNames.push_back("Push");
    animNames.push_back("Shoot");
    animNames.push_back("SoftWalk");
    animNames.push_back("StrongWalk");
    
    int animNameIdx = rand() % animNames.size();
    
    std::string finalAnimName = animNames[animNameIdx];
    
    CCLog("TRANSITION TO ANIMIMATION %s", finalAnimName.c_str());
    
    if(skeleton){
        skeleton->transitionToAnimationWithNameInTime(finalAnimName.c_str(), 4);
    }
}


