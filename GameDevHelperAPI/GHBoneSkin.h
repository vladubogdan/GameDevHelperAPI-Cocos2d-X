//
//  GHBoneSkin.h
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 4/5/13.
//
//
#ifndef __GAME_DEV_HELPER_BONE_SKIN_H__
#define __GAME_DEV_HELPER_BONE_SKIN_H__


#include "ghConfig.h"
#include "cocos2d.h"

//class GHSprite;
class GHBone;

#include "GHSprite.h"

using namespace cocos2d;

/**
 GHBoneSkin is a helper class that connects a bone to a sprite.
 
 End users will probably never have to use this class directly.
 */
class GHBoneSkin : public CCObject
{
public:
    
    GHBoneSkin();
    virtual ~GHBoneSkin();
    
    /**
     Create an autoreleased GHBoneSkin object given the required arguments.
     */
    static GHBoneSkin* createSkinWithSprite(GHSprite* spr,
                                            GHBone* bn,
                                            const char* skinName,
                                            const char* skinUUID);
    
    /**
     Create a GHBoneSkin object given the required arguments.
     */
    virtual bool initWithSprite(GHSprite* spr,
                                GHBone* bn,
                                const char* skinName,
                                const char* skinUUID);
    
    
    /**
     Get the position offset that is used when transforming a sprite based on bone movement.
     */
    inline CCPoint getPositionOffset(){ return positionOffset;}
    
    /**
     Set the position offset that is used when transforming a sprite based on bone movement.
     */
    inline void setPositionOffset(const CCPoint& val){positionOffset = val; }

    /**
     Get the angle offset that is used when transforming a sprite based on bone movement.
     */
    inline float getAngleOffset(){return angleOffset;}
    /**
     Set the angle offset that is used when transforming a sprite based on bone movement.
     */
    inline void setAngleOffset(const float& val){angleOffset = val;}

    /**
     Get the original angle at which the sprite was connected to the bone.
     */
    inline float getConnectionAngle(){return connectionAngle;}
    /**
     Set the original angle at which the sprite was connected to the bone.
     */
    inline void setConnectionAngle(const float& val){connectionAngle = val; }

    /**
     Get the name of this skin connection.
     */
    inline std::string getName(){return name;}

    /**
     Get the unique identifier of this connection.
     */
    inline std::string getUUID(){return uuid;}

    /**
     Get the sprite used in this object.
     */
    inline GHSprite* getSprite(){return sprite;}
    /**
     Set the sprite that will be used by this object.
     */
    inline void setSprite(GHSprite* spr){sprite = spr;}
    
    /**
     Get the bone used in this object.
     */
    inline GHBone* getBone(){return bone;}
    /**
     Set the bone that will be used by this object.
     */
    inline void setBone(GHBone* val){bone = val;}
    
    /**
     Update positionOffset, angleOffset and connectionAngle based on the bone movement.
     */
    void setupTransformations();
    /**
     Update sprite position and rotation based on the bone movement.
     */
    void transform();

    
private:
    
    GHSprite* sprite;
    GHBone* bone;
    std::string name;//the name of this skin
    std::string uuid;//unique identifier for this skin
    
    CCPoint positionOffset;
    float   angleOffset;
    float   connectionAngle;//initial angle when bone was connected with the sprite
};

#endif //__GAME_DEV_HELPER_BONE_SKIN_H__


