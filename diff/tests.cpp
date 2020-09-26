#define CATCH_CONFIG_MAIN

#include "diff.h"

#include <catch2/catch.hpp>
#include <fstream>
#include <sstream>

TEST_CASE("1") {
  std::ifstream file_old ("testfiles/old.txt");
  std::ifstream file_new ("testfiles/new1.txt");
  std::ifstream file_diff ("testfiles/test_diff_1.txt");
  std::string diff_output;
  for (char ch; (ch = file_diff.get()) != EOF;) {
    diff_output += ch;
  }
  std::stringstream stream;
  DiffManager dm(file_old, file_new, stream);
  dm.Print();
  REQUIRE(stream.str() == diff_output);
}

TEST_CASE("2") {
  std::ifstream file_old ("testfiles/old.txt");
  std::ifstream file_new ("testfiles/new2.txt");
  std::ifstream file_diff ("testfiles/test_diff_2.txt");
  std::string diff_output;
  for (char ch; (ch = file_diff.get()) != EOF;) {
    diff_output += ch;
  }
  std::stringstream stream;
  DiffManager dm(file_old, file_new, stream);
  dm.Print();
  REQUIRE(stream.str() == diff_output);
}