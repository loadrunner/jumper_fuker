#include "Terrain.h"

void Terrain::setupDebugDraw()
{
	_debugDraw = new GLESDebugDraw(PTM_RATIO);
	mWorld->SetDebugDraw(_debugDraw);
	_debugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
}

bool Terrain::initWithWorld(b2World *world)
{
	float scale = cocos2d::Director::getInstance()->getContentScaleFactor();
	
	mWindowSize = Director::getInstance()->getWinSize();
	_fromKeyPointI = 0;
	_toKeyPointI = 0;
	mWorld = world;
	mBody = NULL;
//	setGLProgram(GLProgramCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE));
	this->setupDebugDraw();
	this->generateHills();
	this->resetHillVertices();
	
	return true;
}

void Terrain::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	mWorld->DrawDebugData();
}

void Terrain::resetBox2DBody()
{
	if (mBody)
	{
		mWorld->DestroyBody(mBody);
	}
	
	b2BodyDef bd;
	bd.position.Set(0, 0);
	mBody = mWorld->CreateBody(&bd);
	
	b2EdgeShape shape;
	
	//float scale = cocos2d::Director::getInstance()->getContentScaleFactor();
	
	b2Vec2 p1, p2;
	for (int i = 0; i < _nBorderVertices - 1; i++)
	{
		p1 = b2Vec2(_borderVertices[i].x / PTM_RATIO * 1, _borderVertices[i].y / PTM_RATIO * 1);
		p2 = b2Vec2(_borderVertices[i+1].x / PTM_RATIO * 1, _borderVertices[i+1].y / PTM_RATIO * 1);
		shape.Set(p1, p2);
		mBody->CreateFixture(&shape, 0);
	}
}

void Terrain::generateHills()
{
	float scale = 1;//cocos2d::Director::getInstance()->getContentScaleFactor() * 2;
	
	srand(time(0));
	
	float minDX = 20 * scale;
	float minDY = 2 * scale;
	float rangeDX = 10 * scale;
	float rangeDY = 30 * scale;
	
	float x = -minDX;
	float y = mWindowSize.width * scale / 2 - minDY;
	
	float dy, ny;
	float sign = 1;
	float paddingTop = 20;
	float paddingBottom = 20;
	
	for(int i = 0; i < kMaxHillKeyPoints; ++i)
	{
		_hillKeyPoints[i] = cocos2d::Vec2(x / scale, y / scale);
		
		if (i == 0)
		{
			x = 0;
			y = mWindowSize.height * scale / 2;
		}
		else
		{
			x += rand() % (int) rangeDX + minDX;
			while(true)
			{
				dy = rand() % (int) rangeDY + minDY;
				ny = y + dy * sign;
				if (ny < mWindowSize.height * scale - paddingTop && ny > paddingBottom)
				{
					break;
				}
			}
			y = ny;
		}
		sign *= -1;
	}
}

void Terrain::setOffset(float newOffsetX, float newOffsetY)
{
	_offsetX = newOffsetX;
	this->setPosition(Vec2(mWindowSize.width / 8 - newOffsetX * this->getScale(), mWindowSize.height / 2 - newOffsetY * this->getScale()));
	resetHillVertices();
}

void Terrain::resetHillVertices()
{
	static int prevFromKeyPointI = -1;
	static int prevToKeyPointI = -1;
	static float scale = cocos2d::Director::getInstance()->getContentScaleFactor();
	
	while (_hillKeyPoints[_fromKeyPointI+1].x < _offsetX - mWindowSize.width / 8 / this->getScale())
	{
		_fromKeyPointI++;
	}

	while (_hillKeyPoints[_toKeyPointI].x < _offsetX + mWindowSize.width * 9 / 8 / this->getScale())
	{
		_toKeyPointI++;
	}

	if (prevFromKeyPointI != _fromKeyPointI || prevToKeyPointI != _toKeyPointI)
	{
		_nHillVertices = 0;
		_nBorderVertices = 0;
		CCPoint p0, p1, pt0, pt1;
		p0 = _hillKeyPoints[_fromKeyPointI];
		for (int i = _fromKeyPointI+1; i < _toKeyPointI+1; ++i)
		{
			p1 = _hillKeyPoints[i];
			
			int hSegments = floorf((p1.x - p0.x) / kHillSegmentWidth) * scale;
			float dx = (p1.x - p0.x) / hSegments;
			float da = M_PI / hSegments;
			float ymid = (p0.y + p1.y)/2;
			float ampl = (p0.y - p1.y)/2;
			pt0 = p0;
			_borderVertices[_nBorderVertices++] = pt0;
			for (int j = 1; j < hSegments+1; ++j)
			{
				pt1.x = p0.x + j * dx;
				pt1.y = ymid + ampl * cosf(da * j);
				_borderVertices[_nBorderVertices++] = pt1;
				
				_hillVertices[_nHillVertices] = vertex2(pt0.x, 0);
				_hillTexCoords[_nHillVertices++] = vertex2(pt0.x / 512, 1.0f);
				_hillVertices[_nHillVertices] = vertex2(pt0.x, pt0.y);
				_hillTexCoords[_nHillVertices++] = vertex2(pt0.x / 512, 0.0f);
				pt0 = pt1;
			}
			p0 = p1;
		}
		prevFromKeyPointI = _fromKeyPointI;
		prevToKeyPointI = _toKeyPointI;
		
		this->resetBox2DBody();
	}
}
