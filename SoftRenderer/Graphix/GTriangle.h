#pragma once

#include "GLine.h"

class GTriangle
{
private:
	vec2 pos1;
	vec2 pos2;
	vec2 pos3;
	Color color;

public:
	GTriangle(const vec2& p1, const vec2& p2, const vec2& p3, const Color& c): pos1(p1), pos2(p2), pos3(p3), color(c) {}

	void draw()
	{
		GLine line1, line2;
		vec2 top, middle, bottom ,middle2;
		if (pos1.y < pos2.y)
		{
			top = pos1;
			bottom = pos2;
		}
		else
		{
			top = pos2;
			bottom = pos1;
		}
		if (pos3.y < top.y)
		{
			middle = top;
			top = pos3;
		}
			
		if (pos3.y > bottom.y)
		{
			middle = bottom;
			bottom = pos3;
		}
			
		/*if (middle.y == bottom.y)
		{
			bottomFlat(top, middle, bottom);
		}

		else if (middle.y == top.y)
		{
			topFlat(top, middle, bottom);
		}
		else
		{
			middle2 = vec2( (int)(top.x + ((float)(middle.y - top.y) / (float)(bottom.y - top.y)) * (bottom.x - top.x)), middle.y);
			bottomFlat(top, middle, middle2);
			topFlat(middle, middle2, bottom);
		}*/
	}
	
	void drawOutLine()
	{
		GLine line;
		line.set(pos1, pos2, color);
		line.drawAll();

		line.set(pos2, pos3, color);
		line.drawAll();

		line.set(pos3, pos1, color);
		line.drawAll();
	}
};