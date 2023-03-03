#pragma once
#include <Siv3D.hpp>

namespace aiGraphics
{
	/*
	 * タートルグラフィックを実現するクラス
	 */
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

		void clear();

		// まっすぐ直線を引く
		void forward(double length);

		// 右に指定度回転する
		void right(double degree);
		// 左に指定度回転する
		void left(double degree) { right(-degree); }

		void draw(double thickness, const Color& color) const;

	private:
		const Vec2 penStartPosition;

		Vec2 penPosition;
		Vec2 dir;

		Array<Line> lines;
	};
}
