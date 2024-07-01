//
// Created by jonas on 13.12.23.
//
#include "vertex.h"
#include <utility>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "cmath"

using namespace std;

vertex::vertex(double x, double y, std::string name): xy(x, y), name(std::move(name)){};

