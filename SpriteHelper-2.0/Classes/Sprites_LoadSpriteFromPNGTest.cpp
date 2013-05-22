//
//  Sprites_LoadSpriteFromPNGTest.cpp
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#include "Sprites_LoadSpriteFromPNGTest.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

Sprites_LoadSpritesFromPNGTest::~Sprites_LoadSpritesFromPNGTest()
{
	// cpp don't need to call super dealloc
	// virtual destructor will do this
}

Sprites_LoadSpritesFromPNGTest::Sprites_LoadSpritesFromPNGTest()
{
}

CCScene* Sprites_LoadSpritesFromPNGTest::scene()
{
	CCScene * scene = NULL;
	do
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
        
		// 'layer' is an autorelease object
		Sprites_LoadSpritesFromPNGTest *layer = Sprites_LoadSpritesFromPNGTest::create();
		CC_BREAK_IF(! layer);
        
		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);
    
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Sprites_LoadSpritesFromPNGTest::init()
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
        
        
		CCMenuItemFont* item = CCMenuItemFont::create("Back", this,
                                                      menu_selector(Sprites_LoadSpritesFromPNGTest::menuCallback));
        item->setTag(1);
        itemsArray->addObject(item);
        
        CCMenu* menu = CCMenu::createWithArray(itemsArray);
        menu->alignItemsVertically();
        this->addChild(menu);
        
        menu->setPosition(item->getContentSize().width, CCDirector::sharedDirector()->getWinSize().height - item->getContentSize().height/2);
        
        
		bRet = true;
	} while (0);
    
	return bRet;
}

void Sprites_LoadSpritesFromPNGTest::menuCallback(CCObject* sender)
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void Sprites_LoadSpritesFromPNGTest::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    
}
void Sprites_LoadSpritesFromPNGTest::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    
}
void Sprites_LoadSpritesFromPNGTest::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
	CCPoint delta = touch->getDelta();
}