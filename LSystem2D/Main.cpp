# include <Siv3D.hpp> // OpenSiv3D v0.6.6

#if 0
Array<Line> Next(const Array<Line>& lines)
{
	Array<Line> result;

	for (const auto& line : lines)
	{
		const Vec2 p0 = line.begin;
		const Vec2 p1 = line.begin + (line.vector() / 3);
	}
}
#endif

void Main()
{
	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	while (System::Update())
	{
	}
}

