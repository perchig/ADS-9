#include "tree.h"
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

int main() {
  std::vector<char> input = {'1', '2', '3'};
  PMTree tree(input);
  
  std::vector<std::vector<char>> allPerms = getAllPerms(tree);
  for (size_t i = 0; i < allPerms.size(); ++i) {
    for (char c : allPerms[i]) {
      std::cout << c;
    }
    std::cout << std::endl;
  }
  
  for (int i = 1; i <= 6; ++i) {
    std::vector<char> perm1 = getPerm1(tree, i);
    std::vector<char> perm2 = getPerm2(tree, i);
    for (char c : perm1) std::cout << c;
    std::cout << " ";
    for (char c : perm2) std::cout << c;
    std::cout << std::endl;
  }
  
  std::ofstream dataFile("result/experiment_data.csv");
  dataFile << "n,getAllPerms_time,getPerm1_time,getPerm2_time\n";
  
  std::random_device rd;
  std::mt19937 gen(rd());
  
  for (int n = 3; n <= 9; ++n) {
    std::vector<char> alphabet;
    for (int i = 0; i < n; ++i) {
      alphabet.push_back('1' + i);
    }
    
    PMTree testTree(alphabet);
    
    long long totalPerms = 1;
    for (int i = 1; i <= n; ++i) {
      totalPerms *= i;
    }
    
    std::uniform_int_distribution<> dis(1, static_cast<int>(totalPerms));
    int randomPerm = dis(gen);
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<char>> allPermsTest = getAllPerms(testTree);
    auto end = std::chrono::high_resolution_clock::now();
    auto getAllPerms_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    start = std::chrono::high_resolution_clock::now();
    std::vector<char> perm1 = getPerm1(testTree, randomPerm);
    end = std::chrono::high_resolution_clock::now();
    auto getPerm1_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    start = std::chrono::high_resolution_clock::now();
    std::vector<char> perm2 = getPerm2(testTree, randomPerm);
    end = std::chrono::high_resolution_clock::now();
    auto getPerm2_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    dataFile << n << "," << getAllPerms_time << "," << getPerm1_time << "," << getPerm2_time << "\n";
  }
  
  dataFile.close();
  return 0;
}
