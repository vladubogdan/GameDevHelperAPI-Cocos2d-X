//
//  GHAnimationCache.h
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 5/9/13.
//
//

#ifndef __GAME_DEV_HELPER_SPRITE_ANIMATION_CACHE_H__
#define __GAME_DEV_HELPER_SPRITE_ANIMATION_CACHE_H__


#import "cocos2d.h"
using namespace cocos2d;

class GHAnimation;

/** 
 Singleton that manages the GHAnimation objects.
 
 It saves in a cache the sprite sheet animations.
 
 You should use this class if you want to pre-load your animations in a cache.
*/
class GHAnimationCache : public CCObject
{
public:
    
    GHAnimationCache();
    ~GHAnimationCache();
    /** Returns the shared instance of the Animation cache */
    static GHAnimationCache* sharedAnimationCache(void);
    
    /** Purges the cache. It releases all the GHAnimation objects and the shared instance.
     */
    static void purgeSharedAnimationCache(void);
    
    
    /** Adds a GHAnimation with a name.
     */
    void addAnimation(GHAnimation *animation, const char * name);
    
    /** Deletes a GHAnimation from the cache.
     */
    void removeAnimationByName(const char* name);
    
    /** Returns a GHAnimation that was previously added.
     If the name is not found it will return NULL.
     You should retain the returned copy if you are going to use it.
     */
    GHAnimation* animationByName(const char* name);
    
    /** Adds an animation from an CCDictionary
     Make sure that the frames were previously loaded in the CCSpriteFrameCache.
     */
    void addAnimationsWithDictionary(CCDictionary* dictionary);
    
    /** Adds an animation from a plist file.
     Make sure that the frames were previously loaded in the CCSpriteFrameCache.
     */
    void addAnimationsWithFile(const char* plist);

    
    bool init(void);
private:
    
    void parseAnimationDictionary(CCDictionary* animations);
    
    CCDictionary* m_pAnimations;
    static GHAnimationCache* s_pSharedAnimationCache;
};

#endif //__GAME_DEV_HELPER_SPRITE_ANIMATION_CACHE_H__
