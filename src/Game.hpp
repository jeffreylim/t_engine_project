#ifndef GAME_HPP_
#define GAME_HPP_

#include "Shape.hpp"

#include <array>
#include <fstream>
#include <iostream>

/**
 *  Game class. Main class for this project.
 *  All operations (Shape drawing, checking and removal of filled rows) occurs here.
 */
class Game {

public:

   //---------------------------------------------------------
   // static constants
   //---------------------------------------------------------
   static constexpr uint8_t BOARD_WIDTH = 10;
   static constexpr uint8_t BOARD_HEIGHT = 101;
   static constexpr uint16_t ROW_COMPLETED = (1 << BOARD_WIDTH) - 1;


   Game() {

      init();
   }


   /**
    * Initializes the board to zeros.
    */
   void init();

   /**
    * Main starting point.
    * For each input line, draws the sequence of shapes. Outputs board height at end of input line.
    * @param in_stream. input stream class.
    * @param out_stream. output stream class.
    */
   void start(std::ifstream &in, std::ofstream &out);


   /**
    * This member function contains the workflow of all operations needed for drawing a shape.
    * Correct position navigation -> shape drawing -> checking and removing filled rows.
    * @param shape representation. the actual shape to be projected.
    * @param the column as specify in the input token.
    */
   void workflow(const uint16_t shape, const uint8_t column);


   /**
    * Checks the surrounding areas for conflicts between the incoming Shape and existing Board.
    * Shifts Shape up a row if neccessary.
    * @param shape_representation. the actual shape to be projected.
    * @param the column as specify in the input token.
    */
   uint8_t findPosition(const uint16_t shape, const uint8_t column) const;


   /**
    * Shape drawing. Each modulo 4 represents a different row in the Shape.
    * Checks the 12 bits Shape representation for ones and union it with the Board accordingly.
    * @param shape representation. the actual shape to be projected.
    * @param the column as specify in the input token.
    * @param projected_height. The final height/row of the leftmost bottom block.
    */
   void draw(const uint16_t shape, const uint8_t column, const uint8_t lower_y);


   /**
    * Checks and remove filled rows.
    * Atmost two rows can be filled for each incoming Shape. This also holds for L and J shapes.
    * @param bottom_most_row of the newly drawn Shape.
    */
   void handlesFilledRows(const uint8_t lower_y);


   /**
    * Returns the maximum height of the 10 columns.
    */
   const uint8_t maxHeight() const;


   /**
    * Prints the board up to height = DEBUG_PRINT_UPTO_ROW.
    * @param output stream.
    * @param Game object.
    */
   friend std::ostream& operator<<(std::ostream &out, const Game &rhs) {

      static constexpr uint8_t DEBUG_PRINT_UPTO_ROW = 10;
      for (int i=DEBUG_PRINT_UPTO_ROW; i>=0; --i) {
         for (int j=0; j<BOARD_WIDTH; ++j)
            if (rhs.board_[i] & 1<<j)
               out << 1 << ' ';
            else
               out << 0 << ' ';
         out << '\n';
      }
      return out;
   }

private:

   //---------------------------------------------------------------------
   // private data members
   //---------------------------------------------------------------------

   /**
    * Each element of the array represents the 10 columns using 10 bits
    */
   std::array<uint16_t, BOARD_HEIGHT> board_;

   /**
    * Cache the current height of each column.
    */
   std::array<uint8_t, BOARD_WIDTH> column_height_;


}; // class Game

#endif // GAME_HPP_
