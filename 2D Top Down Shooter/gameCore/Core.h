#pragma once

#ifdef GAMECOREDLL_EX
#define GAMECOREDLL_EX __declspec(dllexport)

#else
#define GAMECOREDLL_EX __declspec(dllimport)

#endif

#include <HyperBase.h>
#include <vector>
#include "vec2.h"

double GetAngle(int x1, int y1, int x2, int y2, int _angle);
