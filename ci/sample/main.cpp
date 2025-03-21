#include <Match3/Game.hpp>
#include <cstdlib>

using namespace match3;

int main(int /*argc*/, char** /*argv*/) {
  Game game;
  game.resize({8, 8});
  game.setTypes(Types({{"a"}, {"b"}, {"c"}}));
  game.fillBoard();

  return EXIT_SUCCESS;
}
