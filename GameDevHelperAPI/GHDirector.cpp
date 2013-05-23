//
//  GHDirector.mm
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 4/29/13.
//
//

#include "GHDirector.h"

GHDirector *GHDirector::s_pSharedDirector = 0;
////////////////////////////////////////////////////////////////////////////////
GHDirector* GHDirector::sharedDirector(){
	if (0 == s_pSharedDirector){
		s_pSharedDirector = new GHDirector();
	}
    return s_pSharedDirector;
}
////////////////////////////////////////////////////////////////////////////////
GHDirector::~GHDirector()
{

#if GH_ENABLE_PHYSICS_INTEGRATION
    physicalWorld = NULL;
#endif

}
//------------------------------------------------------------------------------
GHDirector::GHDirector(){

#if GH_ENABLE_PHYSICS_INTEGRATION
    physicalWorld = NULL;
    ptm = 32.0f;
#endif
    
}


#if GH_ENABLE_PHYSICS_INTEGRATION

void GHDirector::setPhysicalWorld(b2World* world){
    physicalWorld = world;
}

b2World* GHDirector::getPhysicalWorld()
{
    return physicalWorld;
}

void GHDirector::setPointToMeterRatio(float value)
{
    ptm = value;
}
float GHDirector::getPointToMeterRatio()
{
    return ptm;
}

#endif

