#include <ctime>
#include <iostream>
#include <pthread.h>
#include <thread>

struct ThreadData {
  long long start;
  long long end;
  long long result;
};

void *partial_sum(void *arg) {
  volatile ThreadData *data = (ThreadData *)arg;
  data->result = 0;
  for (long long i = data->start; i <= data->end; ++i) {
    data->result += i;
  }
  return nullptr;
}

int main() {
  long long N = 2e8;
  const int num_threads = 2;

  std::thread threads[num_threads];
  ThreadData thread_data[num_threads];
  long long chunk_size = N / num_threads;

  clock_t start = clock();

  // Создание потоков
  for (int i = 0; i < num_threads; ++i) {
    thread_data[i].start = i * chunk_size + 1;
    thread_data[i].end = (i + 1) * chunk_size;
    threads[i] = std::thread(partial_sum, &thread_data[i]);
  }

  long long total_sum = 0;
  for (int i = 0; i < num_threads; ++i) {
    threads[i].join();
    total_sum += thread_data[i].result;
  }

  clock_t end = clock();

  std::cout << "=========C++11 Threads: " << std::endl;
  std::cout << "Сумма: " << total_sum << std::endl;
  std::cout << "Время (threads): " << double(end - start) / CLOCKS_PER_SEC
            << " секунд" << std::endl;

  return 0;
}
