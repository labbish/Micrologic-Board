#pragma once

#include <cmath>
#include <string>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <compare>
#include <functional>
#include <easyx.h>

#include "Micrologic/Blocks.h"

#ifdef BOARD_DEBUG
#include <cstdio>
#endif

inline void solidrectangle(RECT r) {
	solidrectangle(r.left, r.top, r.right, r.bottom);
}

inline void fillrectangle(RECT r) {
	fillrectangle(r.left, r.top, r.right, r.bottom);
}