//
// Created by jonas on 1.1.24.
//
#ifndef TRIANGULATION_TRIANGLE_H
#define TRIANGULATION_TRIANGLE_H

#include "vertex.h"
#include <iostream>
#include <utility>
using namespace std;

class triangle {
private:
    int name = 0;

    vertex v1;
    vertex v2;
    vertex v3;


    const string green = "#5EFC82";
    const string dark_green = "#00C853";
    const string ultra_dark_green = "#009624";

    const string red = "#FFFFFF";
    const string dark_red = "#FAFAFA";
    const string ultra_dark_red = "#F5F5F5";

    string color;
    string line = "black";

public:

    triangle(vertex v1, vertex v2, vertex v3, int c) : v1(std::move(v1)), v2(std::move(v2)), v3(std::move(v3)) {
        name = c;

        if (c % 3 == 0) {
            color = green;
        } else if (c % 3 == 1) {
            color = dark_green;
        } else {
            color = ultra_dark_green;
        }
    }
    /*
     * Pomocné funkce pro lepší vizualizaci
     */
    void set_red(){
        line = "#D50000";
       color = "#CFD8DC";

    }
    bool has_vertices(const vertex *_v1, const vertex *_v2, const vertex *_v3) const {
        return v1 == *_v1 && v2 == *_v2 && v3 == *_v3;
    }

    /*
     * Vypočítá vlastní obsah
     */
    double calculate_area_of_triangle() {
        double x1 = v1.getXy().first;
        double y1 = v1.getXy().second;
        double x2 = v2.getXy().first;
        double y2 = v2.getXy().second;
        double x3 = v3.getXy().first;
        double y3 = v3.getXy().second;

        return 0.5 * abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)));

    }

    friend std::ostream& operator<<(std::ostream& out, const triangle& t) {
        out << "<polygon points=\"";
        out << t.v1.getXy().first * 100 << "," << t.v1.getXy().second * -100 << " ";
        out << t.v2.getXy().first * 100 << "," << t.v2.getXy().second * -100 << " ";
        out << t.v3.getXy().first * 100 << "," << t.v3.getXy().second * -100 << "\" ";

        out << R"(stroke-width="1" stroke-dasharray="3,2" )";

        out << " stroke=\""<<t.line<<" \" fill=\""<<t.color<<" \" fill-opacity=\"0.8\" />\n" << std::endl;

        return out;
    }

};

#endif //TRIANGULATION_TRIANGLE_H
