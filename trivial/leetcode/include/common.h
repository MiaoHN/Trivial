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
void print(T& v) {
  cout << "(not implemented)" << endl;
}

template <>
void print(vector<int>& v) {
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

#endif  // __COMMON_H__