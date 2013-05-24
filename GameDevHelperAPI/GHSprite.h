//
//  GHSprite.h
//  GameDevHelper.com
//
//  Created by Bogdan Vladu.
//  Copyright (c) 2013 Bogdan Vladu. All rights reserved.
//

#ifndef __GAME_DEV_HELPER_SPRITE_H__
#define __GAME_DEV_HELPER_SPRITE_H__


#import "cocos2d.h"
#import "ghConfig.h"

#if GH_ENABLE_PHYSICS_INTEGRATION
#import "Box2D.h"
#endif

#import "GHAnimation.h"

/**
 A GHSprite is an advanced subclass of CCSprite.
  
 This class is used throughout the entire GameDevHelper API because it has friendly methods for almost everything you may want. 
 From physics, to sprite sheet and skeleton animations, almost everything is controlled through objects of this class.
 
 */
using namespace cocos2d;


class GHSprite : public CCSprite
{
public:
    
    GHSprite();
    virtual ~GHSprite();
    
#pragma mark INIT

    /**
     * Creates a sprite with an sprite frame name.
     *
     * A CCSpriteFrame will be fetched from the CCSpriteFrameCache by pszSpriteFrameName param.
     * If the CCSpriteFrame doesn't exist it will raise an exception.
     *
     * @param   pszSpriteFrameName A null terminated string which indicates the sprite frame name.
     * @return  A valid sprite object that is marked as autoreleased.
     */
    static GHSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    
    
    /**
     * Initializes a sprite with an sprite frame name.
     *
     * A CCSpriteFrame will be fetched from the CCSpriteFrameCache by name.
     * If the CCSpriteFrame doesn't exist it will raise an exception.
     *
     * @param   pszSpriteFrameName  A key string that can fected a volid CCSpriteFrame from CCSpriteFrameCache
     * @return  true if the sprite is initialized properly, false otherwise.
     */
    virtual bool initWithSpriteFrameName(const char *pszSpriteFrameName);
    

    /**
     * Initializes a sprite with an SpriteFrame. The texture and rect in SpriteFrame will be applied on this sprite
     *
     * @param   pSpriteFrame  A CCSpriteFrame object. It should includes a valid texture and a rect
     * @return  true if the sprite is initialized properly, false otherwise.
     */
    virtual bool initWithSpriteFrame(CCSpriteFrame *pSpriteFrame);

    
    
#pragma mark VARIOUS_PROPERTIES
    /**
     * Set the name of current sprite object.
     * @param  value A null terminated string which indicates the sprite name.
     * @return  Nothing.
     */
     void setName(const char* value);
    
    /**
     * Get the name of current sprite object.
     @return The name of the sprite.
     */
    std::string getName(void);

    /**
     * Set the image file name from where the texture of this sprite was created.
     * @param value A null terminated string which indicates the image file.
     */
    void setImageFile(const char *value);

    /**
     Get the image file name from where the texture of this sprite was created.
     @return The sprite image file name.
     */
    std::string getImageFile(void);
    
    /**
     The sprite frame name used to create the texture rectangle of this sprite.
     @return The Cocos2d sprite frame name.
     */
    std::string getSpriteFrameName(void);
    
    
    
    
#pragma mark ANIMATIONS
    /**
     Prepares a sprite sheet animation on this sprite using the animation object.
     */
     void prepareAnimation(GHAnimation* anim);
    
    /**
     Prepares a sprite sheet animation on this sprite using the animation name.
     Animation has to be previously cache using GHAnimationCache.
     */
    void prepareAnimationWithName(const char* animName);
    
    /**
     Returns the current sprite sheet animation assigned to this sprite object.
     */
    GHAnimation* getAnimation();
    
    /**
     Play's the currently assigned sprite sheet animation.
     */
    void playAnimation(void);
    
    /**
     Pause the currently assigned sprite sheet animation.
     */
    void pauseAnimation(void);
    
    /**
     Restart the currently assigned sprite sheet animation.
     */
    void restartAnimation(void);
    
    /**
     Stop the currently assigned sprite sheet animation.
     @warning Stoping a sprite sheet animation will also remove the animation from this sprite.
     */
    void stopAnimation(void);
    
    /**
     Stop the currently assigned sprite sheet animation and restore original sprite frame that was assigned to this sprite prior preparing the animation.
     
     @warning Stoping a sprite sheet animation will also remove the animation from this sprite.
     
     */
    void stopAnimationAndRestoreOriginalFrame(bool restore);
    
    
    
    /**
     Sets a sprite sheet animation delegate.
     
     Use the delegate to receive animation notifications.
     
     You should consult GHAnimationDelegate to see what method's you have to implement in your class.
     
     */
    void setAnimationDelegate(GHAnimationDelegate* obj);
    
    
    
#if GH_ENABLE_PHYSICS_INTEGRATION
#pragma mark PHYSICS
    
    /**
     Destroy the physical body created on this sprite.
     */
    void destroyBody();
    /**
     Creates the physical body as defined in SpriteHelper.
     */
    void createBody();

    
    virtual bool isDirty(void);
    
    virtual CCAffineTransform nodeToParentTransform(void);
    
    virtual void setPosition(const CCPoint& pos);
    virtual void setRotation(float fRotation);
#endif
    
    /**
     Print ready information about this sprite object.
     */
    std::string description();
    
    
    virtual void update(float dt);

private:
    
    std::string imageFile;
    std::string spriteFrameName;
    std::string name;//name may be the same as spriteFrameName, different or nil
    
    
#if GH_ENABLE_PHYSICS_INTEGRATION
    CCDictionary* physicsInfo;//may be nil - contains all physical information
    b2Body* body;//may be null if sprite has no physical representation
#endif
    
    GHAnimation* activeAnimation;//may be nil
};

#endif //__GAME_DEV_HELPER_SPRITE_H__
