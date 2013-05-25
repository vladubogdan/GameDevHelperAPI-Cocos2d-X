//
//  TestLayer.cpp
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/22/13.
//
//

#include "TestLayer.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

TestLayer::~TestLayer()
{
	// cpp don't need to call super dealloc
	// virtual destructor will do this
}

TestLayer::TestLayer()
{
}

CCScene* TestLayer::scene()
{
	CCScene * scene = NULL;
	do
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
        
		// 'layer' is an autorelease object
		TestLayer *layer = TestLayer::create();
		CC_BREAK_IF(! layer);
        
		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);
    
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestLayer::init()
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
        
		CCMenuItemFont* item = CCMenuItemFont::create("Back", this,
                                                      menu_selector(TestLayer::menuCallback));
        item->setTag(1);
        itemsArray->addObject(item);
        
        CCMenu* menu = CCMenu::createWithArray(itemsArray);
        menu->alignItemsVertically();
        this->addChild(menu);
        
        menu->setPosition(item->getContentSize().width, CCDirector::sharedDirector()->getWinSize().height - item->getContentSize().height/2);
        
        std::string message = this->initTest();
        
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        
        float fontSize = 14;
        if(s.height > 1024)
        {
            fontSize = 34;
        }

        
        CCLabelTTF* label =  CCLabelTTF::create(message.c_str(), "Arial", fontSize);
        
        CCSize labelSize = label->getContentSize();
        
        label->setPosition(ccp(s.width/2, labelSize.height));
        this->addChild(label, -2);
        
		bRet = true;
	} while (0);
    
	return bRet;
}

void TestLayer::menuCallback(CCObject* sender)
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

std::string TestLayer::initTest()
{
    return "Test layer";
}

void TestLayer::executeTestCodeAtPosition(CCPoint p)
{
   
}

void TestLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    
}
void TestLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
    this->executeTestCodeAtPosition(touch->getLocation());
}
void TestLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
//    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
//	CCPoint delta = touch->getDelta();
}