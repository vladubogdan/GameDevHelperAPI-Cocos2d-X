//
//  GHSkeleton.h
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 4/4/13.
//
//

#ifndef __GAME_DEV_HELPER_SKELETON_H__
#define __GAME_DEV_HELPER_SKELETON_H__

#include "cocos2d.h"
#include "ghConfig.h"

using namespace cocos2d;

#include "GHBone.h"

class GHSkeletalAnimation;
class GHSkeleton;

/**
 This protocol is used when the end user wants to receive skeleton animation notifications.

 Example:
 @code
 mySkeleton->setDelegate(this);
 @endcode
 */
class GHSkeletonDelegate
{
public:
    
    GHSkeletonDelegate(){}
    virtual ~GHSkeletonDelegate(){}
    /**
     Receive load pose notification. Returns the skeleton on which the new pose was loaded and the pose name.
     */
    virtual void didLoadPoseWithNameOnSkeleton(const char* poseName, GHSkeleton* skeleton){}

    /**
     Called when a skeleton animation just started. Returns the skeleton on which the animation started and the skeletal animation object.
     */
    virtual void didStartAnimationOnSkeleton(GHSkeletalAnimation* animation, GHSkeleton* skeleton){}

    /**
     Called when a skeleton transitioned to a new animaton. Returns the skeleton and the skeletal animation object.
     */
    virtual void didFinishTransitionToAnimationOnSkeleton(GHSkeletalAnimation* animation, GHSkeleton* skeleton){}

    /**
     Called when a skeleton animation just stoped. Returns the skeleton and the skeletal animation object.
     */
    virtual void didStopAnimationOnSkeleton(GHSkeletalAnimation* animation, GHSkeleton* skeleton){}

    /**
     Called when a skeleton animation just finished a loop. Returns the skeleton and the skeletal animation object.
     */
    virtual void didFinishLoopInAnimationOnSkeleton(GHSkeletalAnimation* animation, GHSkeleton* skeleton){}
    
};



/**
 This class is used to create skeletons as defined in SpriteHelper.

 Example of loading a published skeleton file:
 @code
 skeleton = [GHSkeleton skeletonWithFile:@"resourceFolderWhereItWasPublished/skeletons/DocName_SkeletonName.plist"];
 @endcode
 */
class GHSkeleton : public CCNode
{
public:
    
    GHSkeleton();
    virtual ~GHSkeleton();
    
    /**
     Creates an autoreleased skeleton object given a file name.
     */
    static GHSkeleton* createWithFile(const char* file);
    /**
     Creates a skeleton object given a file name.
     */
    virtual bool initWithFile(const char* file);
    
    /**
     Sets the delegate object to be used by this skeleton.
     
     You should read GHSkeletonDelegate documentation for what methods you have to implement.
     */
    inline void setDelegate(GHSkeletonDelegate* del){delegate = del;}
    
    /**
     Finds a bone in the skeleton structure and set its position.
     */
    void setPositionForBoneNamed(CCPoint position, const char* boneName);
    
    /**
     Loads a pose onto the skeleton given the pose name.
     */
    void setPoseWithName(const char* poseName);
    
    /**
     Returns an array containing all the bone objects (GHBone) in the skeleton.
     */
    CCArray* getAllBones();
    /**
     Returns an array containing all the skin objects (GHBoneSkin) in the skeleton.
     */
    inline CCArray* getSkins(){return skins;}
    /**
     Returns the root bone.
     */
    inline GHBone* getRootBone(){ return rootBone;}
    
    /**
     Adds a skin to the skeleton.
     */
    void addSkin(GHBoneSkin* skin);
    /**
     Removes a skin from the skeleton.
     */
    void removeSkin(GHBoneSkin* skin);
    
    /**
     Start an animation on the skeleton given the animation object.
     */
    void playAnimation(GHSkeletalAnimation* anim);
    /**
     Start an animation on the skeleton given the animation name.
     @warning
     Animation has to be previously cache using GHSkeletalAnimationCache.
     */
    void playAnimationWithName(const char* animName);
    /**
     Returns the current animation active on this skeleton.
     */
    inline GHSkeletalAnimation* getAnimation(){return animation;}
    /**
     This will change or set an animation by transitioning each bone position
     to the new animation bone positions in the period of time specified.
     */
    void transitionToAnimationInTime(GHSkeletalAnimation* anim, float time);
    /**
     This will change or set an animation given its name, by transitioning each bone position
     to the new animation bone positions in the period of time specified.
     @warning
     Animation has to be previously cache using GHSkeletalAnimationCache.
     */
    void transitionToAnimationWithNameInTime(const char* animName, float time);
    
    /**
     Stops the active skeleton animation.
     */
    void stopAnimation();

    
    virtual void update(float dt);

#if GH_DEBUG
    virtual void draw();
#endif
    
private:
    
    GHBone* rootBone;
    CCSpriteBatchNode* batchNode_;//sprites are kept in this batchNode
    
    CCDictionary* poses;//may be nil depending on publish settings
    
    CCArray* skins;//contains GHBoneSkin objects
#if GH_DEBUG
    //debug drawing
    GLint		colorLocation_;
    
    void initShader();
    void debugDrawBone(GHBone* bone);
#endif
    
    GHSkeletalAnimation* animation;//combined animations currently not supported
    
    CCFloat* transitionTime;//not nil only when transtioning to a new animation
    float currentTranstionTime;
    GHSkeletonDelegate* delegate;
    
    void loadSprites(CCArray* spritesInfo);
    void loadBones(CCDictionary* rootBoneInfo);
    void updateSkins();
    void transformSkins();
};

#endif //__GAME_DEV_HELPER_SKELETON_H__
