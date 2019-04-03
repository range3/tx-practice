#include <chrono>

namespace txp {
class elapsed_time {
  std::chrono::high_resolution_clock::time_point t0_;
  std::chrono::high_resolution_clock::time_point t1_;
  bool freezed_ = false;
public:
  elapsed_time() {
    reset();
  }

  void reset() {
    t0_ = std::chrono::high_resolution_clock::now();
    freezed_ = false;
  }

  void freeze() {
    t1_ = std::chrono::high_resolution_clock::now();
    freezed_ = true;
  }

  double sec() {
    const auto end = freezed_ ? t1_ : std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::duration<double>>(
      end - t0_).count();
  }
};

class elapsed_time_raii {
  elapsed_time& t_;
public:
  elapsed_time_raii(elapsed_time &t)
      : t_(t) {
    t_.reset();
  }
  ~elapsed_time_raii() {
    t_.freeze();
  }
};
}
