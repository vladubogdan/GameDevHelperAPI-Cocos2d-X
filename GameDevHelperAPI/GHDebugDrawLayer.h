//
//  GHDebugDraw.h
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 4/29/13.
//
//

#import "ghConfig.h"
#import "cocos2d.h"
using namespace cocos2d;

#if GH_ENABLE_PHYSICS_INTEGRATION

#import "Box2D.h"

/**
 A debug layer for when using physics in order to draw the physic representation on screen.
 
 This debug layer is more advanced then the one that comes with Cocos2d as the drawing will be made on top of the sprite instead of behind letting you see whats really going on.
 
 The end user will have to use this class like this:
 @code
 ....after initializing the physic world
 
 
 GHDebugDrawLayer* debugDraw = GHDebugDrawLayer::createDebugDrawLayerWithWorld(world);
 this->addChild(debugDraw, 1000);
 
 
 @endcode
 */
class GHDebugDrawLayer : public CCLayer
{
public:
    
    /**
     Create an autoreleased object given a Box2d world object.
     */
    static GHDebugDrawLayer* createDebugDrawLayerWithWorld(b2World* world);
    
    virtual bool initDebugDrawLayerWithWorld(b2World* world);
    
    virtual void draw();
    
private:
    
    static void DebugDrawBody(b2Body* body, CCGLProgram* shaderProgram, GLint colorLocation);
    
    
    static void DrawShape(b2Fixture* fixture,
                          b2Body* body,
                          const b2Transform& xf,
                          const b2Color& color,
                          CCGLProgram* shaderProgram,
                          GLint colorLocation,
                          float ratio);


    static void DrawSolidPolygonWithVertices(const b2Vec2* old_vertices,
                                             int32 vertexCount,
                                             const b2Color& color,
                                             CCGLProgram* mShaderProgram,
                                             GLint mColorLocation,
                                             float mRatio);

    static void DrawSegmentWithPoint1(const b2Vec2& p1,
                                      const b2Vec2& p2,
                                      const b2Color& color,
                                      CCGLProgram* mShaderProgram,
                                      GLint mColorLocation,
                                      float mRatio);

    static void DrawSolidCircleWithCenter(const b2Vec2& center,
                                          float32 radius,
                                          const b2Vec2& axis,
                                          const b2Color& color,
                                          CCGLProgram* mShaderProgram,
                                          GLint mColorLocation,
                                          float mRatio);

    static void DrawCircleWithCenter(const b2Vec2& center,
                                     float32 radius,
                                     const b2Color& color,
                                     CCGLProgram* mShaderProgram,
                                     GLint mColorLocation,
                                     float mRatio);

    b2World* m_world;
    
    CCGLProgram* mShaderProgram;
    GLint mColorLocation;
};

#endif



