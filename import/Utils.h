#pragma once
#include <cctype>
#include <string>
#include <sstream>
#include <iomanip>

namespace ch {
bool isdigit(char ch);
bool isalpha(char ch);
bool isspace(char ch);
bool isalnum(char ch);

bool is_identifier_first_char(char ch);
bool is_identifier_char(char ch);
}  // namespace ch

std::string Format(double x, int n);