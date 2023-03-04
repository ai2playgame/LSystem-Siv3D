﻿#include <Siv3D.hpp> // OpenSiv3D v0.6.6
#include "LSystem.h"
#include "Turtle.h"

void Main()
{
	Window::Resize(1280, 720);
	Window::SetStyle(WindowStyle::Sizable);
	Scene::SetBackground(Palette::Black);

	Camera2D camera{ Vec2{0, 0}, 1.0 };

	size_t level = 1;

	while (System::Update())
	{
		size_t level = 5;
		// LSystemセットアップ
		aiGraphics::LSystem lSystem;
		lSystem.move(Vec2{ 0, 0 });
#if false // C曲線
		lSystem.init(U"F");
		const double length = 80.0 / level;
		// F: 直進
		lSystem.set(U'F', [&length](aiGraphics::Turtle& turtle) { turtle.forward(length); });
		// -: 45度左に回転
		lSystem.set(U'-', [](aiGraphics::Turtle& turtle) { turtle.right(45_deg); });
		// +: 45度右に回転
		lSystem.set(U'+', [](aiGraphics::Turtle& turtle) { turtle.left(45_deg); });
		// 置き換えルール
		lSystem.rule(U'F', U"+F--F+");
#elif false // シェルピンスキーの三角形
		lSystem.init(U"A");
		const double length = 60.0 / level;
		// A: 直進
		lSystem.set(U'A', [&length](aiGraphics::Turtle& turtle) { turtle.forward(length); });
		// B: 直進
		lSystem.set(U'B', [&length](aiGraphics::Turtle& turtle) { turtle.forward(length); });
		// -: 60度右に回転
		lSystem.set(U'-', [](aiGraphics::Turtle& turtle) { turtle.right(60_deg); });
		// +: 60度左に回転
		lSystem.set(U'+', [](aiGraphics::Turtle& turtle) { turtle.left(60_deg); });
		// 置き換えルール
		lSystem.rule(U'A', U"B-A-B");
		lSystem.rule(U'B', U"A+B+A");
#elif false // コッホ曲線
		lSystem.init(U"F-F-F-F");
		const double length = 60.0 / level;
		lSystem.set(U'F', [&length](aiGraphics::Turtle& turtle) { turtle.forward(length); });
		lSystem.set(U'+', [](aiGraphics::Turtle& turtle) {turtle.right(90_deg); });
		lSystem.set(U'-', [](aiGraphics::Turtle& turtle) {turtle.left(90_deg); });
		lSystem.rule(U'F', U"FF-F-F-F-F-F+F");
#elif true // 木
		lSystem.init(U"X");
		const double length = 60.0 / level;
		lSystem.set(U'X', [&length](aiGraphics::Turtle& turtle) { turtle.forward(length); });
		lSystem.set(U'F', [&length](aiGraphics::Turtle& turtle) { turtle.forward(length); });
		lSystem.set(U'+', [](aiGraphics::Turtle& turtle) {turtle.right(25_deg); });
		lSystem.set(U'-', [](aiGraphics::Turtle& turtle) {turtle.left(25_deg); });
		lSystem.rule(U'X', U"F[+X]F[-X]+X");
		lSystem.rule(U'F', U"FF");
#endif

		{
			auto t = camera.createTransformer();
			camera.update();

			const double thickness = Min(2.0 / Graphics2D::GetMaxScaling(), 2.0);
			lSystem.draw((uint32)level, thickness);

			camera.draw(Palette::Orange);
		}
	}
}

