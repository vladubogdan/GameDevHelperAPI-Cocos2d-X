//
//  GHSprite.mm
//  GameDevHelper.com
//
//  Created by Bogdan Vladu.
//  Copyright (c) 2013 Bogdan Vladu. All rights reserved.
//

#include "GHSprite.h"
#include "GHDirector.h"
#include "ghMacros.h"
#include "GHAnimationCache.h"



GHSprite* GHSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
#endif
    
    
    GHSprite *pobNode = new GHSprite();
	if (pobNode && pobNode->initWithSpriteFrameName(pszSpriteFrameName))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
}



bool GHSprite::initWithSpriteFrameName(const char *pszSpriteFrameName)
{
    CCAssert(pszSpriteFrameName != NULL, "");
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    if(initWithSpriteFrame(pFrame))
    {
        spriteFrameName = std::string(pszSpriteFrameName);
             

        //lets find the plist file
        std::string filePath = std::string(this->imageFile.c_str());
        std::string path = filePath;
        std::string fileName = filePath;
        
        size_t lastslash = filePath.find_last_of("/");
        if (lastslash != std::string::npos)
        {
            path = filePath.substr(0, lastslash+1);
            fileName = filePath.substr(lastslash+1, filePath.size() - lastslash-1);
        }
        std::string fileNameNoExt = fileName;
        size_t firstDot = fileName.find_first_of(".");
        if (firstDot != std::string::npos)
        {
            fileNameNoExt = fileName.substr(0, firstDot);
        }
        std::string plistFile = fileNameNoExt + ".plist";
        
        plistFile = CCFileUtils::sharedFileUtils()->fullPathForFilename(plistFile.c_str());
        
        //TODO - keep track of this dict so you don't load it again - maybe in the GHSpriteBatchNode
        CCDictionary* dict = CCDictionary::createWithContentsOfFile(plistFile.c_str());
        
        CCDictionary* frames =  (CCDictionary*)dict->objectForKey("frames");
        if(frames)
        {
            CCDictionary* frameInfo = (CCDictionary*)frames->objectForKey(pszSpriteFrameName);

            if(frameInfo){
                
                //if its a normal cocos2d plist we wont have this keys
                CCString* tagInfo = (CCString*)frameInfo->valueForKey("tag");
                
                if(tagInfo){
                    this->setTag(tagInfo->intValue());
                }
                
                CCString* tint = (CCString*)frameInfo->valueForKey("tint");
                
                if(tint){
                    CCRect tintRect = CCRectFromString(tint->getCString());
                    this->setColor(ccc3(tintRect.origin.x, tintRect.origin.y, tintRect.size.width));
                    this->setOpacity(tintRect.size.height);
                }
            }

            
#if GH_ENABLE_PHYSICS_INTEGRATION
                body = NULL;

                CCDictionary* bodyInfo = (CCDictionary*)frameInfo->objectForKey("body");
                if(bodyInfo){
                    physicsInfo = CCDictionary::createWithDictionary(bodyInfo);
                    physicsInfo->retain();
                    this->createBody();
                }
#endif
        }
    
        return true;
    }
    return false;
}

bool GHSprite::initWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    if(CCSprite::initWithSpriteFrame(pSpriteFrame))
    {
        //cocos2d-x does not have a way to get the filename of a texture from a spriteframe just like cocos2d has
        //so we use this ugly trick, while its not nice in most cases it should be ok
        
        //TODO - check if parent is a GHSpriteBatchNode and get the file from there
        CCDictionary* allTextures = CCTextureCache::sharedTextureCache()->snapshotTextures();
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(allTextures, pElement)
        {
            if(this->getTexture() == pElement->getObject())
            {
                this->setImageFile(pElement->getStrKey());
            }
        }

        return true;
    }
    return false;
}

GHSprite::GHSprite():
imageFile(""),
spriteFrameName(""),
name(""),
activeAnimation(NULL)
{
#if GH_ENABLE_PHYSICS_INTEGRATION
    physicsInfo = NULL;
    body = NULL;
#endif

}

GHSprite::~GHSprite(){
    
    if(activeAnimation){
        activeAnimation->setSprite(NULL);
        activeAnimation->release();
        activeAnimation = NULL;
    }
    
#if GH_ENABLE_PHYSICS_INTEGRATION
    if(physicsInfo){
        physicsInfo->release();
        physicsInfo = NULL;
    }
#endif
    
}

void GHSprite::setImageFile(const char *value)
{
    if(value)
        imageFile = std::string(value);
}

std::string GHSprite::getImageFile(void)
{
    return imageFile;
}

std::string GHSprite::getSpriteFrameName(void){
    return spriteFrameName;
}

void GHSprite::setName(const char* val){
    if(val){
        name = std::string(val);
    }
}
std::string GHSprite::getName(){
    return name;
}

std::string GHSprite::description(){
    return "GHSprite imageFile: " + imageFile + " spriteFrameName: " + spriteFrameName;
}


void GHSprite::prepareAnimation(GHAnimation* anim)
{
    if(activeAnimation){
        activeAnimation->setSprite(NULL);
        activeAnimation->release();
        activeAnimation = NULL;
    }
    if(anim){
        activeAnimation = GHAnimation::createWithAnimation(anim);
        activeAnimation->retain();
        activeAnimation->setSprite(this);
        activeAnimation->prepare();
    }
}
void GHSprite::prepareAnimationWithName(const char* animName)
{
    GHAnimation* anim = GHAnimationCache::sharedAnimationCache()->animationByName(animName);
    if(anim){
        this->prepareAnimation(anim);
    }
    else{
        CCLOG("GameDevHelperAPI WARNING: Animation with name %@ was could not be prepared because it was not found.", animName);
    }
}
GHAnimation* GHSprite::getAnimation(){
    return activeAnimation;
}

void GHSprite::playAnimation(){
    if(activeAnimation){activeAnimation->play();};
}
void GHSprite::pauseAnimation(){
    if(activeAnimation)activeAnimation->pause();
}
void GHSprite::restartAnimation(){

}
void GHSprite::stopAnimation(){
    
}
void GHSprite::stopAnimationAndRestoreOriginalFrame(bool restore)
{
    
}

void GHSprite::setAnimationDelegate(GHAnimationDelegate* obj){
    if(activeAnimation){activeAnimation->setDelegate(obj);}
}


void GHSprite::update(float dt){
    if(activeAnimation){
        activeAnimation->update(dt);
    }
}



#if GH_ENABLE_PHYSICS_INTEGRATION
void GHSprite::destroyBody(){
    if(body){
        b2World* bWorld = body->GetWorld();
        bWorld->DestroyBody(body);
        body = NULL;
    }
}
void GHSprite::createBody(){
    
    if(physicsInfo == NULL)return;
    
    this->destroyBody();
    
    b2World* world = GHDirector::sharedDirector()->getPhysicalWorld();

    if(world == NULL)return;
    
    int type = physicsInfo->valueForKey("type")->intValue();
    if(type == 3)//NO PHYSICS
        return;
    
    b2BodyDef bodyDef;
	bodyDef.type = (b2BodyType)type;
	   
	bodyDef.position = GH_POINT_TO_METERS(this->getPosition());
    
	bodyDef.angle = CC_DEGREES_TO_RADIANS(-1*this->getRotation());
    bodyDef.userData = this;

    body = world->CreateBody(&bodyDef);
    
	body->SetFixedRotation(physicsInfo->valueForKey("fixed")->boolValue());
    body->SetGravityScale(physicsInfo->valueForKey("gravityScale")->floatValue());
	body->SetSleepingAllowed(physicsInfo->valueForKey("sleep")->boolValue());
    body->SetBullet(physicsInfo->valueForKey("bullet")->boolValue());
    body->SetAwake(physicsInfo->valueForKey("awake")->boolValue());
    body->SetActive(physicsInfo->valueForKey("active")->boolValue());

    CCArray* shapesInfo = (CCArray*)physicsInfo->objectForKey("shapes");

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(shapesInfo, pObj)
    {
        CCDictionary *shInfo = (CCDictionary*)pObj;

        float density       = shInfo->valueForKey("density")->floatValue();
        float friction      = shInfo->valueForKey("friction")->floatValue();
        float restitution   = shInfo->valueForKey("restitution")->floatValue();
        bool sensor         = shInfo->valueForKey("sensor")->boolValue();

//        <key>name</key>
//        <string>backpackShape</string>
//        <key>sensor</key>
//        <false/>
//        <key>shapeID</key>
//        <integer>0</integer>
//        
        
        int type = shInfo->valueForKey("type")->intValue();

        if(type == 2) //CIRCLE
        {
            b2FixtureDef fixture;
            b2CircleShape circle;
            
            float circleRadius  = shInfo->valueForKey("radius")->floatValue();
            const CCString* offsetStr = shInfo->valueForKey("circleOffset");
            CCPoint offset = CCPointFromString(offsetStr->getCString());
            
            circle.m_radius = GH_VALUE_TO_METERS(circleRadius)/2.0f;

            circle.m_radius /= CC_CONTENT_SCALE_FACTOR();
            offset.x /= CC_CONTENT_SCALE_FACTOR();
            offset.y /= CC_CONTENT_SCALE_FACTOR();
            
            circle.m_p = GH_POINT_TO_METERS(offset);
            
            fixture.shape = &circle;
            
            fixture.density = density;
            fixture.friction = friction;
            fixture.restitution = restitution;
            fixture.isSensor = sensor;
            
            CCObject* cat     = shInfo->objectForKey("category");
            CCObject* mask    = shInfo->objectForKey("mask");
            if(cat && mask)
            {
                
                fixture.filter.categoryBits = ((CCString*)cat)->intValue();
                fixture.filter.maskBits     = ((CCString*)mask)->intValue();                
            }
                        
            body->CreateFixture(&fixture);
        }
        else{//create using points
            CCArray* fixtures = (CCArray*)shInfo->objectForKey("fixtures");
            
            CCObject* pFixObj = NULL;
            CCARRAY_FOREACH(fixtures, pFixObj)
            {
                CCArray* fixPoints = (CCArray*)pFixObj;

                int count = (int)fixPoints->count();
                b2Vec2 *verts = new b2Vec2[count];
                b2PolygonShape shapeDef;
                
                
                int i = count - 1;
                for(int j = 0; j< count; ++j)
                {
                    CCString* pointStr = (CCString*)fixPoints->objectAtIndex(j);
                    CCPoint point = CCPointFromString(pointStr->getCString());

                    point.x /= CC_CONTENT_SCALE_FACTOR();
                    point.y /= CC_CONTENT_SCALE_FACTOR();
                    
                    //flip y for cocos2d coordinate system
                    point.y =  this->getTextureRect().size.height - point.y;
                    point.y = point.y - this->getTextureRect().size.height;
                    
                    
                    verts[i] = GH_POINT_TO_METERS(point);                    
                    i = i-1;
                }
                
                shapeDef.Set(verts, count);
                
                b2FixtureDef fixture;
                //------------------------------------------------------------------
                fixture.density = density;
                fixture.friction = friction;
                fixture.restitution = restitution;
                fixture.isSensor = sensor;
                
                CCObject* cat     = shInfo->objectForKey("category");
                CCObject* mask    = shInfo->objectForKey("mask");
                if(cat && mask)
                {
                    fixture.filter.categoryBits = ((CCString*)cat)->intValue();
                    fixture.filter.maskBits     = ((CCString*)mask)->intValue();
                }
                
                fixture.shape = &shapeDef;
                body->CreateFixture(&fixture);
                delete[] verts;
            }

            
        }
    }
}

// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
bool GHSprite::isDirty(void)
{
	return true;
}

// returns the transform matrix according the Chipmunk Body values
CCAffineTransform GHSprite::nodeToParentTransform(void)
{
    if(body){
        CCPoint pos = GH_METERS_TO_POINT(body->GetPosition());
	
        if(m_bIgnoreAnchorPointForPosition){
            pos.x += m_obAnchorPointInPoints.x;
            pos.y += m_obAnchorPointInPoints.y;
        }
        
        // Make matrix
        float radians = body->GetAngle();
        float c = cosf(radians);
        float s = sinf(radians);

        if(!(m_obAnchorPointInPoints.x == 0 && m_obAnchorPointInPoints.y == 0)){
            pos.x += c*-m_obAnchorPointInPoints.x + -s*-m_obAnchorPointInPoints.y;
            pos.y += s*-m_obAnchorPointInPoints.x + c*-m_obAnchorPointInPoints.y;
        }
        
        // Rot, Translate Matrix
        
        m_sTransform = CCAffineTransformMake( c,  s,
                                           -s,	c,
                                           pos.x,	pos.y);
        
        return m_sTransform;
    }
    
    return CCSprite::nodeToParentTransform();
}

void GHSprite::setPosition(const CCPoint& pos)
{
    CCSprite::setPosition(pos);
    if(body){
        body->SetTransform(GH_POINT_TO_METERS(pos), CC_DEGREES_TO_RADIANS(-1*this->getRotation()));
    }
}

void GHSprite::setRotation(float rot)
{
    CCSprite::setRotation(rot);
    if(body){
        body->SetTransform(GH_POINT_TO_METERS(this->getPosition()), CC_DEGREES_TO_RADIANS(-1*rot));
    }
}

#endif //GH_ENABLE_PHYSICS_INTEGRATION
