#include "HelloWorldScene.h"

#include "Sprites_LoadSpriteFromPNGTest.h"
#include "Sprites_LoadSpriteFromPVRTest.h"
#include "Sprites_LoadSpriteFromPVRCCZTest.h"
#include "SheetAnimations_LoadAnimationTest.h"
#include "SheetAnimations_GameDevHelperAPI_ComplexAnimation.h"
#include "SheetAnimations_GameDevHelperAPI_RandomRepeatTime.h"
#include "SheetAnimations_GameDevHelperAPI_RandomFrames.h"
#include "Physics_LoadSpritesWithPhysicalBody.h"
#include "Physics_CollisionFiltering.h"
#include "Skeletons_LoadTest.h"
#include "Skeletons_LoadPoseTest.h"
#include "Skeletons_AnimationTest.h"
#include "Skeletons_AnimateAndMoveTest.h"
#include "Skeletons_TransitionTest.h"
#include "Skeletons_AnimationPlayMode.h"

using namespace cocos2d;


HelloWorld::~HelloWorld()
{
	// cpp don't need to call super dealloc
	// virtual destructor will do this
}

HelloWorld::HelloWorld()
{
}

#define MENU_TAG 2456

CCScene* HelloWorld::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		HelloWorld *layer = HelloWorld::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////
        this->setTouchEnabled(true);
        
        CCArray* itemsArray = CCArray::create();
        
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        CCMenuItemFont::setFontSize(14);

        if(s.height > 1024)
        {
            CCMenuItemFont::setFontSize(34);
        }
        
        std::string emptyMenu = "************************************************************************";

		CCMenuItemFont* item = CCMenuItemFont::create("Sprites - cocos2d-x - Load from PNG", this,
                                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(1);

        itemsArray->addObject(item);
        
        item = CCMenuItemFont::create("Sprites - cocos2d-x - Load from PVR", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(2);

        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Sprites - cocos2d-x - Load from PVR.CCZ", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(3);
        
        itemsArray->addObject(item);
        
        item = CCMenuItemFont::create(emptyMenu.c_str(), this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(-1);
        itemsArray->addObject(item);


        item = CCMenuItemFont::create("Animations - Cocos2d-x -> Load Animation from plist", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(4);

        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Animations - GameDevHelperAPI - Load Animation from plist & notifications", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(5);
    

        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Animations - GameDevHelperAPI - random frames", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(6);

        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Animations - GameDevHelperAPI - random repeat time", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(7);
        itemsArray->addObject(item);

        
        item = CCMenuItemFont::create(emptyMenu.c_str(), this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(-1);
        itemsArray->addObject(item);

        
        
        item = CCMenuItemFont::create("Physics - GameDevHelperAPI - load sprites with physical body", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(8);
        itemsArray->addObject(item);
        
        item = CCMenuItemFont::create("Physics - GameDevHelperAPI - physics collision filtering", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(9);
        itemsArray->addObject(item);
        
        item = CCMenuItemFont::create(emptyMenu.c_str(), this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(-1);
        itemsArray->addObject(item);
        
        item = CCMenuItemFont::create("Skeletons - GameDevHelperAPI - load skeleton", this,
                                      menu_selector(HelloWorld::menuCallback));
        itemsArray->addObject(item);
        item->setTag(10);
        
        item = CCMenuItemFont::create("Skeletons - GameDevHelperAPI - load skeleton pose", this,
                                      menu_selector(HelloWorld::menuCallback));
        itemsArray->addObject(item);
        item->setTag(11);
        
        item = CCMenuItemFont::create("Skeletons - GameDevHelperAPI - skeletal animation test", this,
                                      menu_selector(HelloWorld::menuCallback));
        itemsArray->addObject(item);
        item->setTag(12);

        item = CCMenuItemFont::create("Skeletons - GameDevHelperAPI - skeletal animate and move test", this,
                                      menu_selector(HelloWorld::menuCallback));
        itemsArray->addObject(item);
        item->setTag(13);

        item = CCMenuItemFont::create("Skeletons - GameDevHelperAPI - transition from one animation to another", this,
                                      menu_selector(HelloWorld::menuCallback));
        itemsArray->addObject(item);
        item->setTag(14);


        item = CCMenuItemFont::create("Skeletons - GameDevHelperAPI - animation play mode", this,
                                      menu_selector(HelloWorld::menuCallback));
        itemsArray->addObject(item);
        item->setTag(15);

        
        
        CCSize size = item->getContentSize();
        menuHeight = itemsArray->count()* (size.height+5);
                
        CCMenu* menu = CCMenu::createWithArray(itemsArray);
        menu->alignItemsVertically();
        menu->setTag(MENU_TAG);
        this->addChild(menu);
        
                
		bRet = true;
	} while (0);

	return bRet;
}

void HelloWorld::menuCallback(CCObject* sender)
{
    CCMenu* menu = (CCMenu*)sender;
    switch (menu->getTag()) {
        case 1:
            CCDirector::sharedDirector()->replaceScene(Sprites_LoadSpritesFromPNGTest::scene());
            break;

        case 2:
            CCDirector::sharedDirector()->replaceScene(Sprites_LoadSpriteFromPVRTest::scene());
            break;

        case 3:
            CCDirector::sharedDirector()->replaceScene(Sprites_LoadSpriteFromPVRCCZTest::scene());
            
            break;

        case 4:
            CCDirector::sharedDirector()->replaceScene(SheetAnimations_LoadAnimationTest::scene());
            
            break;

        case 5:
            CCDirector::sharedDirector()->replaceScene(SheetAnimations_GameDevHelperAPI_ComplexAnimation::scene());

            break;

        case 6:
            CCDirector::sharedDirector()->replaceScene(SheetAnimations_GameDevHelperAPI_RandomFrames::scene());
            
            break;

        case 7:
            CCDirector::sharedDirector()->replaceScene(SheetAnimations_GameDevHelperAPI_RandomRepeatTime::scene());
            break;
            
        case 8:
            CCDirector::sharedDirector()->replaceScene(Physics_LoadSpritesWithPhysicalBody::scene());
            break;
            
        case 9:
            CCDirector::sharedDirector()->replaceScene(Physics_CollisionFiltering::scene());
            break;
            
        case 10:
            CCDirector::sharedDirector()->replaceScene(Skeletons_LoadTest::scene());
            break;
            
        case 11:
            CCDirector::sharedDirector()->replaceScene(Skeletons_LoadPoseTest::scene());
            break;
            
        case 12:
            CCDirector::sharedDirector()->replaceScene(Skeletons_AnimationTest::scene());
            break;
            
        case 13:
            CCDirector::sharedDirector()->replaceScene(Skeletons_AnimateAndMoveTest::scene());
            break;
        
        case 14:
            CCDirector::sharedDirector()->replaceScene(Skeletons_TransitionTest::scene());
            break;

        case 15:
            CCDirector::sharedDirector()->replaceScene(Skeletons_AnimationPlayMode::scene());
            break;

            
        default:

            break;
    }
//    CCLOG("Clicked on menu sprite item %d", menu->getTag());
///    CCDirector::sharedDirector()->replaceScene(anScene);
}

void HelloWorld::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
	CCPoint delta = touch->getDelta();

    CCMenu* menu = (CCMenu*)this->getChildByTag(MENU_TAG);

    if(menu){
        CCPoint menuPosition = menu->getPosition();

        CCSize s = CCDirector::sharedDirector()->getWinSize();
        
        CCPoint newPos = CCPoint(menuPosition.x, menuPosition.y + delta.y);
      
        if(menuHeight > s.height)
        {
            if(newPos.y < s.height - menuHeight/2)
                newPos.y = s.height - menuHeight/2;
            
            if(newPos.y > menuHeight/2)
                newPos.y = menuHeight/2;

            menu->setPosition(newPos);
        }
    }    
}



