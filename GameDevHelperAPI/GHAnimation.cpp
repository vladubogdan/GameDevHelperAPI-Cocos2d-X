//
//  GHAnimation.m
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 5/9/13.
//
//

#include "GHAnimation.h"
#include "GHSprite.h"

GHAnimationFrame::GHAnimationFrame():
m_spriteFrame(NULL),
m_time(0),
m_userInfo(NULL)
{
    
}

GHAnimationFrame::~GHAnimationFrame()
{
    if(m_spriteFrame){
        m_spriteFrame->release();
        m_spriteFrame = NULL;
    }
    
    if(m_userInfo){
        m_userInfo->release();
        m_userInfo = NULL;
    }
}

GHAnimationFrame* GHAnimationFrame::createWithDictionary(CCDictionary* dict)
{
    GHAnimationFrame *pobNode = new GHAnimationFrame();
	if (pobNode && pobNode->initWithDictionary(dict))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
}
bool GHAnimationFrame::initWithDictionary(CCDictionary* dict)
{
    if(NULL == dict)return false;
    
    CCDictionary* notifsInfo = (CCDictionary*)dict->objectForKey("notification");
    //        CGPoint point = [dict objectForKey:@"offset"];//currently not used
    
    CCString* spriteFrameName = (CCString*)dict->objectForKey("spriteframe");
    if(spriteFrameName)
    {
        m_spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName->getCString());
        
#if COCOS2D_DEBUG > 0
        char msg[256] = {0};
        sprintf(msg, "SpriteFrame %s was not found. Use CCSpriteFrameCache to load spriteFrames before loading an animation.", spriteFrameName->getCString());
        CCAssert(m_spriteFrame != NULL, msg);
#endif
        m_spriteFrame->retain();
    }
    
    if(notifsInfo != NULL && notifsInfo->allKeys() && notifsInfo->allKeys()->count() > 0)
    {
        m_userInfo = CCDictionary::createWithDictionary(notifsInfo);
        m_userInfo->retain();
    }

    return true;
}

GHAnimationFrame* GHAnimationFrame::createWithAnimationFrame(GHAnimationFrame* frame){

    GHAnimationFrame *pobNode = new GHAnimationFrame();
	if (pobNode && pobNode->initWithAnimationFrame(frame))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
}

bool GHAnimationFrame::initWithAnimationFrame(GHAnimationFrame* frame){
    
    if(frame == NULL)return false;
    
    this->setSpriteFrame(frame->getSpriteFrame());
    this->setTime(frame->getTime());
    if(m_userInfo){m_userInfo->release(); m_userInfo = NULL;}
    if(frame->getUserInfo())
    {
        m_userInfo = CCDictionary::createWithDictionary(frame->getUserInfo());
        m_userInfo->retain();
    }
    
    return true;
}



float GHAnimationFrame::getTime()
{
    return m_time;
}
void GHAnimationFrame::setTime(float val)
{
    m_time = val;
}


CCSpriteFrame* GHAnimationFrame::getSpriteFrame()
{
    return m_spriteFrame;
}
void GHAnimationFrame::setSpriteFrame(CCSpriteFrame* val)
{
    if(!val)return;
    if(m_spriteFrame){
        m_spriteFrame->release(); m_spriteFrame = NULL;
    }
    
    m_spriteFrame = val;
    m_spriteFrame->retain();
}

CCDictionary* GHAnimationFrame::getUserInfo()
{
    return m_userInfo;
}






GHAnimation::GHAnimation():
name(""),
frames(NULL),
repetitions(0),
loop(false),
randomFrames(false),
restoreSprite(false),
randomReplay(false),
minRandomTime(0),
maxRandomTime(0),
totalTime(0.2f),
playing(false),
currentTime(0),
currentFrameIdx(0),
currentRandomRepeatTime(0),
repetitionsPerformed(0),
activeFrame(NULL),
delegate(NULL),
sprite(NULL)
{
    frames = CCArray::createWithCapacity(10);
    frames->retain();
}
GHAnimation::~GHAnimation()
{
    delegate = NULL;
    activeFrame = NULL;
    sprite = NULL;
    
    frames->release();
    frames = NULL;
}


void GHAnimation::setSprite(GHSprite * spr)
{
    sprite = spr;
}

GHAnimation* GHAnimation::createWithDictionary(CCDictionary* dict, const char* animName)
{
    GHAnimation *pobNode = new GHAnimation();
	if (pobNode && pobNode->initWithDictionary(dict, animName))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
}

bool GHAnimation::initWithDictionary(CCDictionary* dict, const char* animName)
{
    if(dict == NULL)return false;
    
    name = std::string(animName);

    float delayPerUnit = dict->valueForKey("delayPerUnit")->floatValue();
    
    loop = dict->valueForKey("loop")->boolValue();
    
    randomFrames = dict->valueForKey("randomFrames")->boolValue();
    repetitions = dict->valueForKey("loops")->intValue();
    
    maxRandomTime = dict->valueForKey("maxRandomTime")->floatValue();
    minRandomTime = dict->valueForKey("minRandomTime")->floatValue();
    randomReplay  = dict->valueForKey("randomReplay")->boolValue();
    
    restoreSprite = dict->valueForKey("restoreOriginalFrame")->boolValue();
    
    CCArray* framesInfo = (CCArray*)dict->objectForKey("frames");
    
    totalTime = 0;
    
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(framesInfo, pObj)
    {
        CCDictionary* frmInfo = (CCDictionary*)pObj;
        if(frmInfo){
            float delay = frmInfo->valueForKey("delayUnits")->floatValue();
            
            float frameTime = delay*delayPerUnit;
            totalTime += frameTime;
            
            GHAnimationFrame* newFrm = GHAnimationFrame::createWithDictionary(frmInfo);
            if(newFrm){
                frames->addObject(newFrm);
                newFrm->setTime(frameTime);
            }
        }
    }
    
    return true;
}


GHAnimation* GHAnimation::createWithAnimation(GHAnimation* anim)
{
    GHAnimation *pobNode = new GHAnimation();
	if (pobNode && pobNode->initWithAnimation(anim))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
}

bool GHAnimation::initWithAnimation(GHAnimation* anim)
{
    if(anim == NULL)return false;
    
    this->setRepetitions(anim->getRepetitions());
    this->setLoop(anim->getLoop());
    this->setRandomFrames(anim->getRandomFrames());
    this->setRestoreSprite(anim->getRestoreSprite());
    this->setRandomReplay(anim->getRandomReplay());
    this->setMinRandomTime(anim->getMinRandomTime());
    this->setMaxRandomTime(anim->getMaxRandomTime());
    this->setTotalTime(anim->getTotalTime());

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(anim->getFrames(), pObj)
    {
        GHAnimationFrame* frame = (GHAnimationFrame*)pObj;

        if(frame){
            GHAnimationFrame* newFrame = GHAnimationFrame::createWithAnimationFrame(frame);
            if(newFrame){
                this->frames->addObject(newFrame);
            }
        }
    }
    return true;
}

void GHAnimation::setTotalTime(float val)
{
    float newTime = val;
    if(newTime < 0.1)
        newTime = 0.1f;
        
    float currentTotalTime = totalTime;
    totalTime = 0;

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(frames, pObj)
    {
        GHAnimationFrame* frame = (GHAnimationFrame*)pObj;
        float frameUnit = frame->getTime()/currentTotalTime;
        //gives a value between 0 and 1 for the frame time
        //multiplying this unit value with the new total time gives the new frame time
        float newFrameTime = frameUnit*newTime;
        totalTime += newFrameTime;
        frame->setTime(newFrameTime);
    }
}


float GHAnimation::calculatedRandomReplayTime()
{
    float diff = maxRandomTime - minRandomTime;
	//srand ( time(NULL) );
    return (((float) (rand() % ((unsigned)RAND_MAX + 1)) / RAND_MAX) * diff) + minRandomTime;
}


int GHAnimation::randomFrame()
{
    int from = 0;
    int to = frames->count();
    int diff = to - from;
    return rand()%(diff)+from;
}

void GHAnimation::update(float dt)
{
    if(!playing)
        return;
    
    currentTime += dt;
    
    bool endedAllRep = false;
    bool endedRep = false;
    if(activeFrame && activeFrame->getTime() <= currentTime)
    {
        bool resetCurrentTime = true;
        int nextFrame = currentFrameIdx+1;

        if(randomFrames){
            nextFrame = this->randomFrame();;
            
            while (nextFrame == currentFrameIdx) {
                nextFrame = this->randomFrame();
                //in case the random number returns the same frame
            }
        }
        
        if(nextFrame >= frames->count()){
            
            if(loop){
                if(false == randomReplay ||
                   (activeFrame->getTime() + currentRandomRepeatTime <= currentTime))
                {
                    nextFrame = 0;
                    currentRandomRepeatTime = this->calculatedRandomReplayTime();
                    ++repetitionsPerformed;
                    endedRep = true;
                }
                else{
                    nextFrame = 0;//frames->count() - 1;
                    resetCurrentTime = false;
                }
            }
            else
            {
                ++repetitionsPerformed;
                if(repetitionsPerformed >= repetitions)
                {
                    nextFrame = frames->count() -1;
                    endedAllRep = true;
                    playing = false;
                }
                else {
                    if(restoreSprite || repetitionsPerformed < repetitions)
                    {
                        nextFrame = 0;
                        endedRep = true;
                    }
                    else {
                        nextFrame = frames->count() -1;
                    }
                }
            }
        }
        if(resetCurrentTime)
            currentTime = 0.0f;
        
        this->setActiveFrameWithIndex(nextFrame);
    }
    
    if(endedAllRep){
        playing = false;
    }
    if(delegate)
    {
        if(endedRep){
            
            if(delegate)
            {
                delegate->animationDidFinishRepetitionOnSprite(this, repetitionsPerformed, sprite);
            }
        }
        
        if(endedAllRep){
            
            if(delegate)
            {
                delegate->animationDidFinishPlayingOnSprite(this, sprite);
            }
        }
    }
}

void GHAnimation::setActiveFrameWithIndex(int frmIdx)
{
    if(frmIdx < 0){
        frmIdx = 0;
    }
    if(frmIdx >= frames->count()){
        frmIdx = frames->count() - 1;
    }
    
    if(frmIdx == currentFrameIdx && activeFrame != NULL)
        return;
    
    if(frmIdx >= 0 && frmIdx < frames->count()){
        currentFrameIdx = frmIdx;
        activeFrame = (GHAnimationFrame*)frames->objectAtIndex(currentFrameIdx);
        sprite->setDisplayFrame(activeFrame->getSpriteFrame());
        
        if(delegate)
        {
            delegate->animationDidChangeFrameIdxOnSprite(this, currentFrameIdx, sprite);
        }
        
    }
}

void GHAnimation::setRandomReplay(bool val)
{
    randomReplay = val;
    currentRandomRepeatTime = 0;
}

void GHAnimation::prepare()
{
    CCAssert(sprite != NULL, "Animation is not assigned on a sprite. Use [sprite setAnimation:anim] before calling \"prepare\".");

    sprite->unscheduleUpdate();
    sprite->scheduleUpdate();
    
    currentRandomRepeatTime = 0;
    if(randomReplay){
        currentRandomRepeatTime = this->calculatedRandomReplayTime();
    }
    
    playing = false;
    repetitionsPerformed = 0;
    if(activeFrame == NULL || currentFrameIdx == frames->count() - 1){
        this->moveToFirstFrame();
    }
}

void GHAnimation::setActiveFrame(GHAnimationFrame* frm)
{
    int frmIdx = frames->indexOfObject(frm);
    if(frm)
    {
        activeFrame = frm;
        currentFrameIdx = (int)frmIdx;
    }
}

