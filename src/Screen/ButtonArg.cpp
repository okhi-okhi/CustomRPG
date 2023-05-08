#include "ButtonArg.h"
#include <Rectangle.hpp>
#include "../System/PathProvider.h"

ButtonArg::ButtonArg(const std::string& fileName, const Vector2 position, const int width,
	const std::string& i18nKey, const std::map<std::string, argTypes>& args,
	const float fontSize, const textAlign textAlign, const raylib::Color textColor,
	const float textSpacing, const std::function<void()>& function, const std::string& clickSound) :
	Button(fileName, position, width, function, clickSound)
{
	this->text = TextArg(i18nKey, args, position, fontSize, textAlign, textColor, textSpacing);
}

void ButtonArg::draw()
{
	Button::draw();
	this->text.draw();
}

ButtonArg* ButtonArg::clone() const
{
	return new ButtonArg(*this);
}
