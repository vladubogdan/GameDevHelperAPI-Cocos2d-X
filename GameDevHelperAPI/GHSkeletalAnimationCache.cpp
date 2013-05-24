//
//  GHSkeletalAnimationCache.m
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 4/8/13.
//
//

#include "GHSkeletalAnimationCache.h"
#include "GHSkeletalAnimation.h"


#pragma mark CCAnimationCache - Alloc, Init & Dealloc

GHSkeletalAnimationCache* GHSkeletalAnimationCache::s_pSharedAnimationCache = NULL;

GHSkeletalAnimationCache* GHSkeletalAnimationCache::sharedSkeletalAnimationCache(void)
{
    if (! s_pSharedAnimationCache)
    {
        s_pSharedAnimationCache = new GHSkeletalAnimationCache();
        s_pSharedAnimationCache->init();
    }
    
    return s_pSharedAnimationCache;
}

void GHSkeletalAnimationCache::purgeSharedSkeletalAnimationCache(void)
{
    CC_SAFE_RELEASE_NULL(s_pSharedAnimationCache);
}

bool GHSkeletalAnimationCache::init()
{
    return true;
}

GHSkeletalAnimationCache::GHSkeletalAnimationCache()
{
    skeletalAnimations_ = CCDictionary::create();
    skeletalAnimations_->retain();
    loadedFilenames_ = CCDictionary::create();
    loadedFilenames_->retain();
}

GHSkeletalAnimationCache::~GHSkeletalAnimationCache()
{
    CCLOGINFO("GameDevHelperAPI: deallocing %p", this);
    CC_SAFE_RELEASE(skeletalAnimations_);
    CC_SAFE_RELEASE(loadedFilenames_);
}

//- (NSString*) description
//{
//	return [NSString stringWithFormat:@"<%@ = %p | num of sprite frames =  %lu>", [self class], self, (unsigned long)[skeletalAnimations_ count]];
//}

void GHSkeletalAnimationCache::addSkeletalAnimationWithFile(const char* plist)
{
    CCAssert( plist, "Invalid plist file name");
	
    if(! loadedFilenames_->objectForKey(std::string(plist)))
    {
        std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(plist);
        
        CCDictionary* dict = CCDictionary::createWithContentsOfFile(path.c_str());
        
        this->addSkeletalAnimationWithDictionary(dict);
		
        loadedFilenames_->setObject(CCString::create(plist), plist);
    }
	else
		CCLOGINFO(@"GameDevHelper: GHSkeletalAnimationCache: file already loaded: %@", plist);
}

void GHSkeletalAnimationCache::addSkeletalAnimationWithDictionary(CCDictionary* dictionary)
{
    if(NULL == dictionary)return;
    
    GHSkeletalAnimation* anim = GHSkeletalAnimation::createWithDictionary(dictionary);
    skeletalAnimations_->setObject(anim, anim->getName());
}

void GHSkeletalAnimationCache::removeSkeletalAnimations()
{
    skeletalAnimations_->removeAllObjects();
    loadedFilenames_->removeAllObjects();
}

void GHSkeletalAnimationCache::removeUnusedSkeletalAnimations()
{
    
	CCArray *keys = skeletalAnimations_->allKeys();
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(keys, pObj)
    {
        CCString* key = (CCString*)pObj;
        GHSkeletalAnimation* value = (GHSkeletalAnimation*)skeletalAnimations_->objectForKey(key->getCString());
        
        if(value && value->retainCount() == 1){
            CCLOG("GameDevHelper: GHSkeletalAnimationCache: removing unused frame: %@", key);
            
            skeletalAnimations_->removeObjectForKey(key->getCString());
        }
    }
}

void GHSkeletalAnimationCache::removeSkeletalAnimationWithName(const char* name)
{
    // explicit nil handling
	if( ! name )
		return;
    
    skeletalAnimations_->removeObjectForKey(name);
	

	// XXX. Since we don't know the .plist file that originated the frame, we must remove all .plist from the cache
    loadedFilenames_->removeAllObjects();
}

GHSkeletalAnimation* GHSkeletalAnimationCache::skeletalAnimationWithName(const char* name)
{    
    GHSkeletalAnimation *anim = (GHSkeletalAnimation*)skeletalAnimations_->objectForKey(name);
	if( ! anim ) {
			CCLOG("GameDevHelper: GHSkeletalAnimationCache: Animation '%@' not found", name);
	}
    
	return anim;
}

