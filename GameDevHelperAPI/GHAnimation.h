//
//  GHAnimation.h
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 5/9/13.
//
//
#ifndef __GAME_DEV_HELPER_SPRITE_ANIMATION_H__
#define __GAME_DEV_HELPER_SPRITE_ANIMATION_H__


#import "cocos2d.h"

using namespace cocos2d;

class GHAnimation;
class GHSprite;

/**
 This protocol should be used when you want to receive sprite sheet animations notifications.
 
 Implement this protocol in your class and set your class object as delegate of the animation to get notifications.
 
 Example:
 @code
 mySprite->setAnimationDelegate(this);
 @endcode
 */
class GHAnimationDelegate
{
public:
    /**
     Receive finished playing notification for a sprite sheet animation.
     */
    virtual void animationDidFinishPlayingOnSprite(GHAnimation* anim, GHSprite* sprite){
        
    }

    /**
     Receive change frame notification for a sprite sheet animation.
     */
    virtual void animationDidChangeFrameIdxOnSprite(GHAnimation* anim, int frmIdx, GHSprite* sprite){
        
    }

    /**
     Receive did finish repetition notification for a sprite sheet animation.
     */
    virtual void animationDidFinishRepetitionOnSprite(GHAnimation* anim, int repetitionNo, GHSprite* sprite){
        
    }
};






/**
 This class represents a frame of a sprite sheet animation. 
 
 It holds informations such as the Cocos2d sprite frame to be used on the sprite when the animation changes to this object.
 */
class GHAnimationFrame : public CCObject
{
public:
    
    GHAnimationFrame();
    virtual ~GHAnimationFrame();
    
    /**
     * Creates an animation frame object from a dictionary.
     *
     @warning Make sure that the frames were previously loaded in the CCSpriteFrameCache.
     */
    static GHAnimationFrame* createWithDictionary(CCDictionary* dict);

    /**
     Initialize a sprite sheet animation frame with a dictionary.
     */
    virtual bool initWithDictionary(CCDictionary* dict);

    
    /**
     * Creates an animation frame object using another animation frame object.
     */
    static GHAnimationFrame* createWithAnimationFrame(GHAnimationFrame* frame);
    
    /**
     Initialize a sprite sheet animation frame using another animation frame object.
     */
    virtual bool initWithAnimationFrame(GHAnimationFrame* frame);

    
    /**
     Get the time it takes for this sprite sheet animation frame to play.
     */
    float getTime();

    /**
     Set the time it takes for this sprite sheet animation frame to play.
     */
    void setTime(float value);
    
    /**
     Get the Cocos2d-X sprite frame assigned to this sprite sheet animation frame.
     */
    CCSpriteFrame* getSpriteFrame();

    /**
     Set the Cocos2d-X sprite frame assigned to this sprite sheet animation frame.
     */
     void setSpriteFrame(CCSpriteFrame* val);
    
    /**
     Get the user info as defined in SpriteHelper assigned to this sprite sheet animation frame.
     */
    CCDictionary* getUserInfo(void);
  
private:
    CCSpriteFrame* m_spriteFrame;
    float m_time;
    CCDictionary* m_userInfo;
};






/**
 A GHAnimation object is used to play sprite sheet animations on a GHSprite object.
 
 This class contains the properties of a sprite sheet animation as defined in SpriteHelper. You can also change the property as needed.
 
 Use GHAnimationCache to pre-load animations into cache for faster handling.
 
 Users should probably never have to use this class directly but through GHSprite class.
 
 */
class GHAnimation : public CCObject
{
public:

    GHAnimation();
    virtual ~GHAnimation();

    /**
     * Creates an animation from a dictionary.
     *
     @warning Make sure that the frames were previously loaded in the CCSpriteFrameCache.
     */
    static GHAnimation* createWithDictionary(CCDictionary* dict, const char* animName);
    
    /**
     * Initializes a sprite sheet animation with required info from dictionary.
     */
    virtual bool initWithDictionary(CCDictionary* dict, const char* animName);

    /**
     * Creates an animation from another animation.
     */
    static GHAnimation* createWithAnimation(GHAnimation* anim);
    /**
     * Initializes a sprite sheet animation with another animation.
     */
    virtual bool initWithAnimation(GHAnimation* anim);

    
    /**
     Get the name of this sprite sheet animation.
     */
    inline std::string getName(void){return name;}

    /**
     Get the number of repetitions this sprite sheet animation will play.
     */
    inline int getRepetitions(){return repetitions;}
    /**
     Set the number of repetitions this sprite sheet animation will play.
     For this property to take effect, loop must be disabled.
     */
    inline void setRepetitions(int value){repetitions = value;}
    
    /**
     Get whether this sprite sheet animation will loop.
     */
    inline bool getLoop(){return loop;}
    /**
     Set whether this sprite sheet animation will loop.
     */
    inline void setLoop(bool val){loop = val;}
    
    /**
     Get whether this sprite sheet animation will change frames randomly and ignore the frames order.
     */
    inline bool getRandomFrames(){return randomFrames;}
    /**
     Set whether this sprite sheet animation will change frames randomly and ignore the frames order.
     This is useful for animations such as fire flames.
     */
    inline void setRandomFrames(bool val){randomFrames = val;}
    
    /**
     Get whether this sprite sheet animation should restore original Cocos2d sprite frame on the assigned sprite when it finishes.
     */
    inline bool getRestoreSprite(){return restoreSprite;}
    /**
     Set whether this sprite sheet animation should restore original Cocos2d sprite frame on the assigned sprite when it finishes.
     */
    inline void setRestoreSprite(bool val){restoreSprite = val;}
    
    /**
     Get whether this sprite sheet animation should replay with a random delay time between min and max random time.
     */
    inline bool getRandomReplay(){return randomReplay;}
    /**
     Set whether this sprite sheet animation should replay with a random delay time between min and max random time.
     This is useful for animations such as character eyes blinking.
     For this property to take effect, loop must be enabled.
     */
    void setRandomReplay(bool val);

    /**
     Get whether this sprite sheet animation minimum random replay time.
     */
    inline float getMinRandomTime(void){return minRandomTime;}
    /**
     Set whether this sprite sheet animation minimum random replay time.
     For this property to take effect, randomReplay must be enabled.
     */
    inline void setMinRandomTime(float val){minRandomTime = val;}

    /**
     Get whether this sprite sheet animation maximum random replay time.
     */
    inline float getMaxRandomTime(void){return maxRandomTime;}
    /**
     Set whether this sprite sheet animation maximum random replay time.
     For this property to take effect, randomReplay must be enabled.
     */
    inline void setMaxRandomTime(float val){maxRandomTime = val;}
    
    
    /**
     * Set the total time it will take for this sprite sheet animation to complete a loop.
     *
     * Changing the total time value, will change the time on each frame as needed.
     */
    void setTotalTime(float val);
    /**
     * Get the total time it takes for this sprite sheet animation to complete a loop.
     */
    inline float getTotalTime(void){return totalTime;}
    
    /**
     * Return the frames array. This array contains GHAnimationFrame objects.
     */
    inline CCArray* getFrames(){return frames;}
    
    /**
     * Set the sprite sheet animation delegate.
     *
     @warning If you remove an animation in one of the delegate methods you should make the delegate NULL first.
     */
    inline void setDelegate(GHAnimationDelegate* val){delegate = val;}


    inline void moveToFirstFrame(){ this->setActiveFrameWithIndex(0);}
    inline void moveToPreviousFrame(){this->setActiveFrameWithIndex(currentFrameIdx-1);}
    inline void moveToNextFrame(){this->setActiveFrameWithIndex(currentFrameIdx+1);}
    
    inline int getCurrentFrameIndex(){return currentFrameIdx;}
    
private:
    
    friend class GHSprite;
    
    /**
     Method used by GHSprite object to control the animation.
     */
    void setSprite(GHSprite* spr);
    /**
     Method used by GHSprite object to control the animation.
     */
    void prepare();
    /**
     Method used by GHSprite object to control the animation.
     */
    inline void play(){playing = true;}
    /**
     Method used by GHSprite object to control the animation.
     */
    inline void pause(){playing = false;}
    /**
     Method used by GHSprite object to control the animation.
     */
    void update(float dt);
    
    /**
     Method used to calculate a random time for replay when random play time is enabled.
     */
    float calculatedRandomReplayTime();

    /**
     Method used to get a random frame when random frame play is enabled.
     */
    int randomFrame();
    
    /**
     Method used to change the frame when animation is playing.
     */
    void setActiveFrameWithIndex(int frmIdx);

    /**
     Method used to change the frame when animation is playing.
     */
    void setActiveFrame(GHAnimationFrame* frm);
    
    std::string name;
    CCArray* frames;//contains GHAnimationFrame objects
    
    int repetitions;
    bool loop;
    bool randomFrames;
    bool restoreSprite;

    bool randomReplay;
    float minRandomTime;
    float maxRandomTime;
    
    float totalTime;

    bool playing;
    float currentTime;
    int currentFrameIdx;
    float currentRandomRepeatTime;
    int repetitionsPerformed;
    GHAnimationFrame* activeFrame;
    
    GHAnimationDelegate* delegate;
    
    GHSprite* sprite;
};

#endif //__GAME_DEV_HELPER_SPRITE_ANIMATION_H__
