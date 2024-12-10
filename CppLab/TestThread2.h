#pragma once

#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

class some_data {
 public:
  int a{42};
  std::string b{"answer"};

  void do_something() {
    // b = "not answer";
    // a = 43;
    std::cout << "str: " << b << "; a: " << a << std::endl;
  }
};

class data_wrapper {
 private:
  some_data data;
  std::mutex m;

 public:
  template <typename Function>
  void process_data(Function func) {
    std::lock_guard<std::mutex> l(m);
    func(data);
  }
};

some_data* unprotected;
void malicious_function(some_data& protected_data) {
  unprotected = &protected_data;

  unprotected->a = 72;
  unprotected->b = "change the answer to 72.";
}

data_wrapper x;
void foo() {
  x.process_data(malicious_function);
  unprotected->do_something();
}

void simple_dead_lock() {
  std::mutex m1;
  std::mutex m2;
  std::thread t1([&m1, &m2] {
    printf("1. acquiring m1.\n");
    m1.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    printf("1. acquiring m2.\n");
    m2.lock();
  });

  std::thread t2([&m1, &m2] {
    printf("2. acquiring m2.\n");
    m2.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    printf("2. acquiring m1.\n");
    m1.lock();
  });

  t1.join();
  t2.join();
}

struct some_big_object {};

void swap(some_big_object& o1, some_big_object& o2) {}

class X {
 public:
  X(some_big_object& _sbo) : sbo(_sbo) {}

  friend void swap(X& lhs, X& rhs) {
    if (&lhs == &rhs) {
      return;
    }

    std::unique_lock<std::mutex> la(lhs.m, std::defer_lock);
    std::unique_lock<std::mutex> lb(rhs.m, std::defer_lock);

    std::lock(la, lb);

    swap(lhs.sbo, rhs.sbo);
  }

 private:
  some_big_object sbo;
  std::mutex m;
};

void test_thread2() {
  foo();
  // simple_dead_lock();
}
