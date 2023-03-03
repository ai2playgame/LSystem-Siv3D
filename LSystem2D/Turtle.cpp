#include "stdafx.h"
#include "Turtle.h"

void aiGraphics::Turtle::clear()
{
	lines.clear();
	penPosition = penPosition;
}

void aiGraphics::Turtle::forward(double length)
{
	Vec2 nextPosition = penPosition + (dir * length);
	lines.push_back(
		Line{ penPosition, nextPosition }
	);
	penPosition = nextPosition;
}

void aiGraphics::Turtle::right(double degree)
{
	dir = dir.rotate(degree);
}

void aiGraphics::Turtle::draw(double thickness, const Color& color) const
{
	for (const auto& line : lines)
	{
		line.draw(thickness, color);
	}
}
