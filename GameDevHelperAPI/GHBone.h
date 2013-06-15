//
//  GHBone.h
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 4/4/13.
//
//
#ifndef __GAME_DEV_HELPER_BONE_H__
#define __GAME_DEV_HELPER_BONE_H__


#include "cocos2d.h"
#include "ghConfig.h"

using namespace cocos2d;

class GHSprite;
class GHBoneSkin;

/**
 GHBone class is used to define skeleton structures. Each bone is connected to other children bones. 
 
 When a bone is moved each of its children is moved as well in order to simulate skeletons.
 
 End users will probably never have to use this class directly.
 */
class GHBone : public CCNode
{
public:
    
    GHBone();
    virtual ~GHBone();
    
    /**
     Create an autoreleased bone using the options from a dictionary.
     */
    static GHBone* createBoneWithDictionary(CCDictionary* info);

    /**
     Initialize a bone using the options from a dictionary.
     */
    virtual bool initWithDictionary(CCDictionary* info);
    
    /**
     Set the rigid state of this bone.
     */
    inline void setRigid(bool val){m_rigid = val;}
    /**
     Get the rigid state of this bone.
     */
    inline bool getRigid(){return m_rigid;}
    
    /**
     Returns an array which includes self and all children bones.
     */
    CCArray* getAllBones();
    
    /**
     Returns a specific children bone given the name of the bone.
     */
     GHBone* getBoneWithName(const char* val);
    
    /**
     Returns the name of the bone.
     */
    inline std::string getName(){return m_name;}
    
    /**
     Returns the unique identifier of the bone.
     */
    inline std::string getUuid(){return m_uuid;}
    
    /**
     Sets the position of the bone given the bone parent, which may be NULL.
     */
    void setBonePosition(CCPoint pos, GHBone* father);
    
    /**
     Returns the angle between this bone and its parent in degrees.
     */
    float degrees();
    
    /**
     Save the current position to previousPosition. This is called at the begining of a transition.
     */
    void savePosition();
    
    /**
     Returns the previous position.
     */
    CCPoint getPreviousPosition();

    
    virtual void addChild(GHBone* child);
    
    /**
     Checks whether the given object is a GHBone object.
     */
    static bool isGHBone(CCNode* obj);
    
private:
    
    void addNeighbor(GHBone* neighbor);
    void removeNeighbor(GHBone* neighbor);
    void calculateDistancesFromNeighbours();
    void move(GHBone* father);
    void makeMove(GHBone* parent, GHBone* child, float dist);
    
    bool m_rigid;
    std::string m_name;
    std::string m_uuid;
    
    CCArray* neighbours;
    CCArray* neighboursDistances;
    
    CCPoint previousPosition;//used when transitioning
    
    friend class GHSkeleton;
    void updateMovement();
};

#endif //__GAME_DEV_HELPER_BONE_H__
