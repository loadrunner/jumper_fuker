#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"

using namespace cocos2d;

#define kMaxHillKeyPoints 1000
#define kHillSegmentWidth 5

#define kMaxHillVertices 4000
#define kMaxBorderVertices 800

#define PTM_RATIO 4

class Terrain : public Node
{
	int _offsetX;
	Vec2 _hillKeyPoints[kMaxHillKeyPoints];
	int _fromKeyPointI;
	int _toKeyPointI;
	
	int _nHillVertices;
	Vec2 _hillVertices[kMaxHillVertices];
	Vec2 _hillTexCoords[kMaxHillVertices];
	
	int _nBorderVertices;
	Vec2 _borderVertices[kMaxBorderVertices];
	
	Size mWindowSize;
	b2World* mWorld;
	b2Body* mBody;
	GLESDebugDraw* _debugDraw;
	
	void generateHills();
	void resetHillVertices();
	void resetBox2DBody();
	void setupDebugDraw();
public:
	void setOffset(float newOffsetX, float offsetY);
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
	bool initWithWorld(b2World *world);
};

#endif
