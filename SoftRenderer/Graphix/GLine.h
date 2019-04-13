#pragma once
#include "glm.hpp"
#include <SFML\Graphics.hpp>
using namespace glm;
using namespace sf;

class GLine
{
public:
	int curX, curY, curHeight; //��ǰ���Ʋ�������

private:
	static int width;
	static int height;
	static unsigned int *buffer;

	ivec2 start;
	ivec2 end;
	unsigned int color;

	int curCache;
	int curMin,minStart,minInc,minDist;  //pmaxStartΪ�������ͷλ�ã�pmaxEndΪĩ��λ�ã�pΪʣ�µķ�����ͷλ��
	int curMax,maxStart,maxEnd,maxInc,maxDist;//incMaxΪ������Ļ���������inc Ϊʣ�·���������
	void(GLine::*drawStrategy)();
	void(GLine::*initStrategy)();
	bool(GLine::*isYChange)();

public:
	static void setBuffer(unsigned int *buf, const int& w, const int h);

	GLine(){}
	void set(const vec2& s, const vec2& e, const Color& color);
	void drawAll();
	void initStep();
	inline void stepY() //strategyΪ���Ժ���ָ�룬�ڲ�ͬ������ò�ͬ�Ĳ��Ժ���posXMax��posYMax
	{
		(this->*initStrategy)();
		do {
			(this->*drawStrategy)();
			curCache += minDist;    //ÿ�λ���һ�������������������ȣ���¼������ٴβŴ���������
			if (curCache > maxDist) //�����������˷���������һ��
			{
				curCache -= maxDist; //��������»���
				curMin += minInc; //�˷�������һ��
			}
			curMax += maxInc;
		} while ((this->*isYChange)());
	}

private:
	//============���Ժ�������bresenham�������ݲ�ͬ���ͨ������ָ�����===================
	inline bool horizontalLine() { return curMax != maxEnd; } //ˮƽ��
	inline bool yMin() { return curY == curMin; } //x�����
	inline bool yMax() { return curY == curMax; } //y�����
	inline void posXMax() { curX = curMax; curY = curMin; curHeight = curY*width; } //x�����
	inline void posYMax() { curX = curMin; curY = curMax; curHeight = curY*width; } //y�����
	inline void drawXMax() { buffer[curMax + curHeight] = color; } //x�����
	inline void drawYMax() { buffer[curMin + curHeight] = color; } //y�����
};