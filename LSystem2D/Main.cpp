#include <Siv3D.hpp> // OpenSiv3D v0.6.6
#include "Turtle.h"

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

	aiGraphics::Turtle turtle{ Scene::Center() };
	turtle.forward(100);
	turtle.right(45_deg);
	turtle.forward(50);
	turtle.left(45_deg);
	turtle.forward(50);

	while (System::Update())
	{
		turtle.draw(3, Palette::Green);
	}
}

