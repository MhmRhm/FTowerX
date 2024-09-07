#pragma once

/**
 * @namespace toh
 * @brief Contains classes and enumerations for implementing the Tower of Hanoi
 * game.
 */
namespace toh {

/**
 * @brief Solves the Tower of Hanoi puzzle and records the disk moves.
 *
 * @tparam ChoiceType The type representing the tower (e.g., char, int, etc.).
 * @param selections A vector to store the source and destination of each move.
 * @param disk The number of disks to move.
 * @param src The source tower.
 * @param tmp The temporary (auxiliary) tower.
 * @param dst The destination tower.
 *
 * This function recursively solves the Tower of Hanoi puzzle, pushing each move
 * (from the source to the destination) into the selections vector. Each move is
 * represented by a pair of values indicating the source and destination towers.
 */
template <typename ChoiceType>
void solveToh(std::vector<ChoiceType> &selections, size_t disk, ChoiceType src,
              ChoiceType tmp, ChoiceType dst) {
  if (disk > 0) {
    // Move n-1 disks from src to tmp using dst as auxiliary
    solveToh(selections, disk - 1, src, dst, tmp);
    // Move the nth disk from src to dst
    selections.push_back(src);
    selections.push_back(dst);
    // Move the n-1 disks from tmp to dst using src as auxiliary
    solveToh(selections, disk - 1, tmp, src, dst);
  }
}

/**
 * @enum Position
 * @brief Represents the position of the towers in the Tower of Hanoi game.
 */
enum Position : uint64_t {
  Left = 0, ///< The left tower.
  Middle,   ///< The middle tower.
  Right,    ///< The right tower.
  End       ///< Indicates an invalid or no selection.
};

/**
 * @class Game
 * @brief Manages the state and operations of the Tower of Hanoi game.
 *
 * The Game class allows selecting towers, moving disks, and checking if the
 * game is complete. It handles the gameplay logic of the Tower of Hanoi.
 *
 * ### Example
 * ```cpp
 * #include "toh_model.h"
 *
 * using namespace std;
 * using namespace toh;
 *
 * int main() {
 *   Game game{3};
 *   vector<Position> play{Left,  Right,  Left, Middle, Right, Middle, Left,
 *                         Right, Middle, Left, Middle, Right, Left,   Right};
 *   for (auto &&choice : play) {
 *     game.select(choice);
 *   }
 *   return game.isFinished();
 * }
 * ```
 */
class Game {
public:
  /**
   * @brief Constructs a new Game with a specified number of disks.
   * @param size The number of disks in the game.
   */
  Game(size_t size);

  /**
   * @brief Copy constructor for the Game class.
   * @param src The game instance to copy from.
   */
  Game(const Game &src) = default;

  /**
   * @brief Move constructor for the Game class.
   * @param src The game instance to move from.
   */
  Game(Game &&src) noexcept = default;

  /**
   * @brief Copy assignment operator.
   * @param src The game instance to copy from.
   * @return A reference to the current game instance.
   */
  Game &operator=(const Game &src) = default;

  /**
   * @brief Move assignment operator.
   * @param src The game instance to move from.
   * @return A reference to the current game instance.
   */
  Game &operator=(Game &&src) noexcept = default;

  /**
   * @brief Destructor for the Game class.
   */
  virtual ~Game() = default;

  /**
   * @brief Equality comparison operator.
   * @param other The other game instance to compare.
   * @return true if the two game instances are equal, false otherwise.
   */
  [[nodiscard]] bool operator==(const Game &other) const = default;

  /**
   * @brief Selects a tower by its position.
   * @param position The position of the tower to select.
   *
   * If no tower is currently selected, this method selects the specified tower.
   * If a tower is already selected, it attempts to move a disk from the
   * previously selected tower to the new one, following the rules of the Tower
   * of Hanoi game. After a successful move, the selection is reset.
   */
  void select(Position position);

  /**
   * @brief Checks if the game is finished.
   * @return true if the game is finished, false otherwise.
   */
  [[nodiscard]] bool isFinished() const;

  /**
   * @brief Gets the disks from a tower at the specified position.
   * @param position The position of the tower.
   * @return A constant reference to the vector of disk sizes for the selected
   * tower.
   */
  const std::vector<size_t> &getTower(Position position) const;

  /**
   * @brief Checks if the specified tower is currently selected.
   * @param position The position of the tower to check.
   * @return true if the given tower is selected, false otherwise.
   *
   * This method verifies whether the tower at the specified position is the one
   * currently selected.
   */
  [[nodiscard]] bool isSelected(Position position) const;

private:
  /**
   * @brief Moves a disk from one tower to another.
   * @param from The position of the tower to move a disk from.
   * @param to The position of the tower to move the disk to.
   * @return true if the move is successful, false otherwise.
   *
   * This method moves a disk from the 'from' tower to the 'to' tower, following
   * the Tower of Hanoi rules (a larger disk cannot be placed on top of a
   * smaller disk).
   */
  bool move(Position from, Position to);

private:
  std::vector<std::vector<size_t>> m_towers{
      {}, {}, {}};                     ///< The towers in the game.
  Position m_selection{Position::End}; ///< The currently selected tower.
};

} // namespace toh
