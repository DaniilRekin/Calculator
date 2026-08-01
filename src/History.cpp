#include "../import/History.h"

void History::Push(const std::string& task, double ans) {
  data_.emplace_back(task, ans);
}

void History::Clear() {
  data_.clear();
}

std::vector<std::pair<std::string, double>> History::GetLast(size_t count) {
  return {data_.end() - count, data_.end()};
}