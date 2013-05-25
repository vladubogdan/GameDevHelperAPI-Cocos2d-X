//
//  Sprites_LoadSpriteFromPVRTest.cpp
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#include "Sprites_LoadSpriteFromPVRTest.h"
#include "HelloWorldScene.h"
#include "GameDevHelper.h"
using namespace cocos2d;

Sprites_LoadSpriteFromPVRTest::~Sprites_LoadSpriteFromPVRTest()
{
	// cpp don't need to call super dealloc
	// virtual destructor will do this
}

Sprites_LoadSpriteFromPVRTest::Sprites_LoadSpriteFromPVRTest()
{
}

CCScene* Sprites_LoadSpriteFromPVRTest::scene()
{
	CCScene * scene = NULL;
	do
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
        
		// 'layer' is an autorelease object
		Sprites_LoadSpriteFromPVRTest *layer = Sprites_LoadSpriteFromPVRTest::create();
		CC_BREAK_IF(! layer);
        
		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);
    
	// return the scene
	return scene;
}

std::string Sprites_LoadSpriteFromPVRTest::initTest()
{
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
#if 1
    // Use batch node. Faster
    //when using batches - load a batch node using the generated image
    batchNodeParent = CCSpriteBatchNode::create("fruitsPVR_fruits.pvr", 100);
    this->addChild(batchNodeParent, 0);
#endif
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    //load into the sprite frame cache the plist generated by SH
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fruitsPVR_fruits.plist");
    
    this->executeTestCodeAtPosition(ccp(s.width/2, s.height/2));
    
    return "Tap screen to create sprites from a PVR image file.";
}

void Sprites_LoadSpriteFromPVRTest::executeTestCodeAtPosition(CCPoint p)
{
    std::vector<std::string> spriteFrameNames;
    spriteFrameNames.push_back("fruit1");
    spriteFrameNames.push_back("fruit2");
    spriteFrameNames.push_back("fruit3");
    spriteFrameNames.push_back("fruit4");
    spriteFrameNames.push_back("fruit5");
    spriteFrameNames.push_back("fruit6");
    spriteFrameNames.push_back("fruit7");
    spriteFrameNames.push_back("fruit8");
    
    int spriteNameIdx = arc4random() % spriteFrameNames.size();
    
    std::string sprFrameName = spriteFrameNames[spriteNameIdx];
    
    //if you want to load color, opacity and other properties set on sprites inside SH
    //you must use a GHSprite to do that.
    //GHSprite is a subclass of CCSprite that adds some helper methods
    GHSprite* newSpr = GHSprite::createWithSpriteFrameName(sprFrameName.c_str());
    
    
    //else you can also use a CCSprite
    //    CCSprite* newSpr = CCSprite::createWithSpriteFrameName(sprFrameName.c_str());
    
    newSpr->setPosition(p);
    
    if(batchNodeParent != NULL){//if we use batch nodes we must add the sprite to its batch parent
        batchNodeParent->addChild(newSpr);
    }
    else{//if we dont use batch nodes then we must add the sprite to a normal node - e.g the layer or another node
        this->addChild(newSpr);
    }
}
