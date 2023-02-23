#pragma once
// https://zenn.dev/reputeless/articles/sample-fractal

#include <Siv3D.hpp>

Array<Line> Next(const Array<Line>& lines)
{
	Array<Line> result;

	for (const auto& line : lines)
	{
		const Vec2 p0 = line.begin;
		const Vec2 p1 = line.begin + (line.vector() / 3);
		const Vec2 p2 = p1 + (line.vector() / 3).rotate(-60_deg);
		const Vec2 p3 = line.end - (line.vector() / 3);
		const Vec2 p4 = line.end;

		result.emplace_back(p0, p1);
		result.emplace_back(p1, p2);
		result.emplace_back(p2, p3);
		result.emplace_back(p3, p4);
	}

	return result;
}

void Draw(const Array<Line>& lines)
{
	const double thickness = Min(2.0 / Graphics2D::GetMaxScaling(), 2.0);
	constexpr auto color = Palette::Black;

	for (const auto& line : lines)
	{
		line.draw(thickness, color);
	}
}

#if false
void Main()
{
	Window::Resize(1280, 720);
	Window::SetStyle(WindowStyle::Sizable);
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
	const Font font{ 25, Typeface::Heavy };

	const Array<Line> e0 = { Line { -400, 0, 400, 0} };
	const Array<Line> e1 = Next(e0);
	const Array<Line> e2 = Next(e1);
	const Array<Line> e3 = Next(e2);
	const Array<Line> e4 = Next(e3);
	const Array<Line> e5 = Next(e4);
	const Array<Line> e6 = Next(e5);

	Camera2D camera{ Vec2 { 0, 0 }, 1.0 };
	size_t level = 0;

	while (System::Update())
	{
		{
			auto t = camera.createTransformer();
			camera.update();

			switch (level)
			{
			case 0: Draw(e0); break;
			case 1: Draw(e1); break;
			case 2: Draw(e2); break;
			case 3: Draw(e3); break;
			case 4: Draw(e4); break;
			case 5: Draw(e5); break;
			case 6: Draw(e6); break;
			}

			camera.draw(Palette::Orange);
		}

		SimpleGUI::RadioButtons(level, { U"E0", U"E1", U"E2", U"E3", U"E4", U"E5", U"E6" }, Vec2{ 20, 20 });

		Rect{ 20, 500, 300, 200 }
			.drawShadow(Vec2{ 3, 3 }, 8, 0)
			.draw(ColorF{ 1.0, 0.9, 0.8 });

		const Line base{ 40, 600, 280, 600 };
		Draw(Next({ base }));
		font(U"Generator").drawAt(160, 680, ColorF{ 0.0, 0.5 });
	}
}

#endif

