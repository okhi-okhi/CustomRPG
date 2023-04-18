#pragma once
#include "../Screen.h"

class MainScreen final : public Screen
{
public:
	MainScreen();

	Screen* clone() const override;

	static void test();
};

