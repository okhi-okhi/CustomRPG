#include "ButtonArg.h"
#include <Rectangle.hpp>
#include "../System/PathProvider.h"

ButtonArg::ButtonArg(const Vector2 position, const Picture& texture, const TextArg& text,
	const std::function<void()>& function, const std::string& clickSound) :
	Button(position, texture, function, clickSound)
{
	this->text = text;
	this->text.setPosition(position);
}

void ButtonArg::draw()
{
	Button::draw();
	this->text.draw();
}
