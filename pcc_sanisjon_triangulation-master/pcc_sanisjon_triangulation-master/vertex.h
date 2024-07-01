//
// Created by jonas on 28.12.23.
//

#ifndef TRIANGULATION_VERTEX_H
#define TRIANGULATION_VERTEX_H

#include <utility>
#include <string>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "cmath"
using namespace std;
class vertex {
private:
    std::pair<double, double> xy;
    std::string name;
    bool is_pivot = false;
    bool is_end = false;

public:
    vertex() = default;

    vertex(double x, double y, std::string name);

    void setIsPivot(bool isPivot){
        is_pivot = isPivot;

    }
    void setIsEnd(bool isEnd){
        is_end = isEnd;
    }

    const pair<double, double> &getXy() const{
        return xy;
    }

    const string &getName() const{
        return name;
    }


    bool operator==(const vertex &other) const{
        return xy == other.xy && name == other.name;

    }

    friend std::ostream &operator<<(std::ostream &out, const vertex &v){
        double x = v.xy.first;
        double y = v.xy.second;

        if (v.is_pivot or v.is_end){
            out << "<circle cx=\"" << x*100 << "\" cy=\"" << y*-100 << R"(" r="10" )";
            out << "stroke=\"" << "#0026CA" << R"(" stroke-width="2" fill="#84FFFF" />)" << std::endl;
            out << "<text x=\"" << x*100 << "\" y=\"" << y*-100 + 3 << R"(" text-anchor="middle" font-size="12" font-weight="bold">)";
            out << v.name << "</text>\n";
            return out;
        }

        out << "<circle cx=\"" << x*100 << "\" cy=\"" << y*-100 << R"(" r="10" )";
        out << "stroke=\"" << "Black" << R"(" stroke-width="2" fill="white" />)" << std::endl;
        out << "<text x=\"" << x*100 << "\" y=\"" << y*-100 + 3 << R"(" text-anchor="middle" font-size="12" font-weight="bold">)";
        out << v.name << "</text>\n";
        return out;
    }


};
#endif //TRIANGULATION_VERTEX_H
