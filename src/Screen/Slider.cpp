#include "Slider.h"
#include "../Utils/RaylibUtils.h"

Slider::Slider(const Picture& bar, const Picture& background, int* value, const int minValue,
	const int maxValue, const bool horizontal, const std::function<void()>& dragFunction) :
	Slider(Vector2(0, 0), bar, background, value, minValue, maxValue, horizontal, dragFunction)
{
}

Slider::Slider(const Vector2 bounds, const Picture& bar, const Picture& background,
               int* value, const int minValue, const int maxValue,
               const bool horizontal, const std::function<void()>& dragFunction)
{
	using RaylibUtils::getRealLength;
	this->elementType = ElementType::SLIDER;

	this->background = std::make_shared<Button>(Vector2(bounds.x, bounds.y),
		background, [this] { backgroundClick(); }, "none");

	this->position = this->background->getPosition();
	this->bounds = this->background->getHitbox()[0];

	this->minValue = minValue;
	this->maxValue = maxValue;
	this->value = value;
	this->horizontal = horizontal;
	this->dragFunction = dragFunction;
	this->dragging = false;

	if (this->horizontal)
	{
		this->bar = std::make_shared<ButtonHold>(Vector2(this->bounds.x, bounds.y),
			bar, [this] { barDrag(); });

		this->displayValueSpacing = (this->bounds.width) / static_cast<float>(this->maxValue - this->minValue);
		this->valueSpacing = this->bounds.width / static_cast<float>(this->maxValue - this->minValue + 1);
	}
	else
	{
		this->bar = std::make_shared<ButtonHold>(Vector2(bounds.x, this->bounds.y + bar.getHitbox()[0].height /2),
			bar, [this] { barDrag(); });

		this->displayValueSpacing = (this->bounds.height - this->bar->getHitbox()[0].height) / static_cast<float>(this->maxValue - this->minValue);
		this->valueSpacing = this->bounds.height / static_cast<float>(this->maxValue - this->minValue + 1);
	}

	this->children.push_back(this->background);
	this->children.push_back(this->bar);
}

Slider::Slider(const Slider& other) : ElementGroup(other),
	bounds(other.bounds),
	bar(other.bar),
	background(other.background),
	value(other.value),
	minValue(other.minValue),
	maxValue(other.maxValue),
	horizontal(other.horizontal),
	dragFunction(other.dragFunction),
	dragging(other.dragging),
	displayValueSpacing(other.displayValueSpacing),
	valueSpacing(other.valueSpacing)
{
	updateChildren();
}

Slider& Slider::operator=(Slider other)
{
	swap(*this, other);
	return *this;
}

void Slider::updateChildren()
{
	ElementGroup::updateChildren();
	this->children.push_back(this->background);
	this->children.push_back(this->bar);
	this->bar->setFunction([this] { barDrag(); });
	this->background->setFunction([this] { backgroundClick(); });
}

void Slider::draw()
{
	if(this->dragging)
	{
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			barDrag();
		}
		else
		{
			this->dragging = false;
			dragFunction();
		}
	}
	if (this->horizontal)
	{
		if (minValue <= *this->value && *this->value <= this->maxValue)
		{
			this->bar->setPositionX(this->bounds.x+
			(*this->value - this->minValue) * this->displayValueSpacing);
		}
	}
	else
	{
		if (minValue <= *this->value && *this->value <= this->maxValue)
		{
			this->bar->setPositionY(this->bounds.y+
				(*this->value - this->minValue) * this->displayValueSpacing);
		}
	}
}

void Slider::updatePosition()
{
	this->background->setPosition(this->position);
	this->bounds = this->background->getHitbox()[0];
	if(this->horizontal)
	{
		this->bar->setPositionY(this->position.y);
	}
	else
	{
		this->bar->setPositionX(this->position.x);
	}
}

void Slider::barDrag()
{
	this->dragging = true;
	if(this->horizontal)
	{
		if(GetMouseX() <= this->bounds.x)
		{
			*this->value = this->minValue;
		}
		else if(GetMouseX() >= this->bounds.x + this->bounds.width)
		{
			*this->value = this->maxValue;
		}
		else
		{
			*this->value = this->minValue + static_cast<int>((GetMouseX() - this->bounds.x) / this->valueSpacing);
		}
	}
	else
	{
		if (GetMouseY() <= this->bounds.y)
		{
			*this->value = this->minValue;
		}
		else if (GetMouseY() >= this->bounds.y + this->bounds.height)
		{
			*this->value = this->maxValue;
		}
		else
		{
			*this->value = this->minValue + static_cast<int>((GetMouseY() - this->bounds.y) / this->valueSpacing);
		}
	}
}

void Slider::backgroundClick()
{
	using std::cout, std::endl;
	this->dragging = true;
	if (this->horizontal)
	{
		*this->value = this->minValue + static_cast<int>((GetMouseX() - this->bounds.x) / this->valueSpacing);
	}
	else
	{
		*this->value = this->minValue + static_cast<int>((GetMouseY() - this->bounds.y) / this->valueSpacing);
	}
}

void swap(Slider& first, Slider& second) noexcept
{
	using std::swap;
	swap(static_cast<ElementGroup&>(first), static_cast<ElementGroup&>(second));

	swap(first.bounds, second.bounds);
	swap(first.bar, second.bar);
	swap(first.background, second.background);
	swap(first.value, second.value);
	swap(first.minValue, second.minValue);
	swap(first.maxValue, second.maxValue);
	swap(first.horizontal, second.horizontal);
	swap(first.dragging, second.dragging);
	swap(first.displayValueSpacing, second.displayValueSpacing);
	swap(first.valueSpacing, second.valueSpacing);

	first.updateChildren();
}
