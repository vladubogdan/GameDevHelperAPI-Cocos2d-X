//
//  GHPoint.cpp
//  SpriteHelper2-TestCases
//
//  Created by Bogdan Vladu on 5/23/13.
//
//

#include "GHPoint.h"


GHPoint* GHPoint::createWithValues(float x, float y){
    
    GHPoint *pobNode = new GHPoint();
	if (pobNode && pobNode->initWithValues(x, y))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
    
}
bool GHPoint::initWithValues(float x, float y){
    setPoint(x, y);
    return true;
}



GHPoint* GHPoint::createWithPoint(GHPoint* pt){
    
    GHPoint *pobNode = new GHPoint();
	if (pobNode && pobNode->initWithPoint(pt))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
    
}
bool GHPoint::initWithPoint(GHPoint* pt){
    setPoint(pt->x, pt->y);
    return true;
}



GHPoint::GHPoint(void)
{
    setPoint(0.0f, 0.0f);
}

GHPoint::~GHPoint(){
    
}

GHPoint::GHPoint(float x, float y)
{
    setPoint(x, y);
}

GHPoint::GHPoint(const GHPoint& other)
{
    setPoint(other.x, other.y);
}

GHPoint::GHPoint(const CCPoint& other){
    setPoint(other.x, other.y);
}

GHPoint& GHPoint::operator= (const GHPoint& other)
{
    setPoint(other.x, other.y);
    return *this;
}

void GHPoint::setPoint(float x, float y)
{
    this->x = x;
    this->y = y;
}

CCObject* GHPoint::copyWithZone(CCZone* pZone)
{
    GHPoint* pRet = new GHPoint();
    pRet->setPoint(this->x, this->y);
    return pRet;
}
