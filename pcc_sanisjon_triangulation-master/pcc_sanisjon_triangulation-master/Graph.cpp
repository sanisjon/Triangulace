//
// Created by jonas on 13.12.23.
//
#include <chrono>
#include "Graph.h"

// GET SET
const vector<vertex> &Graph::getVertices() const {
    return vertices;
}
double Graph::getArea() const {
    return area;
}


// CREATOR
void Graph::add_vertex(double x, double y) {
    auto it = find_if(vertices.begin(), vertices.end(), [=](const vertex& v) {
        return v.getXy() == make_pair(x, y);
    });

    if (it == vertices.end()) {
        vertices.emplace_back(x, y, to_string(num_of_vertices));
        num_of_vertices++;
    } else{
        cout << redText<<"Vertex with coordinates (" << x << ", " << y << ") already exists.\n"<<reset;
    }
}

void Graph::add_vertex_list(const vector<pair<double, double>>& vxs) {
    for(auto p: vxs ){
        add_vertex(p.first,p.second);
    }
}

void Graph::add_triangle(vertex *v1, vertex *v2, vertex *v3) {
    auto it = find_if(triangles.begin(), triangles.end(), [&](const triangle& t) {
        return t.has_vertices(v1, v2, v3);
    });

    if (it == triangles.end()) {
        triangles.emplace_back(*v1, *v2, *v3,num_of_triangles+1);
        num_of_triangles++;
    }
}

void Graph::separate_high_low() {
    pivot = get_pivot();
    end = get_end();
    top = get_top();
}


// INFO
bool Graph::empty() const {
    return num_of_vertices==0;
}
size_t Graph::size() const {
    return num_of_vertices;
}
void Graph::clear() {
    vertices.clear();
    triangles.clear();

    num_of_vertices = 0;
    num_of_triangles = 0;
    area = 0;

    pivot = nullptr;
    end = nullptr;
    top = nullptr;
}

// HELPERS
vertex *Graph::get_pivot() {
    vertex* lowestXVertex = &vertices[0];
    for (size_t i = 1; i < vertices.size(); ++i) {
        if (vertices[i].getXy().first == lowestXVertex -> getXy().first){
            if (vertices[i].getXy().second < lowestXVertex -> getXy().second) {
                lowestXVertex = &vertices[i];

            }
        }
        if (vertices[i].getXy().first < lowestXVertex -> getXy().first) {
            lowestXVertex = &vertices[i];
        }
    }
    lowestXVertex->setIsPivot(true);
    return lowestXVertex;
}
vertex *Graph::get_end() {
    vertex* lastVertex = &vertices[0];
    for (size_t i = 1; i < vertices.size(); ++i) {
        if (vertices[i].getXy().first == lastVertex -> getXy().first){
            if (vertices[i].getXy().second < lastVertex -> getXy().second) {
                lastVertex = &vertices[i];

            }
        }
        if (vertices[i].getXy().first > lastVertex -> getXy().first) {
            lastVertex = &vertices[i];
        }
    }
    lastVertex->setIsEnd(true);
    return lastVertex;
}
vertex *Graph::get_top() {
    vertex* topVertex = &vertices[0];
    for (size_t i = 1; i < vertices.size(); ++i) {

        if (vertices[i].getXy().second > topVertex -> getXy().second) {
            topVertex = &vertices[i];
        }
    }
    return topVertex;
}



// VALIDATORS
bool Graph::dont_contains(vertex& v1, vertex& v2, vertex& v3,vector<vertex>& inputVector) {

    return all_of(inputVector.begin(), inputVector.end(), [&](const auto& vx) {
        return vx == v1 or vx == v2 or vx == v3 or !is_point_inside_triangle(vx, v1, v2, v3);
    });
}
    bool Graph::is_point_inside_triangle(const vertex& point, const vertex& v1, const vertex& v2, const vertex& v3) {
    double denominator = ((v2.getXy().second - v3.getXy().second) * (v1.getXy().first - v3.getXy().first) +
                          (v3.getXy().first - v2.getXy().first) * (v1.getXy().second - v3.getXy().second));

    double alpha = ((v2.getXy().second - v3.getXy().second) * (point.getXy().first - v3.getXy().first) +
                    (v3.getXy().first - v2.getXy().first) * (point.getXy().second - v3.getXy().second)) / denominator;

    double beta = ((v3.getXy().second - v1.getXy().second) * (point.getXy().first - v3.getXy().first) +
                   (v1.getXy().first - v3.getXy().first) * (point.getXy().second - v3.getXy().second)) / denominator;

    double gamma = 1 - alpha - beta;

    return alpha >= 0 && beta >= 0 && gamma >= 0;
}

bool Graph::is_convex(vertex &v1, vertex &v2, vertex &v3) {
    pair<double, double> vec1 = {v1.getXy().first - v2.getXy().first, v1.getXy().second - v2.getXy().second};
    pair<double, double> vec3 = {v3.getXy().first - v2.getXy().first, v3.getXy().second - v2.getXy().second};

    double cross_product = vec1.first * vec3.second - vec1.second * vec3.first;
    return cross_product > 0;
    }

    double Graph::get_cos_A(pair<double, double> v1, pair<double, double> v3) {
            return (double) (   dot_product(v1,v3)/
                                (norm(v1)* norm(v3))
                            );
        }
            double Graph::norm(pair<double, double> v) {
                return (double) (pow(pow(v.first,2)+pow(v.second,2),0.5));
            }
            double Graph::dot_product(pair<double, double> v1, pair<double, double> v2) {
                return (double) ((v1.first * v2.first) + (v1.second * v2.second));
            }

// MANIPULATOR
void Graph::exclude_vertex() {
    vector<vertex> new_vertices;
    for (int i = 0; i < size(); ++i) {
        auto cur = vertices[i];
        auto next = get_next(i, vertices);
        auto prev = get_prev(i, vertices);

        if(!is_in_line(prev,cur,next)){
            new_vertices.emplace_back(cur);
        }
    }
    vertices = new_vertices;
    num_of_vertices = new_vertices.size();
}

    vertex Graph::get_next(int i, const vector<vertex>& vec) {
    if(i+1 == vec.size())return vec[0];
    return vec[i+1];
}
    vertex Graph::get_prev(int i, const vector<vertex>& vec) {
    if(i == 0)return vec[vec.size()-1];
    return vec[i-1];
}

    bool Graph::is_in_line(vertex &v1, vertex &v2, vertex &v3) {
        pair<double, double> vec1 = {v1.getXy().first - v2.getXy().first, v1.getXy().second - v2.getXy().second};
        pair<double, double> vec3 = {v3.getXy().first - v2.getXy().first, v3.getXy().second - v2.getXy().second};
        if(abs(get_cos_A(vec1,vec3))==1.0){
            return true;
        }
        return false;
    }

// TRIANGULATION
void Graph::triangulate() {
    if (size()<3){ return;}

    vector<vertex> vecCopy = vertices;
    vertex cur, next, prev;
    while (vecCopy.size()>2) {
        for (int i = 0; i < vecCopy.size(); ++i) {
            cur = vecCopy[i];
            next = get_next(i, vecCopy);
            prev = get_prev(i, vecCopy);

            if (is_convex(prev, cur, next) && dont_contains(prev, cur, next, vecCopy)) {
                add_triangle(&prev, &cur, &next);
                vecCopy = removeElementAtIndex(vecCopy, i);
            }
        }
    }
}
    vector<vertex> Graph::removeElementAtIndex(const vector<vertex>& inputVector, int index) {
        if (index < inputVector.size()) {
            std::vector<vertex> resultVector = inputVector;
            resultVector.erase(resultVector.begin() + index);
            return resultVector;
        }
        return inputVector;
}

void Graph::calculate_area() {
    double sum = 0;
    for (auto t :triangles) {
        sum += t.calculate_area_of_triangle();
    }
    area = sum;
}

template<typename TimePoint>
chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

double Graph::Process(const vector<pair<double, double>> &vxs) {
    if(vxs.empty()){cout<<redText<<"INVALID INPUT"<<endl;
        area = 0;
        num_of_vertices = 0;
        num_of_vertices = 0;
        return 0;
    }

    auto  total_tart = chrono::high_resolution_clock::now();

    auto start = std::chrono::high_resolution_clock::now();
    add_vertex_list(vxs);
    auto ende = std::chrono::high_resolution_clock::now();
    std::cout << grayBC<<" Add_vertex_list() needed "<<reset <<grayBCbluueText<< to_ms(ende - start).count() <<reset << grayBC<< " ms to finish.\n";

    start = std::chrono::high_resolution_clock::now();
    separate_high_low();
    ende = std::chrono::high_resolution_clock::now();
    std::cout  << grayBC<<" Separate_high_low() needed " <<grayBCbluueText<< to_ms(ende - start).count() <<reset << grayBC<< " ms to finish.\n";

    start = std::chrono::high_resolution_clock::now();
    exclude_vertex();
    ende = std::chrono::high_resolution_clock::now();
    std::cout << grayBC<< " Exclude_vertex() needed " <<grayBCbluueText<< to_ms(ende - start).count() <<reset << grayBC<< " ms to finish.\n";

    start = std::chrono::high_resolution_clock::now();
    triangulate();
    ende = std::chrono::high_resolution_clock::now();
    std::cout << grayBC<< " Triangulate(vertices) needed " <<grayBCbluueText<< to_ms(ende - start).count() <<reset << grayBC<< " ms to finish.\n";

    start = std::chrono::high_resolution_clock::now();
    calculate_area();
    ende = std::chrono::high_resolution_clock::now();
    std::cout  << grayBC<< " Calculate_area() needed " <<grayBCbluueText<< to_ms(ende - start).count() <<reset << grayBC<< " ms to finish.\n";

    auto total_ende = std::chrono::high_resolution_clock::now();


    cout<<endl<<blueBc<<" Area = "<<blueBcUnde<<area<<endl<<reset<<blueBc
        <<" Number of Triangles created= "<<blueBcUnde<<num_of_triangles<<endl<<reset<<blueBc
        <<" Num of input Vertices = "<<blueBcUnde<<num_of_vertices<<endl<<reset;

    cout<<" " <<blueTextUnde<< "Total time needed " << to_ms(total_ende - total_tart).count()<< " ms to finish.\n"<<reset;
    return to_ms(total_ende - total_tart).count();

}


