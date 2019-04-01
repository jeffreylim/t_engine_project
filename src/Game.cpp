#include "Game.hpp"

#include <algorithm>

inline void Game::init() {

    board_.fill(0);
    column_height_.fill(0);
}


void Game::start(std::ifstream &in, std::ofstream &out) {

   char c1, c2;
   
   while (in >> c1 >> c2) {
      workflow(representation_.at(c1), c2-'0');
      if (in.peek() == '\n') {
         out << static_cast<unsigned short>(maxHeight()) << '\n';
         init();
      } else in.ignore(); 
   }
}


void Game::workflow(const uint16_t shape, const uint8_t column) {

   uint8_t lower_y = findPosition(shape, column);

   draw(shape, column, lower_y);

   handlesFilledRows(lower_y);
}


inline uint8_t Game::findPosition(const uint16_t shape, const uint8_t column) const {

  uint8_t lower_y = 0;                        /// Each Shape affects at most 4 columns.
  for (uint8_t i=0; i<SHAPE_DIM_WIDTH; ++i)  /// Least significant 4 bits represents the bottom row.
      if (shape & 1<<i)
          lower_y = std::max(lower_y, column_height_[column + i]);

  /// Each Shape representation is 12 bits. Each modulo 4 represents a different row in the Shape.
  for (uint8_t i=0; i<SHAPE_NUM_BITS; ++i)
      if ((shape & 1<<i) &&
          (board_[lower_y + (i / SHAPE_DIM_WIDTH)] & 1<<(i % SHAPE_DIM_WIDTH + column))) {
          ++lower_y;   // conflict. Shift shape up a row.
          i = 0;
      }

  return lower_y;
}

inline void Game::draw(const uint16_t shape,
                       const uint8_t column,
                       const uint8_t lower_y) {

   /// Actual drawing of Shape takes place here.
   /// Checks the 12 bits Shape representation for ones and union it with the Board accordingly.
   /// Each modulo 4 represents a different row in the Shape.
   for (uint8_t i=0; i<SHAPE_NUM_BITS; ++i)
      if (shape & 1<<i) {
         board_[lower_y + (i / SHAPE_DIM_WIDTH)] |= 1 << (i % SHAPE_DIM_WIDTH + column);
         column_height_[(i % SHAPE_DIM_WIDTH) + column] = lower_y + (i / SHAPE_DIM_WIDTH) + 1;
      }
}


void Game::handlesFilledRows(const uint8_t lower_y) {

   uint8_t filled_row_bitmask = 0;
   filled_row_bitmask |= (board_[lower_y] == ROW_COMPLETED) ? 1<<0 : filled_row_bitmask;
   filled_row_bitmask |= (board_[lower_y + 1] == ROW_COMPLETED) ? 1<<1 : filled_row_bitmask;

   if (!filled_row_bitmask) return;      //No filled rows.

   // Atmost two rows can be filled for each incoming Shape. This also holds for L and J shapes.
   const uint8_t max_height = maxHeight();

   if (filled_row_bitmask == 3) {   //Two filled rows            
   
      for (uint8_t i=lower_y+2; i<=max_height+1; ++i)
          board_[i-2] = board_[i];
      for (uint8_t i=0; i<BOARD_WIDTH; ++i)
          column_height_[i] -= 2;
   
   } else {                         //One filled row.
   
      for (uint8_t i=lower_y+filled_row_bitmask; i<=max_height; ++i)
          board_[i-1] = board_[i];
      for (uint8_t i=0; i<BOARD_WIDTH; ++i)
          --column_height_[i];
   }
}


inline const uint8_t Game::maxHeight() const {

   return *std::max_element(column_height_.begin(), column_height_.end());
}
