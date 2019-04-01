#include "Game.hpp"

int main(int argc, char *argv[]) {

   std::ios::sync_with_stdio(0);
   std::cin.tie(0);

   static const std::string input_file {"input.txt"};
   std::ifstream in_stream(input_file, std::ifstream::in);
   if (!in_stream) {
      std::cerr << "Invalid input file. Expected: ./" << input_file << std::endl;
      return 1;
   }

   static const std::string output_file {"output.txt"};
   std::ofstream out_stream(output_file, std::ofstream::out);
   if (!out_stream) {
      std::cerr << "Unable to generate output file. Expected: ./" << output_file << std::endl;
      return 1;
   }

   Game game;
   game.start(in_stream, out_stream);

   in_stream.close();
   out_stream.close();
   
   return 0;
}
