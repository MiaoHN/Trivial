#ifndef __COMMON_H__
#define __COMMON_H__

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

template <typename T>
void print(const T& v) {
  cout << "(print not implemented)" << endl;
}

template <>
void print(const bool& v) {
  cout << (v ? "true" : "false") << endl;
}

template <typename T>
T load(const string& values) {
  cout << "(load not implemented)" << endl;
}

template <>
vector<int> load(const string& values) {
  vector<int> result;
  int cursor = 0;
  while (true) {
    while (cursor < values.size() && !isdigit(values[cursor])) ++cursor;
    if (cursor == values.size()) break;
    int num = 0;
    while (cursor < values.size() && isdigit(values[cursor])) {
      num *= 10;
      num += values[cursor++] - '0';
    }
    result.push_back(num);
  }
  return result;
}

template <>
void print(const vector<int>& v) {
  if (v.empty()) {
    cout << "(empty)" << endl;
    return;
  }
  cout << "[" << v[0];
  for (int i = 1; i < v.size(); ++i) {
    cout << ", " << v[i];
  }
  cout << "]" << endl;
}

template <>
void print(const vector<vector<int>>& v) {
  if (v.empty()) {
    cout << "(empty)" << endl;
    return;
  }
  cout << "[";
  if (v[0].empty()) {
    cout << "(empty)";
  } else {
    cout << "[" << v[0][0];
    for (int i = 1; i < v[0].size(); ++i) {
      cout << ", " << v[0][i];
    }
    cout << "]";
  }
  for (int i = 1; i < v.size(); ++i) {
    cout << ", ";
    if (v[i].empty()) {
      cout << "(empty)";
    } else {
      cout << "[" << v[i][0];
      for (int j = 1; j < v[i].size(); ++j) {
        cout << ", " << v[i][j];
      }
      cout << "]";
    }
  }
  cout << "]" << endl;
}

template <>
void print(const int& v) {
  cout << v << endl;
}

template <>
void print(const string& v) {
  cout << v << endl;
}

#endif  // __COMMON_H__