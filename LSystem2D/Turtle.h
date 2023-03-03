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
			, dir{ 0, -1 }
		{}

		void clear();

		// まっすぐ直線を引く
		void forward(double length);

		// 右に指定度回転する
		void right(double degree);
		// 左に指定度回転する
		void left(double degree) { right(-degree); }

		// 亀を指定した位置に移動させる
		void move(Vec2 position) { this->penPosition = position; }
		void rotate(Vec2 dir) { this->dir = dir; }

		// 今の亀の位置を取得する
		Vec2 getTurtlePosition() const;
		// 今の亀の向きを取得する
		Vec2 getTurtleDir() const;

		void draw(double thickness, const Color& color) const;

	private:
		const Vec2 penStartPosition;

		Vec2 penPosition;
		Vec2 dir;

		Array<Line> lines;
	};
}
