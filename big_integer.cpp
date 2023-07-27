#include "big_integer.hpp"

BigInt::BigInt() { is_negative_ = false; };  // default constructor

BigInt::BigInt(const std::string& num) {  // constructor for strings
  if (num.empty()) {
    number_.push_back(0);
    return;
  }
  if (num.size() > 1) {
    if ((num[0] == '-') && (num[1] != '0')) {
      is_negative_ = true;
    }
  }
  size_t idx = 0;
  if (num[0] == '-') {
    idx = 1;
  }
  for (; idx < num.size(); ++idx) {
    int digit = num[idx] - '0';
    number_.push_back(digit);
  }
  Reverse();
}

BigInt::BigInt(int64_t num) {  // constructor for int64_t
  if (num == 0) {
    number_.push_back(0);
    return;
  }
  if (num > 0) {
    while (num != 0) {
      number_.push_back(num % kBase);
      num /= kBase;
    }
  } else {
    num *= -1;
    while (num != 0) {
      number_.push_back(std::abs(num % kBase));
      num /= kBase;
    }
    is_negative_ = true;
  }
}

BigInt::BigInt(const BigInt& num) : is_negative_(num.is_negative_) {
  for (int i = 0; i < static_cast<int>(num.number_.size()); ++i) {
    number_.push_back(num.number_[i]);
  }
}

BigInt& BigInt::operator=(const BigInt& num) {
  BigInt copy = num;
  number_.swap(copy.number_);
  is_negative_ = copy.is_negative_;
  return *this;
}

bool operator==(BigInt one, BigInt num) {
  if (one.number_.size() == num.number_.size()) {
    for (size_t i = 0; i < one.number_.size(); ++i) {
      if (one.number_[i] != num.number_[i]) {
        return false;
      }
    }
    return (num.is_negative_ == one.is_negative_);
  }
  return false;
}

bool operator!=(BigInt one, BigInt num) {
  if (one.number_.size() == num.number_.size()) {
    for (size_t i = 0; i < one.number_.size(); ++i) {
      if (one.number_[i] != num.number_[i]) {
        return true;
      }
    }
    return (num.is_negative_ != one.is_negative_);
  }
  return true;
}

bool operator<(BigInt one, BigInt num) {
  if (one.is_negative_ != num.is_negative_) {
    return static_cast<int>(one.is_negative_) >
           static_cast<int>(num.is_negative_);
  }
  if (one.number_.size() != num.number_.size() && !one.is_negative_) {
    return one.number_.size() < num.number_.size();
  }
  if (one.number_.size() != num.number_.size() && one.is_negative_) {
    return one.number_.size() > num.number_.size();
  }
  if (one.is_negative_) {
    for (int i = one.number_.size() - 1; i >= 0; --i) {
      if (one.number_[i] != num.number_[i]) {
        return one.number_[i] > num.number_[i];
      }
    }
  } else {
    for (int i = one.number_.size() - 1; i >= 0; --i) {
      if (one.number_[i] != num.number_[i]) {
        return one.number_[i] < num.number_[i];
      }
    }
  }
  return one.number_.size() != num.number_.size();
}

bool operator>(BigInt one, BigInt num) {
  if (one.is_negative_ != num.is_negative_) {
    return static_cast<int>(one.is_negative_) <
           static_cast<int>(num.is_negative_);
  }
  if (one.number_.size() != num.number_.size() && !one.is_negative_) {
    return one.number_.size() > num.number_.size();
  }
  if (one.number_.size() != num.number_.size() && one.is_negative_) {
    return one.number_.size() < num.number_.size();
  }
  if (one.is_negative_) {
    for (int i = one.number_.size() - 1; i >= 0; --i) {
      if (one.number_[i] != num.number_[i]) {
        return one.number_[i] < num.number_[i];
      }
    }
  } else {
    for (int i = one.number_.size() - 1; i >= 0; --i) {
      if (one.number_[i] != num.number_[i]) {
        return one.number_[i] > num.number_[i];
      }
    }
  }
  return one.number_.size() != num.number_.size();
}

bool operator<=(BigInt one, BigInt num) {
  if (one.is_negative_ != num.is_negative_) {
    return one.is_negative_;
  }
  if (one.number_.size() != num.number_.size() && !one.is_negative_) {
    return one.number_.size() < num.number_.size();
  }
  if (one.number_.size() != num.number_.size() && one.is_negative_) {
    return one.number_.size() > num.number_.size();
  }
  if (one.is_negative_) {
    for (int i = one.number_.size() - 1; i >= 0; --i) {
      if (one.number_[i] != num.number_[i]) {
        return one.number_[i] > num.number_[i];
      }
    }
  } else {
    for (int i = one.number_.size() - 1; i >= 0; --i) {
      if (one.number_[i] != num.number_[i]) {
        return one.number_[i] < num.number_[i];
      }
    }
  }
  return true;
}

bool operator>=(BigInt one, BigInt num) {
  if (one.is_negative_ != num.is_negative_) {
    return static_cast<int>(one.is_negative_) <
           static_cast<int>(num.is_negative_);
  }
  if (one.number_.size() != num.number_.size() && !one.is_negative_) {
    return one.number_.size() > num.number_.size();
  }
  if (one.number_.size() != num.number_.size() && one.is_negative_) {
    return one.number_.size() < num.number_.size();
  }
  if (one.is_negative_) {
    for (int i = one.number_.size() - 1; i >= 0; --i) {
      if (one.number_[i] != num.number_[i]) {
        return one.number_[i] < num.number_[i];
      }
    }
  } else {
    for (int i = one.number_.size() - 1; i >= 0; --i) {
      if (one.number_[i] != num.number_[i]) {
        return one.number_[i] > num.number_[i];
      }
    }
  }
  return one.number_.size() == num.number_.size();
}

BigInt operator+(BigInt one, BigInt num) {
  BigInt val;
  if (!one.is_negative_ && !num.is_negative_) {
    val = one.Addition(num);
    val.is_negative_ = false;
  }
  if (one.is_negative_ && num.is_negative_) {
    val = one.Addition(num);
    val.is_negative_ = true;
  }
  if (one.is_negative_ && !num.is_negative_) {
    val = num.Substraction(one.Module());
    one.is_negative_ = true;
  }
  if (!one.is_negative_ && num.is_negative_) {
    val = one.Substraction(num.Module());
    num.is_negative_ = true;
  }
  return val;
}

BigInt operator-(BigInt one, BigInt num) {
  BigInt val;
  if (!one.is_negative_ && !num.is_negative_) {
    val = one.Substraction(num);
  }
  if (one.is_negative_ && num.is_negative_) {
    val = one.Substraction(num);
    num.is_negative_ = true;
  }
  if (one.is_negative_ && !num.is_negative_) {
    one.is_negative_ = false;
    val = one.Addition(num);
    val.is_negative_ = true;
    one.is_negative_ = true;
  }
  if (!one.is_negative_ && num.is_negative_) {
    num.is_negative_ = false;
    val = one.Addition(num);
    num.is_negative_ = true;
  }
  return val;
}

BigInt BigInt::operator+=(BigInt& num) {
  *this = *this + num;
  return *this;
}

BigInt BigInt::operator-=(BigInt& num) {
  *this = *this - num;
  return *this;
}

BigInt& BigInt::operator++() {
  BigInt val = 1;
  *this += val;
  return *this;
}

BigInt BigInt::operator++(int) {
  BigInt val = *this;
  ++*this;
  return val;
}

BigInt& BigInt::operator--() {
  BigInt val = 1;
  *this -= val;
  if (number_[number_.size() - 1] == 0 && number_.size() > 1) {
    number_.pop_back();
  }
  return *this;
}

BigInt BigInt::operator--(int) {
  BigInt val = *this;
  --*this;
  return val;
}

BigInt& BigInt::operator-() {
  SignChange();
  return *this;
}

BigInt operator*(BigInt one, BigInt num) {
  BigInt val;
  std::vector<bool> memory;
  memory.push_back(one.is_negative_);
  memory.push_back(num.is_negative_);
  one.is_negative_ = false;
  val = one.Multiply(num.Module());
  if (!one.IsNull() && !num.IsNull()) {
    val.is_negative_ = !(memory[0] == memory[1]);
  }
  one.is_negative_ = memory[0];
  num.is_negative_ = memory[1];
  return val;
}

BigInt BigInt::operator*=(BigInt& num) {
  *this = *this * num;
  return *this;
}

BigInt BigInt::operator/(BigInt& num) {
  std::vector<bool> memory;
  memory.push_back(is_negative_);
  memory.push_back(num.is_negative_);
  is_negative_ = false;
  num.is_negative_ = false;
  if (*this < num) {
    return 0;
  }
  BigInt result;
  result = Division(num);
  if (result.number_.empty()) {
    result.number_.push_back(0);
  }
  result.Reverse();
  if (memory[0] != memory[1]) {
    result.is_negative_ = true;
  }
  is_negative_ = memory[0];
  num.is_negative_ = memory[1];
  return result;
}

BigInt BigInt::operator/=(BigInt& num) {
  *this = *this / num;
  return *this;
}

BigInt BigInt::operator%(BigInt& num) {
  std::vector<bool> memory;
  memory.push_back(is_negative_);
  memory.push_back(num.is_negative_);
  BigInt val;
  if (static_cast<int>(memory[0]) <= static_cast<int>(memory[1])) {
    BigInt div = *this / num;
    BigInt mult = div * num;
    val = *this - mult;
  }
  if (static_cast<int>(memory[0]) > static_cast<int>(memory[1])) {
    is_negative_ = false;
    BigInt div = *this / num;
    BigInt mult = div * num;
    val = *this - mult;
    val.is_negative_ = true;
  }
  val.DeleteZeroes();
  if (val.number_.empty()) {
    val.number_.push_back(0);
  }
  return val;
}

BigInt BigInt::operator%=(BigInt& num) {
  *this = *this % num;
  return *this;
}

std::istream& operator>>(std::istream& iss, BigInt& num) {  // is
  std::string string;
  iss >> string;
  num = BigInt(string);
  return iss;
}

std::ostream& operator<<(std::ostream& oss, const BigInt& num) {  // os
  if (num.is_negative_) {
    oss << '-';
  }
  for (int i = num.number_.size() - 1; i >= 0; --i) {
    oss << num.number_[i];
  }
  return oss;
}

BigInt::~BigInt() {}

void BigInt::Reverse() {
  for (int i = 0; i < static_cast<int>(number_.size()); ++i) {
    if (i > (static_cast<int>(number_.size()) - 1) - i ||
        static_cast<int>(number_.size()) <= 1) {
      break;
    }
    std::swap(number_[i], number_[(number_.size() - 1) - i]);
  }
}

bool BigInt::IsNull() { return (number_.size() == 1 && number_[0] == 0); }

BigInt BigInt::Addition(BigInt num) {
  BigInt val;
  if (num.IsNull()) {
    val = *this;
    return val;
  }
  if (IsNull()) {
    val = num;
    return val;
  }
  if (number_.size() < num.number_.size()) {
    while (number_.size() < num.number_.size()) {
      number_.push_back(0);
    }
  }
  if (number_.size() > num.number_.size()) {
    while (number_.size() > num.number_.size()) {
      num.number_.push_back(0);
    }
  }
  val = AdditionSubmodule(num);
  return val;
}

BigInt BigInt::AdditionSubmodule(BigInt& num) {
  BigInt val;
  int mem = 0;
  int old_mem = 0;
  int digit = 0;
  for (size_t i = 0; i < num.number_.size(); ++i) {
    digit = num.number_[i] + number_[i] + old_mem;
    if (digit > (kBase - 1)) {
      digit = digit % kBase;
      mem = 1;
    }
    val.number_.push_back(digit);
    digit = 0;
    old_mem = mem;
    mem = 0;
  }
  if (old_mem > 0) {
    val.number_.push_back(old_mem);
  }
  return val;
}

BigInt BigInt::Substraction(BigInt& num) {
  BigInt val;
  if (*this == num) {
    val = 0;
    return val;
  }
  if (num.IsNull()) {
    val = *this;
    return val;
  }
  if (IsNull()) {
    val = num;
    val.SignChange();
    return val;
  }
  std::vector<bool> memory;
  memory.push_back(is_negative_);
  memory.push_back(num.is_negative_);

  if (Module() > num.Module()) {
    val = SubstractionDistributionMinued(num, memory);
  }
  if (Module() < num.Module()) {
    val = SubstractionDistributionSubtrahend(num, memory);
  }

  return val;
}

BigInt BigInt::SubstractionDistributionMinued(BigInt& num,
                                              std::vector<bool>& memory) {
  BigInt val;
  if (memory[0] == memory[1] && !memory[0]) {  // |a| > |b| a - b
    val = SubstractionSubmodule(num);
  }
  if (memory[0] != memory[1] && !memory[0]) {  // |a| > |b| a - (-b)
    val = Addition(num);
    num.is_negative_ = memory[1];
  }
  if (memory[0] == memory[1] && memory[0]) {  // |a| > |b| - a - (-b)
    val = SubstractionSubmodule(num);
    val.is_negative_ = memory[0];
    is_negative_ = memory[0];
    num.is_negative_ = memory[1];
  }
  if (memory[0] != memory[1] && memory[0]) {  // |a| > |b| - a - b
    val = Addition(num);
    val.is_negative_ = memory[0];
    is_negative_ = memory[0];
  }
  return val;
}

BigInt BigInt::SubstractionDistributionSubtrahend(BigInt& num,
                                                  std::vector<bool>& memory) {
  BigInt val;
  if (memory[0] == memory[1] && !memory[0]) {  // |a| < |b| a - b
    val = num.SubstractionSubmodule(*this);
    val.is_negative_ = true;
  }
  if (memory[0] != memory[1] && !memory[0]) {  // |a| < |b| a - (-b)
    val = Addition(num);
    num.is_negative_ = memory[1];
  }
  if (memory[0] == memory[1] && memory[0]) {  // |a| < |b| - a - (-b)
    val = num.SubstractionSubmodule(*this);
    is_negative_ = memory[0];
    num.is_negative_ = memory[1];
  }
  if (memory[0] != memory[1] && memory[0]) {  // |a| < |b| - a - b
    val = Addition(num);
    val.is_negative_ = memory[0];
    is_negative_ = memory[0];
  }
  return val;
}

BigInt BigInt::SubstractionSubmodule(BigInt& subtrahend) {
  if (subtrahend.number_.size() < number_.size()) {
    while (subtrahend.number_.size() < number_.size()) {
      subtrahend.number_.push_back(0);
    }
  }
  BigInt val;
  int mem = 0;
  int old_mem = 0;
  int digit = 0;
  for (size_t i = 0; i < number_.size(); ++i) {
    digit = number_[i] - subtrahend.number_[i] - old_mem;
    if (digit < 0) {
      digit = ((kBase + number_[i] - old_mem) - subtrahend.number_[i]) % kBase;
      mem = 1;
    }
    val.number_.push_back(digit);
    digit = 0;
    old_mem = mem;
    mem = 0;
  }
  return val;
}

BigInt BigInt::Multiply(BigInt num) {
  BigInt val;
  BigInt result = 0;
  if (IsNull() || num.IsNull()) {
    return result;
  }
  result = MultiplySubmodule(num, val, result);
  return result;
}

BigInt BigInt::MultiplySubmodule(BigInt& num, BigInt& val, BigInt& result) {
  std::vector<BigInt> arr;
  long long digit = 0;
  long long mem = 0;
  for (int i = 0; i < static_cast<int>(number_.size()); ++i) {
    for (int j = 0; j < static_cast<int>(num.number_.size()); ++j) {
      digit = number_[i] * num.number_[j] + mem;
      mem = digit / kBase;
      digit = digit % kBase;
      val.number_.push_back(digit);
      digit = 0;
    }
    if (mem > 0) {
      val.number_.push_back(mem);
      mem = 0;
    }
    if (i > 1) {
      val.Reverse();
      for (int k = 1; k < i; ++k) {
        val.number_.push_back(0);
      }
      val.Reverse();
    }
    arr.push_back(val);
    val = 0;
  }
  for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
    result += arr[i];
  }
  return result;
}

BigInt BigInt::Division(BigInt num) {
  BigInt val;
  BigInt result;
  int cnt = num.number_.size() - 1;
  Reverse();
  for (int i = 0; i <= cnt; ++i) {
    val.number_.push_back(number_[i]);
  }
  val.Reverse();
  if (val < num) {
    val.Reverse();
    cnt++;
    val.number_.push_back(number_[cnt]);
    val.Reverse();
  }
  Reverse();
  result = DivisionSubmodule(num, cnt, val);
  return result;
}

BigInt BigInt::DivisionSubmodule(BigInt& num, int cnt, BigInt& val) {
  BigInt result;
  while (cnt < static_cast<int>(number_.size())) {
    int64_t detected = BinSearch(num, val);
    result.number_.push_back(detected);
    BigInt multed = num.MultSingle(detected);
    val -= multed;
    val.DeleteZeroes();
    cnt++;
    if (cnt < static_cast<int>(number_.size())) {
      val.Reverse();
      if (val.number_.size() == 1 && val.number_[0] == 0) {
        val.number_[0] = number_[number_.size() - cnt - 1];
      } else {
        val.number_.push_back(number_[number_.size() - cnt - 1]);
      }
      val.Reverse();
    }
  }
  return result;
}

void BigInt::DeleteZeroes() {
  while (number_.size() > 1 && number_.back() == 0) {
    number_.erase(number_.end() - 1);
  }
  if (number_.size() == 1 && number_[0] == 0) {
    is_negative_ = false;
  }
}

BigInt BigInt::MultSingle(int64_t num) {
  BigInt result;
  BigInt multed;
  multed.number_.push_back(num);
  result = *this * multed;
  return result;
}

int64_t BigInt::BinSearch(BigInt& div, BigInt& sub) {
  int64_t required = 0;
  int64_t left = 0;
  const int64_t kKTen = 10;
  int64_t right = kKTen;
  while (left <= right) {
    int64_t mid = (left + right) / 2;
    BigInt multed = div.MultSingle(mid);
    if (multed <= sub) {
      required = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return required;
}

BigInt& BigInt::Module() {
  if (is_negative_) {
    SignChange();
  }
  return *this;
}

void BigInt::SignChange() {
  if (!IsNull()) {
    if (is_negative_) {
      BigInt val = 0;
      is_negative_ = val.is_negative_;
    } else {
      is_negative_ = true;
    }
  }
}