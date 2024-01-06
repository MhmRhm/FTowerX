#pragma once

#include <stack>
#include <vector>

class Disk {};

template <typename T> class StackManager {
public:
  T pop() {
    if (!m_stack.size()) {
      throw std::out_of_range("calling pop on an empty StackManager");
    }
    auto var{std::move(m_stack.top())};
    m_stack.pop();
    return var;
  };
  bool push(T &&) { return false; };

private:
  std::stack<T> m_stack;
};
