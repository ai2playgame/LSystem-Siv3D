#include <Siv3D.hpp> // OpenSiv3D v0.6.6
#include "Turtle.h"
#include "LSystem.h"

void Main()
{
	Window::Resize(1280, 720);
	Window::SetStyle(WindowStyle::Sizable);
	Scene::SetBackground(Palette::Black);

	/*
		// 想定する使い方
		LSystem lSystem {最初の直線のサイズを指定};
		LSystem::Operator minusOperator;
		minusOperator.Set(minusOperator);
		lSystem.Set("-", minusOperator)

		LSystem::Operator plusOperator;
		plusOpeartor.Set(plusOperator);
		lSystem.Set("+", plusOperator);

		LSystem::Operator fOperator;
		fOpeartor.Set(fOperator);
		lSystem.Set("F", fOperator);

		lSystem.Init("F"); // 初期状態
		lSystem.Rule("F", "F-F++F--F"); // Fをどう置き換えるか

		lSystem.Draw(level);

		コッホ曲線は、まっすぐを以下に置き換え続ければ出来る
		1. まっすぐ
		2. 左に60度回転
		3. まっすぐ
		4. 右に60度回転
		5. 右に60度回転
		6. まっすぐ
		7. 左に60度回転
		8. まっすぐ
	*/
	Camera2D camera{ Vec2{0, 0}, 1.0 };

	size_t radioIndex = 1;
	while (System::Update())
	{
		size_t level = radioIndex;
		if (level == 0) { level = 1; }
		else { level *= 3; }

		SimpleGUI::RadioButtons(radioIndex, { U"LV1", U"LV3", U"LV6", U"LV9", U"LV12" }, Vec2{ 20, 20 });

		// LSystemセットアップ
		aiGraphics::LSystem lSystem;
		lSystem.move(Vec2{ 0, 0 }/*Scene::Center()*/);
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
#else
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
#endif

		{
			auto t = camera.createTransformer();
			camera.update();

			const double thickness = Min(2.0 / Graphics2D::GetMaxScaling(), 2.0);
			lSystem.draw(level, thickness);

			camera.draw(Palette::Orange);
		}
	}
}

