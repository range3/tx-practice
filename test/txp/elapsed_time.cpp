#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <stdexcept>
#include "txp/elapsed_time.hpp"

TEST(TXP_ELAPSED_TIME, all) {
  txp::elapsed_time t;

  std::this_thread::sleep_for(std::chrono::seconds(1));

  ASSERT_GT(t.sec(), 0.5);
  ASSERT_LT(t.sec(), 1.5);
}

TEST(TXP_ELAPSED_TIME, freeze) {
  txp::elapsed_time t;

  std::this_thread::sleep_for(std::chrono::seconds(1));

  t.freeze();

  std::this_thread::sleep_for(std::chrono::seconds(1));

  ASSERT_GT(t.sec(), 0.5);
  ASSERT_LT(t.sec(), 1.5);
}

TEST(TXP_ELAPSED_TIME_RAII, scoped) {
  txp::elapsed_time t;

  try {
    txp::elapsed_time_raii st(t);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    throw std::runtime_error("something wrong");
  } catch (...) {
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  ASSERT_GT(t.sec(), 0.5);
  ASSERT_LT(t.sec(), 1.5);
}
