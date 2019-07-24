
   Run instructions:
   1) make
   2) ./project (reads from ./input.txt, writes to ./output.txt)
   3) make clean
   
   
   Optimizations:
   1) Cache-friendly bitset representations and bitwise programming.
   2) Filled rows equivalent to the integer 2^10 - 1 = 1023
   
   
   /**
    * Each Shape is uniquely represented by 12 bits simulating a 3x4 grid.
    * Bottom row is the least significant 4 bits.
    * Top row is the most significant 4 bits.
    */
   enum : uint8_t {
      Q_REPRESENTATION = 0x33,   //0000 0011 0011
      Z_REPRESENTATION = 0x36,   //0000 0011 0110
      S_REPRESENTATION = 0x63,   //0000 0110 0011
      T_REPRESENTATION = 0x72,   //0000 0111 0010
      I_REPRESENTATION = 0xF,    //0000 0000 1111
      L_REPRESENTATION = 0x113,  //0001 0001 0011
      J_REPRESENTATION = 0x223   //0010 0010 0011
   };
   
   
   /**
    * Mapping of Shape Names to their Shape representations.
    */
    static const std::unordered_map<char, uint16_t> representation_= {
                                                                        {'I', I_REPRESENTATION},
                                                                        {'J', J_REPRESENTATION},
                                                                        {'L', L_REPRESENTATION},
                                                                        {'Q', Q_REPRESENTATION},
                                                                        {'S', S_REPRESENTATION},
                                                                        {'T', T_REPRESENTATION},
                                                                        {'Z', Z_REPRESENTATION}
                                                                     };
   
   
   /**
    * Classes.
    */

   main.cpp ==> initializes the input and output streams and starts the Game. 
   
   Game.hpp, Game.cpp ==> Main class for this project.
   All operations (Shape drawing, checking and removal of filled rows) occurs here.
   
   Shape.hpp ==> Shape definitions and representations.
   Contains only enums and static const type declarations.
