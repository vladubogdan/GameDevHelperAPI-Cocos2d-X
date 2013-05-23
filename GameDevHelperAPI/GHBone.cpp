//
//  GHBone.cpp
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 4/4/13.
//
//

#include "GHBone.h"

GHBone::GHBone():
m_rigid(false),
m_name(""),
m_uuid(""),
neighbours(NULL),
neighboursDistances(NULL)
{
    
}
GHBone::~GHBone(){

    if(neighbours){
        neighbours->release();
        neighbours = NULL;
    }

    if(neighboursDistances){
        neighboursDistances->release();
        neighboursDistances = NULL;
    }
}


GHBone* GHBone::createBoneWithDictionary(CCDictionary* info)
{
    GHBone *pobNode = new GHBone();
	if (pobNode && pobNode->initWithDictionary(info))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
}

bool GHBone::initWithDictionary(CCDictionary* info)
{
    if(info == NULL)return false;
    
    neighbours = NULL;
    neighboursDistances = NULL;
    
    m_rigid = info->valueForKey("rigid")->boolValue();
    
    CCPoint localPos = ccp(0,0);

    CCString* bonePos = (CCString*)info->objectForKey("localPos"); //this position is local from the root bone
    if(bonePos){
        localPos = CCPointFromString(bonePos->getCString());
    }
    localPos.x /= CC_CONTENT_SCALE_FACTOR();
    localPos.y /= CC_CONTENT_SCALE_FACTOR();
    
    CCString* boneName = (CCString*)info->objectForKey("name");
    if(boneName){
        m_name = std::string(boneName->getCString());
    }
    else{
        m_name = std::string("UntitledBone");
    }
    
    CCString* boneUUID = (CCString*)info->objectForKey("uuid");
    if(boneUUID){
        m_uuid = std::string(boneUUID->getCString());
    }
    else{
        m_uuid = std::string("ERROR_NO_UUID_FOUND");
    }
    
    this->setPosition(localPos);
    
    
    CCArray* childrenInfo = (CCArray*)info->objectForKey("children");

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(childrenInfo, pObj)
    {
        CCDictionary* childInfo = (CCDictionary*)pObj;

        GHBone* childBone = GHBone::createBoneWithDictionary(childInfo);
        if(childBone){
            this->addChild(childBone);
        }
    }
    
    return true;
}


void GHBone::addNeighbor(GHBone* neighbor)
{
    if(neighbours == NULL){
        neighbours = CCArray::create();
        neighbours->retain();
        neighboursDistances = CCArray::create();
        neighboursDistances->retain();
    }
    
    neighbours->addObject(neighbor);
    this->calculateDistancesFromNeighbours();
}

void GHBone::removeNeighbor(GHBone* neighbor)
{
    neighbours->removeObject(neighbor);
}

// Calculates the distance from neighbours
void GHBone::calculateDistancesFromNeighbours()
{
    neighboursDistances->removeAllObjects();

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(neighbours, pObj)
    {
        GHBone* node = (GHBone*)pObj;

        float dx = node->getPosition().x - this->getPosition().x;
        float dy = node->getPosition().y - this->getPosition().y;
        neighboursDistances->addObject(CCFloat::create(sqrtf(dx*dx+dy*dy)));
    }
};

void GHBone::addChild(GHBone* child)
{
    this->addNeighbor(child);
    CCNode::addChild(child);
    this->calculateDistancesFromNeighbours();
    child->addNeighbor(this);
}

CCArray* GHBone::getAllBones(){
    
    CCArray* array = CCArray::create();
    
    array->addObject(this);
    
    CCArray* boneChildren = this->getChildren();
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(boneChildren, pObj)
    {
        GHBone* bone = (GHBone*)pObj;
        array->addObjectsFromArray(bone->getAllBones());
    }
    return array;
}

GHBone* GHBone::getBoneWithName(const char* val){

    if(m_name == std::string(val))
    {
        return this;
    }
    
    CCArray* boneChildren = this->getChildren();
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(boneChildren, pObj)
    {
        GHBone* bone = (GHBone*)pObj;

        GHBone* retBone = bone->getBoneWithName(val);
        if(retBone){
            return retBone;
        }
    }
    
    return NULL;
}

void GHBone::setBonePosition(CCPoint pos, GHBone* father)
{
    this->setPosition(pos);
    this->move(father);
}

bool GHBone::isGHBone(CCNode* obj){
    
    if( 0 != dynamic_cast<GHBone*>(obj))
        return true;
    
    return false;
}

float GHBone::degrees()//return the angle between bone and parent
{
    GHBone* _father = (GHBone*)this->getParent();
    if(_father && GHBone::isGHBone(_father))
    {
        CCPoint curPoint = ccp(((GHBone*)_father)->getPosition().x,
                               ((GHBone*)_father)->getPosition().y);
        CCPoint endPoint = ccp(this->getPosition().x,
                               this->getPosition().y);
        
        //we inverse y points here because of cocos2d flip coordinates
        return  (atan2(curPoint.y - endPoint.y,
                       endPoint.x - curPoint.x)*180.0)/M_PI + 90;
    }
    
    return 0;
}


void GHBone::move(GHBone* father)
{
    for(int i = 0; i < neighbours->count(); ++i)
    {
        GHBone* node = (GHBone*)neighbours->objectAtIndex(i);
        if(node != father)
        {
            node->makeMove(this, node, ((CCFloat*)neighboursDistances->objectAtIndex(i))->getValue());
            
            node->move(this);
        }
    }
}

void GHBone::makeMove(GHBone* parent, GHBone* child, float dist)
{
    if(child && child->getRigid())
    {
        //do nothing
    }
    else if(parent)
    {
        float dx = this->getPosition().x - parent->getPosition().x;
        float dy = this->getPosition().y - parent->getPosition().y;
        float angle = atan2f(dy, dx);

        this->setPosition(ccp(parent->getPosition().x + cos(angle)*dist,
                              parent->getPosition().y + sin(angle)*dist));
    }
}

void GHBone::savePosition(){
    previousPosition = this->getPosition();
}
CCPoint GHBone::getPreviousPosition(){
    return previousPosition;
}

