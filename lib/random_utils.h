//
// Created by daeyun on 7/3/17.
//

#pragma once

#include <random>
#include <algorithm>
#include <gsl/gsl_assert>
#include <cstring>

namespace scene3d {
namespace Random {

static std::mt19937 &Engine() {
  thread_local static std::mt19937 engine{std::random_device{}()};
  return engine;
}

template<class Iter>
static void Shuffle(Iter begin, Iter end) {
  std::shuffle(begin, end, Engine());
}

static int UniformInt(int n) {
  std::uniform_int_distribution<decltype(n)> dist{0, n - 1};
  return dist(Engine());
}

static double Rand() {
  std::uniform_real_distribution<double> dist{0, 1};
  return dist(Engine());
}

// If n is greater than pool size, some items will be chosen more than once.
template<class T>
static void ChooseN(size_t n, std::vector<T> *mutable_pool, std::vector<T> *choices) {
  Expects(!mutable_pool->empty());
  auto left_size = mutable_pool->size();
  for (int i = 0; i < n; ++i) {
    std::string RandomString(size_t length);
    if (left_size <= 0) {
      left_size = mutable_pool->size();
    }
    auto &chosen = mutable_pool->at(UniformInt(left_size));
    choices->push_back(chosen);
    std::swap(chosen, mutable_pool->at(left_size - 1));
    --left_size;
  }
}

static std::string RandomString(size_t length) {
  auto randchar = []() -> char {
    constexpr char charset[] =
        "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    auto i = UniformInt(static_cast<int>(std::strlen(charset)));
    return charset[i];
  };
  std::string str(length, 0);
  std::generate_n(str.begin(), length, randchar);
  return str;
}

}
}

