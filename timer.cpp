//
// Created by Chuying He on 20/04/2021.
//

#include "timer.hpp"

timer::timer() {
    m_StartTimePoint = std::chrono::high_resolution_clock::now();
}
timer::~timer() {
    stop();
}
void timer::stop() {
    auto endTimePoint = std::chrono::high_resolution_clock::now();

    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

    auto duration = end - start;
    double ms = duration*0.001;

    std::cout <<duration <<" us (" <<ms<<" ms)" << std::endl;
}
