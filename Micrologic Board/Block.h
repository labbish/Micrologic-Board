#pragma once

#include "Utils.h"
#include "Coordinate.h"

class Block {
public:
	int x = 1, y = 1;
	static const COLORREF FillColor = CYAN, TextColor = BLACK;
	Block() :type(L"") {}
	Block(std::wstring type) :type(type) {}
	Block(std::wstring type, int x, int y) :type(type), x(x), y(y) {}
	std::wstring type;
	inline void draw(RECT r) const {
		double length = abs(r.right - r.left);
		setfillcolor(FillColor);
		setfillstyle(BS_SOLID);
		solidrectangle(r.left, r.top, r.right, r.bottom);
		setbkmode(TRANSPARENT);
		settextcolor(TextColor);
		settextstyle((int)(length / 3), 0, L"Consolas");
		drawtext(type.c_str(), &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX);
	}
	inline GridCoordinate gridSize() {
		return GridCoordinate(x, y);
	}
};

class BlockModel :public Block {
public:
	static const COLORREF OnFillColor = LIGHTCYAN;
	COLORREF fillColor = FillColor;
	using Block::Block;
	BlockModel(LPCTSTR type, COLORREF fillColor) :Block(type), fillColor(fillColor) {}
	inline void draw(RECT r) const {
		double length = abs(r.right - r.left);
		setfillcolor(fillColor);
		setfillstyle(BS_SOLID);
		setlinecolor(TextColor);
		setlinestyle(BS_SOLID);
		fillrectangle(r.left, r.top, r.right, r.bottom);
		setbkmode(TRANSPARENT);
		settextcolor(TextColor);
		settextstyle((int)(length), 0, L"Consolas");
		drawtext(type.c_str(), &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX);
	}
};