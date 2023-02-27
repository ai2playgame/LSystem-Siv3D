#pragma once
namespace aiGraphics
{
	// タートルグラフィック
	class Turtle
	{
	public:
		Turtle(Vec2 start);

		void Forward(float length);

		void Right(float degree);
		void Left(float degree) { Right(-degree); }
	};
}
