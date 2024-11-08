#pragma once

#include "Utils.h"

class Button;
void defaultDrawText(const Button*);

class Button {
public:
	bool isDown = false;
	bool isEnabled = false;
	enum STATUS {
		NONE, ON, DOWN, CLICKED
	};
	RECT area;
	COLORREF color;
	static const COLORREF TextColor = BLACK;
	const LPCTSTR text;
	std::function<void(const Button*)> drawText, drawOnText;
	inline Button() :area(), color(), text(L""),
		drawText([](const Button* button) {defaultDrawText(button); }), drawOnText(nullptr) {
	}
	inline Button(const RECT area, const COLORREF color, const LPCTSTR text) : area(area), color(color), text(text),
		drawText([](const Button* button) {defaultDrawText(button); }), drawOnText(nullptr) {
	}
	inline Button(const RECT area, const COLORREF color, const LPCTSTR text, std::function<void(const Button*)> drawText) :
		area(area), color(color), text(text), drawText(drawText), drawOnText(nullptr) {
	}
	inline Button(const RECT area, const COLORREF color, const LPCTSTR text,
		std::function<void(const Button*)> drawText, std::function<void(const Button*)> drawOnText) :
		area(area), color(color), text(text), drawText(drawText), drawOnText(drawOnText) {
	}
	inline friend bool operator==(const Button&, const Button&) {
		return false;
	}
	inline void draw() const {
		setfillcolor(color);
		setfillstyle(BS_SOLID);
		solidrectangle(area);

		if (isEnabled && drawOnText != nullptr) drawOnText(this);
		else drawText(this);
	}
	inline bool isOn(const ExMessage& mouseMsg) const {
		return mouseMsg.x >= area.left && mouseMsg.x <= area.right && mouseMsg.y >= area.top && mouseMsg.y <= area.bottom;
	}
	inline STATUS flushStatus(const ExMessage& mouseMsg) {
		bool last = isDown;
		isDown = isOn(mouseMsg) && mouseMsg.lbutton;
		if (!isOn(mouseMsg)) return NONE;
		if (!isDown) return ON;
		if (last) return DOWN;
		isEnabled = !isEnabled;
		return CLICKED;
	}
};

inline void defaultDrawText(const Button* button) {
	int length = abs(button->area.top - button->area.bottom);
	setbkmode(TRANSPARENT);
	settextcolor(button->TextColor);
	settextstyle((int)(2 * length / (wcslen(button->text))), 0, L"Consolas");
	RECT area = button->area;
	drawtext(button->text, &area, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX);
}

inline std::string to_string(Button::STATUS status) {
	switch (status) {
	case Button::NONE:return "NONE";
	case Button::ON:return "ON";
	case Button::DOWN:return "DOWN";
	case Button::CLICKED:return "CLICKED";
	}
}

namespace std {
	template <>
	struct hash<Button> {
		std::size_t operator()(const Button& button) const {
			std::size_t h1 = std::hash<int>()(button.area.left);
			std::size_t h2 = std::hash<int>()(button.area.top);
			std::size_t h3 = std::hash<int>()(button.area.right);
			std::size_t h4 = std::hash<int>()(button.area.bottom);
			std::size_t h5 = std::hash<int>()(button.color);
			return h1 ^ h2 ^ h3 ^ h4 ^ h5;
		}
	};
}