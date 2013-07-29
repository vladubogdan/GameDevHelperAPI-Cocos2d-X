//
//  GHSkeleton.m
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 4/4/13.
//
//

#include "GHSkeleton.h"
#include "GHSprite.h"
#include "GHBoneSkin.h"
#include "GHSkeletalAnimationCache.h"
#include "GHSkeletalAnimation.h"
#include "GHPoint.h"
GHSkeleton::GHSkeleton():

rootBone(NULL),
batchNode_(NULL),
poses(NULL),
skins(NULL),
#if GH_DEBUG
colorLocation_(0),
#endif
animation(NULL),
transitionTime(NULL),
currentTranstionTime(0),
delegate(NULL)
{
    
}
GHSkeleton::~GHSkeleton(){
 
    delegate = NULL;
    
#ifdef GH_DEBUG
    m_pShaderProgram = NULL;
#endif
    
    this->unscheduleAllSelectors();
    this->unscheduleUpdate();

    CC_SAFE_RELEASE(rootBone);
    CC_SAFE_RELEASE(poses);
    CC_SAFE_RELEASE(transitionTime);
    CC_SAFE_RELEASE(animation);
}

GHSkeleton* GHSkeleton::createWithFile(const char* file){
    
    GHSkeleton *pobNode = new GHSkeleton();
	if (pobNode && pobNode->initWithFile(file))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
}

bool GHSkeleton::initWithFile(const char* file){
    
    if(!file)return false;
    
    //maybe the file has or does not have extension given - we do this little trick
//    std::string plistFile = [file stringByDeletingPathExtension];
//    plistFile = [plistFile stringByAppendingPathExtension:@"plist"];
//    
//    //maye the user has given a suffix - not necessary
//    plistFile =  [[CCFileUtils sharedFileUtils] removeSuffixFromFile:plistFile];
//    NSString *path = [[CCFileUtils sharedFileUtils] fullPathFromRelativePath:plistFile];
//
    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(file);
    
    
    CCDictionary *dict = CCDictionary::createWithContentsOfFile(path.c_str());
    
    std::string pathToSkeleton = "";// [file stringByDeletingLastPathComponent];
    std::string pathToSheet = "";//[pathToSkeleton stringByDeletingLastPathComponent];
    
    CCString* sheetName = (CCString*)dict->objectForKey("sheet");
    if(sheetName)
    {
       // std::string sheetFile = "";//[pathToSheet stringByAppendingPathComponent:sheetName];
        batchNode_ = CCSpriteBatchNode::create(sheetName->getCString());
        this->addChild(batchNode_, -1);//this way debug drawing will be 0
        batchNode_->setPosition(ccp(0,0));
        
        std::string sheetPlist = "";//[sheetFile stringByDeletingPathExtension];
        sheetPlist = "";//[sheetPlist stringByAppendingPathExtension:@"plist"];
        
        
        
        //lets find the plist file
        std::string sheetImgFile = std::string(sheetName->getCString());        
        size_t lastslash = sheetImgFile.find_last_of("/");
        if (lastslash != std::string::npos)
        {
            sheetImgFile = sheetImgFile.substr(lastslash+1, sheetImgFile.size() - lastslash-1);
        }
        std::string fileNameNoExt = sheetImgFile;
        size_t firstDot = sheetImgFile.find_first_of(".");
        if (firstDot != std::string::npos)
        {
            fileNameNoExt = sheetImgFile.substr(0, firstDot);
        }
        std::string plistFile = fileNameNoExt + ".plist";
                
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistFile.c_str());
    }
    
    this->loadBones((CCDictionary*)dict->objectForKey("root"));
    this->loadSprites((CCArray*)dict->objectForKey("sprites"));
    this->updateSkins();
    
    
    CCDictionary* posesDict = (CCDictionary*)dict->objectForKey("poses");
    if(posesDict){
        poses = CCDictionary::createWithDictionary(posesDict);
        poses->retain();
    }
    
#if GH_DEBUG
    this->initShader();
#endif

    return true;
}

void GHSkeleton::loadSprites(CCArray* spritesInfo)
{
    if(!spritesInfo)return;
    
    CCArray* allBones = this->getAllBones();//CCArray::createWithArray(this->getAllBones());

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(spritesInfo, pObj)
    {
        CCDictionary* sprInfo = (CCDictionary*)pObj;

        //name
        //angle
        //localPos
        //visible
        CCPoint localPos = CCPointMake(0, 0);
        
        CCString* sprPos = (CCString*)sprInfo->objectForKey("localPos");
        if(sprPos){
            localPos = CCPointFromString(sprPos->getCString());
        }
        localPos.x /=CC_CONTENT_SCALE_FACTOR();
        localPos.y /=CC_CONTENT_SCALE_FACTOR();
        
        
        float angle = 0;
        CCString* sprAngle = (CCString*)sprInfo->objectForKey("angle");
        if(sprAngle){
            angle = sprAngle->floatValue();
        }
        
        bool visible = true;
        CCString* sprVis = (CCString*)sprInfo->objectForKey("visible");
        if(sprVis){
            visible = sprVis->boolValue();
        }
        
        CCString* boneUUID = (CCString*)sprInfo->objectForKey("boneUUID");
        
        CCString* skinName = (CCString*)sprInfo->objectForKey("skinName");
        CCString* skinUUID = (CCString*)sprInfo->objectForKey("skinUUID");
        
        CCString* sprName = (CCString*)sprInfo->objectForKey("sprName");
        if(sprName){
            GHSprite* newSpr = GHSprite::createWithSpriteFrameName(sprName->getCString());
            newSpr->setName(skinName->getCString());
            newSpr->setPosition(localPos);
            newSpr->setRotation(angle);
            newSpr->setColor(ccc3(255, 255, 255));
            newSpr->setVisible(visible);
            if(batchNode_ != NULL){
                batchNode_->addChild(newSpr);
            }
            
            if(boneUUID){
                CCObject* pBoneObj = NULL;
                CCARRAY_FOREACH(allBones, pBoneObj)
                {
                    GHBone* bone = (GHBone*)pBoneObj;

                    if(bone->getUuid() == boneUUID->getCString())
                    {
                        this->addSkin(GHBoneSkin::createSkinWithSprite(newSpr,
                                                                       bone,
                                                                       skinName->getCString(),
                                                                       skinUUID->getCString()));
                        break;//exit for loop
                    }
                }
            }
            else{
                this->addSkin(GHBoneSkin::createSkinWithSprite(newSpr,
                                                               NULL,
                                                               skinName->getCString(),
                                                               skinUUID->getCString()));
            }
        }
    }
}

void GHSkeleton::loadBones(CCDictionary* rootBoneInfo)
{
    if(!rootBoneInfo)return;
    rootBone = GHBone::createBoneWithDictionary(rootBoneInfo);
}

CCArray* GHSkeleton::getAllBones()
{
    CCArray* array = CCArray::create();
    
    array->addObject(rootBone);

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(rootBone->getChildren(), pObj)
    {
        GHBone* bone = (GHBone*)pObj;
        array->addObjectsFromArray(bone->getAllBones());
    }
    
    return array;
}

void GHSkeleton::setPositionForBoneNamed(CCPoint location, const char * boneName)
{
    GHBone* bone = rootBone->getBoneWithName(boneName);

    if(bone){
        CCPoint localPoint = ccp(location.x - this->getPosition().x,
                                 location.y - this->getPosition().y);
        bone->setBonePosition(localPoint, NULL);
    }
    rootBone->updateMovement();
    this->transformSkins();
}

void GHSkeleton::setPoseWithName(const char* poseName)
{
    CCAssert( poses != NULL, "\n\nERROR: Skeleton has no poses or poses were not publish.\n\n");

    CCDictionary* poseInfo = (CCDictionary*)poses->objectForKey(poseName);
    CCAssert( poseInfo != NULL, "\n\nERROR: Skeleton has no pose with the given \"poseName\" argument.\n\n");
        
    CCDictionary* visibility = (CCDictionary*)poseInfo->objectForKey("visibility");
    CCAssert( visibility != NULL, "\n\nERROR: Skeleton pose is in wrong format. Skin visibilities were not found.\n\n");
    
    CCDictionary* zOrder = (CCDictionary*)poseInfo->objectForKey("zOrder");
    CCAssert( visibility != NULL, "\n\nERROR: Skeleton pose is in wrong format. Skin z orders were not found.\n\n");
    
    CCDictionary* skinTex = (CCDictionary*)poseInfo->objectForKey("skinTex");
    CCAssert( skinTex != NULL, "\n\nERROR: Skeleton pose is in wrong format. Skin sprite frame names were not found.\n\n");
    
    CCDictionary* connections = (CCDictionary*)poseInfo->objectForKey("connections");
    CCAssert( connections != NULL, "\n\nERROR: Skeleton pose is in wrong format. Skin connections were not found.\n\n");
    
    CCArray* allBones = this->getAllBones();
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(skins, pObj)
    {
        GHBoneSkin* skin = (GHBoneSkin*)pObj;

        skin->getSprite()->setVisible(true);

        CCString* value = (CCString*)visibility->objectForKey(skin->getUUID());
        if(value){
            skin->getSprite()->setVisible(false);
        }

        CCString* zValue = (CCString*)zOrder->objectForKey(skin->getUUID());
        if(zValue){
            batchNode_->reorderChild(skin->getSprite(), zValue->intValue());
        }
        
        CCString* spriteFrameName = (CCString*)skinTex->objectForKey(skin->getUUID());
        if(spriteFrameName){
            CCSpriteFrame* frame =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName->getCString());
            if(frame){
                skin->getSprite()->setDisplayFrame(frame);
            }
        }
        
        CCDictionary* connectionInfo = (CCDictionary*)connections->objectForKey(skin->getUUID());
        if(connectionInfo){
            //angleOff
            //boneUUID //this may be missing if no connection
            //conAngle
            //posOff
            
            CCString* boneUUID = (CCString*)connectionInfo->objectForKey("boneUUID");
            if(boneUUID)
            {
                //check if the current bone is already our connection bone - if not change it
                if(!(skin->getBone() && skin->getBone()->getUuid() == boneUUID->getCString()))
                {
                    CCObject* pBoneObj = NULL;
                    CCARRAY_FOREACH(allBones, pBoneObj)
                    {
                        GHBone* bone = (GHBone*)pBoneObj;

                        if(bone->getUuid() == boneUUID->getCString())
                        {
                            skin->setBone(bone);
                            break;
                        }
                    }
                }
            }
            else{
                skin->setBone(NULL);
            }
            
            CCString* angleOff = (CCString*)connectionInfo->objectForKey("angleOff");
            if(angleOff){
                skin->setAngleOffset(angleOff->floatValue());
            }
            
            CCString* posOff = (CCString*)connectionInfo->objectForKey("posOff");
            if(posOff)
            {
                CCPoint newPos = CCPointFromString(posOff->getCString());
                newPos.x /= CC_CONTENT_SCALE_FACTOR();
                newPos.y /= CC_CONTENT_SCALE_FACTOR();
                skin->setPositionOffset(newPos);
            }
    
            CCString* connectionAngle = (CCString*)connectionInfo->objectForKey("conAngle");
            if(connectionAngle){
                skin->setConnectionAngle(connectionAngle->floatValue());
            }
        }
    }

    
    CCDictionary* positions = (CCDictionary*)poseInfo->objectForKey("positions");
    CCAssert( positions != NULL, "\n\nERROR: Skeleton pose is in wrong format. Bone positions were not found.\n\n");
    
    CCObject* pBoneObj = NULL;
    CCARRAY_FOREACH(allBones, pBoneObj)
    {
        GHBone* bone = (GHBone*)pBoneObj;

        std::string uuid = bone->getUuid();
        CCAssert( uuid != "", "\n\nERROR: Bone has no UUID.\n\n");
        
        CCString* bonePos = (CCString*)positions->objectForKey(uuid);
        CCAssert( bonePos != NULL, "\n\nERROR: Bone pose does not have a position value. Must be in a wrong format.\n\n");
        
        CCPoint newPos = CCPointFromString(bonePos->getCString());
        newPos.x /= CC_CONTENT_SCALE_FACTOR();
        newPos.y /= CC_CONTENT_SCALE_FACTOR();
        bone->setPosition(newPos);
        
//        CCLog("BONE %s setPos %f %f", bone->getName().c_str(), newPos.x, newPos.y);
    }
    
    this->transformSkins();
    
    if(delegate)
    {
        delegate->didLoadPoseWithNameOnSkeleton(poseName, this);
    }
}


void GHSkeleton::addSkin(GHBoneSkin* skin)
{
    if(!skin)return;
    
    if(!skins){
        skins = CCArray::create();
        skins->retain();
    }
    skins->addObject(skin);
}
void GHSkeleton::removeSkin(GHBoneSkin* skin)
{
    if(skins)
        skins->removeObject(skin);
}


void GHSkeleton::playAnimation(GHSkeletalAnimation* anim)
{
    if(NULL == anim)return;
    
    this->stopAnimation();

    CC_SAFE_RELEASE(transitionTime);
    
    currentTranstionTime = 0;
    
    animation = GHSkeletalAnimation::createWithAnimation(anim);
    animation->retain();
    
    animation->setCurrentTime(0);
    animation->setCurrentLoop(0);
    
    if(delegate){
        delegate->didStartAnimationOnSkeleton(animation, this);
    }
    this->scheduleUpdate();
}

void GHSkeleton::playAnimationWithName(const char* animName)
{
    GHSkeletalAnimation* anim = GHSkeletalAnimationCache::sharedSkeletalAnimationCache()->skeletalAnimationWithName(animName);
    this->playAnimation(anim);
}

void GHSkeleton::transitionToAnimationInTime(GHSkeletalAnimation* anim, float time)
{
    if(NULL == anim)return;

    CCArray* allBones = this->getAllBones();
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(allBones, pObj)
    {
        GHBone* bone = (GHBone*)pObj;
        bone->savePosition();
    }

    this->playAnimation(anim);//this will also remove any previous transition time
    
    transitionTime = CCFloat::create(time);
    transitionTime->retain();
    currentTranstionTime = 0;
}

void GHSkeleton::transitionToAnimationWithNameInTime(const char* animName, float time)
{
    GHSkeletalAnimation* anim = GHSkeletalAnimationCache::sharedSkeletalAnimationCache()->skeletalAnimationWithName(animName);
    this->transitionToAnimationInTime(anim, time);
}


void GHSkeleton::stopAnimation(){
    CC_SAFE_RELEASE_NULL(animation);
    this->unscheduleUpdate();
}

void GHSkeleton::update(float dt)
{
    float time = 0;
    
    if(transitionTime != NULL)
    {
        if(transitionTime->getValue() < currentTranstionTime)
        {
            CC_SAFE_RELEASE_NULL(transitionTime);

            animation->setCurrentTime(dt);
            animation->setCurrentLoop(0);
            currentTranstionTime = 0;
            time = dt;
            
            if(delegate){
                delegate->didFinishTransitionToAnimationOnSkeleton(animation, this);
            }
        }
        time = currentTranstionTime;
        currentTranstionTime += dt;
    }
    else{
        time = animation->getCurrentTime();
        
        if(animation->getReversed()){
            animation->setCurrentTime(animation->getCurrentTime() - dt);
        }else{
            animation->setCurrentTime(animation->getCurrentTime() + dt);
        }
    }

    
    if(animation->getReversed() && transitionTime == NULL)
    {
        if(time <= 0){
            
            switch (animation->getPlayMode()) {
                case GH_SKELETAL_ANIM_PLAY_NORMAL:
                case GH_SKELETAL_ANIM_PLAY_LOOP:
                {
                    animation->setCurrentTime(animation->getTotalTime());
                }
                    break;
                    
                case GH_SKELETAL_ANIM_PLAY_PINGPONG:
                {
                    animation->setCurrentTime(0);
                    animation->setReversed(false);
                }
                    break;
                    
                default:
                    break;
            }
            
            if(delegate){
                delegate->didFinishLoopInAnimationOnSkeleton(animation, this);
            }
            animation->setCurrentLoop(animation->getCurrentLoop() + 1);
        }
    }
    else{
        if(time >= animation->getTotalTime()){
            
            switch(animation->getPlayMode())
            {
                case GH_SKELETAL_ANIM_PLAY_NORMAL:
                {
                    this->stopAnimation();
                    return;
                }
                    break;
                    
                case GH_SKELETAL_ANIM_PLAY_LOOP:
                {
                    animation->setCurrentTime(0);
                }
                    break;

                case GH_SKELETAL_ANIM_PLAY_PINGPONG:
                {
                    animation->setCurrentTime(animation->getTotalTime());
                    animation->setReversed(true);
                }
                    break;

                default:
                    break;
            }
            animation->setCurrentLoop(animation->getCurrentLoop()+1);
            if(delegate){
                delegate->didFinishLoopInAnimationOnSkeleton(animation, this);
            }
        }
    }
    
    if(animation->getNumberOfLoops() != 0 && animation->getCurrentLoop() >= animation->getNumberOfLoops())
    {
        this->stopAnimation();
    }
    
    
    CCArray* allBones = this->getAllBones();

    
    { //handle positions
        GHSkeletalAnimationFrame* beginFrame = NULL;
        GHSkeletalAnimationFrame* endFrame = NULL;
        
        
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(animation->getBonePositionFrames(), pObj)
        {
            GHSkeletalAnimationFrame* frm = (GHSkeletalAnimationFrame*)pObj;
            
            if(frm->getTime() <= time){
                beginFrame = frm;
            }
            
            if(frm->getTime() > time){
                endFrame = frm;
                break;//exit for
            }
        }
        
        if(transitionTime)
        {
            CCArray* positionFrames = animation->getBonePositionFrames();
            
            if(positionFrames->count() > 0)
                beginFrame = (GHSkeletalAnimationFrame*)positionFrames->objectAtIndex(0);
            
            
            float beginTime = 0;
            float endTime = transitionTime->getValue();
            
            float framesTimeDistance = endTime - beginTime;
            float timeUnit = (time-beginTime)/framesTimeDistance; //a value between 0 and 1
                        
            CCDictionary* beginBonesInfo = beginFrame->getBonePositions();
            
            if(NULL == beginBonesInfo)
                return;
                        
            CCObject* pBoneObj = NULL;
            CCARRAY_FOREACH(allBones, pBoneObj)
            {
                GHBone* bone = (GHBone*)pBoneObj;

                GHPoint* beginValue = (GHPoint*)beginBonesInfo->objectForKey(bone->getName());
                
                CCPoint beginPosition = bone->getPreviousPosition();
                CCPoint endPosition = bone->getPosition();
                
                if(beginValue){
                    endPosition = beginValue->getPoint();
                }
                
                //lets calculate the position of the bone based on the start - end and unit time
                float newX = beginPosition.x + (endPosition.x - beginPosition.x)*timeUnit;
                float newY = beginPosition.y + (endPosition.y - beginPosition.y)*timeUnit;
                
                CCPoint newPos = ccp(newX, newY);
                bone->setPosition(newPos);
                this->transformSkins();
            }
            rootBone->updateMovement();
        }
        else if(beginFrame && endFrame){
            
            float beginTime = beginFrame->getTime();
            float endTime   = endFrame->getTime();

            float framesTimeDistance = endTime - beginTime;
            float timeUnit = (time-beginTime)/framesTimeDistance; //a value between 0 and 1

            CCDictionary* beginBonesInfo  = beginFrame->getBonePositions();
            CCDictionary* endBonesInfo    = endFrame->getBonePositions();

            if(NULL == beginBonesInfo || endBonesInfo == NULL)
                return;
            
            CCObject* pBoneObj = NULL;
            CCARRAY_FOREACH(allBones, pBoneObj)
            {
                GHBone* bone = (GHBone*)pBoneObj;
                
                GHPoint* beginValue = (GHPoint*)beginBonesInfo->objectForKey(bone->getName());
                GHPoint* endValue   = (GHPoint*)endBonesInfo->objectForKey(bone->getName());
                
                
                CCPoint beginPosition   = bone->getPosition();
                CCPoint endPosition     = bone->getPosition();
                
                if(beginValue){
                    beginPosition = beginValue->getPoint();
                }
                
                if(endValue){
                    endPosition = endValue->getPoint();
                }
                
                //lets calculate the position of the bone based on the start - end and unit time
                
                float newX = beginPosition.x + (endPosition.x - beginPosition.x)*timeUnit;
                float newY = beginPosition.y + (endPosition.y - beginPosition.y)*timeUnit;
                
                CCPoint newPos = ccp(newX, newY);
                bone->setPosition(newPos);
            }
            rootBone->updateMovement();
        }
        else if(beginFrame)
        {
            CCDictionary* beginBonesInfo = beginFrame->getBonePositions();
            
            CCObject* pBoneObj = NULL;
            CCARRAY_FOREACH(allBones, pBoneObj)
            {
                GHBone* bone = (GHBone*)pBoneObj;

                GHPoint* beginValue = (GHPoint*)beginBonesInfo->objectForKey(bone->getName());

                CCPoint beginPosition = bone->getPosition();
                if(beginValue){
                    beginPosition = beginValue->getPoint();
                }
                bone->setPosition(beginPosition);
            }
            rootBone->updateMovement();
        }
    }
    
    if(transitionTime){
        time = 0;
    }
    
    {//handle sprites z order
        
        GHSkeletalAnimationFrame* beginFrame = NULL;
        
        //for loop in reverse and break when you find the first frame
        //TODO optimize code here
        
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(animation->getSpriteZOrderFrames(), pObj)
        {
            GHSkeletalAnimationFrame* frm = (GHSkeletalAnimationFrame*)pObj;
            if(frm->getTime() <= time){
                beginFrame = frm;
            }
        }
        
        //we have the last frame with smaller time
        if(beginFrame){
            
            CCDictionary* zOrderInfo = beginFrame->getSpritesZOrder();
            
            CCObject* pSprObj = NULL;
            CCARRAY_FOREACH(batchNode_->getChildren(), pSprObj)
            {
                GHSprite* sprite = (GHSprite*)pSprObj;
                
                std::string sprName = sprite->getName();
                if(sprName != ""){
                    
                    CCString* zNum = (CCString*)zOrderInfo->objectForKey(sprName);
                    if(zNum)
                    {
                        batchNode_->reorderChild(sprite, zNum->intValue());
                    }
                }
            }
        }
    }
    
    
         
    {//handle skin connections        
        GHSkeletalAnimationFrame* beginFrame = NULL;
        
        CCObject* pSkinFrmObj = NULL;
        CCARRAY_FOREACH(animation->getSkinConnectionFrames(), pSkinFrmObj)
        {
            GHSkeletalAnimationFrame* frm = (GHSkeletalAnimationFrame*)pSkinFrmObj;
         
            if(frm->getTime() <= time){
                beginFrame = frm;
            }
        }
        
        //we have the last frame with smaller time
        if(beginFrame){
            
            CCDictionary* connections = beginFrame->getSkinConnections();
            
            
            CCObject* pSkinObj = NULL;
            CCARRAY_FOREACH(skins, pSkinObj)
            {
                GHBoneSkin* skin = (GHBoneSkin*)pSkinObj;
                
                GHSprite* sprite = skin->getSprite();
                if(sprite){
                    std::string sprName = sprite->getName();
                    if(sprName != ""){
                        GHSkeletalSkinConnectionInfo* connectionInfo = (GHSkeletalSkinConnectionInfo*)connections->objectForKey(sprName);
                        
                        if(connectionInfo)
                        {
                            std::string boneName = connectionInfo->getBoneName();
                                                        
                            skin->setAngleOffset(connectionInfo->getAngleOffset());
                            skin->setPositionOffset(connectionInfo->getPositionOffset());
                            skin->setConnectionAngle(connectionInfo->getConnectionAngle());
                         
                            
                            if(boneName == "")//we may not have a bone
                            {
                                skin->setBone(NULL);
                            }
                            else{
                                
                                CCObject* pBoneObj = NULL;
                                CCARRAY_FOREACH(allBones, pBoneObj)
                                {
                                    GHBone* bone = (GHBone*)pBoneObj;

                                    if(bone->getName() == boneName){
                                        skin->setBone(bone);
                                        break;//exit for loop
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
        
   

    
    {//handle skin sprites
        GHSkeletalAnimationFrame* beginFrame = NULL;
        
        CCObject* pFrmObj = NULL;
        CCARRAY_FOREACH(animation->getSkinSpriteFrames(), pFrmObj)
        {
            GHSkeletalAnimationFrame* frm = (GHSkeletalAnimationFrame*)pFrmObj;
         
            if(frm->getTime() <= time){
                beginFrame = frm;
            }
        }
        
        //we have the last frame with smaller time
        if(beginFrame){
            CCDictionary* info = beginFrame->getSkinSprites();
            if(info){
                
                CCObject* pSkinObj = NULL;
                CCARRAY_FOREACH(skins, pSkinObj)
                {
                    GHBoneSkin* skin = (GHBoneSkin*)pSkinObj;
                    
                    CCString* newSprFrameName = (CCString*)info->objectForKey(skin->getName());
                    if(newSprFrameName){
                        
                        CCSpriteFrame* frame =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(newSprFrameName->getCString());
                        if(frame){
                            skin->getSprite()->setDisplayFrame(frame);
                        }
                    }
                }
            }
        }
    }
    
  
    {//handle sprites visibility

        GHSkeletalAnimationFrame* beginFrame = NULL;
        
        
        CCObject* pFrmObj = NULL;
        CCARRAY_FOREACH(animation->getVisibilityFrames(), pFrmObj)
        {
            GHSkeletalAnimationFrame* frm = (GHSkeletalAnimationFrame*)pFrmObj;
            if(frm->getTime() <= time){
                beginFrame = frm;
            }
        }
        
        //we have the last frame with smaller time
        if(beginFrame){
            CCDictionary* info = beginFrame->getSpritesVisibility();
            
            if(info){
                
                CCObject* pSprObj = NULL;
                CCARRAY_FOREACH(batchNode_->getChildren(), pSprObj)
                {
                    GHSprite* sprite = (GHSprite*)pSprObj;

                    std::string sprFrmName = sprite->getName();
                    
                    if(sprFrmName != ""){
                        CCString* val = (CCString*)info->objectForKey(sprFrmName);
                        if(val){
                            sprite->setVisible(val->boolValue());
                        }
                    }
                }
            }
        }
    }
    
    
    
    { //handle sprites transform
        GHSkeletalAnimationFrame* beginFrame = NULL;
        GHSkeletalAnimationFrame* endFrame = NULL;
        
        CCObject* pFrmObj = NULL;
        CCARRAY_FOREACH(animation->getSpritesTransformFrames(), pFrmObj)
        {
            GHSkeletalAnimationFrame* frm = (GHSkeletalAnimationFrame*)pFrmObj;
            if(frm->getTime() <= time){
                beginFrame = frm;
            }
            
            if(frm->getTime() > time){
                endFrame = frm;
                break;//exit for
            }
        }
                
        if(beginFrame && endFrame){
            
            float beginTime = beginFrame->getTime();
            float endTime   = endFrame->getTime();
            
            float framesTimeDistance = endTime - beginTime;
            float timeUnit = (time-beginTime)/framesTimeDistance; //a value between 0 and 1
            
            CCDictionary* beginFrameInfo = beginFrame->getSpritesTransform();
            CCDictionary* endFrameInfo   = endFrame->getSpritesTransform();
             
            if(beginFrameInfo == NULL || endFrameInfo == NULL)
                return;
            
            
            CCObject* pSkinObj = NULL;
            CCARRAY_FOREACH(skins, pSkinObj)
            {
                GHBoneSkin* skin = (GHBoneSkin*)pSkinObj;
                
                GHSkeletalSkinConnectionInfo* beginInfo = (GHSkeletalSkinConnectionInfo*)beginFrameInfo->objectForKey(skin->getName());
                GHSkeletalSkinConnectionInfo* endInfo   = (GHSkeletalSkinConnectionInfo*)endFrameInfo->objectForKey(skin->getName());
            
                if(skin->getSprite() && beginInfo && endInfo)
                {
                
                    //set position
                    CCPoint beginPos    = beginInfo->getPosition();
                    CCPoint endPos      = endInfo->getPosition();
                    float newX = beginPos.x + (endPos.x - beginPos.x)*timeUnit;
                    float newY = beginPos.y + (endPos.y - beginPos.y)*timeUnit;
                    
                    skin->getSprite()->setPosition(ccp(newX, newY));

                    //set angle
                    float beginAngle = beginInfo->getAngle();
                    float endAngle   = endInfo->getAngle();
                    float newAngle   = beginAngle + (endAngle - beginAngle)*timeUnit;
                    skin->getSprite()->setRotation(newAngle);
                    
                    //set angle at skin time
                    float beginSkinAngle= beginInfo->getConnectionAngle();
                    float endSkinAngle  = endInfo->getConnectionAngle();
                    float newSkinAngle  = beginSkinAngle + (endSkinAngle - beginSkinAngle)*timeUnit;
                    skin->setConnectionAngle(newSkinAngle);

                    
                    {
                        //set skin angle
                        float beginAngle= beginInfo->getAngleOffset();
                        float endAngle  = endInfo->getAngleOffset();
                        float newAngle  = beginAngle + (endAngle - beginAngle)*timeUnit;
                        skin->setAngleOffset(newAngle);
                        
                        //set skin position offset
                        CCPoint beginPosOff = beginInfo->getPositionOffset();
                        CCPoint endPosOff   = endInfo->getPositionOffset();
                        
                        float newX = beginPosOff.x + (endPosOff.x - beginPosOff.x)*timeUnit;
                        float newY = beginPosOff.y + (endPosOff.y - beginPosOff.y)*timeUnit;
                        skin->setPositionOffset(ccp(newX, newY));
                    }
                }
            }
        }
    }
        

    this->transformSkins();
    
    currentTranstionTime += dt;
}




void GHSkeleton::updateSkins(){
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(skins, pObj)
    {
        GHBoneSkin* skin = (GHBoneSkin*)pObj;
        skin->setupTransformations();
    }
}

void GHSkeleton::transformSkins()
{
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(skins, pObj)
    {
        GHBoneSkin* skin = (GHBoneSkin*)pObj;
        skin->transform();
    }
}


#if GH_DEBUG

void GHSkeleton::initShader()
{
	m_pShaderProgram = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_Position_uColor);
	colorLocation_ = glGetUniformLocation( m_pShaderProgram->getProgram(), "u_color");
}

void GHSkeleton::debugDrawBone(GHBone* bone)
{
    if(bone->getRigid()){
        m_pShaderProgram->setUniformLocationWith4f(colorLocation_, 0, 0, 1, 1);
    }
    else{
        m_pShaderProgram->setUniformLocationWith4f(colorLocation_, 0, 1, 0, 1);
    }
    
    CCArray* boneChildren = bone->getChildren();
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(boneChildren, pObj)
    {
        GHBone* child = (GHBone*)pObj;
        if(child)
        {
            GLfloat	vertices[] = {
                bone->getPosition().x, bone->getPosition().y,
                child->getPosition().x, child->getPosition().y
            };
                        
            
            glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
            
            glDrawArrays(GL_LINES, 0, 2);
            this->debugDrawBone(child);
        }
    }
}

void GHSkeleton::draw(){
    if(!m_pShaderProgram)return;
    
    m_pShaderProgram->use();
    m_pShaderProgram->setUniformsForBuiltins();
    
    
    this->debugDrawBone(rootBone);
    
    CC_INCREMENT_GL_DRAWS(1);
	CHECK_GL_ERROR_DEBUG();
}

#endif

