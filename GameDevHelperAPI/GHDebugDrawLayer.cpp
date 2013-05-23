//
//  GHDebugDraw.m
//  cocos2d-ios
//
//  Created by Bogdan Vladu on 4/29/13.
//
//

#include "GHDebugDrawLayer.h"
#include "GHDirector.h"
#include "ghMacros.h"
#include "GHSprite.h"

#if GH_ENABLE_PHYSICS_INTEGRATION


GHDebugDrawLayer* GHDebugDrawLayer::createDebugDrawLayerWithWorld(b2World* world)
{
    GHDebugDrawLayer *pobNode = new GHDebugDrawLayer();
	if (pobNode && pobNode->initDebugDrawLayerWithWorld(world))
    {
	    pobNode->autorelease();
        return pobNode;
    }
    CC_SAFE_DELETE(pobNode);
	return NULL;
}

bool GHDebugDrawLayer::initDebugDrawLayerWithWorld(b2World* world)
{
    if(world == NULL)return false;
    
    m_world = world;
    mShaderProgram = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_Position_uColor);
    mColorLocation = glGetUniformLocation( mShaderProgram->getProgram(), "u_color");
        
    return true;
}

void GHDebugDrawLayer::draw()
{
	
#ifdef GH_DEBUG
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	
    //Iterate over the bodies in the physics world
    for (b2Body* body = m_world->GetBodyList(); body; body = body->GetNext())
    {
        GHDebugDrawLayer::DebugDrawBody(body, mShaderProgram ,mColorLocation);
    }
    
	kmGLPopMatrix();
#endif
}



void GHDebugDrawLayer::DebugDrawBody(b2Body* body, CCGLProgram* shaderProgram, GLint colorLocation)
{
    const b2Transform& xf = body->GetTransform();
    for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
    {
        b2Color color = b2Color(0.5f, 0.5f, 0.3f);
        
        if (body->IsActive() == false)
        {
            color = b2Color(0.5f, 0.5f, 0.3f);
        }
        else if (body->GetType() == b2_staticBody)
        {
            color = b2Color(0.5f, 0.9f, 0.5f);
        }
        else if (body->GetType() == b2_kinematicBody)
        {
            color =  b2Color(0.5f, 0.5f, 0.9f);
        }
        else if (body->IsAwake() == false)
        {
            color = b2Color(0.6f, 0.6f, 0.6f);
        }
        else
        {
            color = b2Color(0.9f, 0.7f, 0.7f);
        }
        
        GHDebugDrawLayer::DrawShape(f, body, xf, color, shaderProgram, colorLocation, GH_METER_RATIO());
    }
}

void GHDebugDrawLayer::DrawShape(b2Fixture* fixture,
                                 b2Body* body,
                                 const b2Transform& xf,
                                 const b2Color& color, CCGLProgram* shaderProgram, GLint colorLocation,
                                 float ratio)
{    
    switch (fixture->GetType())
    {
        case b2Shape::e_circle:
        {
            b2CircleShape* circle = (b2CircleShape*)fixture->GetShape();

            b2Vec2 center = b2Mul(xf, -circle->m_p);

            float32 radius = circle->m_radius;
            b2Vec2 axis = b2Mul(xf.q, b2Vec2(1.0f, 0.0f));
            
            GHDebugDrawLayer::DrawSolidCircleWithCenter(center,
                                                        radius,
                                                        axis,
                                                        color,
                                                        shaderProgram,
                                                        colorLocation,
                                                        ratio);

        }
            break;
            
        case b2Shape::e_edge:
        {
            b2EdgeShape* edge = (b2EdgeShape*)fixture->GetShape();
            b2Vec2 v1 = b2Mul(xf, edge->m_vertex1);
            b2Vec2 v2 = b2Mul(xf, edge->m_vertex2);
            
            
            GHDebugDrawLayer::DrawSegmentWithPoint1(v1,
                                                    v2,
                                                    color,
                                                    shaderProgram,
                                                    colorLocation,
                                                    ratio);

        }
            break;
            
        case b2Shape::e_chain:
        {
            b2ChainShape* chain = (b2ChainShape*)fixture->GetShape();
            int32 count = chain->m_count;
            const b2Vec2* vertices = chain->m_vertices;
            
            b2Vec2 v1 = b2Mul(xf, vertices[0]);

            for (int32 i = 1; i < count; ++i)
            {
                b2Vec2 v2 = b2Mul(xf, vertices[i]);

                GHDebugDrawLayer::DrawSegmentWithPoint1(v1,
                                                        v2,
                                                        color,
                                                        shaderProgram,
                                                        colorLocation,
                                                        ratio);

                GHDebugDrawLayer::DrawCircleWithCenter(v1,
                                                       0.05f,
                                                       color,
                                                       shaderProgram,
                                                       colorLocation,
                                                       ratio);

                v1 = v2;
            }
        }
            break;
            
        case b2Shape::e_polygon:
        {
            b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
            int32 vertexCount = poly->m_vertexCount;
            b2Assert(vertexCount <= b2_maxPolygonVertices);
            b2Vec2 vertices[b2_maxPolygonVertices];
            
            for (int32 i = 0; i < vertexCount; ++i)
            {
                vertices[i] = b2Mul(xf, poly->m_vertices[i]);

            }
            GHDebugDrawLayer::DrawSolidPolygonWithVertices(vertices,
                                                           vertexCount,
                                                           color,
                                                           shaderProgram,
                                                           colorLocation,
                                                           ratio);
        }
            break;
            
        default:
            break;
    }
}


void GHDebugDrawLayer::DrawSolidPolygonWithVertices(const b2Vec2* old_vertices,
                                                    int32 vertexCount,
                                                    const b2Color& color,
                                                    CCGLProgram* mShaderProgram,
                                                    GLint mColorLocation,
                                                    float mRatio)
{
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();

    ccVertex2F vertices[vertexCount];
    
	for( int i=0;i<vertexCount;i++) {
		b2Vec2 tmp = old_vertices[i];
		tmp = old_vertices[i];
		tmp *= mRatio;
		vertices[i].x = tmp.x;
		vertices[i].y = tmp.y;
	}
    
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r*0.5f, color.g*0.5f, color.b*0.5f, 0.5f);
    

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
    
	CC_INCREMENT_GL_DRAWS(2);
    
	CHECK_GL_ERROR_DEBUG();
}

void GHDebugDrawLayer::DrawSegmentWithPoint1(const b2Vec2& p1,
                                             const b2Vec2& p2,
                                             const b2Color& color,
                                             CCGLProgram* mShaderProgram,
                                             GLint mColorLocation,
                                             float mRatio)
{
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();

    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
    
	GLfloat				glVertices[] = {
		p1.x * mRatio, p1.y * mRatio,
		p2.x * mRatio, p2.y * mRatio
	};
    
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
    
	glDrawArrays(GL_LINES, 0, 2);
	
	CC_INCREMENT_GL_DRAWS(1);
    
	CHECK_GL_ERROR_DEBUG();
}

void GHDebugDrawLayer::DrawSolidCircleWithCenter(const b2Vec2& center,
                                                 float32 radius,
                                                 const b2Vec2& axis,
                                                 const b2Color& color,
                                                 CCGLProgram* mShaderProgram,
                                                 GLint mColorLocation,
                                                 float mRatio)
{
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();
    
	const float32 k_segments = 16.0f;
	int vertexCount=16;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
    
	GLfloat				glVertices[vertexCount*2];
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertices[i*2]=v.x * mRatio;
		glVertices[i*2+1]=v.y * mRatio;
		theta += k_increment;
	}
    
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r*0.5f, color.g*0.5f, color.b*0.5f, 0.5f);

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
    
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
    
	// Draw the axis line
    
    GHDebugDrawLayer::DrawSegmentWithPoint1(center,
                                            center+radius*axis,
                                            color,
                                            mShaderProgram,
                                            mColorLocation,
                                            mRatio);
        
	CC_INCREMENT_GL_DRAWS(2);
    
	CHECK_GL_ERROR_DEBUG();
}

void GHDebugDrawLayer::DrawCircleWithCenter(const b2Vec2& center,
                                            float32 radius,
                                            const b2Color& color,
                                            CCGLProgram* mShaderProgram,
                                            GLint mColorLocation,
                                            float mRatio)
{
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();
    
	const float32 k_segments = 16.0f;
	int vertexCount=16;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
    
	GLfloat				glVertices[vertexCount*2];
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertices[i*2]=v.x * mRatio;
		glVertices[i*2+1]=v.y * mRatio;
		theta += k_increment;
	}
    
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);
    
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
    
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
    
	CC_INCREMENT_GL_DRAWS(1);
    
	CHECK_GL_ERROR_DEBUG();
}

#endif
