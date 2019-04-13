#include "GLine.h"

unsigned int *GLine::buffer = NULL;
int GLine::width;
int GLine::height;

void GLine::setBuffer(unsigned int *buf, const int& w, const int h)
{
	width = w;
	height = h;
	buffer = buf;
}

void GLine::set(const vec2& _start, const vec2& _end, const Color& _color)
{
	start = _start;
	end = _end;
	color = *((unsigned int*)&_color); //使用指针类型转换

	ivec2 delta = end - start; //线段向量，记录每个分量的距离
	ivec2 inc = clamp(delta, ivec2(-1), ivec2(1)); //计算偏移量，每个分量i>0 i=1,i<0 i=-1, i==0 i=0
	delta = abs(delta);
	end += inc; //加一格以判断结束条件

	if (delta.x > delta.y) //x分量最大
	{
		minStart = start.y; minInc = inc.y; minDist = delta.y;
		maxStart = start.x; maxInc = inc.x; maxDist = delta.x; maxEnd = end.x;
		drawStrategy = &GLine::drawXMax;
		initStrategy = &GLine::posXMax;
		isYChange = (delta.y==0)? &GLine::horizontalLine : &GLine::yMin;
	}
	else //y分量最大
	{
		minStart = start.x; minInc = inc.x; minDist = delta.x;
		maxStart = start.y; maxInc = inc.y; maxDist = delta.y; maxEnd = end.y;
		drawStrategy = &GLine::drawYMax;
		initStrategy = &GLine::posYMax;
		isYChange = &GLine::yMax;
	}
}

void GLine::initStep()
{
	curCache = 0; //缓存小分量的递增距离
	curMin = minStart;
	curMax = maxStart;
}

void GLine::drawAll()
{
	initStep();
	while (curMax != maxEnd) //以最长分量的长度作为线段的总像素数量，并进行插值
		stepY();
}