//
//  GHPoint.h
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/23/13.
//
//

#ifndef __GAME_DEV_HELPER_GHPOINT_H__
#define __GAME_DEV_HELPER_GHPOINT_H__

#include "cocos2d.h"
using namespace cocos2d;

/*
There are multiple versions of Cocos2d-x out there. In some GHPoint is a subclass of CCObject - as it should be in order
 to add points to a CCArray or CCDictionary - in other versions is NOT
 
 In order to get around the problems of using GameDevHelper API with different cocos2d-x version this class has been created.
 */

class CC_DLL GHPoint : public CCObject
{
public:
    float x;
    float y;

    GHPoint();
    virtual ~GHPoint();
    
    static GHPoint* createWithValues(float x, float y);
    virtual bool initWithValues(float x, float y);

    static GHPoint* createWithPoint(GHPoint* pt);
    virtual bool initWithPoint(GHPoint* pt);

    CCPoint getPoint(){return ccp(x, y);}
    
    GHPoint(float x, float y);
    GHPoint(const GHPoint& other);
    GHPoint(const CCPoint& other);
    
    GHPoint& operator= (const GHPoint& other);
    void setPoint(float x, float y);
    virtual CCObject* copyWithZone(CCZone* pZone);
    bool equals(const GHPoint& target) const;
};


#endif /* __GAME_DEV_HELPER_GHPOINT_H__ */
