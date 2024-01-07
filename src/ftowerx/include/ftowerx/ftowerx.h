#pragma once

#include <stack>
#include <vector>

namespace toh {

class Disk {
public:
  Disk(size_t size) : m_size{size} {}
  size_t getSize() const { return m_size; }

private:
  size_t m_size{};
};

bool operator<(const Disk &lhs, const Disk &rhs) {
  return lhs.getSize() < rhs.getSize();
}

template <typename T, class Compare = std::less<>> class UniformStack {
public:
  T pop() {
    if (m_stack.empty()) {
      throw std::out_of_range("calling pop on an empty StackManager");
    }
    auto var{std::move(m_stack.top())};
    m_stack.pop();
    return var;
  };
  bool push(T &&var) {
    if (!m_stack.empty() && !Compare{}(var, m_stack.top()))
      return false;
    m_stack.push(std::move(var));
    return true;
  };

private:
  std::stack<T> m_stack;
};

auto Less{[](std::unique_ptr<Disk> &left, std::unique_ptr<Disk> &right) {
  return *left < *right;
}};
using Stack = UniformStack<std::unique_ptr<Disk>, decltype(Less)>;
} // namespace toh
