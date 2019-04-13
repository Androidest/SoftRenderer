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
	color = *((unsigned int*)&_color); //ʹ��ָ������ת��

	ivec2 delta = end - start; //�߶���������¼ÿ�������ľ���
	ivec2 inc = clamp(delta, ivec2(-1), ivec2(1)); //����ƫ������ÿ������i>0 i=1,i<0 i=-1, i==0 i=0
	delta = abs(delta);
	end += inc; //��һ�����жϽ�������

	if (delta.x > delta.y) //x�������
	{
		minStart = start.y; minInc = inc.y; minDist = delta.y;
		maxStart = start.x; maxInc = inc.x; maxDist = delta.x; maxEnd = end.x;
		drawStrategy = &GLine::drawXMax;
		initStrategy = &GLine::posXMax;
		isYChange = (delta.y==0)? &GLine::horizontalLine : &GLine::yMin;
	}
	else //y�������
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
	curCache = 0; //����С�����ĵ�������
	curMin = minStart;
	curMax = maxStart;
}

void GLine::drawAll()
{
	initStep();
	while (curMax != maxEnd) //��������ĳ�����Ϊ�߶ε������������������в�ֵ
		stepY();
}