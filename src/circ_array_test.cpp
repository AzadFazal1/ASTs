

#include "circ_array.h"
#include <cassert>
#include <iostream>

using namespace cs225;

void test_empty_array() {
  circ_array<uint64_t> emptyy{};
  assert(emptyy.empty() == 1);
}

void test_copy_construction() {
  circ_array<uint64_t> arr{4};
  for (uint64_t i = 0; i < arr.size(); ++i)
    arr[i] = i * 2;

  circ_array<uint64_t> copy{arr};
  assert(copy.size() == 4);
  for (uint64_t i = 0; i < copy.size(); ++i)
    assert(copy.at(i) == arr.at(i));

  assert(copy.size() == arr.size());
}
void test_move_construction() {
  circ_array<uint64_t> arr{4};
  for (uint64_t i = 0; i < arr.size(); ++i)
    arr[i] = i * 2;

  circ_array<uint64_t> mvd{std::move(arr)};
  assert(arr.size() == 0);
  assert(mvd.size() == 4);
  for (uint64_t i = 0; i < mvd.size(); ++i)
    assert(mvd.at(i) == i * 2);
}

void test_move_assignment() {
  circ_array<uint64_t> arr{4};
  for (uint64_t i = 0; i < arr.size(); ++i)
    arr[i] = i * 2;

  circ_array<uint64_t> mvd{14};
  for (uint64_t i = 0; i < mvd.size(); ++i)
    mvd[i] = 42;

  mvd = std::move(arr);
  assert(arr.size() == 0);
  assert(mvd.size() == 4);
  for (uint64_t i = 0; i < mvd.size(); ++i)
    assert(mvd.at(i) == i * 2);
}

int main() {
  circ_array<uint64_t> arr{6};
  circ_array<uint64_t> arr1(arr);
  circ_array<uint64_t> arr2 = arr;
  circ_array<uint64_t> arr3(std::move(arr2));
  test_copy_construction();
  test_empty_array();
  test_move_construction();
  test_move_assignment();

  for (uint64_t i = 0; i < arr.size(); ++i)
    arr[i] = i + 1;

  arr.push_front(0);
  arr.push_back(7);
  for (uint64_t i = 0; i < arr.size(); ++i) {
    assert(arr.at(i) == i);
  }
  assert(arr.size() == 8);
  arr.pop_front();
  assert(arr[0] == 1);
  arr.pop_front();
  assert(arr[0] == 2);

  arr.pop_back();
  assert(arr[arr.size() - 1] == 6);
  arr.pop_back();
  assert(arr[arr.size() - 1] == 5);
  assert(arr.size() == 4);
  arr.erase(2);

  assert(arr[0] == 2);
  assert(arr[1] == 3);
  assert(arr[2] == 5);
  assert(arr.size() == 3);

  for (uint64_t i = 4; i < 10; i++) {
    arr.push_back(i);
  }
  assert(arr[8] == 9);
  arr.pop_front();
  arr.pop_front();
  arr.pop_front();
  arr.push_back(90);
  arr.push_back(100);
  arr.push_back(110);
  arr.push_back(220);
  assert(arr[arr.size() - 1 == 220]);
  arr.pop_front();
  arr.pop_front();
  arr.pop_front();
  arr.pop_front();
  arr.pop_front();
  arr.pop_front();
  arr.pop_front();
  assert(arr[0] == 100);

  return 0;
}
