#pragma once

#ifdef _DEBUG
#define BOARD_DEBUG
#endif

#include "Utils.h"
#include "Block.h"
#include "Line.h"
#include "Button.h"

using Length = double;
using TrueLength = double;

class Board {
public:
	static const COLORREF BkColor = WHITE, GridLineColor = BLACK,
		BlockColor = Block::FillColor, BlockOnColor = BlockModel::OnFillColor,
		ButtonColor = GREEN, EndButtonColor = RED, TextColor = Button::TextColor;
	static constexpr TrueLength Width = 960, Height = 720, GridLength = 100,
		ButtonWidth = 30, ButtonHeight = 30, ButtonWidthSpacing = 10, ButtonHeightSpacing = 10;
	static const GridCoordinate NoGrid;
	static const std::wstring NoInput;
	static const std::vector<double> scales;
	inline static const Coordinate midPoint() {
		return Coordinate(Width / 2, Height / 2);
	}
	inline Board() :origin(midPoint()), scaleNum(2), scale(scales[2]),
		gridWidth(GridLength), gridHeight(GridLength), blocks(), lines() {
	}
	Coordinate origin;
	int scaleNum;
	double scale;
	Length gridWidth, gridHeight;
	std::unordered_map<GridCoordinate, Block> blocks;
	std::unordered_map<GridCoordinate, Line> lines;
	std::vector<Button> buttons;
	inline TrueCoordinate trueCoordinate(Coordinate C) {
		return origin + ySymmetry(scale * C);
	}
	inline TrueLength trueLength(Length l) {
		return scale * l;
	}
	inline void setOrigin(Coordinate o) {
		origin = o;
	}
	inline void moveOrigin(Coordinate c) {
		origin += c;
	}
	inline void multiplyScale(double s) {
		origin = s * (origin - midPoint()) + midPoint();
		scale *= s;
	}
	inline void setScale(double s) {
		multiplyScale(s / scale);
	}
	inline void addScale() {
		if (scaleNum < scales.size() - 1) {
			scaleNum++;
			scale = scales[scaleNum];
		}
	}
	inline void minusScale() {
		if (scaleNum > 0) {
			scaleNum--;
			scale = scales[scaleNum];
		}
	}
	inline Coordinate gridPointCoordinate(int x, int y) {
		return Coordinate(gridWidth * x, gridHeight * y);
	}
	inline Coordinate gridPointCoordinate(GridCoordinate gridPos) {
		return Coordinate(gridWidth * gridPos.x, gridHeight * gridPos.y);
	}
	inline Coordinate gridPointTrueCoordinate(int x, int y) {
		return trueCoordinate(gridPointCoordinate(x, y));
	}
	inline Coordinate gridPointTrueCoordinate(GridCoordinate gridPos) {
		return trueCoordinate(gridPointCoordinate(gridPos));
	}
	inline bool inBoard(TrueCoordinate C) {
		return C.x > 0 && C.x < Width && C.y > 0 && C.y < Height;
	}
	inline RECT buttonPosition(int x, int y) {
		return {
			(int)(ButtonWidthSpacing + (ButtonWidth + ButtonWidthSpacing) * x),
			(int)(ButtonHeightSpacing + (ButtonHeight + ButtonHeightSpacing) * y),
			(int)((ButtonWidth + ButtonWidthSpacing) * (x + 1)),
			(int)((ButtonHeight + ButtonHeightSpacing) * (y + 1))
		};
	}
	inline RECT buttonPosition(ButtonCoordinate buttonPos) {
		return buttonPosition(buttonPos.x, buttonPos.y);
	}
	inline bool inBoard(GridCoordinate C) {
		return inBoard(gridPointTrueCoordinate(C));
	}
	template <class someCoordinate>
	inline RECT Rect(someCoordinate C1, someCoordinate C2) {
		return { (long)C1.x, (long)C1.y, (long)C2.x, (long)C2.y };
	}
	inline GridCoordinate mouseGrid(const ExMessage& mouseMsg) {
		return GridCoordinate((int)floor((mouseMsg.x - origin.x) / (scale * gridWidth)),
			(int)floor((origin.y - mouseMsg.y) / (scale * gridHeight)));
	}
	inline GridCoordinate getMouseGrid(std::function<bool(const ExMessage&)> exitCondition) {
		while (1) {
			ExMessage mouseMsg;
			peekmessage(&mouseMsg, EX_MOUSE);
			GridCoordinate pos = mouseGrid(mouseMsg);
			if (exitCondition(mouseMsg)) return NoGrid;
			if (inBoard(pos) && mouseMsg.lbutton) return pos;
		}
	}
	inline std::wstring getText(LPCTSTR pPrompt, LPCTSTR pTitle, LPCTSTR pDefault,
		std::function<bool(std::wstring)> isAcceptable) {
		while (1) {
			wchar_t str[128];
			bool inputted = InputBox(str, 128, pPrompt, pTitle, pDefault, 0, 0, false);
			if (!inputted) return NoInput;
			if (isAcceptable(str)) return str;
		}
	}
	inline bool isBlockType(std::wstring type) {
		return true;
	}
	static void line(Coordinate, Coordinate);
	void init();
	void initButtons();
	void drawOrigin();
	void drawGrid();
	void drawBlocks();
	void drawLines();
	void drawButtons();
	void flushButtons();
	void tickTest();
	void draw();
	void flush();
	void tick();
};
