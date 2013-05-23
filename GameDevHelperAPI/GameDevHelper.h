//
//  GameDevHelper.h
//  GameDevHelper.com
//
//  Created by Bogdan Vladu.
//  Copyright (c) 2013 Bogdan Vladu. All rights reserved.
//

#ifndef _GameDevHelper_API_h
#define _GameDevHelper_API_h


// 0x00 HI ME LO
// 00   02 01 00
/**
 The version of the API. Use this in order to support multiple versions of the api in your code. 
 
 @code
 #if GAME_DEV_HELPER_API_VERSION == 0x00010000
    //do something
 #else
    //do something else
 #endif
 @endcode
 */
#define GAME_DEV_HELPER_API_VERSION 0x00010000


// all GameDevHelepr API include files
#import "ghConfig.h"	//should be included first
#import "ghMacros.h"
//#import "GHSpriteBatchNode.h"
#import "GHSprite.h"
#import "GHAnimationCache.h"
#import "GHAnimation.h"

//#import "GHSkeleton.h"
//#import "GHSkeletalAnimationCache.h"
//#import "GHSkeletalAnimation.h"
//#import "GHDirector.h"
//#import "GHDebugDrawLayer.h"
//#import "GHDirector.h"


#endif//_GameDevHelper_API_h
