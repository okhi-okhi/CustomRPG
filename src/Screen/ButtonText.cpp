#include "ButtonText.h"

ButtonText::ButtonText(const std::string& fileName, Vector2 position, float zoomPercent, const std::string& i18nKey,
	float fontSize, textAlign textAlign, raylib::Color textColor, float textSpacing,
	const std::function<void()>& function, const std::string& clickSound) :
	Button(fileName, position, zoomPercent, function, clickSound)
{
	this->elementType = elementTypes::BUTTON_TEXT;
	this->text = Text(i18nKey, this->getTextPos(textAlign), fontSize, textAlign, textColor, textSpacing);
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
