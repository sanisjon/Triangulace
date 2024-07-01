//
// Created by jonas on 2.1.24.
//
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "Graph.h"
#include "ThreadGraph.h"
#include "DataHelper.h"
#include <random>
#include <algorithm>
#include <iomanip>
#include "DataHelper.h"

using namespace std;
 const char* DataHelper::greenText = "\033[0;32m";
 const char* DataHelper::magentaText = "\033[0;35m";
 const char* DataHelper::blueText = "\033[1;36m";
 const char* DataHelper::reset = "\033[0m";
 const char* DataHelper::redText = "\033[1;31m";

const vector<vector<int>> DataHelper::Data = {{3,5,3},
                                         {10,10,5},
                                         {30,10,5},
                                         {50,10,5},
                                         {100,80,5},
                                         {300,80,5},
                                         {500,80,5},
                                         {1000,800,5},
                                         {3000,800,5},
                                         {5000,800,5},
                                         {10000,800,5},
                                         {30000,1000,5},
//                                         {50000,1000,5},
//                                         {100000,1000,5},
};

double DataHelper::get_random_double(int bottom, int top) {
    static mt19937 mt{ std::random_device{}() };
    static uniform_real_distribution<> dist(bottom, top);
    return dist(mt);
}
vector<pair<double, double>> DataHelper::create_random_polygon(int n, int top, int threshold) {
    if (n < 3){
        cout<<endl<<redText<<"Input N must be at least 3"<<endl<<reset;
        return {};
    }
    if (top < threshold){
        cout<<endl<<redText<<"Top must be greater than threshold"<<endl<<reset;
        return {};
    }
    if (top == 0 and threshold == 0){
        cout<<endl<<redText<<"Input Top  and threshold must not be 0 at same time"<<endl<<reset;
        return {};
    }

    vector<pair<double, double>> polygon;
    int break_point;

    if (n % 2 == 0) { break_point = n / 2; } else { break_point = (n + 1) / 2; }


    polygon.reserve(break_point);
    for (int i = 0; i < break_point; ++i) {
        polygon.emplace_back(i, get_random_double(threshold, top));
    }
    for (int i = 0; i < n - break_point; ++i) {
        polygon.emplace_back(break_point - i, -get_random_double(threshold, top));
    }
    return polygon;
}
vector<pair<double, double>> DataHelper::create_complex_polygon(int n, double r) {
    if (n < 3){
        cout<<endl<<redText<<"Input N must be at least 3"<<endl<<reset;
        return {};
    }
    if (r <= 0){
        cout<<endl<<redText<<"Input radius must be greater then 0"<<endl<<reset;
        return {};
    }
    std::vector<std::pair<double, double>> complexPolygon;

    for (int i = 0; i < n; ++i) {
        double x =r+0.5 + r * std::cos(2 * 3.14159265359 * i / -n);
        double y =r+0.5 + r * std::sin(2 * 3.14159265359 * i / n);
        complexPolygon.emplace_back(x, y);
    }

    reverse(complexPolygon.begin(),complexPolygon.end());
    return complexPolygon;
}




void DataHelper::START() {
    Graph g;
    ThreadGraph tg;


    vector<pair<double, double>> random_polygon;
    vector<pair<double, double>> complex_polygon;

    vector<pair<int, int>> results_random;
    vector<pair<int, int>> results_complex;





    for (auto inp: Data) {
        double result_random_standard = 0;
        double result_random_thread = 0;
        double result_complex_standard = 0;
        double result_complex_thread = 0;

        random_polygon = create_random_polygon(inp[0],inp[1],inp[2]);
        complex_polygon = create_complex_polygon(inp[0],inp[2]);

        cout<<" RANDOM POLYGON"<<endl;
        cout<<" Number of vertices: "<<magentaText<<inp[0]<<reset<<endl<<
            " Top = "<<magentaText<<inp[1]<<reset<<endl<<
            " Treshold = "<<magentaText<<inp[2]<<reset<<endl;
        cout<<" vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv"<<endl<<endl;


        cout<<blueText<<" STANDARD GRAPH"<<reset<<endl;
        result_random_standard = g.Process(random_polygon);
        cout<<endl<<endl;

        cout<<greenText<<" THREAD GRAPH"<<reset<<endl;
        result_random_thread = tg.Proces(random_polygon);
        cout<<endl<<endl;

        g.clear();
        tg.clear();






        cout<<" COMPLEX POLYGON"<<endl;
        cout<<" Number of vertices: "<<magentaText<<inp[0]<<reset<<endl<<
            " Radius = "<<magentaText<<inp[2]<<reset<<endl;
        cout<<" vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv"<<endl<<endl;

        cout<<blueText<<" STANDARD GRAPH"<<reset<<endl;
        result_complex_standard = g.Process(complex_polygon);
        cout<<endl<<endl;

        cout<<greenText<<" THREAD GRAPH"<<reset<<endl;
        result_complex_thread = tg.Proces(complex_polygon);
        cout<<endl;

        g.clear();
        tg.clear();

        results_random.emplace_back(result_random_standard,result_random_thread);
        results_complex.emplace_back(result_complex_standard,result_complex_thread);
        cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;

    }
    result_printer(results_random, results_complex);


}
    void DataHelper::result_printer(vector<pair<int, int>> results_random, vector<pair<int, int>> results_complex){
        int i = 0;
        cout <<endl<<endl<<endl<<setfill(' ')<< setw(20) << right<< "" << "RANDOM" << endl;
        cout <<setfill(' ') << setw(15) <<right <<""<<blueText<<"STANDARD" <<reset<<"/"<<greenText<< "THREAD" <<reset<< "\n";
        cout << setfill('-') << setw(45) << "" << setfill(' ') << "\n";

        for (const auto& pair : results_random) {
            cout << blueText << setw(7) << right << pair.first << reset << " ms" << setw(15) << right<< Data[i][0] << setw(20) << right << greenText << pair.second << reset << " ms" << "\n";
            i++;
        }
        i=0;
        cout <<endl<<endl<<endl<<setfill(' ')<< setw(20) << right<< "" << "COMPLEX" <<  endl;
        cout <<setfill(' ') << setw(15) <<right <<""<<blueText<<"STANDARD" <<reset<<"/"<<greenText<< "THREAD" <<reset<< "\n";
        cout << setfill('-') << setw(45) << "" << setfill(' ') << "\n"; // Separator line


        for (const auto& pair : results_complex) {
            cout << blueText << setw(7) << right << pair.first << reset << " ms" << setw(15) << right<< Data[i][0] << setw(20) << right << greenText << pair.second << reset << " ms" << "\n";
            i++;
        }

    }

void DataHelper::CUSTOME(int N, int top, int threshold, int radius, bool R_C) {


    Graph g;
    ThreadGraph tg;

    vector<pair<double, double>> random_polygon;
    vector<pair<double, double>> complex_polygon;

    if (R_C){
        cout << "You chose to create a random polygon with " << N << " vertices, with a maximum absolute amplitude of " << top << " and a minimum of " << threshold << "."
             << "\nBelow, you can observe the statistics of the process." << endl << endl;

        cout<<" RANDOM POLYGON"<<endl;
        cout << " Number of vertices: " << magentaText << N << reset << endl <<
             " Top = " << magentaText << top << reset << endl <<
             " Treshold = " << magentaText << threshold << reset << endl;
        cout<<" vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv"<<endl<<endl;

        random_polygon = create_random_polygon(N, top, threshold);

        cout<<blueText<<" STANDARD GRAPH"<<reset<<endl;
        g.Process(random_polygon); Graph::save_graph(g);
        cout<<endl<<endl;

        cout<<greenText<<" THREAD GRAPH"<<reset<<endl;
        tg.Proces(random_polygon);ThreadGraph::save_graph(tg);
    } else{
        cout << "You chose to create a complex polygon with " << N << " vertices and a radius of " << radius << "."
             << "\nBelow, you can observe the statistics of the process." << endl << endl<< endl << endl << endl;

        cout<<" COMPLEX POLYGON"<<endl;
        cout<<" Number of vertices: "<<magentaText<<N<<reset<<endl<<
            " Radius = "<<magentaText<<radius<<reset<<endl;
        cout<<" vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv"<<endl<<endl;

        complex_polygon = create_complex_polygon(N, radius);
        cout<<blueText<<"STANDARD GRAPH"<<reset<<endl;
        g.Process(complex_polygon); Graph::save_graph(g);
        cout<<endl<<endl;

        cout<<greenText<<"THREAD GRAPH"<<reset<<endl;
        tg.Proces(complex_polygon);ThreadGraph::save_graph(tg);
    }
    g.clear();
    tg.clear();

    cout<< endl<<endl<<endl<<magentaText<<"In the project folder /cmake-build-debug, ""\n""you can find two .svg images illustrating triangulated polygons." << endl << endl << endl<<reset;

}

void DataHelper::CUSTOME_inp() {
    Graph g;
    ThreadGraph tg;

    vector<pair<double, double>> polygon = DataHelper::get_input();


    cout << "You chose to create a custom polygon."
         << "\nBelow, you can observe the statistics of the process." << endl << endl;

    cout<<" POLYGON"<<endl;
    cout << " Number of vertices: " << magentaText << polygon.size() << reset << endl;
    cout<<" vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv"<<endl<<endl;

    cout<<blueText<<" STANDARD GRAPH"<<reset<<endl;
    g.Process(polygon); Graph::save_graph(g);
    cout<<endl<<endl;

    cout<<greenText<<" THREAD GRAPH"<<reset<<endl;
    tg.Proces(polygon);ThreadGraph::save_graph(tg);


    g.clear();
    tg.clear();
}

void DataHelper::GO() {
    cout << "Planar Triangulation by Jonáš Sanislo's Semester Project" << endl;
    cout << "1. Run Comprehensive Test and Comparison (may take more than 30 minutes)" << endl;
    cout << "2. Provide Custom Inputs" <<endl
         << "3. HELP"<<endl;

    int choice;
    cout << "Enter your choice (1 or 2 or 3): ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout<<endl<< "Running Comprehensive Test and Comparison. This may take a while..." << endl;
            DataHelper::START();
            return;
        case 2:
            cout<<endl<<"1. Use polygon generators."
                <<endl<<"2. Enter custom input"<<endl;
            cout << "Enter your choice (1 or 2): ";
            cin >> choice;
            if(choice == 1){
                int N, top, Threshold, radius;
                string booleanValue;

                cout << "Enter R if you want to create a random polygon or C if complex: ";
                cin >> booleanValue;
                bool R_C = (booleanValue == "R");

                if(R_C){
                    cout <<endl<< "Enter number of vertices: ";
                    cin >> N;

                    cout << "Enter Top amplitude value: ";
                    cin >> top;

                    cout << "Enter Threshold amplitude value: ";
                    cin >> Threshold;

                    cout<<endl<< "Running Custom Input..." << endl<< endl;
                    DataHelper::CUSTOME(N, top, Threshold, 0 , true);
                    return;
                }else{
                    cout <<endl<< "Enter number of vertices: ";
                    cin >> N;

                    cout << "Enter Radius: ";
                    cin >> radius;

                    cout<<endl<< "Running Custom Input..." << endl<< endl;
                    DataHelper::CUSTOME(N, 0, 0, radius , false);
                    return;
                }

            }
            else if(choice == 2){
                DataHelper::CUSTOME_inp();
                return;
            }
            else{
                cout << "Invalid choice. Please choose 1 or 2." << endl;
                return;
            }
        case 3:
            cout<<endl<<"Na tohle už nemám nervy."<<endl<<
            "Instrukce jsou dosti přímé, potřebujete-li hlubší informace, pročtěte si dokumentaci."<<endl<<
            "Jinak 2 jednoduchá pravidla "<<endl<<
            "1. Zadávejte požadovaný typ vstupu, 'hodně' opravdu není množství vrcholů" <<endl<<
            "2. Zadááváteli polygon ručně. Zadávejte je v pořadí v jakém jdou za sebou, \n "
            "  po směru hodinových ručiček."<<endl<<
            "   Pokud Váš polygon nebude takřka instantně vypočítán a zobrazen?"<<endl<<
            "   A pokud jste neztrávili posledních 5 let zadávaním vstupu."<<endl<<
            "   Tak jste to někde zmrvili !!!!"<<endl;
            return;

    }
    cout << "Invalid choice. Please choose 1 or 2." << endl;

}








