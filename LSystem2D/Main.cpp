# include <Siv3D.hpp> // OpenSiv3D v0.6.6

void Main()
{
	Window::Resize(1280, 720);
	Window::SetStyle(WindowStyle::Sizable);
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	while (System::Update())
	{
	}
}

