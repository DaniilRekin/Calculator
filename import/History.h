#pragma once
#include <string>
#include <vector>
#include <utility>

class History {
  std::vector<std::pair<std::string, double>> data_;

 public:
  void Push(const std::string& task, double ans);
  void Clear();
  std::vector<std::pair<std::string, double>> GetLast(size_t count);
};