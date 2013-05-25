//
//  GHSkeletalAnimation.m
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 4/8/13.
//
//

#include "GHSkeletalAnimation.h"
#include "GHPoint.h"

GHSkeletalSkinConnectionInfo::GHSkeletalSkinConnectionInfo():
boneName(""),
angleOffset(0),
connectionAngle(0),
positionOffset(),
position(),
angle(0)
{
    
}
GHSkeletalSkinConnectionInfo::~GHSkeletalSkinConnectionInfo()
{
    
}

GHSkeletalSkinConnectionInfo* GHSkeletalSkinConnectionInfo::createSkinConnectionInfoWithBoneName(const char* name)
{
    GHSkeletalSkinConnectionInfo *pobNode = new GHSkeletalSkinConnectionInfo();
	if (pobNode && pobNode->initSkinConnectionInfoWithBoneName(name))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
}

bool GHSkeletalSkinConnectionInfo::initSkinConnectionInfoWithBoneName(const char* name)
{
    if(name)
        boneName = std::string(name);

    return true;
}

GHSkeletalSkinConnectionInfo* GHSkeletalSkinConnectionInfo::copyWithZone(CCZone *pZone)
{
    CC_UNUSED_PARAM(pZone);
    GHSkeletalSkinConnectionInfo *pCopy = new GHSkeletalSkinConnectionInfo();
    
    pCopy->initSkinConnectionInfoWithBoneName(boneName.c_str());
    pCopy->setAngleOffset(angleOffset);
    pCopy->setConnectionAngle(connectionAngle);
    pCopy->setPositionOffset(positionOffset);
    pCopy->setPosition(position);
    pCopy->setAngle(angle);
    
    return pCopy;
}



GHSkeletalAnimationFrame::GHSkeletalAnimationFrame():
time_(0),
bonePositions_(NULL),
spritesZOrder_(NULL),
skinConnections_(NULL),
skinSprites_(NULL),
spritesVisibility_(NULL),
spritesTransform_(NULL)
{
    
}
GHSkeletalAnimationFrame::~GHSkeletalAnimationFrame(){
    
    CC_SAFE_RELEASE_NULL(bonePositions_);
    CC_SAFE_RELEASE_NULL(spritesZOrder_);
    CC_SAFE_RELEASE_NULL(skinConnections_);
    CC_SAFE_RELEASE_NULL(skinSprites_);
    CC_SAFE_RELEASE_NULL(spritesVisibility_);
    CC_SAFE_RELEASE_NULL(spritesTransform_);    
}

GHSkeletalAnimationFrame* GHSkeletalAnimationFrame::createWithTime(float tm){

    GHSkeletalAnimationFrame *pobNode = new GHSkeletalAnimationFrame();
	if (pobNode && pobNode->initWithTime(tm))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
}
bool GHSkeletalAnimationFrame::initWithTime(float tm){
    time_ = tm;
    return true;
}


GHSkeletalAnimationFrame* GHSkeletalAnimationFrame::createWithFrame(GHSkeletalAnimationFrame* frm){

    GHSkeletalAnimationFrame *pobNode = new GHSkeletalAnimationFrame();
	if (pobNode && pobNode->initWithFrame(frm))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
}
bool GHSkeletalAnimationFrame::initWithFrame(GHSkeletalAnimationFrame* frm){

    if(!frm)return false;
    
    time_ = frm->getTime();
    
    
    {//copy positions
        CCDictionary* bonePoses = frm->getBonePositions();
        if(bonePoses){
            CC_SAFE_RELEASE_NULL(bonePositions_);
            bonePositions_ = CCDictionary::createWithDictionary(bonePoses);
            bonePositions_->retain();
        }
    }
    
    {//copy sprites z order
        CCDictionary* zOrders = frm->getSpritesZOrder();
        if(zOrders){
            CC_SAFE_RELEASE_NULL(spritesZOrder_);
            spritesZOrder_ = CCDictionary::createWithDictionary(zOrders);
            spritesZOrder_->retain();
        }
    }
    
    {//copy skin connections
        CCDictionary* skinCon = frm->getSkinConnections();
        if(skinCon){
            CC_SAFE_RELEASE_NULL(skinConnections_);
            skinConnections_ = CCDictionary::createWithDictionary(skinCon);
            skinConnections_->retain();
        }
    }
    
    {//copy skin sprites
        CCDictionary* skinSpr = frm->getSkinSprites();
        if(skinSpr){
            CC_SAFE_RELEASE_NULL(skinSprites_);
            skinSprites_ = CCDictionary::createWithDictionary(skinSpr);
            skinSprites_->retain();
        }
    }
    
    {//copy sprites visibility
        CCDictionary* sprVis = frm->getSpritesVisibility();
        if(sprVis){
            CC_SAFE_RELEASE_NULL(spritesVisibility_);
            spritesVisibility_ = CCDictionary::createWithDictionary(sprVis);
            spritesVisibility_->retain();
        }
    }
    
    {//copy sprites transform
        CCDictionary* sprTrans = frm->getSpritesTransform();
        if(sprTrans)
        {
            CC_SAFE_RELEASE_NULL(spritesTransform_);
            spritesTransform_ = CCDictionary::createWithDictionary(sprTrans);
            spritesTransform_->retain();
        }
    }
    
    return true;
}




void GHSkeletalAnimationFrame::setBonePositionsWithDictionary(CCDictionary* bones){
    
    if(NULL == bones)return;
    
    CC_SAFE_RELEASE_NULL(bonePositions_);
    
    
    bonePositions_ = CCDictionary::create();
    bonePositions_->retain();
    
    
    CCArray* keys = bones->allKeys();
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(keys, pObj)
    {
        CCString* boneName = (CCString*)pObj;
        CCString* bonePos = (CCString*)bones->objectForKey(boneName->getCString());
        
        if(bonePos)
        {
            CCPoint position = CCPointFromString(bonePos->getCString());
            position.x /= CC_CONTENT_SCALE_FACTOR();
            position.y /= CC_CONTENT_SCALE_FACTOR();
            
            bonePositions_->setObject(GHPoint::createWithValues(position.x, position.y),
                                      std::string(boneName->getCString()));
        }
    }
}

void GHSkeletalAnimationFrame::setSpritesZOrderWithDictionary(CCDictionary* sprites)
{
    if(NULL == sprites)return;
    
    CC_SAFE_RELEASE_NULL(spritesZOrder_);
    
    spritesZOrder_ = CCDictionary::createWithDictionary(sprites);
    spritesZOrder_->retain();
}

void GHSkeletalAnimationFrame::setSkinConnectionsWithDictionary(CCDictionary* connections)
{
    if(NULL == connections)return;
    
    CC_SAFE_RELEASE_NULL(skinConnections_);
    
    skinConnections_ = CCDictionary::create();
    skinConnections_->retain();
    
    CCArray* keys = connections->allKeys();
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(keys, pObj)
    {
        CCString* sprName = (CCString*)pObj;

        CCDictionary* connectionInfo = (CCDictionary*)connections->objectForKey(sprName->getCString());
        
        if(connectionInfo){
            
            CCString* boneName  = (CCString*)connectionInfo->objectForKey("bone");
            float angleOff      = connectionInfo->valueForKey("angleOff")->floatValue();
            float connAngle     = connectionInfo->valueForKey("connAngle")->floatValue();
            CCPoint posOff      = CCPointFromString(connectionInfo->valueForKey("posOff")->getCString());
            posOff.x /= CC_CONTENT_SCALE_FACTOR();
            posOff.y /= CC_CONTENT_SCALE_FACTOR();
            
            GHSkeletalSkinConnectionInfo* skinInfo = NULL;
            if(boneName)
                skinInfo = GHSkeletalSkinConnectionInfo::createSkinConnectionInfoWithBoneName(boneName->getCString());
            else
                skinInfo = GHSkeletalSkinConnectionInfo::createSkinConnectionInfoWithBoneName(NULL);
            
            if(skinInfo){
                skinInfo->setAngleOffset(angleOff);
                skinInfo->setConnectionAngle(connAngle);
                skinInfo->setPositionOffset(posOff);
           
                skinConnections_->setObject(skinInfo, std::string(sprName->getCString()));
            }
        }
    }
}

void GHSkeletalAnimationFrame::setSkinSpritesWithDictionary(CCDictionary* dictionary)
{
    if(NULL == dictionary)return;
    
    CC_SAFE_RELEASE_NULL(skinSprites_);
    
    skinSprites_ = CCDictionary::createWithDictionary(dictionary);
    skinSprites_->retain();
}

void GHSkeletalAnimationFrame::setSpritesVisibilityWithDictionary(CCDictionary* dictionary)
{
    if(NULL == dictionary)return;
    
    CC_SAFE_RELEASE_NULL(spritesVisibility_);

    spritesVisibility_ = CCDictionary::createWithDictionary(dictionary);
    spritesVisibility_->retain();
}

void GHSkeletalAnimationFrame::setSpritesTransformWithDictionary(CCDictionary* dictionary)
{
    if(NULL == dictionary)return;
    
    CC_SAFE_RELEASE_NULL(spritesTransform_);

    spritesTransform_ = CCDictionary::create();
    spritesTransform_->retain();
    
    CCArray* keys = dictionary->allKeys();
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(keys, pObj)
    {
        CCString* sprName = (CCString*)pObj;

        CCDictionary* transformInfo = (CCDictionary*)dictionary->objectForKey(sprName->getCString());
        if(transformInfo)
        {
            float angleOff  = transformInfo->valueForKey("angleOff")->floatValue();
            float connAngle = transformInfo->valueForKey("connAngle")->floatValue();
            CCPoint posOff = CCPointFromString(transformInfo->valueForKey("posOff")->getCString());
            posOff.x /= CC_CONTENT_SCALE_FACTOR();
            posOff.y /= CC_CONTENT_SCALE_FACTOR();
            
            float angle     = transformInfo->valueForKey("angle")->floatValue();
            CCPoint position = CCPointFromString(transformInfo->valueForKey("position")->getCString());
            position.x /= CC_CONTENT_SCALE_FACTOR();
            position.y /= CC_CONTENT_SCALE_FACTOR();
            
            GHSkeletalSkinConnectionInfo* transform = GHSkeletalSkinConnectionInfo::createSkinConnectionInfoWithBoneName(NULL);

            if(transform){
                transform->setAngleOffset(angleOff);
                transform->setConnectionAngle(connAngle);
                transform->setPositionOffset(posOff);
                
                transform->setAngle(angle);
                transform->setPosition(position);
                
                spritesTransform_->setObject(transform, std::string(sprName->getCString()));
            }
        }
    }
}









GHSkeletalAnimation::GHSkeletalAnimation():
name_(""),
totalTime_(0),
currentTime_(0),
playMode_(GH_SKELETAL_ANIM_PLAY_NORMAL),
bonePositionFrames_(NULL),
spriteZOrderFrames_(NULL),
skinConnectionFrames_(NULL),
skinSpriteFrames_(NULL),
visibilityFrames_(NULL),
spritesTransformFrames_(NULL),
numberOfLoops_(0),
currentLoop_(0),
reversed_(false),
paused_(false)
{
    
    bonePositionFrames_ = CCArray::create();
    bonePositionFrames_->retain();
    
    spriteZOrderFrames_ = CCArray::create();
    spriteZOrderFrames_->retain();
    
    skinConnectionFrames_ = CCArray::create();
    skinConnectionFrames_->retain();
    
    skinSpriteFrames_ = CCArray::create();
    skinSpriteFrames_->retain();
    
    visibilityFrames_ = CCArray::create();
    visibilityFrames_->retain();
    
    spritesTransformFrames_ = CCArray::create();
    spritesTransformFrames_->retain();
    
}
GHSkeletalAnimation::~GHSkeletalAnimation(){
    
    CCLOGINFO( @"GameDevHelper: deallocing %@",self);
    
    CC_SAFE_RELEASE_NULL(bonePositionFrames_);
    CC_SAFE_RELEASE_NULL(spriteZOrderFrames_);
    CC_SAFE_RELEASE_NULL(skinConnectionFrames_);
    CC_SAFE_RELEASE_NULL(skinSpriteFrames_);
    CC_SAFE_RELEASE_NULL(visibilityFrames_);
    CC_SAFE_RELEASE_NULL(spritesTransformFrames_);
    
}

GHSkeletalAnimation* GHSkeletalAnimation::createWithDictionary(CCDictionary* dict){
    
    GHSkeletalAnimation *pobNode = new GHSkeletalAnimation();
	if (pobNode && pobNode->initWithDictionary(dict))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
}
bool GHSkeletalAnimation::initWithDictionary(CCDictionary* dict){
    if(!dict)return false;
    
    
    paused_ = false;
    currentTime_ = 0;
    numberOfLoops_ = 0;
    currentLoop_ = 0;
    reversed_ = false;
    
    CCString* dictAnimName = (CCString*)dict->objectForKey("name");
    if(dictAnimName)
    {
        name_ = std::string(dictAnimName->getCString());
    }
    else{
        name_ = std::string("UntitledAnimation");
    }
    
    totalTime_  = dict->valueForKey("totalTime")->floatValue();
    playMode_   = (GHSkeletalAnimationPlayMode)dict->valueForKey("playMode")->intValue();
    
    {//setting bone positions
        CCArray* posFrames = (CCArray*)dict->objectForKey("positionFrames");
        
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(posFrames, pObj)
        {
            CCDictionary* frmInfo = (CCDictionary*)pObj;
            
            float frmTime = frmInfo->valueForKey("time")->floatValue();
            
            GHSkeletalAnimationFrame* frm = GHSkeletalAnimationFrame::createWithTime(frmTime);
            frm->setBonePositionsWithDictionary((CCDictionary*)frmInfo->objectForKey("bones"));
            
            bonePositionFrames_->addObject(frm);
        }
    }
    
    
    {//setting sprites z order
        CCArray* zOrderFrames = (CCArray*)dict->objectForKey("zOrderFrames");
        
        
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(zOrderFrames, pObj)
        {
            CCDictionary* frmInfo = (CCDictionary*)pObj;
            
            float frmTime = frmInfo->valueForKey("time")->floatValue();
            
            GHSkeletalAnimationFrame* frm = GHSkeletalAnimationFrame::createWithTime(frmTime);
            frm->setSpritesZOrderWithDictionary((CCDictionary*)frmInfo->objectForKey("sprites"));
            spriteZOrderFrames_->addObject(frm);
        }
    }
    
    {//setting skin connection frames
        CCArray* connectionFrames = (CCArray*)dict->objectForKey("connectionFrames");
        
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(connectionFrames, pObj)
        {
            CCDictionary* frmInfo = (CCDictionary*)pObj;
            
            float frmTime = frmInfo->valueForKey("time")->floatValue();
            
            GHSkeletalAnimationFrame* frm = GHSkeletalAnimationFrame::createWithTime(frmTime);
            frm->setSkinConnectionsWithDictionary((CCDictionary*)frmInfo->objectForKey("connections"));
            skinConnectionFrames_->addObject(frm);
        }
    }
    
    {//setting skin sprite frames
        CCArray* skinFrames = (CCArray*)dict->objectForKey("skinFrames");

        CCObject* pObj = NULL;
        CCARRAY_FOREACH(skinFrames, pObj)
        {
            CCDictionary* frmInfo = (CCDictionary*)pObj;
            
            float frmTime = frmInfo->valueForKey("time")->floatValue();
            
            GHSkeletalAnimationFrame* frm = GHSkeletalAnimationFrame::createWithTime(frmTime);
            frm->setSkinSpritesWithDictionary((CCDictionary*)frmInfo->objectForKey("skins"));
            skinSpriteFrames_->addObject(frm);
        }
    }
    
    {//setting sprite visibility frames
        CCArray* visFrames = (CCArray*)dict->objectForKey("visibilityFrames");
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(visFrames, pObj)
        {
            CCDictionary* frmInfo = (CCDictionary*)pObj;
            
            float frmTime = frmInfo->valueForKey("time")->floatValue();
            
            GHSkeletalAnimationFrame* frm = GHSkeletalAnimationFrame::createWithTime(frmTime);
            frm->setSpritesVisibilityWithDictionary((CCDictionary*)frmInfo->objectForKey("sprites"));
            visibilityFrames_->addObject(frm);
        }
    }
    
    {//setting sprite transform frames
        CCArray* transformFrames = (CCArray*)dict->objectForKey("spriteTransformFrames");
        
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(transformFrames, pObj)
        {
            CCDictionary* frmInfo = (CCDictionary*)pObj;
            
            float frmTime = frmInfo->valueForKey("time")->floatValue();
            
            GHSkeletalAnimationFrame* frm = GHSkeletalAnimationFrame::createWithTime(frmTime);
            frm->setSpritesTransformWithDictionary((CCDictionary*)frmInfo->objectForKey("transform"));
            spritesTransformFrames_->addObject(frm);
        }
    }
    
    
    
    return true;
}

void GHSkeletalAnimation::setTotalTime(float newTime)
{    
    if(newTime < 0.1)
        newTime = 0.1;
    
    float currentTotalTime = totalTime_;
    
    this->changeTimeForFrames(bonePositionFrames_, currentTotalTime ,newTime);
    
    this->changeTimeForFrames(spriteZOrderFrames_, currentTotalTime, newTime);
    
    this->changeTimeForFrames(skinConnectionFrames_, currentTotalTime, newTime);

    this->changeTimeForFrames(skinSpriteFrames_, currentTotalTime, newTime);

    this->changeTimeForFrames(visibilityFrames_, currentTotalTime, newTime);

    this->changeTimeForFrames(spritesTransformFrames_, currentTotalTime, newTime);

    
    totalTime_ = newTime;
}
void GHSkeletalAnimation::changeTimeForFrames(CCArray* frames, float currentTotalTime, float newTime)
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(frames, pObj)
    {
        GHSkeletalAnimationFrame* frame = (GHSkeletalAnimationFrame*)pObj;
        
        float currentFrameTime = frame->getTime();
        float frameUnit = currentFrameTime/currentTotalTime;
        //gives a value between 0 and 1 for the frame time
        //multiplying this unit value with the new total time gives use the new frame time
        float newFrameTime = frameUnit*newTime;
        frame->setTime(newFrameTime);
    }    
}

void GHSkeletalAnimation::setCurrentTime(float val)
{
    if(!paused_){
        currentTime_ = val;
    }
}


int GHSkeletalAnimation::goToNextFrameUsingFramesArray(CCArray* array)
{
    GHSkeletalAnimationFrame* currentFrame = NULL;
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(array, pObj)
    {
        GHSkeletalAnimationFrame* frm = (GHSkeletalAnimationFrame*)pObj;
        if(frm->getTime() <= currentTime_){
            currentFrame = frm;
        }
    }
    
    if(currentFrame){
        int idx = array->indexOfObject(currentFrame);
        ++idx;
        if(idx >= array->count()){
            idx = array->count()-1;
        }
        GHSkeletalAnimationFrame* nextFrame = (GHSkeletalAnimationFrame*)array->objectAtIndex(idx);
        currentTime_ = nextFrame->getTime();
        
        return idx;
    }
    
    return -1;
}

int GHSkeletalAnimation::goToPreviousFrameUsingFramesArray(CCArray* array)
{
    
    GHSkeletalAnimationFrame* currentFrame = NULL;
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(array, pObj)
    {
        GHSkeletalAnimationFrame* frm = (GHSkeletalAnimationFrame*)pObj;
        
        if(frm->getTime() <= currentTime_){
            currentFrame = frm;
        }
    }
    
    if(currentFrame){
        int idx = array->indexOfObject(currentFrame);
        --idx;
        if(idx <0){
            idx = 0;
        }
        GHSkeletalAnimationFrame* nextFrame = (GHSkeletalAnimationFrame*)array->objectAtIndex(idx);
        currentTime_ = nextFrame->getTime();
        return idx;
    }
    return -1;
}


GHSkeletalAnimation* GHSkeletalAnimation::createWithAnimation(GHSkeletalAnimation* other)
{
    GHSkeletalAnimation *pobNode = new GHSkeletalAnimation();
	if (pobNode && pobNode->initWithAnimation(other))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
}

void GHSkeletalAnimation::copyFramesFrom(CCArray* otherArray, CCArray* toArray)
{
    if(otherArray){
        
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(otherArray, pObj)
        {
            GHSkeletalAnimationFrame* frm = (GHSkeletalAnimationFrame*)pObj;
            if(frm){
                toArray->addObject(GHSkeletalAnimationFrame::createWithFrame(frm));
            }
        }
    }
}

bool GHSkeletalAnimation::initWithAnimation(GHSkeletalAnimation* other)
{
    //WE SHOULD CREATE NEW FRAMES FROM THIS ANIMATIONS FRAMES IN CASE THE USER CHANGES THE TIME
    //OF AN ANIMATION TO NOT CHANGE ON ALL SAME ANIMATIONS

    this->copyFramesFrom(other->getBonePositionFrames(), bonePositionFrames_);
    
    this->copyFramesFrom(other->getSpriteZOrderFrames(), spriteZOrderFrames_);

    this->copyFramesFrom(other->getSkinConnectionFrames(), skinConnectionFrames_);

    this->copyFramesFrom(other->getSkinSpriteFrames(), skinSpriteFrames_);

    this->copyFramesFrom(other->getVisibilityFrames(), visibilityFrames_);
   
    this->copyFramesFrom(other->getSpritesTransformFrames(), spritesTransformFrames_);
    
    totalTime_ = other->getTotalTime();
    name_ = std::string(other->getName());
    
    this->setNumberOfLoops(other->getNumberOfLoops());
    this->setCurrentLoop(other->getCurrentLoop());
    this->setPlayMode(other->getPlayMode());
    this->setCurrentTime(other->getCurrentTime());
    this->setReversed(other->getReversed());
    
    return true;
}



