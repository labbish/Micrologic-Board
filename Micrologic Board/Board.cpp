#include "Board.h"

bool end = false;

const std::vector<double> Board::scales = { 1.0 / 2, 2.0 / 3, 1, 1.5, 2 };

void Board::init() {
	initgraph((int)Width, (int)Height);
	setbkcolor(BkColor);
	cleardevice();
	initButtons();
	BeginBatchDraw();
}

void Board::initButtons() {
	//[0]:up
	std::function<void(const Button*)> upText = [this](const Button* button) {
		setlinecolor(TextColor);
		setlinestyle(PS_SOLID, 1);
		::line((int)(0.5 * button->area.left + 0.5 * button->area.right), (int)(0.8 * button->area.top + 0.2 * button->area.bottom),
			(int)(0.5 * button->area.left + 0.5 * button->area.right), (int)(0.2 * button->area.top + 0.8 * button->area.bottom));
		::line((int)(0.5 * button->area.left + 0.5 * button->area.right), (int)(0.8 * button->area.top + 0.2 * button->area.bottom),
			(int)(0.2 * button->area.left + 0.8 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom));
		::line((int)(0.5 * button->area.left + 0.5 * button->area.right), (int)(0.8 * button->area.top + 0.2 * button->area.bottom),
			(int)(0.8 * button->area.left + 0.2 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom));
		};
	buttons.push_back(Button(buttonPosition(1, 0), ButtonColor, L"", upText));
	//[1]:down
	std::function<void(const Button*)> downText = [this](const Button* button) {
		setlinecolor(TextColor);
		setlinestyle(PS_SOLID, 1);
		::line((int)(0.5 * button->area.left + 0.5 * button->area.right), (int)(0.8 * button->area.top + 0.2 * button->area.bottom),
			(int)(0.5 * button->area.left + 0.5 * button->area.right), (int)(0.2 * button->area.top + 0.8 * button->area.bottom));
		::line((int)(0.2 * button->area.left + 0.8 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom),
			(int)(0.5 * button->area.left + 0.5 * button->area.right), (int)(0.2 * button->area.top + 0.8 * button->area.bottom));
		::line((int)(0.8 * button->area.left + 0.2 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom),
			(int)(0.5 * button->area.left + 0.5 * button->area.right), (int)(0.2 * button->area.top + 0.8 * button->area.bottom));
		};
	buttons.push_back(Button(buttonPosition(1, 2), ButtonColor, L"", downText));
	//[2]:left
	std::function<void(const Button*)> leftText = [this](const Button* button) {
		setlinecolor(TextColor);
		setlinestyle(PS_SOLID, 1);
		::line((int)(0.8 * button->area.left + 0.2 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom),
			(int)(0.2 * button->area.left + 0.8 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom));
		::line((int)(0.8 * button->area.left + 0.2 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom),
			(int)(0.5 * button->area.left + 0.5 * button->area.right), (int)(0.2 * button->area.top + 0.8 * button->area.bottom));
		::line((int)(0.8 * button->area.left + 0.2 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom),
			(int)(0.5 * button->area.left + 0.5 * button->area.right), (int)(0.8 * button->area.top + 0.2 * button->area.bottom));
		};
	buttons.push_back(Button(buttonPosition(0, 1), ButtonColor, L"", leftText));
	//[3]:right
	std::function<void(const Button*)> rightText = [this](const Button* button) {
		setlinecolor(TextColor);
		setlinestyle(PS_SOLID, 1);
		::line((int)(0.8 * button->area.left + 0.2 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom),
			(int)(0.2 * button->area.left + 0.8 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom));
		::line((int)(0.5 * button->area.left + 0.5 * button->area.right), (int)(0.2 * button->area.top + 0.8 * button->area.bottom),
			(int)(0.2 * button->area.left + 0.8 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom));
		::line((int)(0.5 * button->area.left + 0.5 * button->area.right), (int)(0.8 * button->area.top + 0.2 * button->area.bottom),
			(int)(0.2 * button->area.left + 0.8 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom));
		};
	buttons.push_back(Button(buttonPosition(2, 1), ButtonColor, L"", rightText));
	//[4]:end
	std::function<void(const Button*)> endText = [this](const Button* button) {
		setlinecolor(TextColor);
		setlinestyle(PS_SOLID, 1);
		::line((int)(0.8 * button->area.left + 0.2 * button->area.right), (int)(0.8 * button->area.top + 0.2 * button->area.bottom),
			(int)(0.2 * button->area.left + 0.8 * button->area.right), (int)(0.2 * button->area.top + 0.8 * button->area.bottom));
		::line((int)(0.8 * button->area.left + 0.2 * button->area.right), (int)(0.2 * button->area.top + 0.8 * button->area.bottom),
			(int)(0.2 * button->area.left + 0.8 * button->area.right), (int)(0.8 * button->area.top + 0.2 * button->area.bottom));
		};
	buttons.push_back(Button({ (long)(Width - 40), (long)(Height - 40), (long)(Width - 10), (long)(Height - 10) }, EndButtonColor, L"", endText));
	//[5]:tick
	buttons.push_back(Button(buttonPosition(1, 1), ButtonColor, L"Tick"));
	//[6]:add
	std::function<void(const Button*)> addText = [this](const Button* button) {
		setlinecolor(TextColor);
		setlinestyle(PS_SOLID, 1);
		::line((int)(0.5 * button->area.left + 0.5 * button->area.right), (int)(0.8 * button->area.top + 0.2 * button->area.bottom),
			(int)(0.5 * button->area.left + 0.5 * button->area.right), (int)(0.2 * button->area.top + 0.8 * button->area.bottom));
		::line((int)(0.8 * button->area.left + 0.2 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom),
			(int)(0.2 * button->area.left + 0.8 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom));
		};
	buttons.push_back(Button(buttonPosition(0, 0), ButtonColor, L"", addText));
	//[7]:minus
	std::function<void(const Button*)> minusText = [this](const Button* button) {
		setlinecolor(TextColor);
		setlinestyle(PS_SOLID, 1);
		::line((int)(0.8 * button->area.left + 0.2 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom),
			(int)(0.2 * button->area.left + 0.8 * button->area.right), (int)(0.5 * button->area.top + 0.5 * button->area.bottom));
		};
	buttons.push_back(Button(buttonPosition(2, 0), ButtonColor, L"", minusText));
	//[8]:block
	std::function<void(const Button*)> blockText = [this](const Button* button) {
		RECT r = { (int)(0.9 * button->area.left + 0.1 * button->area.right), (int)(0.9 * button->area.top + 0.1 * button->area.bottom),
			(int)(0.1 * button->area.left + 0.9 * button->area.right), (int)(0.1 * button->area.top + 0.9 * button->area.bottom) };
		BlockModel(L"B").draw(r);
		};
	std::function<void(const Button*)> blockOnText = [this](const Button* button) {
		RECT r = { (int)(0.9 * button->area.left + 0.1 * button->area.right), (int)(0.9 * button->area.top + 0.1 * button->area.bottom),
			(int)(0.1 * button->area.left + 0.9 * button->area.right), (int)(0.1 * button->area.top + 0.9 * button->area.bottom) };
		BlockModel(L"B", BlockOnColor).draw(r);
		};
	buttons.push_back(Button(buttonPosition(0, 2), ButtonColor, L"", blockText, blockOnText));
	//[9]:line
	std::function<void(const Button*)> lineText = [this](const Button* button) {
		RECT r = { (int)(0.9 * button->area.left + 0.1 * button->area.right), (int)(0.9 * button->area.top + 0.1 * button->area.bottom),
			(int)(0.1 * button->area.left + 0.9 * button->area.right), (int)(0.1 * button->area.top + 0.9 * button->area.bottom) };
		LineModel(0, LineModel::CONNECT, LineModel::CONNECT, LineModel::CONNECT, LineModel::CONNECT).draw(r);
		};
	std::function<void(const Button*)> lineOnText = [this](const Button* button) {
		RECT r = { (int)(0.9 * button->area.left + 0.1 * button->area.right), (int)(0.9 * button->area.top + 0.1 * button->area.bottom),
			(int)(0.1 * button->area.left + 0.9 * button->area.right), (int)(0.1 * button->area.top + 0.9 * button->area.bottom) };
		LineModel(1, LineModel::CONNECT, LineModel::CONNECT, LineModel::CONNECT, LineModel::CONNECT).draw(r);
		};
	buttons.push_back(Button(buttonPosition(0, 3), ButtonColor, L"", lineText, lineOnText));
	//[10]:wide line
	std::function<void(const Button*)> wlineText = [this](const Button* button) {
		RECT r = { (int)(0.9 * button->area.left + 0.1 * button->area.right), (int)(0.9 * button->area.top + 0.1 * button->area.bottom),
			(int)(0.1 * button->area.left + 0.9 * button->area.right), (int)(0.1 * button->area.top + 0.9 * button->area.bottom) };
		LineModel({ 0, 0, 0, 0 }, LineModel::CONNECT, LineModel::CONNECT, LineModel::CONNECT, LineModel::CONNECT).draw(r);
		};
	std::function<void(const Button*)> wlineOnText = [this](const Button* button) {
		RECT r = { (int)(0.9 * button->area.left + 0.1 * button->area.right), (int)(0.9 * button->area.top + 0.1 * button->area.bottom),
			(int)(0.1 * button->area.left + 0.9 * button->area.right), (int)(0.1 * button->area.top + 0.9 * button->area.bottom) };
		LineModel({ 1, 1, 1, 1 }, LineModel::CONNECT, LineModel::CONNECT, LineModel::CONNECT, LineModel::CONNECT).draw(r);
		};
	buttons.push_back(Button(buttonPosition(1, 3), ButtonColor, L"", wlineText, wlineOnText));
}

void Board::line(Coordinate C1, Coordinate C2) {
	::line((int)C1.x, (int)C1.y, (int)C2.x, (int)C2.y);
}

void Board::drawOrigin() {
	setfillcolor(BLUE);
	setfillstyle(BS_SOLID);
	solidcircle((int)origin.x, (int)origin.y, 3);
}

void Board::drawGrid() {
	int minX = (int)ceil(-origin.x / (gridWidth * scale));
	int maxX = (int)floor((Width - origin.x) / (gridWidth * scale));
	int minY = (int)ceil((origin.y - Height) / (gridHeight * scale));
	int maxY = (int)floor(origin.y / (gridHeight * scale));
	setlinecolor(GridLineColor);
	setlinestyle(PS_SOLID, 1);
	for (int x = minX; x <= maxX; x++) {
		line(gridPointTrueCoordinate(x, minY - 1), gridPointTrueCoordinate(x, maxY + 1));
	}
	for (int y = minY; y <= maxY; y++) {
		line(gridPointTrueCoordinate(minX - 1, y), gridPointTrueCoordinate(maxX + 1, y));
	}
}

void Board::drawBlocks() {
	for (const std::pair<GridCoordinate, Block>& blockPos : blocks) {
		GridCoordinate pos = blockPos.first;
		Block block = blockPos.second;
		block.draw(Rect(gridPointTrueCoordinate(pos), gridPointTrueCoordinate(pos + GridCoordinate(1, 1))));
	}
}

void Board::drawLines() {
	for (const std::pair<GridCoordinate, Line>& linePos : lines) {
		GridCoordinate pos = linePos.first;
		Line line = linePos.second;
		line.draw(Rect(gridPointTrueCoordinate(pos), gridPointTrueCoordinate(pos + GridCoordinate(1, 1))));
	}
}

void Board::drawButtons() {
	for (const Button& button : buttons) {
		button.draw();
	}
	ExMessage mouseMsg;
	peekmessage(&mouseMsg, EX_MOUSE);
	for (int i = 0; i < buttons.size(); i++) {
		if (mouseMsg.lbutton) {
			GridCoordinate grid = mouseGrid(mouseMsg);
			if (inBoard(grid)) {
				grid.print();
				printf("\n");
			}
		}
		if (buttons[i].flushStatus(mouseMsg) == Button::CLICKED) {
			switch (i) {
			case 0:moveOrigin(Coordinate(0, -20)); break;
			case 1:moveOrigin(Coordinate(0, 20)); break;
			case 2:moveOrigin(Coordinate(-20, 0)); break;
			case 3:moveOrigin(Coordinate(20, 0)); break;
			case 4:end = true; break;
			case 5:/*tick*/ break;
			case 6:addScale(); break;
			case 7:minusScale(); break;
			case 8:break;
			case 9:break;
			case 10:break;
			}
		}
	}
}

void Board::drawTest() {
#ifdef BOARD_DEBUG
	lines[GridCoordinate(-3, 0)].value = !lines[GridCoordinate(-3, 0)].value;
#endif
}

void Board::draw() {
	cleardevice();

	drawOrigin();
	drawGrid();
	drawTest();
	drawBlocks();
	drawLines();
	drawButtons();

	FlushBatchDraw();
}