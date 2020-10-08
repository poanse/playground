#define CATCH_CONFIG_MAIN

#include "diff.h"

#include <catch2/catch.hpp>
#include <fstream>
#include <sstream>

TEST_CASE("All") {
  std::ifstream file_N ("testfiles/Ntests.txt");
  int N = 0;
  file_N >> N;
  for (auto i=1; i <= N; ++i) {
    std::ifstream file_old ("testfiles/test"+std::to_string(i)+"_old.txt");
    std::ifstream file_new ("testfiles/test"+std::to_string(i)+"_new.txt");
    std::ifstream file_diff ("testfiles/test"+std::to_string(i)+"_diff.txt");

    std::string diff_output;
    std::getline(file_diff, diff_output, char(EOF));
    
    std::stringstream stream;
    DiffManager dm(file_old, file_new);
    dm.Print(stream);
    REQUIRE(stream.str() == diff_output);
  }
}
