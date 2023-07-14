#pragma once
#include <functional>
#include <Sound.hpp>
#include "Picture.h"

enum class ButtonState
{
	IDLE = 0,
	HOVER
};

class Button : public Element
{
protected:
	Picture texture;
	Sound clickSound;
	std::function<void()> function;
	bool lockState;
	std::vector<raylib::Rectangle> reserveRec{};

public:
	Button() : clickSound(), lockState(false) {}
	Button(Vector2 position, const Picture& texture,
		const std::function<void()>& function,
		const std::string& clickSound = "button_click.wav");
	Button(const Picture& texture, const std::function<void()>& function,
		const std::string& clickSound = "button_click.wav");

	void draw() override;
	void updatePosition() override;

	virtual void update();

	void checkCollision(const std::vector<raylib::Rectangle>& recs);
	void setState(ButtonState buttonState) { this->texture.setCurrentFrame(static_cast<int>(buttonState)); }
	void setLockState(const bool _lockState) { this->lockState = _lockState; }
	void setFunction(const std::function<void()>& _function) { this->function = _function; }

	void addReserveRec(const raylib::Rectangle hitbox) { this->reserveRec.push_back(hitbox); }
	void clearReserveRec() { this->reserveRec.clear(); }

	const Picture& getTexture() const { return this->texture; }
	ButtonState getButtonState() const { return static_cast<ButtonState>(this->texture.getCurrentFrame()); }
	float getButtonHeight() const { return this->texture.getHeight(); }
	const std::vector<raylib::Rectangle>& getReserveRec() const { return this->reserveRec; }
};

