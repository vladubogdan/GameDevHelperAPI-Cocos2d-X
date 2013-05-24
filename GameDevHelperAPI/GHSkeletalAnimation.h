//
//  GHSkeletalAnimation.h
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 4/8/13.
//
//
#ifndef __GAME_DEV_HELPER_SKELETAL_ANIMATION_H__
#define __GAME_DEV_HELPER_SKELETAL_ANIMATION_H__

#include "cocos2d.h"

#include "ghMacros.h"

using namespace cocos2d;

class GHSkeletalSkinConnectionInfo : public CCObject
{
public:
    
    GHSkeletalSkinConnectionInfo();
    virtual ~GHSkeletalSkinConnectionInfo();
    
    static GHSkeletalSkinConnectionInfo* createSkinConnectionInfoWithBoneName(const char* name);

    virtual bool initSkinConnectionInfoWithBoneName(const char* name);

    
    std::string getBoneName(){return boneName;}
    
    float getAngleOffset(){return angleOffset;}
    void setAngleOffset(float val){angleOffset = val;}
    
    float getConnectionAngle(){return connectionAngle;}
    void setConnectionAngle(float val){connectionAngle = val;}
    
    CCPoint getPositionOffset(){return positionOffset;}
    void setPositionOffset(const CCPoint& val){positionOffset = val;}
    
    CCPoint getPosition(){return position;}
    void setPosition(const CCPoint& val){position = val;}


    float getAngle(){return angle;}
    void setAngle(float val){angle = val;}
    
private:
    //used with skin connections
    std::string boneName;//may be nil;
    
    //used with sprites transform and skin connections
    float angleOffset;
    float connectionAngle;
    CCPoint positionOffset;
    
    //used with sprites transform
    CCPoint position;
    float angle;
};




class GHSkeletalAnimationFrame : public CCObject
{
public:

    GHSkeletalAnimationFrame();
    virtual ~GHSkeletalAnimationFrame();
    
    static GHSkeletalAnimationFrame* createWithTime(float tm);
    virtual bool initWithTime(float tm);
    
    static GHSkeletalAnimationFrame* createWithFrame(GHSkeletalAnimationFrame* frm);
    virtual bool initWithFrame(GHSkeletalAnimationFrame* frm);
    
    float getTime(){return time_;}
    void setTime(float val){time_ = val;}
    
    
    CCDictionary* getBonePositions(){return bonePositions_;}
    CCDictionary* getSpritesZOrder(){return spritesZOrder_;}
    CCDictionary* getSkinConnections(){return skinConnections_;}
    CCDictionary* getSkinSprites(){return skinSprites_;}
    CCDictionary* getSpritesVisibility(){return spritesVisibility_;}
    CCDictionary* getSpritesTransform(){return spritesTransform_;}

private:
    float time_;
    
    friend class GHSkeletalAnimation;
    
    CCDictionary* bonePositions_;//key bone name / value - NSValue with point
    CCDictionary* spritesZOrder_;//key sprite name/ value - NSNumber with int
    CCDictionary* skinConnections_;//key sprite name/ value - GHSkeletalSkinConnectionInfo
    CCDictionary* skinSprites_;//key skin name/ value sprite name
    CCDictionary* spritesVisibility_;//key sprite name / value NO (sprite only available if its invisible)
    CCDictionary* spritesTransform_;//key sprite name / value GHSkeletalSkinConnectionInfo
    
    void setBonePositionsWithDictionary(CCDictionary* bones);
    void setSpritesZOrderWithDictionary(CCDictionary* sprites);
    void setSkinConnectionsWithDictionary(CCDictionary* connections);
    void setSkinSpritesWithDictionary(CCDictionary* dictionary);
    void setSpritesVisibilityWithDictionary(CCDictionary* dictionary);
    void setSpritesTransformWithDictionary(CCDictionary* dictionary);
};




typedef enum GHSkeletalAnimationPlayMode_ {
	GH_SKELETAL_ANIM_PLAY_NORMAL,
	GH_SKELETAL_ANIM_PLAY_LOOP,
	GH_SKELETAL_ANIM_PLAY_PINGPONG,
    
} GHSkeletalAnimationPlayMode;


class GHSkeletalAnimation : public CCObject
{
public:
    GHSkeletalAnimation();
    virtual ~GHSkeletalAnimation();
    
    static GHSkeletalAnimation* createWithDictionary(CCDictionary* dict);
    virtual bool initWithDictionary(CCDictionary* dict);
    
    static GHSkeletalAnimation* createWithAnimation(GHSkeletalAnimation* other);
    virtual bool initWithAnimation(GHSkeletalAnimation* anim);
    
    inline int getNumberOfLoops(){return numberOfLoops_;}
    
    GH_READWRITE_PROPERTY(int, numberOfLoops_, NumberOfLoops);
    
    GH_READWRITE_PROPERTY(int, currentLoop_, CurrentLoop);
    
    GH_READWRITE_PROPERTY(GHSkeletalAnimationPlayMode, playMode_, PlayMode);
    
    GH_READWRITE_PROPERTY(bool, reversed_, Reversed);

    GH_READWRITE_PROPERTY(bool, paused_, Paused);
    
    GH_READONLY_PROPERTY(std::string, name_, Name);
    
    //this will scale frame times in order to match the new time
    void setTotalTime(float val);
    inline float getTotalTime(){return totalTime_;}
    
    //this method has no effect if the animation is paused
    void setCurrentTime(float val);
    inline float getCurrentTime(){return currentTime_;}
    
    CCArray* getBonePositionFrames(){return bonePositionFrames_;}
    CCArray* getSpriteZOrderFrames(){return spriteZOrderFrames_;}
    CCArray* getSkinConnectionFrames(){return skinConnectionFrames_;}
    CCArray* getSkinSpriteFrames(){return skinSpriteFrames_;}
    CCArray* getVisibilityFrames(){return visibilityFrames_;}
    CCArray* getSpritesTransformFrames(){return spritesTransformFrames_;}
    
    inline int goToNextBonePositionFrame(){
        return this->goToNextFrameUsingFramesArray(this->getBonePositionFrames());
    }
    inline int goToPreviousBonePositionFrame(){
        return this->goToPreviousFrameUsingFramesArray(this->getBonePositionFrames());
    }
    
    inline int goToNextSpriteZOrderFrame(){
        return this->goToNextFrameUsingFramesArray(this->getSpriteZOrderFrames());
    }
    inline int goToPreviousSpriteZOrderFrame(){
        return this->goToPreviousFrameUsingFramesArray(this->getSpriteZOrderFrames());
    }
    
    
    inline int goToNextSkinConnectionFrame(){
        return this->goToNextFrameUsingFramesArray(this->getSkinConnectionFrames());
    }
    inline int goToPreviousSkinConnectionFrame(){
        return this->goToPreviousFrameUsingFramesArray(this->getSkinConnectionFrames());
    }
    
    
    inline int goToNextSkiSpriteFrame(){
        return this->goToNextFrameUsingFramesArray(this->getSkinSpriteFrames());
    }
    inline int goToPreviousSkinSpriteFrame(){
        return this->goToPreviousFrameUsingFramesArray(this->getSkinSpriteFrames());
    }
    
    
    inline int goToNextVisibilityFrame(){
        return this->goToNextFrameUsingFramesArray(this->getVisibilityFrames());
    }
    inline int goToPreviousVisibilityFrameFrame(){
        return this->goToPreviousFrameUsingFramesArray(this->getVisibilityFrames());
    }
    
    
    inline int goToNextSpriteTransformFrame(){
        return this->goToNextFrameUsingFramesArray(this->getSpritesTransformFrames());
    }
    inline int goToPreviousSpriteTransformFrame(){
        return this->goToPreviousFrameUsingFramesArray(this->getSpritesTransformFrames());
    }


    
private:
    std::string name_;
    float totalTime_;
    float currentTime_;
    GHSkeletalAnimationPlayMode playMode_;
    
    CCArray* bonePositionFrames_;
    CCArray* spriteZOrderFrames_;
    CCArray* skinConnectionFrames_;
    CCArray* skinSpriteFrames_;
    CCArray* visibilityFrames_;
    CCArray* spritesTransformFrames_;
    
    int numberOfLoops_; //0 loops forever;
    int currentLoop_;
    bool reversed_;
    
    bool paused_;
    
    
    void changeTimeForFrames(CCArray* frames, float currentTotalTime, float newTime);
    
    int goToNextFrameUsingFramesArray(CCArray* array);
    int goToPreviousFrameUsingFramesArray(CCArray* array);
    
    void copyFramesFrom(CCArray* otherArray, CCArray* toArray);
};

#endif //__GAME_DEV_HELPER_SKELETAL_ANIMATION_H__