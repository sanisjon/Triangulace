//
// Created by jonas on 13.12.23.
//

#ifndef TRIANGULATION_GRAPH_H
#define TRIANGULATION_GRAPH_H
#include <vector>
#include <iostream>
#include "vertex.h"
#include "triangle.h"
using namespace std;

/*
 * Graf prijima vector pair<doubke,double> v poradi smeru hodinovych rucicek,
 * musi vzdy yacinat pivotem s nejnizsi hodnotou X
 */

class Graph {
private:
    vector<vertex> vertices;
    vector<triangle> triangles;

    size_t num_of_vertices = 0;
    size_t num_of_triangles = 0;

    double area = 0;

    vertex* pivot{};
    vertex* end{};
    vertex* top{};

    const string dark_green = "#21FF00";
    const string dark_red = "#FF0000";
    const string light_blue = "#00F5FF";

    const char* redText = "\033[1;31m";
    const char* reset = "\033[0m";

    const char* blueBc = "\033[3;46;30m";
    const char* blueBcUnde = "\033[4;46;30m";
    const char* blueTextUnde = "\033[4;36m";

    const char* grayBC = "";
    const char* grayBCbluueText ="\033[0;36m";



public:

    [[nodiscard]] const vector<vertex> &getVertices() const;

    [[nodiscard]] double getArea() const;

public:

    explicit Graph() = default;


    /*
     * Pridat vertex do grafu;
     */
    void add_vertex(double x, double y);

    /*
     * Prida vertexy do grafu z vectoru paru
     */
    void add_vertex_list(const vector<pair<double,double>>& vxs);
    void add_triangle(vertex* v1, vertex* v2, vertex* v3);

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


    /*
     * Rozdeli polygon na dva chainy dle krajních pivotních bodů
     */
    void separate_high_low();

    /*
     * Ověří že je úhel u v2 tvořený dvěma vectory v1 v3 s počátkem ve v2 je koncexní
     */
    static bool is_convex(vertex& v1, vertex& v2, vertex& v3 );
//        Matematické operátory pro práci s vectory
        static double get_cos_A(pair<double,double> v1, pair<double,double> v3);
            static double norm(pair<double,double> v);
            static double dot_product(pair<double,double> v1, pair<double,double> v2);

    /*
     * Zjistí zada-li se v trojuhelníku nenachází jiný vrchol náležící polygonu
     */
    static bool dont_contains(vertex& v1, vertex& v2, vertex& v3, vector<vertex>& inputVector) ;
        static bool is_point_inside_triangle(const vertex& point, const vertex& v1, const vertex& v2, const vertex& v3) ;

    /*
     * Vyřadí vrcholy polzgonu, které se tvoří úsečku a ponechá pouze krajní vrcholy
     * pro zjednodušení procesu triangulace
     */
    void exclude_vertex();
        static vertex get_next(int i, const vector<vertex>& vec );
        static vertex get_prev(int i, const vector<vertex>& vec);
        static bool is_in_line(vertex& v1, vertex& v2, vertex&);

        /*
         * Provádí triangulaci poolygonu dle algoritmu
         */
    void triangulate();
        /*
         * Odstraní vrchol ze seznamu a vrátí pozměněný seznam
         */
        static vector<vertex> removeElementAtIndex(const std::vector<vertex>& inputVector, int index);
        /*
         * Vrátí sumu všech vztvořených triangle
         */
        void calculate_area();

    /*
     * Kompletní proces triangulace ze vstupu
     */
    double Process(const vector<pair<double,double>>& vxs);











    /*
     * Operator zapisu do proudu
     * Vytvoří .svg soubor s vozualizací triangulovaného polygonu.
     */
    friend std::ostream& operator<<(std::ostream& out, const Graph& g) {
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

        out << "<line x1=\"" << min_X << "\" y1=\"" << 0 << "\" x2=\"" << max_X << "\" y2=\"" << 0 << "\" stroke=\"" << "white" << "\" stroke-width=\"2\" stroke-dasharray=\"5,5\" />\n";
        out << "<line x1=\"" << 0 << "\" y1=\"" << min_Y << "\" x2=\"" << 0 << "\" y2=\"" << max_Y << "\" stroke=\"" << "white" << "\" stroke-width=\"2\" stroke-dasharray=\"5,5\" />\n";



        if(!g.triangles.empty()){
            for (const auto& t: g.triangles) {
                out << t;
            }
        }

        if(!g.vertices.empty()){

            for (size_t vx = 0; vx < g.vertices.size(); ++vx) {
                if(vx+1==g.vertices.size()) break;

                std::pair<double, double> vv = g.vertices[vx].getXy();
                out << "<line x1=\"" << vv.first * 100 << "\" y1=\"" << vv.second * -100 << "\" ";
                vv = g.vertices[vx+1].getXy();
                out << "x2=\"" << vv.first*100 << "\" y2=\"" << vv.second*-100 << "\" stroke=\"" << "blue" << "\" stroke-width=\"2\" />\n";
            }
            out << "<line x1=\"" << g.vertices[0].getXy().first * 100 << "\" y1=\"" << g.vertices[0].getXy().second * -100
                << "\" x2=\"" << g.vertices[g.size()-1].getXy().first * 100
                << "\" y2=\"" << g.vertices[g.size()-1].getXy().second * -100 << "\" stroke=\"" << "blue" << "\" stroke-width=\"2\" />\n";

            for (const auto& vx: g.vertices)
                out << vx;
        }



        out << *g.pivot;
        out << *g.end;

        out << R"(</svg>)" << std::endl;
        return out;
    };

    /*
     * Zapis do SVG souboru
     */
    static void save_graph(Graph& g) {
        std::ofstream f("image.svg");
        f << g;
        f.close();
    }

};


#endif //TRIANGULATION_GRAPH_H
