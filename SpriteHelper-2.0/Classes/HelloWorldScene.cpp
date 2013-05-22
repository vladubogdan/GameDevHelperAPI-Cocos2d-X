#include "HelloWorldScene.h"

#include "Sprites_LoadSpriteFromPNGTest.h"
#include "Sprites_LoadSpriteFromPVRTest.h"
#include "Sprites_LoadSpriteFromPVRCCZTest.h"
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

		CC_BREAK_IF(! CCLayerColor::initWithColor( ccc4(0,0,0,255) ) );

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////
        this->setTouchEnabled(true);
        
        CCArray* itemsArray = CCArray::create();
        

		CCMenuItemFont* item = CCMenuItemFont::create("Sprites - Load from PNG", this,
                                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(1);
        itemsArray->addObject(item);
        
        item = CCMenuItemFont::create("Sprites - Load from PVR", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(2);
        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Sprites - Load from PVR.CCZ", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(3);
        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Test 4", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(4);
        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Test 5", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(5);
        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Test 6", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(6);
        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Test 7", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(7);
        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Test 8", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(8);
        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Test 9", this,
                                      menu_selector(HelloWorld::menuCallback));
        item->setTag(9);
        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Test 10", this,
                                      menu_selector(HelloWorld::menuCallback));
        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Test 11", this,
                                      menu_selector(HelloWorld::menuCallback));
        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Test 12", this,
                                      menu_selector(HelloWorld::menuCallback));
        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Test 13", this,
                                      menu_selector(HelloWorld::menuCallback));
        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Test 14", this,
                                      menu_selector(HelloWorld::menuCallback));
        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Test 15", this,
                                      menu_selector(HelloWorld::menuCallback));
        itemsArray->addObject(item);

        item = CCMenuItemFont::create("Test 16", this,
                                      menu_selector(HelloWorld::menuCallback));
        itemsArray->addObject(item);

        CCSize s = CCDirector::sharedDirector()->getWinSizeInPixels();
        
        CCMenu* menu = CCMenu::createWithArray(itemsArray);
        menu->alignItemsVertically();
        menu->setTag(MENU_TAG);
        this->addChild(menu);
        
    
        if(s.height <= menu->getContentSize().height)
        {
            menu->setPosition(CCPoint(menu->getPosition().x,  s.height - menu->getContentSize().height));
        }
                
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
            
            break;

        case 5:
            
            break;

        case 6:
            
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

        CCSize s = CCDirector::sharedDirector()->getWinSizeInPixels();
        
        if(s.height <= menu->getContentSize().height)
        {
            CCPoint newPos = CCPoint(menuPosition.x, menuPosition.y + delta.y);
            
            if(newPos.y < 0)
                newPos.y = 0;

            if(newPos.y > s.height)
                newPos.y = s.height;

            menu->setPosition(newPos);
        }
    }
    
}
