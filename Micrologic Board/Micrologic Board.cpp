#include <iostream>

#include "Board.h"

extern bool end;

void test(Board& board) {
#ifdef BOARD_DEBUG
	board.blocks.insert({ GridCoordinate(0, 0), Block(L"B") });

	board.lines.insert({ GridCoordinate(2, -2), Line(0, Line::INPUT, Line::INPUT, Line::INPUT, Line::INPUT) });
	board.lines.insert({ GridCoordinate(2, -0), Line(1, Line::OUTPUT, Line::OUTPUT, Line::OUTPUT, Line::OUTPUT) });
	board.lines.insert({ GridCoordinate(2, 2), Line({ 1, 0, 0, 1 }, Line::INPUT, Line::OUTPUT, Line::NONE, Line::NONE) });
	board.lines.insert({ GridCoordinate(0, 2), Line({ 1, 1, 1, 0 }, Line::NONE, Line::OUTPUT, Line::OUTPUT, Line::OUTPUT) });
	board.lines.insert({ GridCoordinate(-3, 0), Line(0, Line::OUTPUT, Line::OUTPUT, Line::OUTPUT, Line::OUTPUT) });
#endif
}

int main() {
	Board board;
	board.init();
	test(board);
	while (1) {
		board.draw();
		if (end) break;
	}
	return 0;
}