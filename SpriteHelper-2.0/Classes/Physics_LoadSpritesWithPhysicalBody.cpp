//
//  Physics_LoadSpritesWithPhysicalBody.cpp
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#include "Physics_LoadSpritesWithPhysicalBody.h"
#include "HelloWorldScene.h"
#include "GameDevHelper.h"
using namespace cocos2d;

Physics_LoadSpritesWithPhysicalBody::~Physics_LoadSpritesWithPhysicalBody()
{
    GHDirector::sharedDirector()->setPhysicalWorld(NULL);
    delete world;
    world = NULL;
}

Physics_LoadSpritesWithPhysicalBody::Physics_LoadSpritesWithPhysicalBody()
{
}

CCScene* Physics_LoadSpritesWithPhysicalBody::scene()
{
	CCScene * scene = NULL;
	do
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
        
		// 'layer' is an autorelease object
		Physics_LoadSpritesWithPhysicalBody *layer = Physics_LoadSpritesWithPhysicalBody::create();
		CC_BREAK_IF(! layer);
        
		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);
    
	// return the scene
	return scene;
}

std::string Physics_LoadSpritesWithPhysicalBody::initTest()
{
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
#if 1
    // Use batch node. Faster
    //when using batches - load a batch node using the generated image
    batchNodeParent = CCSpriteBatchNode::create("PhysicalSpritesObjects_Objects.png", 100);
    this->addChild(batchNodeParent, 0);
#endif
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    
    //load into the sprite frame cache the plist generated by SH
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PhysicalSpritesObjects_Objects.plist");
    
    
    this->initPhysics();
    
    
    GHDebugDrawLayer* debugDraw = GHDebugDrawLayer::createDebugDrawLayerWithWorld(world);
    this->addChild(debugDraw, 1000);

    
    
    this->executeTestCodeAtPosition(ccp(s.width/2, s.height/2));
    
    this->scheduleUpdate();
    
    
    return "Tap screen to create physical sprites.\nDemonstrate loading a sprite with physics\nand GameDevHelper debug drawing.";
}

void Physics_LoadSpritesWithPhysicalBody::executeTestCodeAtPosition(CCPoint p)
{
    
    std::vector<std::string> spriteFrameNames;
    spriteFrameNames.push_back("backpack");
    spriteFrameNames.push_back("banana");
    spriteFrameNames.push_back("bananabunch");
    spriteFrameNames.push_back("canteen");
    spriteFrameNames.push_back("hat");
    spriteFrameNames.push_back("pineapple");
    spriteFrameNames.push_back("statue");
    spriteFrameNames.push_back("ball");
    
    int spriteNameIdx = rand() % spriteFrameNames.size();
    
    std::string sprFrameName = spriteFrameNames[spriteNameIdx];
    
    
    //set the current world you want to use when creating bodies
    //in case you have multiple worlds just set the coresponding world before creating the sprites
    //CAREFULL - when deleting the box2d world you should also pass NULL to this method
    GHDirector::sharedDirector()->setPhysicalWorld(world);

    CCLog("PTM IS %d", PTM_RATIO );
    
    //set your custom PTM_RATIO
    GHDirector::sharedDirector()->setPointToMeterRatio(PTM_RATIO);


    
    
    //if you want to load color, opacity and other properties set on sprites inside SH
    //you must use a GHSprite to do that.
    //GHSprite is a subclass of CCSprite that adds some helper methods
    GHSprite* newSpr = GHSprite::createWithSpriteFrameName(sprFrameName.c_str());
    
    
    //else you can also use a CCSprite
    //CCSprite* newSpr = CCSprite::createWithSpriteFrameName(sprFrameName.c_str());
    
    if(newSpr){
        newSpr->setPosition(p);
        
        if(batchNodeParent != NULL){//if we use batch nodes we must add the sprite to its batch parent
            batchNodeParent->addChild(newSpr);
        }
        else{//if we dont use batch nodes then we must add the sprite to a normal node - e.g the layer or another node
            this->addChild(newSpr);
        }
    }
}


void Physics_LoadSpritesWithPhysicalBody::initPhysics()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);
    
    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);
    
    world->SetContinuousPhysics(true);
    
    
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
    
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    
    // Define the ground box shape.
    b2EdgeShape groundBox;
    
    // bottom
    
    groundBox.Set(b2Vec2(0,0), b2Vec2(s.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);
    
    // top
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // left
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(0,0));
    groundBody->CreateFixture(&groundBox,0);
    
    // right
    groundBox.Set(b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);
}

void Physics_LoadSpritesWithPhysicalBody::update(float dt)
{
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/
	
	int32 velocityIterations = 8;
	int32 positionIterations = 1;
	
	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	world->Step(dt, velocityIterations, positionIterations);
}


