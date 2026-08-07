#pragma once
#include <format>
#include <stdexcept>
#include <string>

class Exception : public std::runtime_error {
  std::string colored_string_;

 public:
  Exception(const std::string& str) : runtime_error(str), colored_string_(str) {}

  Exception(const std::string& str, size_t start) : runtime_error(str) {
    colored_string_ = str.substr(0, start) + "\033[31m\033[1m" + str.substr(start) + "\033[0m";
  }

  Exception(const std::string& str, size_t start, size_t end) : runtime_error(str) {
    colored_string_ = str.substr(0, start) + "\033[31m\033[1m" + str.substr(start, end) +
                      "\033[0m" + str.substr(end);
  }

  const std::string& colored() const {
    return colored_string_;
  }
};

#include <iostream>
#include <string>
#include <utility>

constexpr std::string Bold = "\033[1m";

constexpr std::string Red = "\033[31m";
constexpr std::string Green = "\033[32m";
constexpr std::string Yellow = "\033[33m";
constexpr std::string Blue = "\033[34m";
constexpr std::string Purple = "\033[35m";

constexpr std::string Reset = "\033[0m";