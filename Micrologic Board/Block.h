#pragma once

#include "Utils.h"
#include "Coordinate.h"

class Block {
public:
	static const COLORREF FillColor = CYAN, TextColor = BLACK;
	Block() :type(L"") {}
	Block(LPCTSTR type) :type(type) {}
	LPCTSTR type;
	inline void draw(RECT r) const {
		double length = abs(r.right - r.left);
		setfillcolor(FillColor);
		setfillstyle(BS_SOLID);
		solidrectangle(r.left, r.top, r.right, r.bottom);
		setbkmode(TRANSPARENT);
		settextcolor(TextColor);
		settextstyle((int)(length / 3), 0, L"Consolas");
		drawtext(type, &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX);
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
		drawtext(type, &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX);
	}
};