//
// Created by Chuying He on 20/04/2021.
//

#ifndef DUCKDB_RL_TIMER_HPP
#define DUCKDB_RL_TIMER_HPP

#include <chrono>
#include <iostream>

class timer {
public:
    timer();
    ~timer();
    void stop();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
};

#endif //DUCKDB_RL_TIMER_HPP
