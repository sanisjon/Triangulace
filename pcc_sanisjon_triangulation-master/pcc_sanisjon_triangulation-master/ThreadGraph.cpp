//
// Created by jonas on 13.12.23.
//
#include <chrono>
#include <thread>
#include <numeric>
#include <algorithm>
#include <future>
#include "ThreadGraph.h"

// GET SET
const vector<vertex> &ThreadGraph::getVertices() const {
    return vertices;
}
double ThreadGraph::getArea() const {
    return area;
}


// CREATOR
void ThreadGraph::add_vertex(double x, double y) {
    auto it = find_if(vertices.begin(), vertices.end(), [=](const vertex& v) {
        return v.getXy() == make_pair(x, y);
    });

    if (it == vertices.end()) {
        vertices.emplace_back(x, y, to_string(num_of_vertices));
        num_of_vertices++;
    }
}

void ThreadGraph::add_vertex_list(const vector<pair<double, double>>& vxs) {
    for(auto p: vxs ){
        add_vertex(p.first,p.second);
    }
}

void ThreadGraph::add_triangle_to_higher(vertex *v1, vertex *v2, vertex *v3) {
    auto it = find_if(higher_triangles.begin(), higher_triangles.end(), [&](const triangle& t) {
        return t.has_vertices(v1, v2, v3);
    });

    if (it == higher_triangles.end()) {
        higher_triangles.emplace_back(*v1, *v2, *v3,num_of_higher_triangles+1);
        num_of_higher_triangles++;
    }
}
void ThreadGraph::add_triangle_to_lower(vertex *v1, vertex *v2, vertex *v3) {
    auto it = find_if(lower_triangles.begin(), lower_triangles.end(), [&](const triangle& t) {
        return t.has_vertices(v1, v2, v3);
    });

    if (it == lower_triangles.end()) {
        lower_triangles.emplace_back(*v1, *v2, *v3,num_of_lower_triangles+1);
        num_of_lower_triangles++;
    }
}


void ThreadGraph::separate_high_low() {
    pivot = get_pivot();
    end = get_end();
    top = get_top();
    bottom = get_bottom();


    bool up = true;
    int pivot_i = 0;

    for (int i = 0; i < size(); i++) {
        if(vertices[i]==*pivot)pivot_i = i;
    }

    int i = pivot_i+1;


    while(!(vertices[i]==*pivot)){
        if(i==size()){
            i=0;
            if(vertices[i]==*pivot)break;
        }
        vertex cur = vertices[i];

        if(cur==*end){i++; up = !up; continue;}

        if (up){
            higher_chain.emplace_back(vertices[i]);
        }else{
            lower_chain.emplace_back(vertices[i]);
        }
        i++;
    }



    higher_chain.insert(higher_chain.begin(), *pivot);
    higher_chain.emplace_back(*end);

    lower_chain.insert(lower_chain.begin(), *end);
    lower_chain.emplace_back(*pivot);


    alternate_chains();


}
    void ThreadGraph::alternate_chains() {
    double bottom_y = bottom->getXy().second-0.5;
    double min_x = pivot->getXy().first;
    double max_x = end->getXy().first;

    std::unique_ptr<vertex> v1 = std::make_unique<vertex>(min_x, bottom_y, "A");
    std::unique_ptr<vertex> v2 = std::make_unique<vertex>(max_x, bottom_y, "B");

    higher_chain.emplace_back(*v2);
    lower_chain.emplace_back(*v1);

    higher_chain.insert(higher_chain.begin(), *v1);
    lower_chain.insert(lower_chain.begin(), *v2);
    reverse(lower_chain.begin(), lower_chain.end());
}


// INFO
bool ThreadGraph::empty() const {
    return num_of_vertices==0;
}
size_t ThreadGraph::size() const {
    return num_of_vertices;
}
void ThreadGraph::clear() {
    // Clear all vectors
    vertices.clear();
    higher_triangles.clear();
    lower_triangles.clear();
    higher_chain.clear();
    lower_chain.clear();

    // Reset pointers
    pivot = nullptr;
    end = nullptr;
    top = nullptr;
    bottom = nullptr;

    // Reset counts
    num_of_vertices = 0;
    num_of_lower_triangles = 0;
    num_of_higher_triangles = 0;

    // Reset area
    area = 0;
}

// HELPERS
vertex *ThreadGraph::get_pivot() {
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
vertex *ThreadGraph::get_end() {
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
vertex *ThreadGraph::get_top() {
    vertex* topVertex = &vertices[0];
    for (size_t i = 1; i < vertices.size(); ++i) {

        if (vertices[i].getXy().second > topVertex -> getXy().second) {
            topVertex = &vertices[i];
        }
    }
    return topVertex;
}
vertex *ThreadGraph::get_bottom() {
    vertex* bottomVertex = &vertices[0];
    for (size_t i = 1; i < vertices.size(); ++i) {
        if (vertices[i].getXy().second < bottomVertex->getXy().second) {
            bottomVertex = &vertices[i];
        }
    }
    return bottomVertex;
}


// VALIDATORS
bool ThreadGraph::dont_contains(vertex &v1, vertex &v2, vertex &v3, vector<vertex>& inputVector) const {
    return all_of(inputVector.begin(), inputVector.end(), [&](const auto& vx) {
        return vx == v1 or vx == v2 or vx == v3 or !is_point_inside_triangle(vx, v1, v2, v3);
    });
}

bool ThreadGraph::is_point_inside_triangle(const vertex& point, const vertex& v1, const vertex& v2, const vertex& v3) {
    double denominator = ((v2.getXy().second - v3.getXy().second) * (v1.getXy().first - v3.getXy().first) +
                          (v3.getXy().first - v2.getXy().first) * (v1.getXy().second - v3.getXy().second));

    double alpha = ((v2.getXy().second - v3.getXy().second) * (point.getXy().first - v3.getXy().first) +
                    (v3.getXy().first - v2.getXy().first) * (point.getXy().second - v3.getXy().second)) / denominator;

    double beta = ((v3.getXy().second - v1.getXy().second) * (point.getXy().first - v3.getXy().first) +
                   (v1.getXy().first - v3.getXy().first) * (point.getXy().second - v3.getXy().second)) / denominator;

    double gamma = 1 - alpha - beta;

    return alpha >= 0 && beta >= 0 && gamma >= 0;
}

bool ThreadGraph::is_convex(vertex &v1, vertex &v2, vertex &v3) {
    pair<double, double> vec1 = {v1.getXy().first - v2.getXy().first, v1.getXy().second - v2.getXy().second};
    pair<double, double> vec3 = {v3.getXy().first - v2.getXy().first, v3.getXy().second - v2.getXy().second};

    double cross_product = vec1.first * vec3.second - vec1.second * vec3.first;
    return cross_product > 0;
}

double ThreadGraph::get_cos_A(pair<double, double> v1, pair<double, double> v3) {
    return (double) (   dot_product(v1,v3)/
                        (norm(v1)* norm(v3))
    );
}
double ThreadGraph::norm(pair<double, double> v) {
    return (double) (pow(pow(v.first,2)+pow(v.second,2),0.5));
}
double ThreadGraph::dot_product(pair<double, double> v1, pair<double, double> v2) {
    return (double) ((v1.first * v2.first) + (v1.second * v2.second));
}

// MANIPULATOR
void ThreadGraph::exclude_vertex() {
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

vertex ThreadGraph::get_next(int i, const vector<vertex>& vec) {
    if(i+1 == vec.size())return vec[0];
    return vec[i+1];
}
vertex ThreadGraph::get_prev(int i, const vector<vertex>& vec) {
    if(i == 0)return vec[vec.size()-1];
    return vec[i-1];
}

bool ThreadGraph::is_in_line(vertex &v1, vertex &v2, vertex &v3) {
    pair<double, double> vec1 = {v1.getXy().first - v2.getXy().first, v1.getXy().second - v2.getXy().second};
    pair<double, double> vec3 = {v3.getXy().first - v2.getXy().first, v3.getXy().second - v2.getXy().second};
    if(abs(get_cos_A(vec1,vec3))==1.0){
        return true;
    }
    return false;
}


// TRIANGULATION
void ThreadGraph::triangulate() {

    future<double> higherChainFuture = async(std::launch::async, &ThreadGraph::triangulate_higher_chain_async, this);
    future<double> lowerChainFuture = async(std::launch::async, &ThreadGraph::triangulate_lower_chain_async, this);

    double result_higher = higherChainFuture.get();
    double result_lower = lowerChainFuture.get();

    area = result_higher-result_lower;
}

//HIGHER
void ThreadGraph::triangulate_higher_chain() {
    if (size()<2){ return;}

    vector<vertex> vecCopy = higher_chain;
    vertex cur, next, prev;
    while (vecCopy.size()>2) {

        for (int i = 0; i < vecCopy.size(); ++i) {
            cur = vecCopy[i];
            next = get_next(i, vecCopy);
            prev = get_prev(i, vecCopy);

            if (is_convex(prev, cur, next) && dont_contains(prev, cur, next, vecCopy)) {
                add_triangle_to_higher(&prev, &cur, &next);
                vecCopy = removeElementAtIndex(vecCopy, i);
            }
        }
    }
}
double ThreadGraph::triangulate_higher_chain_async() {
    triangulate_higher_chain();
    return calculate_area(higher_triangles);
}

//LOWER
void ThreadGraph::triangulate_lower_chain() {
    if (size()<3){ return;}

    vector<vertex> vecCopy = lower_chain;
    vertex cur, next, prev;
    while (vecCopy.size()>2) {
        for (int i = 0; i < vecCopy.size(); ++i) {
            cur = vecCopy[i];
            next = get_next(i, vecCopy);
            prev = get_prev(i, vecCopy);

            if (is_convex(prev, cur, next) && dont_contains(prev, cur, next, vecCopy)) {
                add_triangle_to_lower(&prev, &cur, &next);
                vecCopy = removeElementAtIndex(vecCopy, i);
            }
        }
    }
}
double ThreadGraph::triangulate_lower_chain_async() {
    triangulate_lower_chain();
    return calculate_area(lower_triangles);
}

    vector<vertex> ThreadGraph::removeElementAtIndex(const vector<vertex>& inputVector, int index) {
    if (index < inputVector.size()) {
        std::vector<vertex> resultVector = inputVector;
        resultVector.erase(resultVector.begin() + index);
        return resultVector;
    }
    return inputVector;
}


// RESULT_CALCULATION
double ThreadGraph::calculate_area(vector<triangle>& inputVector) {

    const size_t numOfTriangles = inputVector.size();

    size_t num_threads = thread::hardware_concurrency();
    size_t chunk_size = numOfTriangles / num_threads;

    size_t remaining_triangles = numOfTriangles % num_threads;

    if(chunk_size == 0){chunk_size = 1, remaining_triangles = 0, num_threads = numOfTriangles;}

    auto calculate_area_range = [](size_t start, size_t stop, vector<triangle>& inputVector) {
        double local_sum = 0;
        for (size_t i = start; i < stop; ++i) {
            local_sum += inputVector[i].calculate_area_of_triangle();
        }
        return local_sum;
    };

    vector<double> partial_sums(num_threads, 0.0);

    vector<thread> threads;
    vector<pair<int,int>> start_end;

    for (size_t i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t ende = start + chunk_size;
        if (i == num_threads - 1) {
            ende += remaining_triangles;
        }
        start_end.emplace_back(start,ende);
    }

    for (size_t i = 0; i < num_threads; ++i) {
        threads.emplace_back([=, &start_end, &partial_sums, &inputVector]{
            auto [start, anEnd] = start_end[i];
            partial_sums[i] = calculate_area_range(start, anEnd, inputVector);
        });
    }

    // Wait for all threads to finish
    for_each(threads.begin(), threads.end(), [](thread &t) {
        t.join();
    });

    // Sum up the partial results
    return accumulate(partial_sums.begin(), partial_sums.end(), 0.0);
}

template<typename TimePoint>
chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

double ThreadGraph::Proces(const vector<pair<double, double>> &vxs) {
    if(vxs.empty()){cout<<redText<<"INVALID INPUT"<<endl;
        area = 0;
        num_of_vertices = 0;
        num_of_vertices = 0;
        return 0;
    }

    if(vxs.empty()){cout<<redText<<"INVALID INPUT"<<endl; return 0;}

    auto  total_tart = chrono::high_resolution_clock::now();

    auto start = std::chrono::high_resolution_clock::now();
    add_vertex_list(vxs);
    auto ende = std::chrono::high_resolution_clock::now();
    std::cout << grayBC<<" Add_vertex_list() needed " <<grayBCgreenText<< to_ms(ende - start).count() <<reset<<grayBC<< " ms to finish.\n";

    start = std::chrono::high_resolution_clock::now();
    exclude_vertex();
    ende = std::chrono::high_resolution_clock::now();
    std::cout << grayBC<< " Exclude_vertex() needed " <<grayBCgreenText<< to_ms(ende - start).count() <<reset<<grayBC<< " ms to finish.\n";

    start = std::chrono::high_resolution_clock::now();
    separate_high_low();
    ende = std::chrono::high_resolution_clock::now();
    std::cout << grayBC<< " Separate_high_low() needed " <<grayBCgreenText<< to_ms(ende - start).count() <<reset<<grayBC<< " ms to finish.\n";

    start = std::chrono::high_resolution_clock::now();
    triangulate();
    ende = std::chrono::high_resolution_clock::now();
    std::cout << grayBC<< " Triangulate(vertices) needed " <<grayBCgreenText<< to_ms(ende - start).count() <<reset<<grayBC<< " ms to finish.\n";


    auto total_ende = std::chrono::high_resolution_clock::now();
    cout<<endl<<greenBc<<" Area = "<<greenBCUnde<<area<<endl<<reset<<greenBc
        <<" Number of Triangles created= "<<greenBCUnde<<num_of_higher_triangles+num_of_lower_triangles<<endl<<reset<<greenBc
        <<" Num of input Vertices = "<<greenBCUnde<<num_of_vertices<<endl<<reset;

    cout <<" "<<greenTextUnde<< "Total time needed " << to_ms(total_ende - total_tart).count()<< " ms to finish.\n"<<reset;
    return to_ms(total_ende - total_tart).count();

}


