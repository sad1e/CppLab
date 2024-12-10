#pragma once

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <memory>
#include <numeric>
#include <thread>
#include <vector>

constexpr std::chrono::milliseconds g_timespan(1000);

void print_thread_id() {
  std::thread::id thread_id = std::this_thread::get_id();
  printf("current thread id: %u.\n", thread_id);
}

void do_sth(int& i) {
  std::this_thread::sleep_for(g_timespan);
  std::thread::id thread_id = std::this_thread::get_id();

  std::cout << "do sth in thread: " << thread_id << std::endl;

  i = 1;
  std::cout << "assign i: " << i << std::endl;
}

struct background_task {
  void do_sth_inner() const { printf("do sth in `background_task`!\n"); }

  void operator()() const { do_sth_inner(); }
};

void do_print(uint32_t i) { printf("%u\n", i); }

struct func {
  int& i;
  func(int& i_) : i(i_) {}
  void operator()() {
    for (uint32_t i = 0; i < 1000000; ++i) {
      do_print(i);
    }
  }
};

void oops() {
  int local_state = 0;
  func my_func(local_state);
  std::thread my_thread(my_func);

  my_thread.join();
}

struct big_object {
  int a;
  float b;
  char c;
};

void process_big_object(std::unique_ptr<big_object> p) {
  printf("bo: %d, %.3f, %c\n", p->a, p->b, p->c);
}

void some_func() { printf("some func.\n"); }
void some_other_func() { printf("some other func.\n"); }

class scoped_thread {
  std::thread t;

 public:
  explicit scoped_thread(std::thread _t) : t(std::move(_t)) {
    if (!t.joinable()) {
      throw std::logic_error("no thread.");
    }
  }

  ~scoped_thread() { t.join(); }

  scoped_thread(scoped_thread const&) = delete;
  scoped_thread& operator=(scoped_thread const&) = delete;
};

template <typename Iterator, typename T>
struct AccumulateBlock {
  void operator()(Iterator first, Iterator last, T& result) {
    result = std::accumulate(first, last, result);
  }
};

template <typename Iterator, typename T>
T ParallelAccumulate(Iterator first, Iterator last, T init) {
  unsigned long const length = std::distance(first, last);
  if (!length) {
    return init;
  }

  unsigned long const min_per_thread = 25;
  unsigned long const max_threads =
      (length + min_per_thread - 1) / min_per_thread;

  unsigned long const hardware_threads = std::thread::hardware_concurrency();

  unsigned long const num_threads =
      std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

  unsigned long const block_size = length / num_threads;

  std::vector<T> results(num_threads);
  std::vector<std::thread> threads(num_threads - 1);

  Iterator block_start = first;
  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);
    threads[i] = std::thread(AccumulateBlock<Iterator, T>(), block_start,
                             block_end, std::ref(results[i]));
    block_start = block_end;
  }

  AccumulateBlock<Iterator, T>()(block_start, last, results[num_threads - 1]);

  for (auto& entry : threads) {
    entry.join();
    return std::accumulate(results.begin(), results.end(), init);
  }
}

void test_thread() {
  std::cout << "hardware concurrency(): " << std::thread::hardware_concurrency()
            << std::endl;

  int i = 0;
  // std::thread my_thread{do_sth, i};
  // std::thread my_thread(do_sth, std::ref(i));

  // background_task f;
  // std::thread my_thread1{f};

  // my_thread.join();
  // my_thread1.join();

  // printf("newest i: %d.\n", i);
  // printf("print after join.\n");

  // std::unique_ptr<big_object> p(new big_object);
  // p->a = 1.0;
  // p->b = 2.0f;
  // p->c = 'a';

  // std::thread t(process_big_object, std::move(p));

  // if (p == nullptr) {
  //   printf("p is nullptr.\n");
  // }

  // t.join();

  // oops();

  // scoped_thread(std::thread(process_big_object, std::move(p)));

  std::thread t0(do_sth, std::ref(i));

  t0.join();

  std::thread t1 = std::move(t0);
  // t1.join();
}
