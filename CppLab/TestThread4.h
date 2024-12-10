#pragma once

namespace tt4 {

bool flag;
std::mutex m;

void wait_for_flag() {
  std::unique_lock<std::mutex> lk(m);

  while (!flag) {
    lk.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    lk.lock();
  }
}

struct data_chunk {};
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

data_chunk prepare_data() { return data_chunk(); }

bool more_data_to_prepare() { return true; }

void process(data_chunk& data) {}

bool is_last_chunk(data_chunk& data) { return true; }

void data_preparation_thread() {
  while (more_data_to_prepare()) {
    data_chunk const data = prepare_data();
    std::lock_guard<std::mutex> l(m);

    data_queue.push(data);

    data_cond.notify_one();
  }
}

void data_processing_thread() {
  while (true) {
    std::unique_lock<std::mutex> l(m);
    data_cond.wait(l, [] { return !data_queue.empty(); });

    data_chunk data = data_queue.front();

    data_queue.pop();

    l.unlock();

    process(data);

    if (is_last_chunk(data)) {
      break;
    }
  }
}

}  // namespace tt4

void test_thread4() {}
