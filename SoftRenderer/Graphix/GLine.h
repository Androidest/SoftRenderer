#pragma once
#include "glm.hpp"
#include <SFML\Graphics.hpp>
using namespace glm;
using namespace sf;

class GLine
{
public:
	int curX, curY, curHeight; //当前绘制步的坐标

private:
	static int width;
	static int height;
	static unsigned int *buffer;

	ivec2 start;
	ivec2 end;
	unsigned int color;

	int curCache;
	int curMin,minStart,minInc,minDist;  //pmaxStart为最长分量的头位置，pmaxEnd为末端位置，p为剩下的分量的头位置
	int curMax,maxStart,maxEnd,maxInc,maxDist;//incMax为最长分量的绘制增量，inc 为剩下分量的增量
	void(GLine::*drawStrategy)();
	void(GLine::*initStrategy)();
	bool(GLine::*isYChange)();

public:
	static void setBuffer(unsigned int *buf, const int& w, const int h);

	GLine(){}
	void set(const vec2& s, const vec2& e, const Color& color);
	void drawAll();
	void initStep();
	inline void stepY() //strategy为策略函数指针，在不同情况调用不同的策略函数posXMax、posYMax
	{
		(this->*initStrategy)();
		do {
			(this->*drawStrategy)();
			curCache += minDist;    //每次缓存一个分量长度与最长分量相比，记录缓存多少次才大于最大分量
			if (curCache > maxDist) //缓存溢出代表此分量将递增一格
			{
				curCache -= maxDist; //溢出后重新缓存
				curMin += minInc; //此分量增加一格
			}
			curMax += maxInc;
		} while ((this->*isYChange)());
	}

private:
	//============策略函数，由bresenham函数根据不同情况通过函数指针调用===================
	inline bool horizontalLine() { return curMax != maxEnd; } //水平线
	inline bool yMin() { return curY == curMin; } //x分量最长
	inline bool yMax() { return curY == curMax; } //y分量最长
	inline void posXMax() { curX = curMax; curY = curMin; curHeight = curY*width; } //x分量最长
	inline void posYMax() { curX = curMin; curY = curMax; curHeight = curY*width; } //y分量最长
	inline void drawXMax() { buffer[curMax + curHeight] = color; } //x分量最长
	inline void drawYMax() { buffer[curMin + curHeight] = color; } //y分量最长
};