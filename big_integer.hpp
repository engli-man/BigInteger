#pragma once
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
class BigInt {
 public:
  BigInt();
  BigInt(const std::string& num);
  BigInt(int64_t num);
  BigInt(const BigInt& num);
  BigInt& operator=(const BigInt& num);
  friend bool operator==(BigInt one, BigInt num);
  friend bool operator!=(BigInt one, BigInt num);
  friend bool operator<(BigInt one, BigInt num);
  friend bool operator>(BigInt one, BigInt num);
  friend bool operator<=(BigInt one, BigInt num);
  friend bool operator>=(BigInt one, BigInt num);
  friend BigInt operator+(BigInt one, BigInt num);
  friend BigInt operator-(BigInt one, BigInt num);
  BigInt operator+=(BigInt& num);
  BigInt operator-=(BigInt& num);
  BigInt& operator++();
  BigInt operator++(int);
  BigInt& operator--();
  BigInt operator--(int);
  BigInt& operator-();
  friend BigInt operator*(BigInt one, BigInt num);
  BigInt operator*=(BigInt& num);
  BigInt operator/(BigInt& num);
  BigInt operator/=(BigInt& num);
  BigInt operator%(BigInt& num);
  BigInt operator%=(BigInt& num);
  friend std::istream& operator>>(std::istream& iss, BigInt& num);
  friend std::ostream& operator<<(std::ostream& oss, const BigInt& num);
  ~BigInt();
  void Reverse();
  bool IsNull();
  BigInt Addition(BigInt num);
  BigInt AdditionSubmodule(BigInt& num);
  BigInt Substraction(BigInt& num);
  BigInt SubstractionDistributionMinued(BigInt& num, std::vector<bool>& memory);
  BigInt SubstractionDistributionSubtrahend(BigInt& num,
                                            std::vector<bool>& memory);
  BigInt SubstractionSubmodule(BigInt& subtrahend);
  BigInt Multiply(BigInt num);
  BigInt MultiplySubmodule(BigInt& num, BigInt& val, BigInt& result);
  BigInt Division(BigInt num);
  BigInt DivisionSubmodule(BigInt& num, int cnt, BigInt& val);
  void DeleteZeroes();
  BigInt MultSingle(int64_t num);
  int64_t static BinSearch(BigInt& div, BigInt& sub);
  BigInt& Module();
  void SignChange();

 private:
  std::vector<int64_t> number_;
  bool is_negative_ = false;
  const int64_t kBase = 10;
};