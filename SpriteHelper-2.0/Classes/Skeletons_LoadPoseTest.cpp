//
//  Skeletons_LoadPoseTest.cpp
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#include "Skeletons_LoadPoseTest.h"
#include "HelloWorldScene.h"
#include "GameDevHelper.h"
using namespace cocos2d;

Skeletons_LoadPoseTest::~Skeletons_LoadPoseTest()
{
	// cpp don't need to call super dealloc
	// virtual destructor will do this
}

Skeletons_LoadPoseTest::Skeletons_LoadPoseTest()
{
}

CCScene* Skeletons_LoadPoseTest::scene()
{
	CCScene * scene = NULL;
	do
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
        
		// 'layer' is an autorelease object
		Skeletons_LoadPoseTest *layer = Skeletons_LoadPoseTest::create();
		CC_BREAK_IF(! layer);
        
		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);
    
	// return the scene
	return scene;
}

std::string Skeletons_LoadPoseTest::initTest()
{
    skeleton = NULL;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    
    this->executeTestCodeAtPosition(ccp(s.width/2, s.height/2));
    
    return "Demonstrate loading skeleton poses.\nClick for next random pose...";
}

void Skeletons_LoadPoseTest::executeTestCodeAtPosition(CCPoint p)
{
    
    if(skeleton == NULL)
    {
        skeleton = GHSkeleton::createWithFile("skeletons/Officer_Officer.plist");
        
        skeleton->setPosition(p);
        this->addChild(skeleton);
    }
}

void Skeletons_LoadPoseTest::changePose(){
    
    std::vector<std::string> poseNames;
//    poseNames.push_back("DefaultPose");
//    poseNames.push_back("BowPose");
//    poseNames.push_back("DeathPose");
    poseNames.push_back("HatWave");
//    poseNames.push_back("IdlePose");
//    poseNames.push_back("PushPose");
    poseNames.push_back("ShootPose");
    
    int poseNameIdx = rand() % poseNames.size();
    
    std::string poseName = poseNames[poseNameIdx];
    
    if(skeleton){
        CCLog("CHANGE TO POSE NAME %s", poseName.c_str());
        skeleton->setPoseWithName(poseName.c_str());
    }
}


void Skeletons_LoadPoseTest::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    this->changePose();
}
