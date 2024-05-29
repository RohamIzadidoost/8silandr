#include<bits/stdc++.h>

int main () {
  int first[] = {5,10,15,20,25}; // Should be sorted
  int second[] = {10, 20, 30, 40, 50}; // Should be sorted
  std::vector<int> v(10);                      // 0  0  0  0  0  0  0  0  0  0
  std::vector<int>::iterator it;

  it=std::set_intersection (first, first+5, second, second+5, v.begin()); // 10 20 0  0  0  0  0  0  0  0
  v.resize(it-v.begin());                      // 10 20
  return 0;
}
