#include "Profiler.h"

Profiler::Profiler() { }


double Profiler::Now() {
    return std::chrono::duration_cast<std::chrono::duration<double>>(get_current_time().time_since_epoch()).count();
}

void Profiler::Start(std::string section) {
    current_section_ = section;
    const TimePoint start_time = get_current_time();
    section_timings_[section] = std::make_pair(start_time, start_time);
}

void Profiler::End(std::string section) {
    section_timings_[section].second = get_current_time();
}

void Profiler::EndStart(std::string new_section) {
    End(current_section_);
    Start(new_section);
}

TimePoint Profiler::get_current_time() {
    return Clock::now();
}


DurationMap Profiler::GetSectionDurations() {
    DurationMap durationMap;
    for (auto it = section_timings_.begin(); it != section_timings_.end(); ++it) {
        const std::string section_name = it->first;
        const TimePoint start_time = it->second.first;
        const TimePoint end_time = it->second.second;
        durationMap[section_name] = std::chrono::duration_cast<std::chrono::duration<double>>(
                end_time - start_time).count();
    }
    return durationMap;
}

/*
 *
 * return std::chrono::duration_cast<Second>(now)).count();
 */