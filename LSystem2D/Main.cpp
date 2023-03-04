#include <Siv3D.hpp> // OpenSiv3D v0.6.6
#include "LSystem.h"
#include "Turtle.h"

void Main()
{
	Window::Resize(1280, 720);
	Window::SetStyle(WindowStyle::Sizable);
	Scene::SetBackground(Palette::Black);

	Camera2D camera{ Vec2{0, 0}, 1.0 };

	size_t level = 1;
	double levelDecimal = 0.1;
	double rotatedDegreeDetail = 45;
	int rotatedDegree = static_cast<int>(rotatedDegreeDetail);
	double lineLength = 30;
	TextEditState initialStringText;
	initialStringText.text = U"A";
	TextEditState replacedRuleAText;
	replacedRuleAText.text = U"+A--A+";
	TextEditState replacedRuleBText;

	auto getUiPosition = [](int i)
	{
		constexpr Vec2 uiBasePos{ 20, 20 };
		constexpr Vec2 uiOffset{ 0, 40 };
		return (uiBasePos + (uiOffset * i));
	};

	// LSystem初期化
	aiGraphics::LSystem lSystem;

	while (System::Update())
	{
		SimpleGUI::Headline(U"initial string", getUiPosition(0));
		SimpleGUI::TextBox(initialStringText, getUiPosition(1), 200);
		SimpleGUI::Headline(U"replaced rule (A)", getUiPosition(2));
		SimpleGUI::TextBox(replacedRuleAText, getUiPosition(3), 200);
		SimpleGUI::Headline(U"replaced rule (B)", getUiPosition(4));
		SimpleGUI::TextBox(replacedRuleBText, getUiPosition(5), 200);
		// 値域0.1~1.0でLSystemのレベルを決めるスライダー
		SimpleGUI::Slider(U"Level: {}"_fmt(level), levelDecimal, 0.1, 1.0, getUiPosition(6), 135);
		// 値域1~100で線分の長さを決めるスライダー
		SimpleGUI::Slider(U"Length: {:.2f}"_fmt(lineLength), lineLength, 1.0, 100.0, getUiPosition(7), 135);
		// 値域0-90で回転量を決めるスライダー
		SimpleGUI::Slider(U"Angle: {}"_fmt(rotatedDegree), rotatedDegreeDetail, 0.0, 90.0, getUiPosition(8), 135);

		auto updated = SimpleGUI::Button(U"Update", getUiPosition(9));

		// 0.1~1.0のdouble型で決めたLSystemのレベルを1-10の整数に変換
		level = static_cast<size_t>(levelDecimal * 10);
		// 度数法の回転量を弧度法に変換する
		rotatedDegree = static_cast<int>(rotatedDegreeDetail);
		double rotatedRad = Math::ToRadians(rotatedDegree);

		if (updated)
		{
			// Lsystemの設定を更新する
			lSystem.clear();

			lSystem.init(initialStringText.text);
			lSystem.rule(U'A', replacedRuleAText.text);
			lSystem.rule(U'B', replacedRuleBText.text);
			lSystem.set(U'A', [lineLength](aiGraphics::Turtle& turtle) { turtle.forward(lineLength); });
			lSystem.set(U'B', [lineLength](aiGraphics::Turtle& turtle) { turtle.forward(lineLength); });
			lSystem.set(U'+', [rotatedRad](aiGraphics::Turtle& turtle) { turtle.right(rotatedRad); });
			lSystem.set(U'-', [rotatedRad](aiGraphics::Turtle& turtle) { turtle.left(rotatedRad); });
		}

		{
			auto t = camera.createTransformer();
			camera.update();

			const double thickness = Min(2.0 / Graphics2D::GetMaxScaling(), 2.0);

			if (!lSystem.validate())
			{
				continue;
			}

			lSystem.draw((uint32)level, thickness);

			camera.draw(Palette::Orange);
		}
	}
}

