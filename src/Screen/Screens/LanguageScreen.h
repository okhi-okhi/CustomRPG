#pragma once
#include "../Screen.h"

class LanguageScreen final : public Screen
{
private:
	const int* selectedLangIndex;

public:
	LanguageScreen();

	void changeLanguage() const;
	static void closeLanguage();
};

