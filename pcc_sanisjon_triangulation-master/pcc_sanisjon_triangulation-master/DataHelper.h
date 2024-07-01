//
// Created by jonas on 2.1.24.
//

#ifndef TRIANGULATION_DATAHELPER_H
#define TRIANGULATION_DATAHELPER_H

#include <utility>
#include <vector>
#include <chrono>

using namespace std;

class DataHelper {
private:
    static const vector<vector<int>> Data;

    static const char* redText;
    static const char* greenText;
    static const char* magentaText;
    static const char* blueText;
    static const char* reset;
public:
    explicit DataHelper()=default;


    static double get_random_double(int bottom, int top);
    /*
     ** Generuje nepravidelný polygon s N vrcholy,
     * 'top' označuje extrémní hodnotu absolutní vzdálenosti od osy x,
     * 'threshold' určuje minimální hodnotu vzdálenosti od osy x.
     * Rozměry polygonu reps. hodnoty jichyž můžou vrcholy polygonu nabývat x(0, n/2), y(-top, top).
     */
    static vector<pair<double, double>> create_random_polygon(int n, int top, int threshold);
    /*
    * Vytvari pravidelny n-uhelnik o danem poctu vrcholu a polomeru.
    */
    static vector<pair<double, double>> create_complex_polygon(int n, double r);

    /*
     * Tato funkce provede celkove testovani.
     * Funkce dle dného vstupu DataHelper::Data, udávajíc hodnoty pro generování polygonlů.
     * 1. "Random" >> standardní jednovláknová >> více vláknová.
     * 2. "Complex" >> standardní jednovláknová >> více vláknová.
     *
     * V průběhu je genorován výpis o výsledcích procesů.
     * Na konci je vidět celkové srovnání obou algoritmů a jejich performance na rozdílných polygonech.
     */
    static void START();
    static void result_printer(vector<pair<int, int>> results_random, vector<pair<int, int>> results_complex);
    /*
     * Zadejte:
     * N: Počet vrcholů
     * top: Maximální hodnota amplitudy
     * threshold: Minimální hodnota amplitudy
     * radius: poloměr N-úhelníku resp. vzdálenost od středu P(0.0)
     */
    static void CUSTOME(int N, int top, int threshold, int radius, bool R_C);

    static void CUSTOME_inp();
        static vector<pair<double, double>> get_input(){
        vector<pair<double, double>> pairs = {};
        cout << "Enter pairs of numbers to create pairs. Type 'x' to exit.\n";
        while (true) {
            cout << "Enter two numbers separated by a space (or 'x' to exit): ";
            string input1, input2;
            cin >> input1;

            if (input1 == "x") {
                break; // Exit the loop if the user types 'x'
            }

            cin >> input2;

            try {
                int number1 = std::stoi(input1);
                int number2 = std::stoi(input2);
                pairs.emplace_back(number1, number2); // Create a pair and push it to the vector
            } catch (invalid_argument&) {
                cout << "Invalid input. Please enter valid numbers or 'x'.\n";
                // Clear the input buffer in case of invalid input
                cin.clear();
                break;
            }
        }
        return pairs;
    }

    static void GO();

};


#endif //TRIANGULATION_DATAHELPER_H
