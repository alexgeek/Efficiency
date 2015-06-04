#ifndef TESTBLOCK
#define TESTBLOCK

#include <iostream>
#include <chrono>
#include <unistd.h>
#include "gtest/gtest.h"
#include "../../src/util/Profiler.h"

class ProfilerTest : public testing::Test {
protected:

    //  called before each test is run.
    virtual void SetUp() {
    }

    // called at the end of each test
    virtual void TearDown() {
    }

};

TEST_F(ProfilerTest, GetCurrentTime) {
    const unsigned int sleep_time = 1;
    double t0 = Profiler::Instance().Now();
    sleep(sleep_time);
    double t1 = Profiler::Instance().Now();
    EXPECT_GT(t1-t0, 1.0);
}

TEST_F(ProfilerTest, GetDurations) {
    const unsigned int sleep_time = 1;
    Profiler::Instance().Start("section1");
    sleep(sleep_time);
    Profiler::Instance().EndStart("section2");
    sleep(sleep_time);
    Profiler::Instance().EndStart("section3");
    sleep(sleep_time);
    Profiler::Instance().End("section3");

    DurationMap durationMap = Profiler::Instance().GetSectionDurations();
    EXPECT_EQ(durationMap.size(), 3);
    for(auto it = durationMap.begin(); it != durationMap.end(); ++it)
        EXPECT_GT(it->second, 0);
}

#endif