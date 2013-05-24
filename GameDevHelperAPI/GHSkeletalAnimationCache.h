//
//  GHSkeletalAnimationCache.h
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 4/8/13.
//
//
#ifndef __GAME_DEV_HELPER_SKELETAL_ANIM_CACHE_H__
#define __GAME_DEV_HELPER_SKELETAL_ANIM_CACHE_H__


#include "cocos2d.h"
using namespace cocos2d;

class GHSkeletalAnimation;

/** Singleton that manages the GHSkeletalAnimation objects.
 It saves in a cache the animations. You should use this class if you want to save your animations in a cache.
 
 */
class GHSkeletalAnimationCache : public CCObject
{
public:
    
    GHSkeletalAnimationCache();
    ~GHSkeletalAnimationCache();
    /** Returns ths shared instance of the Skeletal Animation cache */
    static GHSkeletalAnimationCache* sharedSkeletalAnimationCache(void);
    
    /** Purges the cache. It releases all the Skeletal Animations and the retained instance.*/
    static void purgeSharedSkeletalAnimationCache(void);
    
    
    /** Adds a skeleton animation in cache given the file name.*/
    void  addSkeletalAnimationWithFile(const char* plist);
    
    
    /** Purges the dictionary of loaded skeletal animations.*/
    void removeSkeletalAnimations();
    
    /** Removes unused skeletal animations.
     * Skeletal Animations that have a retain count of 1 will be deleted.
     * It is convinient to call this method when starting a new Scene.
     */
    void removeUnusedSkeletalAnimations();
    
    /** Deletes a skeleton animation from the the cache.*/
    void removeSkeletalAnimationWithName(const char* name);
    
    
    /** Returns a Skeleton Animation that was previously added.
     If the name is not found it will return nil.
     You should retain the returned copy if you are going to use it.
     */
    GHSkeletalAnimation* skeletalAnimationWithName(const char* name);

    bool init(void);
private:
	CCDictionary *skeletalAnimations_;
	CCDictionary *loadedFilenames_;
    
    static GHSkeletalAnimationCache* s_pSharedAnimationCache;
    
    void addSkeletalAnimationWithDictionary(CCDictionary* dictionary);
};

#endif //__GAME_DEV_HELPER_SKELETAL_ANIM_CACHE_H__
