#pragma once

class LSystem
{
public:

	struct Command
	{
		// Lineを返す
	};

	LSystem();

	void Set(String token, void* command);

	void Init(String start);
	void Rule(String token, String replaced);
	void Draw(uint32 state);
};

