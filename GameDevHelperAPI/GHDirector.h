//
//  GHDirector.h
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 4/29/13.
//
//
#ifndef __GAME_DEV_HELPER_DIRECTOR_H__
#define __GAME_DEV_HELPER_DIRECTOR_H__


#import "ghConfig.h"

#if GH_ENABLE_PHYSICS_INTEGRATION
#import "Box2D.h"
#endif


/**
 This singleton is used to control the entire API. 
 
 Right now, not much is handled here, but more will be added soon.
 
 Since the GHDirector is a singleton, the standard way to use it is by calling:
 @code
    GHDirector::sharedDirector->getPhysicalWorld();
 @endcode
 */
class GHDirector
{
public:
    
    virtual ~GHDirector();
    
    /**
     Returns the singleton shared instance.
     */
    static GHDirector* sharedDirector();
    
#if GH_ENABLE_PHYSICS_INTEGRATION
    
    /**
     When physics support is enabled this will set the physics world.
     */
    void setPhysicalWorld(b2World* world);
    /**
     When physics support is enabled this will return the physics world.
     */
    b2World* getPhysicalWorld();
    
    /**
     When physics support is enabled this will set the current point to meter ratio you want to use.
     */
    void setPointToMeterRatio(float value);
    /**
     When physics support is enabled this will return the current point to meter ratio in use.
     */
    float getPointToMeterRatio();
    
#endif

    
    
    
private:
#if GH_ENABLE_PHYSICS_INTEGRATION
    b2World* physicalWorld;
    float ptm;
#endif
    
    GHDirector();    
    static GHDirector* s_pSharedDirector;
};

#endif //__GAME_DEV_HELPER_DIRECTOR_H__
