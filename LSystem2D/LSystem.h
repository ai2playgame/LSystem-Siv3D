#pragma once

class LSystem
{
public:
	LSystem();

	void Set(String token, void* command);

	void Init(String start);
	void Rule(String token, String replaced);
	void Draw(uint32 state);
};

