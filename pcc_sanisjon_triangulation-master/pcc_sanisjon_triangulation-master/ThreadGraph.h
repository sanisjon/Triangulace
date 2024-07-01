//
// Created by jonas on 31.12.23.
//

#ifndef TRIANGULATION_THREADGRAPH_H
#define TRIANGULATION_THREADGRAPH_H
#include <vector>
#include <iostream>
#include "vertex.h"
#include "triangle.h"


class ThreadGraph {
private:
    vector<vertex> vertices;

    vector<triangle> higher_triangles;
        size_t num_of_lower_triangles = 0;

    vector<triangle> lower_triangles;
        size_t num_of_higher_triangles = 0;

    vector<vertex> higher_chain;
    vector<vertex> lower_chain;

    size_t num_of_vertices = 0;
    double area = 0;

    vertex* pivot{};
    vertex* end{};
    vertex* top{};
    vertex* bottom{};


    const string dark_green = "#21FF00";
    const string dark_red = "#FF0000";
    const string light_blue = "#00F5FF";

    const char* redText = "\033[1;31m";
    const char* reset = "\033[0m";

    const char* greenBc = "\033[3;42;30m";
    const char* greenBCUnde = "\033[4;42;30m";
    const char* greenTextUnde = "\033[4;32m";

    const char* grayBC = "";
    const char* grayBCgreenText = "\033[0;32m";

public:

    [[nodiscard]] const vector<vertex> &getVertices() const;

    [[nodiscard]] double getArea() const;

public:



    explicit ThreadGraph() = default;

    /*
     * Pridat vertex do grafu;
     */
    void add_vertex(double x, double y);

    /*
     * Prida vertexy do grafu z vectoru paru
     */
    void add_vertex_list(const vector<pair<double,double>>& vxs);

    void add_triangle(vertex* v1, vertex* v2, vertex* v3);

    void add_triangle_to_higher(vertex* v1, vertex* v2, vertex* v3);
    void add_triangle_to_lower(vertex* v1, vertex* v2, vertex* v3);



    /*
     * Zjisti, zda je graf prazdny, tj. neobsahuje zadne vrcholy
     */
    [[nodiscard]] bool empty() const;

    /*
     * Vrati pocet vrcholu grafu
     */
    [[nodiscard]] size_t size() const;

    void clear();

    /*
     * nalezne pivotni prvek grafu
     * predpokladame ze nenalezneme na y ose dva potencionalni pivotni prvky
     */

    vertex* get_pivot();
    vertex* get_end();
    vertex* get_top();
    vertex* get_bottom();

    /*
     * Rozdeli polygon na dva chainy
     */
    void separate_high_low();
        /*
         * do higher a lower chain přidá takové dva vrcholy, které jsou X souřadnicí
         * shodné s pivotními body a jejich Y složka je nižší než nejnižšího vhrcholu polygonu
         */
        void alternate_chains();

    static bool is_convex(vertex& v1, vertex& v2, vertex& v3 );
    static double get_cos_A(pair<double,double> v1, pair<double,double> v3);
    static double norm(pair<double,double> v);
    static double dot_product(pair<double,double> v1, pair<double,double> v2);

    bool dont_contains(vertex& v1, vertex& v2, vertex& v3, vector<vertex>& inputVector) const;

    static bool is_point_inside_triangle(const vertex& point, const vertex& v1, const vertex& v2, const vertex& v3) ;

    void exclude_vertex();
    static vertex get_next(int i, const vector<vertex>& vec );
    static vertex get_prev(int i, const vector<vertex>& vec);
    static bool is_in_line(vertex& v1, vertex& v2, vertex&);

    /*
     * Zde probíhá paralelní triangulace modifikovaných chinů, které po void alternate_chains()
     * tvoří samstatné polygony.
     * Process výpočtu obsahu obou je také asynchoní, navazuje po triangulaci danného chainu
     */
    void triangulate();
        vector<vertex> removeElementAtIndex(const vector<vertex>& inputVector, int index);
        double Proces(const vector<pair<double,double>>& vxs);
        double calculate_area(vector<triangle>& inputVector);

    void triangulate_higher_chain();
        double triangulate_higher_chain_async();

    void triangulate_lower_chain();
        double triangulate_lower_chain_async();







    /*
     * Operator zapisu do proudu
     */
    friend std::ostream& operator<<(std::ostream& out, const ThreadGraph& g) {
        /*
        * V pripade prazdneho grafu
        */
        if (g.empty()){
            out << R"(<svg viewBox="-150 -150 300 300" xmlns='http://www.w3.org/2000/svg'>)"<<endl;
            out << R"(<rect x="-100" y="-20" width="200" height="40" fill="lightgray" stroke="black" stroke-width="2" />)"<<endl;
            out << R"(<text x="0" y="0" text-anchor="middle" dy="8" font-size="12" fill="black">Empty Graph</text>)"<<endl;
            out << R"(</svg>)" << std::endl;
            return out;
        }

        double min_X = -100;
        double min_Y = (abs(g.top->getXy().second*100)+100)*-1;
        double max_X = abs(g.end->getXy().first*110)+abs(min_X);
        double max_Y = 2* min_Y * -1;


        out << "<svg viewBox=\"" << min_X << " "<< min_Y<<" "<< max_X<<" "<< max_Y<<  "\" xmlns='http://www.w3.org/2000/svg'>"<<endl;
//        out << "<rect x=\"" << min_X << "\" y=\"" << min_Y << "\" width=\"" << max_X - min_X << "\" height=\"" << max_Y - min_Y << "\" fill=\"#CFD8DC\" />";

        out << "<line x1=\"" << min_X << "\" y1=\"" << 0 << "\" x2=\"" << max_X << "\" y2=\"" << 0 << "\" stroke=\"" << "#263238" << "\" stroke-width=\"3\" stroke-dasharray=\"8,10\" />\n";
        out << "<line x1=\"" << 0 << "\" y1=\"" << min_Y << "\" x2=\"" << 0 << "\" y2=\"" << max_Y << "\" stroke=\"" << "#263238" << "\" stroke-width=\"3\" stroke-dasharray=\"8,10\" />\n";

        if(!g.higher_triangles.empty()){
            for (const auto& t: g.higher_triangles) {
                out << t;
            }
        }

        if(!g.lower_chain.empty()){out << chain_writer(g.lower_chain);}

        out << "<line x1=\"" << min_X << "\" y1=\"" << 0 << "\" x2=\"" << max_X << "\" y2=\"" << 0 << "\" stroke=\"" << "#263238" << "\" stroke-width=\"3\" stroke-dasharray=\"8,10\" />\n";
        out << "<line x1=\"" << 0 << "\" y1=\"" << min_Y << "\" x2=\"" << 0 << "\" y2=\"" << max_Y << "\" stroke=\"" << "#263238" << "\" stroke-width=\"3\" stroke-dasharray=\"8,10\" />\n";

        if(!g.lower_triangles.empty()){
            for (auto t: g.lower_triangles) {
                t.set_red();
                out << t;
            }
        }





        if (!g.higher_chain.empty()){
            for (size_t vx = 0; vx < g.higher_chain.size(); ++vx) {
                if(vx+1==g.higher_chain.size()) break;

                std::pair<double, double> vv = g.higher_chain[vx].getXy();
                out << "<line x1=\"" << vv.first * 100 << "\" y1=\"" << vv.second * -100 << "\" ";
                vv = g.higher_chain[vx+1].getXy();
                out << "x2=\"" << vv.first*100 << "\" y2=\"" << vv.second*-100 << "\" stroke=\"" << "blue" << "\" stroke-width=\"2\" />\n";
            }
//            FROM A to B
            out << "<line x1=\"" << g.higher_chain[0].getXy().first * 100 << "\" y1=\"" << g.higher_chain[0].getXy().second * -100
                << "\" x2=\"" << g.higher_chain[g.higher_chain.size()-1].getXy().first * 100
                << "\" y2=\"" << g.higher_chain[g.higher_chain.size()-1].getXy().second * -100 << "\" stroke=\"" << "green" << "\" stroke-width=\"2\" />\n";

            for (const auto& vx: g.higher_chain)
                out << vx;
        }
        if (!g.lower_chain.empty()){
            for (size_t vx = 0; vx < g.lower_chain.size(); ++vx) {
                if(vx+1==g.lower_chain.size()) break;

                std::pair<double, double> vv = g.lower_chain[vx].getXy();
                out << "<line x1=\"" << vv.first * 100 << "\" y1=\"" << vv.second * -100 << "\" ";
                vv = g.lower_chain[vx+1].getXy();
                out << "x2=\"" << vv.first*100 << "\" y2=\"" << vv.second*-100 << "\" stroke=\"" << "red" << "\" stroke-width=\"2\" />\n";
            }

//            FROM A to B
            out << "<line x1=\"" << g.lower_chain[0].getXy().first * 100 << "\" y1=\"" << g.lower_chain[0].getXy().second * -100
                << "\" x2=\"" << g.lower_chain[g.lower_chain.size()-1].getXy().first * 100
                << "\" y2=\"" << g.lower_chain[g.lower_chain.size()-1].getXy().second * -100 << "\" stroke=\"" << "green" << "\" stroke-width=\"2\" />\n";

            for (const auto& vx: g.lower_chain)
                out << vx;
        }

        out << *g.pivot;
        out << *g.end;

        out << R"(</svg>)" << std::endl;
        return out;
    };
        static string chain_writer(const vector<vertex>& vertices) {
        std::string out = "<polygon points=\"";
        for (const auto& v : vertices) {
            out += std::to_string(v.getXy().first * 100) + "," + std::to_string(v.getXy().second * -100) + " ";
        }
        out += "\" ";
        out += R"(stroke="CFD8DC" stroke-width="1" )";
        out += "fill= \" white \"  fill-opacity=\"1\" />\n";
        return out;
    }
    /*
     * Zapis do SVG souboru
     */
    static void save_graph(ThreadGraph& g) {
        std::ofstream f("t_image.svg");
        f << g;
        f.close();
    }
};


#endif //TRIANGULATION_THREADGRAPH_H
