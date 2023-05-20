#include "ButtonText.h"

ButtonText::ButtonText(const std::string& fileName, const Vector2 position, const int width,
	const std::string& i18nKey, const float fontSize, const textAlign textAlign,
	const raylib::Color textColor, const float textSpacing,
	const std::function<void()>& function, const std::string& clickSound) :
	Button(fileName, position, width, function, clickSound)
{
	this->elementType = elementTypes::BUTTON_TEXT;
	this->text = Text(i18nKey, position, fontSize, textAlign, textColor, textSpacing);
}

void ButtonText::draw()
{
	Button::draw();
	this->text.draw();
}

ButtonText* ButtonText::clone() const
{
	return new ButtonText(*this);
}
