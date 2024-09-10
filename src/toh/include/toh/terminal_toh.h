#pragma once

#include <chrono>
#include <map>

#include "ftxui/component/screen_interactive.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "libtoh/toh_model.h"

/**
 * @class GameViewer
 * @brief Responsible for rendering the visual representation of the Tower of
 * Hanoi game.
 *
 * The GameViewer class provides an interface to display the current state of
 * the game using FTXUI components. It manages the creation of UI elements, such
 * as the top bar and the towers, and supports rendering the game state in a
 * terminal-based interface.
 *
 * ### Example
 * ```cpp
 * #include "ftxui/component/screen_interactive.hpp"
 * #include "libtoh/toh_model.h"
 * #include "toh/terminal_toh.h"
 *
 * using namespace std;
 * using namespace ftxui;
 * using namespace toh;
 *
 * int main() {
 *   auto screen{ScreenInteractive::Fullscreen()};
 *
 *   Game game{3};
 *   GameViewer viewer{game};
 *   GameController controller{game, screen};
 *
 *   auto component{viewer.createView()};
 *   component |= CatchEvent(controller);
 *
 *   screen.Loop(component);
 * }
 * ```
 */
class GameViewer {
public:
  /**
   * @brief Constructs a GameViewer object.
   * @param game A reference to a Game instance to be viewed.
   */
  explicit GameViewer(const toh::Game &game);

  /**
   * @brief Default copy constructor.
   *
   * @param src The source GameViewer object to copy from.
   */
  GameViewer(const GameViewer &src) = default;

  /**
   * @brief Default move constructor.
   *
   * @param src The source GameViewer object to move from.
   * @note This operation is noexcept.
   */
  GameViewer(GameViewer &&src) noexcept = default;

  /**
   * @brief Deleted copy assignment operator.
   *
   * Copy assignment is disabled for GameViewer.
   * @param src The source GameViewer object (unused).
   * @return Deleted.
   */
  GameViewer &operator=(const GameViewer &src) = delete;

  /**
   * @brief Deleted move assignment operator.
   *
   * Move assignment is disabled for GameViewer.
   * @param src The source GameViewer object (unused).
   * @return Deleted.
   */
  GameViewer &operator=(GameViewer &&src) noexcept = delete;

  /**
   * @brief Get the FTXUI component representing the game view.
   * @return The component for the game view.
   *
   * @note This function can only be called on lvalue objects, not rvalues.
   */
  ftxui::Component createView() const &;

  /**
   * @brief Deleted overload to prevent calling createView on rvalue objects.
   */
  ftxui::Component createView() const && = delete;

private:
  /**
   * @brief Creates the legend component for the UI.
   *
   * @details The legend displays useful information such as the elapsed time
   * and a help for the control keys, providing context and guidance to the
   * user during gameplay.
   *
   * @return The FTXUI element representing the top bar.
   */
  ftxui::Element createLegend() const;

  /**
   * @brief Creates the visual representation of the towers.
   * @return The FTXUI element representing the towers.
   */
  ftxui::Element createTowers() const;

  /**
   * @brief Creates the visual representation of a single tower.
   * @param tower The vector representing the disks on the tower.
   * @param is_selected Whether the tower is currently selected.
   * @return The FTXUI element representing the tower.
   */
  ftxui::Element createTower(const std::vector<size_t> &tower,
                             bool is_selected) const;

  /**
   * @brief Resets the completion time if the number of disks has changed or
   * sets the start time.
   */
  void resetCompletionTimeIfNeeded() const;

  /**
   * @brief Updates the recorded completion time when the game is finished.
   */
  void updateCompletionTime() const;

  /**
   * @brief Formats the completion duration into a human-readable string.
   *
   * @return A string representing the formatted completion time.
   */
  std::string formatCompletionDuration() const;

private:
  const toh::Game &m_game; ///< A reference to the Game instance being viewed.
  mutable std::chrono::steady_clock::time_point
      m_startTime{}; ///< The start time of the game session.
  mutable std::chrono::steady_clock::duration
      m_completionDuration{}; ///< The time taken to complete the game, in
                              ///< milliseconds.
};

/**
 * @class GameController
 * @brief Handles user input and updates the game state.
 *
 * ### Example
 * ```cpp
 * #include "ftxui/component/screen_interactive.hpp"
 * #include "libtoh/toh_model.h"
 * #include "toh/terminal_toh.h"
 *
 * using namespace std;
 * using namespace ftxui;
 * using namespace toh;
 *
 * int main() {
 *   auto screen{ScreenInteractive::Fullscreen()};
 *
 *   Game game{3};
 *   GameViewer viewer{game};
 *   GameController controller{game, screen};
 *
 *   auto component{viewer.createView()};
 *   component |= CatchEvent(controller);
 *
 *   screen.Loop(component);
 * }
 * ```
 */
class GameController {
public:
  /**
   * @brief Constructs a GameController with the specified game and screen.
   * @param game A reference to the game to control.
   * @param screen A reference to the FTXUI screen for rendering.
   */
  explicit GameController(toh::Game &game, ftxui::ScreenInteractive &screen);

  /**
   * @brief Default copy constructor.
   *
   * @param src The source GameController object to copy from.
   */
  GameController(const GameController &src) = default;

  /**
   * @brief Default move constructor.
   *
   * @param src The source GameController object to move from.
   * @note This operation is noexcept.
   */
  GameController(GameController &&src) noexcept = default;

  /**
   * @brief Deleted copy assignment operator.
   *
   * Copy assignment is disabled for GameController.
   * @param src The source GameController object (unused).
   * @return Deleted.
   */
  GameController &operator=(const GameController &src) = delete;

  /**
   * @brief Deleted move assignment operator.
   *
   * Move assignment is disabled for GameController.
   * @param src The source GameController object (unused).
   * @return Deleted.
   */
  GameController &operator=(GameController &&src) noexcept = delete;

  /**
   * @brief Processes user input events and updates the game.
   * @param event The input event to handle.
   * @return True if the event was handled, false otherwise.
   */
  bool operator()(ftxui::Event event) &;

  /**
   * @brief Deleted overload to prevent calling operator() on rvalue objects.
   */
  bool operator()(ftxui::Event event) && = delete;

private:
  /**
   * @brief Handles the movement of disks based on the input event.
   *
   * @param event The input event to process.
   * @return True if the movement event was handled, false otherwise.
   */
  bool handleMovement(ftxui::Event event);

  /**
   * @brief Handles events that modify the game, such as resizing the number of
   * disks.
   *
   * @param event The input event related to game modification.
   * @return True if the modification event was handled, false otherwise.
   */
  bool handleGameModification(ftxui::Event event);

  /**
   * @brief Modifies the game size by adding or removing disks.
   *
   * @param delta The number of disks to add (positive) or remove (negative).
   */
  void modifyGameSize(int delta);

private:
  toh::Game &m_game; ///< Reference to the game being controlled.
  ftxui::ScreenInteractive
      &m_screen; ///< Reference to the FTXUI screen for rendering.
};
