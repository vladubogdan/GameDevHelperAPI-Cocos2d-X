//
//  GHBoneSkin.cpp
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 4/5/13.
//
//

#include "GHBoneSkin.h"
#include "GHBone.h"
#include "GHSprite.h"

GHBoneSkin::GHBoneSkin():
sprite(NULL),
bone(NULL),
name(""),
uuid("")
{
    positionOffset = ccp(0,0);
    angleOffset = 0;
    connectionAngle = 0;
}

GHBoneSkin::~GHBoneSkin(){

    sprite = NULL;
    bone = NULL;
}

GHBoneSkin* GHBoneSkin::createSkinWithSprite(GHSprite* spr,
                                             GHBone* bn,
                                             const char* skinName,
                                             const char* skinUUID)
{
    GHBoneSkin *pobNode = new GHBoneSkin();
	if (pobNode && pobNode->initWithSprite(spr, bn, skinName, skinUUID));
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
}

bool GHBoneSkin::initWithSprite(GHSprite* spr,
                                GHBone* bn,
                                const char* skinName,
                                const char* skinUUID)
{    
    sprite = spr;
    bone = bn;
    name = std::string(skinName);
    uuid = std::string(skinUUID);
    
    return true;
}


void GHBoneSkin::setupTransformations()
{
    if(bone && sprite)
    {
        GHBone* _father = (GHBone*)bone->getParent();
        
        
        angleOffset = 0;//needs to be calculated
        
        CCPoint bonePoint = _father->getPosition();
        CCPoint currentPos = sprite->getPosition();
        
        float curAngle = sprite->getRotation();
        connectionAngle = curAngle;
        
        //we flip y for cocos2d
        CCPoint posOffset = ccp(currentPos.x - bonePoint.x,
                                bonePoint.y - currentPos.y);
        
        positionOffset = posOffset;
        
        float boneAngle = bone->degrees();
        
        angleOffset = boneAngle - curAngle;
    }
}

void GHBoneSkin::transform()
{
    if(sprite == NULL || bone == NULL)return;
    
    float degrees = bone->degrees();
    
    CCPoint posOffset = positionOffset;
    
    CCPoint bonePos = ccp(((GHBone*)bone->getParent())->getPosition().x,
                          ((GHBone*)bone->getParent())->getPosition().y);
    
    
    CCAffineTransform transformOffset = CCAffineTransformTranslate(CCAffineTransformMakeIdentity(), bonePos.x, bonePos.y);
   
    CCAffineTransform transform = CCAffineTransformRotate(CCAffineTransformMakeIdentity(),
                                                          CC_DEGREES_TO_RADIANS(degrees - angleOffset));
    
    
    //we need 2 points
    //origin - upward point, in order to calculate new position and new angle
    CCPoint origin = ccp(0,0);
    CCPoint upward = ccp(0, -10);
    
    
    CCAffineTransform transform3 = CCAffineTransformRotate(CCAffineTransformMakeIdentity(),
                                                           CC_DEGREES_TO_RADIANS(degrees - angleOffset - connectionAngle));
    
    posOffset = CCPointApplyAffineTransform(posOffset, transform3);
    
    origin = CCPointApplyAffineTransform(origin, transform);
    upward = CCPointApplyAffineTransform(upward, transform);
    
    origin = CCPointApplyAffineTransform(origin, transformOffset);
    upward = CCPointApplyAffineTransform(upward, transformOffset);
    
    
    //now that we have the 2 points - lets calculate the angle
    float newAngle = (atan2(upward.y - origin.y,
                            upward.x - origin.x)*180.0)/M_PI + 90.0;
    
    
    sprite->setPosition(ccp(origin.x + posOffset.x, origin.y - posOffset.y));
    sprite->setRotation(newAngle);    
}

