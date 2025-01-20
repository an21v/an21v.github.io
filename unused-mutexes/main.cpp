#include <chrono>
#include <iostream>
#include <mutex>

class Timer {
public:
  using Clock_t = std::chrono::high_resolution_clock;
  using Timepoint_t = std::chrono::time_point<Clock_t>;
  using Resolution_t = std::chrono::microseconds;

  Timer() 
    : _start(Clock_t::now()) {}

  ~Timer() {
    auto end = Clock_t::now();
    std::cout << std::chrono::duration_cast<Resolution_t>(end - _start).count() << " us.\n";
  }

private:
  Timepoint_t _start;
};

int main()
{
  constexpr int n = 100'000'000;

  std::cout << "Computing " << n << " iterations\n";
  {
    int j = 0;
    Timer t;
    for (int x = 0; x < n; x++)
    {
	j += 1;
    }
  }
 
  std::cout << "Computing " << n << " iterations\n";
  {
    int j = 0;
    Timer t;
    std::mutex m;
    for (int x = 0; x < n; x++)
    {
      std::lock_guard guard(m);
      j += 1;
    }
  }
  return 0;
}
