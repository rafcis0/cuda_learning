#include <iostream>

// this would be a basic addition loop in cpp
int main() {
  int x[] = {1, 2, 3};
  int y[] = {4, 5, 6};
  int N = sizeof(x) / sizeof(x[0]);
  
  //easy for loop
  for (int i = 0; i < N; i++)
    y[i] = x[i] + y[i];

    // print out the results
  for (int i = 0; i < N; i++) {
    std::cout << y[i];
    if (i < N - 1) std::cout << ", ";
  }
  std::cout << std::endl;
  
  return 0;
}
