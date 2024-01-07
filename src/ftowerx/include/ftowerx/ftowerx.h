#pragma once

#include <array>
#include <optional>
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
  size_t size() const { return m_stack.size(); }
  bool empty() const { return m_stack.empty(); }
  T pop() {
    if (m_stack.empty()) {
      throw std::out_of_range("calling pop on an empty UniformStack");
    }
    auto var{std::move(m_stack.back())};
    m_stack.pop_back();
    return var;
  };
  std::optional<T> push(T &&var) {
    if (!m_stack.empty() && !Compare{}(var, m_stack.back()))
      return std::move(var);
    m_stack.push_back(std::move(var));
    return {};
  };
  const T &operator[](size_t index) const { return m_stack[index]; }

private:
  std::vector<T> m_stack;
};

auto Less{[](std::unique_ptr<Disk> &left, std::unique_ptr<Disk> &right) {
  return *left < *right;
}};
using Stack = UniformStack<std::unique_ptr<Disk>, decltype(Less)>;

// In the game of TOH you either win or die.
class GameOfTOH {
public:
  enum TOWERS : size_t {
    TOWER_1 = 0,
    TOWER_2 = 1,
    TOWER_3 = 2,
    TOWER_END = 3,
  };
  GameOfTOH(size_t size) {
    while (size > 0) {
      m_towers[TOWER_1].push(std::make_unique<Disk>(size--));
    }
  }
  const Stack &getTower(TOWERS index) { return m_towers[index]; }
  bool isSourceTower(TOWERS index) { return &m_towers[index] == m_srcTower; }
  void selectOrMoveToTower(TOWERS index) {
    if (index == TOWER_END) {
      m_srcTower = nullptr;
      return;
    }
    if (m_srcTower && moveDisk(m_srcTower, &m_towers[index])) {
      m_srcTower = nullptr;
    } else {
      if (!m_towers[index].empty()) {
        m_srcTower = &m_towers[index];
      }
    }
  }

private:
  bool moveDisk(Stack *src, Stack *dst) {
    if (!src->empty()) {
      auto disk{src->pop()};
      std::optional<std::unique_ptr<Disk>> rejectedDisk{};
      if (rejectedDisk = dst->push(std::move(disk))) {
        src->push(std::move(*std::move(rejectedDisk)));
        return false;
      }
      return true;
    }
    return false;
  }

private:
  std::array<Stack, TOWER_END> m_towers{};
  Stack *m_srcTower{};
};
} // namespace toh
