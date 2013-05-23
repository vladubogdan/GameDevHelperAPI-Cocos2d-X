//
//  GHAnimationCache.m
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 5/9/13.
//
//

#import "GHAnimationCache.h"
#import "GHAnimation.h"

#pragma mark CCAnimationCache - Alloc, Init & Dealloc

GHAnimationCache* GHAnimationCache::s_pSharedAnimationCache = NULL;

GHAnimationCache* GHAnimationCache::sharedAnimationCache(void)
{
    if (! s_pSharedAnimationCache)
    {
        s_pSharedAnimationCache = new GHAnimationCache();
        s_pSharedAnimationCache->init();
    }
    
    return s_pSharedAnimationCache;
}

void GHAnimationCache::purgeSharedAnimationCache(void)
{
    CC_SAFE_RELEASE_NULL(s_pSharedAnimationCache);
}

bool GHAnimationCache::init()
{
    m_pAnimations = new CCDictionary();
    return true;
}

GHAnimationCache::GHAnimationCache()
: m_pAnimations(NULL)
{
}

GHAnimationCache::~GHAnimationCache()
{
    CCLOGINFO("GameDevHelperAPI: deallocing %p", this);
    CC_SAFE_RELEASE(m_pAnimations);
}


//- (NSString*) description
//{
//	return [NSString stringWithFormat:@"<%@ = %p | num of animations =  %lu>", [self class], self, (unsigned long)[animations_ count]];
//}

#pragma mark GHAnimationCache - load/get/del

void GHAnimationCache::addAnimation(GHAnimation *animation, const char * name)
{
    m_pAnimations->setObject(animation, name);
}

void GHAnimationCache::removeAnimationByName(const char* name)
{
    if (! name)
    {
        return;
    }
    
    m_pAnimations->removeObjectForKey(name);
}

GHAnimation* GHAnimationCache::animationByName(const char* name)
{
    return (GHAnimation*)m_pAnimations->objectForKey(name);
}


#pragma mark GHAnimationCache - from file

void GHAnimationCache::parseAnimationDictionary(CCDictionary* animations)
{
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(animations, pElement)
    {
        const char* name = pElement->getStrKey();
        CCDictionary* animationDict = (CCDictionary*)pElement->getObject();
        
        CCArray* frameArray = (CCArray*)animationDict->objectForKey("frames");

        if(frameArray->count() > 0)
        {
            CCDictionary* firstFrameInfo = (CCDictionary*)frameArray->objectAtIndex(0);
            if(firstFrameInfo)
            {
                CCString* spriteFrameName = (CCString*)firstFrameInfo->objectForKey("spriteframe");
                if(spriteFrameName)
                {
                    CCSpriteFrame *spriteFrame = frameCache->spriteFrameByName(spriteFrameName->getCString());
                    
                    if(spriteFrame)
                    {
                       GHAnimation* newAnimation = GHAnimation::createWithDictionary(animationDict, name);
                        if(newAnimation){
                            GHAnimationCache::sharedAnimationCache()->addAnimation(newAnimation, name);
                        }
                    }
                    else{
                        CCLog("GameDevHelperAPI WARNING: Sprite frames for animation %s were not found. Animation will not be loaded.", name);
                    }
                }
            }
        }
	}
}


void GHAnimationCache::addAnimationsWithDictionary(CCDictionary* dictionary)
{
    CCDictionary* animations = (CCDictionary*)dictionary->objectForKey("animations");
    
    if ( animations == NULL ) {
        CCLOG("GameDevHelperAPI: GHAnimationCache: No animations were found in provided dictionary.");
        return;
    }
    
    unsigned int version = 2;
    CCDictionary* properties = (CCDictionary*)dictionary->objectForKey("properties");
    if( properties )
    {
        version = properties->valueForKey("format")->intValue();
        CCArray* spritesheets = (CCArray*)properties->objectForKey("spritesheets");
        
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(spritesheets, pObj)
        {
            CCString* name = (CCString*)(pObj);
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(name->getCString());
        }
    }
    
    switch (version) {
        case 2:
            this->parseAnimationDictionary(animations);
            break;
        default:
            CCAssert(false, "Invalid animation format");
    }
}

/** Read an NSDictionary from a plist file and parse it automatically for animations */
void GHAnimationCache::addAnimationsWithFile(const char* plist)
{
    CCAssert( plist, "Invalid animation file name");
    
    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(plist);
    CCDictionary* dict = CCDictionary::createWithContentsOfFile(path.c_str());
    
    CCAssert( dict, "GHAnimationCache: File could not be found");
    
    this->addAnimationsWithDictionary(dict);
}
