#pragma once
#include "../../Screen.h"

class LanguageScreen final : public Screen
{
private:
	const int* selectedLangIndex;

	void changeLanguage() const;
	static void closeLanguage();

public:
	LanguageScreen();
};

