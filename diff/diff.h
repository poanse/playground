#pragma once

#include <iostream>
#include <vector>
#include <string>

class DiffManager{
private:
  std::istream& oldFile;
  std::istream& newFile;
  std::ostream& os;
  std::vector<std::string> oldLines;
  std::vector<std::string> newLines;
  std::vector<int> oldHashes;
  std::vector<int> newHashes;
  std::vector<std::vector<int>> LCS_table;
  std::vector<int> indexes;
  
public:
  DiffManager(std::istream& oldfile, std::istream& newfile, std::ostream& os);
  void Print();
  
private:
  void PrintStep(int oldIdx, int newIdx, int oldIdxPrev, int newIdxPrev);
  void PrintHeadLine(int oldIdxPrev, int idx, int newIdxPrev, int new_idx, char mode);
  void PrintAddition(int oldIdx, int newIdx, int oldIdxPrev, int newIdxPrev);
  void PrintDeletion(int oldIdx, int newIdx, int oldIdxPrev, int newIdxPrev);
  void PrintChange(int oldIdx, int newIdx, int oldIdxPrev, int newIdxPrev);
  
  std::vector<std::string> _ReadLines(std::istream& input);
  std::vector<int> _ComputeHashes(const std::vector<std::string>& strings);
  std::vector<std::vector<int>> LCS( std::vector<int> const& X, 
                                     std::vector<int> const& Y );
  void backtrack(std::vector<int>& idx, std::vector<std::vector<int>> const& C, 
    std::vector<int> const& X, std::vector<int> const& Y, int i, int j);
};