#pragma once
#include <Siv3D.hpp>

namespace aiGraphics
{
	// タートルグラフィック
	class Turtle
	{
	public:
		Turtle()
			: Turtle{ Vec2(0, 0) }
		{}

		Turtle(Vec2 start)
			: penStartPosition{ start }
			, penPosition{ start }
			, dir{ 1, 0 }
		{}

		void clear()
		{
			lines.clear();
			penPosition = penPosition;
		}

		void forward(float length)
		{
			Vec2 nextPosition = penPosition + (dir * length);
			lines.push_back(
				Line{ penPosition, nextPosition }
			);
			penPosition = nextPosition;
		}

		void right(float degree)
		{
			dir = dir.rotate(degree);
		}
		void left(float degree) { right(-degree); }

		void draw(double thickness, const Color& color) const
		{
			for (const auto& line : lines)
			{
				line.draw(thickness, color);
			}
		}

	private:
		const Vec2 penStartPosition;

		Vec2 penPosition;
		Vec2 dir;

		Array<Line> lines;
	};
}
