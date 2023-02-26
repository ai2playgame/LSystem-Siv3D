# include <Siv3D.hpp> // OpenSiv3D v0.6.6

void Main()
{
	Window::Resize(1280, 720);
	Window::SetStyle(WindowStyle::Sizable);
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

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

		コッホ曲線は
		1. まっすぐ
		2. 左に60度回転
		3. まっすぐ
		4. 右に60度回転
		5. 右に60度回転
		6. まっすぐ
		7. 左に60度回転
		8. まっすぐ
	*/

	while (System::Update())
	{
	}
}

