#ifndef GAME_PROFILER_H
#define GAME_PROFILER_H

#include <iostream>
#include <chrono>
#include <unordered_map>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::high_resolution_clock::time_point TimePoint;
typedef std::chrono::duration<double, std::ratio<1> > Second;
typedef std::chrono::duration<double, std::nano> NanoSeconds;

typedef std::unordered_map<std::string, double> DurationMap;

class Profiler
{
public:
    static Profiler& Instance()
    {
        static Profiler instance;
        return instance;
    }

    double Now();
    void Start(std::string section);
    void End(std::string section);
    void EndStart(std::string section);
    DurationMap GetSectionDurations();

private:
    Profiler(void);
    Profiler(Profiler const&); // prevent copies
    void operator=(Profiler const&); // prevent assignments
    ~Profiler() {};

    std::unordered_map<std::string, std::pair<TimePoint, TimePoint>> section_timings_;
    std::string current_section_;

    TimePoint get_current_time();
};

#endif //GAME_PROFILER_H
