#pragma once
#include "../Screen.h"

class LanguageScreen final : public Screen
{
public:
	LanguageScreen();

	static void changeLanguage(const int* index);
	static void closeLanguage();
};

