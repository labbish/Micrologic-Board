#pragma once

#include "Utils.h"

class Line {
public:
	static const COLORREF LineColor = RED, OnLineColor = LIGHTRED, WideLineColor = MAGENTA,
		ArrayColor = BLACK, OffLightColor = DARKGRAY, OnLightColor = YELLOW;
	const enum TYPE {
		LINE = 0,
		WIDELINE = 1
	};
	const enum STATUS {
		NONE = 0, INPUT, OUTPUT
	};
	TYPE mode;
	bool value;
	std::array<bool, 4> wideValue;
	STATUS left, up, right, down;
	inline Line() :mode(LINE), value(0), wideValue({ 0, 0, 0, 0 }), left(NONE), up(NONE), right(NONE), down(NONE) {}
	inline Line(bool value, STATUS left, STATUS up, STATUS right, STATUS down) : mode(LINE), value(value), wideValue({ 0, 0, 0, 0 }), left(left), up(up), right(right), down(down) {}
	inline Line(std::array<bool, 4> wideValue, STATUS left, STATUS up, STATUS right, STATUS down) : mode(WIDELINE), value(0), wideValue(wideValue), left(left), up(up), right(right), down(down) {}
	inline void draw(RECT r) const {
		COLORREF color;
		if (mode == LINE) color = value ? OnLineColor : LineColor;
		if (mode == WIDELINE) color = WideLineColor;
		setfillcolor(color);
		setfillstyle(BS_SOLID);
		setlinecolor(ArrayColor);
		setlinestyle(PS_SOLID, 1);

		if (left) {
			RECT leftSide = RECT{ (long)(r.left), (long)(0.6 * r.top + 0.4 * r.bottom), (long)(0.6 * r.left + 0.4 * r.right), (long)(0.4 * r.top + 0.6 * r.bottom) };
			solidrectangle(leftSide);
			if (left == INPUT) {
				line((int)(0.5 * leftSide.left + 0.5 * leftSide.right), (int)(leftSide.top), (int)(1.0 / 3 * leftSide.left + 2.0 / 3 * leftSide.right), (int)(0.5 * leftSide.top + 0.5 * leftSide.bottom));
				line((int)(0.5 * leftSide.left + 0.5 * leftSide.right), (int)(leftSide.bottom), (int)(1.0 / 3 * leftSide.left + 2.0 / 3 * leftSide.right), (int)(0.5 * leftSide.top + 0.5 * leftSide.bottom));
			}
			if (left == OUTPUT) {
				line((int)(0.5 * leftSide.left + 0.5 * leftSide.right), (int)(leftSide.top), (int)(2.0 / 3 * leftSide.left + 1.0 / 3 * leftSide.right), (int)(0.5 * leftSide.top + 0.5 * leftSide.bottom));
				line((int)(0.5 * leftSide.left + 0.5 * leftSide.right), (int)(leftSide.bottom), (int)(2.0 / 3 * leftSide.left + 1.0 / 3 * leftSide.right), (int)(0.5 * leftSide.top + 0.5 * leftSide.bottom));
			}
		}
		if (up) {
			RECT upSide = RECT{ (long)(0.6 * r.left + 0.4 * r.right),(long)(0.4 * r.top + 0.6 * r.bottom),(long)(0.4 * r.left + 0.6 * r.right),(long)(r.bottom) };
			solidrectangle(upSide);
			if (up == INPUT) {
				line((int)(upSide.left), (int)(0.5 * upSide.top + 0.5 * upSide.bottom), (int)(0.5 * upSide.left + 0.5 * upSide.right), (int)(2.0 / 3 * upSide.top + 1.0 / 3 * upSide.bottom));
				line((int)(upSide.right), (int)(0.5 * upSide.top + 0.5 * upSide.bottom), (int)(0.5 * upSide.left + 0.5 * upSide.right), (int)(2.0 / 3 * upSide.top + 1.0 / 3 * upSide.bottom));
			}
			if (up == OUTPUT) {
				line((int)(upSide.left), (int)(0.5 * upSide.top + 0.5 * upSide.bottom), (int)(0.5 * upSide.left + 0.5 * upSide.right), (int)(1.0 / 3 * upSide.top + 2.0 / 3 * upSide.bottom));
				line((int)(upSide.right), (int)(0.5 * upSide.top + 0.5 * upSide.bottom), (int)(0.5 * upSide.left + 0.5 * upSide.right), (int)(1.0 / 3 * upSide.top + 2.0 / 3 * upSide.bottom));
			}
		}
		if (right) {
			RECT rightSide = RECT{ (long)(0.4 * r.left + 0.6 * r.right), (long)(0.6 * r.top + 0.4 * r.bottom), (long)(r.right), (long)(0.4 * r.top + 0.6 * r.bottom) };
			solidrectangle(rightSide);
			if (left == INPUT) {
				line((int)(0.5 * rightSide.left + 0.5 * rightSide.right), (int)(rightSide.top), (int)(2.0 / 3 * rightSide.left + 1.0 / 3 * rightSide.right), (int)(0.5 * rightSide.top + 0.5 * rightSide.bottom));
				line((int)(0.5 * rightSide.left + 0.5 * rightSide.right), (int)(rightSide.bottom), (int)(2.0 / 3 * rightSide.left + 1.0 / 3 * rightSide.right), (int)(0.5 * rightSide.top + 0.5 * rightSide.bottom));
			}
			if (left == OUTPUT) {
				line((int)(0.5 * rightSide.left + 0.5 * rightSide.right), (int)(rightSide.top), (int)(1.0 / 3 * rightSide.left + 2.0 / 3 * rightSide.right), (int)(0.5 * rightSide.top + 0.5 * rightSide.bottom));
				line((int)(0.5 * rightSide.left + 0.5 * rightSide.right), (int)(rightSide.bottom), (int)(1.0 / 3 * rightSide.left + 2.0 / 3 * rightSide.right), (int)(0.5 * rightSide.top + 0.5 * rightSide.bottom));
			}
		}
		if (down) {
			RECT downSide = RECT{ (long)(0.6 * r.left + 0.4 * r.right),(long)(r.top),(long)(0.4 * r.left + 0.6 * r.right),(long)(0.6 * r.top + 0.4 * r.bottom) };
			solidrectangle(downSide);
			if (up == INPUT) {
				line((int)(downSide.left), (int)(0.5 * downSide.top + 0.5 * downSide.bottom), (int)(0.5 * downSide.left + 0.5 * downSide.right), (int)(1.0 / 3 * downSide.top + 2.0 / 3 * downSide.bottom));
				line((int)(downSide.right), (int)(0.5 * downSide.top + 0.5 * downSide.bottom), (int)(0.5 * downSide.left + 0.5 * downSide.right), (int)(1.0 / 3 * downSide.top + 2.0 / 3 * downSide.bottom));
			}
			if (up == OUTPUT) {
				line((int)(downSide.left), (int)(0.5 * downSide.top + 0.5 * downSide.bottom), (int)(0.5 * downSide.left + 0.5 * downSide.right), (int)(2.0 / 3 * downSide.top + 1.0 / 3 * downSide.bottom));
				line((int)(downSide.right), (int)(0.5 * downSide.top + 0.5 * downSide.bottom), (int)(0.5 * downSide.left + 0.5 * downSide.right), (int)(2.0 / 3 * downSide.top + 1.0 / 3 * downSide.bottom));
			}
		}

		RECT center = RECT{ (long)(0.6 * r.left + 0.4 * r.right),(long)(0.6 * r.top + 0.4 * r.bottom),(long)(0.4 * r.left + 0.6 * r.right), (long)(0.4 * r.top + 0.6 * r.bottom) };
		solidrectangle(center);

		if (mode == LINE) {
			double length = (double)(abs(center.top - center.bottom));
			int radius = (int)(2.0 / 5 * length);
			setfillcolor(value ? OnLightColor : OffLightColor);
			setfillstyle(BS_SOLID);
			solidcircle((int)(0.5 * center.left + 0.5 * center.right), (int)(0.5 * center.top + 0.5 * center.bottom), radius);
		}
		if (mode == WIDELINE) {
			double length = (double)(abs(center.top - center.bottom));
			int radius = (int)(2.0 / 11 * length);
			setfillcolor(wideValue[0] ? OnLightColor : OffLightColor);
			setfillstyle(BS_SOLID);
			solidcircle((int)(3.0 / 11 * center.left + 8.0 / 11 * center.right), (int)(3.0 / 11 * center.top + 8.0 / 11 * center.bottom), radius);
			setfillcolor(wideValue[1] ? OnLightColor : OffLightColor);
			setfillstyle(BS_SOLID);
			solidcircle((int)(8.0 / 11 * center.left + 3.0 / 11 * center.right), (int)(3.0 / 11 * center.top + 8.0 / 11 * center.bottom), radius);
			setfillcolor(wideValue[2] ? OnLightColor : OffLightColor);
			setfillstyle(BS_SOLID);
			solidcircle((int)(3.0 / 11 * center.left + 8.0 / 11 * center.right), (int)(8.0 / 11 * center.top + 3.0 / 11 * center.bottom), radius);
			setfillcolor(wideValue[3] ? OnLightColor : OffLightColor);
			setfillstyle(BS_SOLID);
			solidcircle((int)(8.0 / 11 * center.left + 3.0 / 11 * center.right), (int)(8.0 / 11 * center.top + 3.0 / 11 * center.bottom), radius);
		}
	}
};

class LineModel :public Line {
public:
	static const COLORREF WideOnLineColor = LIGHTMAGENTA;
	static const STATUS CONNECT = INPUT;
	using Line::Line;
	inline void draw(RECT r) const {
		COLORREF color;
		if (mode == LINE) color = value ? OnLineColor : LineColor;
		if (mode == WIDELINE) color = (wideValue[0] + wideValue[1] + wideValue[2] + wideValue[3] >= 2) ? WideOnLineColor : WideLineColor;
		setfillcolor(color);
		setfillstyle(BS_SOLID);
		setlinecolor(ArrayColor);
		setlinestyle(PS_SOLID, 1);

		if (left) {
			RECT leftSide = RECT{ (long)(r.left), (long)(0.6 * r.top + 0.4 * r.bottom), (long)(0.6 * r.left + 0.4 * r.right), (long)(0.4 * r.top + 0.6 * r.bottom) };
			solidrectangle(leftSide);
		}
		if (up) {
			RECT upSide = RECT{ (long)(0.6 * r.left + 0.4 * r.right),(long)(0.4 * r.top + 0.6 * r.bottom),(long)(0.4 * r.left + 0.6 * r.right),(long)(r.bottom) };
			solidrectangle(upSide);
		}
		if (right) {
			RECT rightSide = RECT{ (long)(0.4 * r.left + 0.6 * r.right), (long)(0.6 * r.top + 0.4 * r.bottom), (long)(r.right), (long)(0.4 * r.top + 0.6 * r.bottom) };
			solidrectangle(rightSide);
		}
		if (down) {
			RECT downSide = RECT{ (long)(0.6 * r.left + 0.4 * r.right),(long)(r.top),(long)(0.4 * r.left + 0.6 * r.right),(long)(0.6 * r.top + 0.4 * r.bottom) };
			solidrectangle(downSide);
		}

		RECT center = RECT{ (long)(0.6 * r.left + 0.4 * r.right),(long)(0.6 * r.top + 0.4 * r.bottom),(long)(0.4 * r.left + 0.6 * r.right), (long)(0.4 * r.top + 0.6 * r.bottom) };
		solidrectangle(center);
	}
};