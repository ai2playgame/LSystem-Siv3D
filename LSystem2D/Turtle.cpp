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

Vec2 aiGraphics::Turtle::getTurtlePosition() const
{
	if (lines.size() == 0)
	{
		return Vec2{ 0, 0 };
	}
	else
	{
		return lines.back().end;
	}
}

Vec2 aiGraphics::Turtle::getTurtleDir() const
{
	return dir;
}

void aiGraphics::Turtle::draw(double thickness, const Color& color) const
{
	for (const auto& line : lines)
	{
		line.draw(thickness, color);
	}
}
