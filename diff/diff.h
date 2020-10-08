#pragma once

#include <iostream>
#include <vector>
#include <string>

class DiffManager{
public:
  class Lines {
  private:
    std::vector<int> starts;
    std::vector<int> hashes;
  public:
    void emplace_back(int start, int hash) {
      starts.push_back(start);
      hashes.push_back(hash);
    }
    std::vector<int> const& get_starts() const {
      return starts;
    }
    std::vector<int> const& get_hashes() const {
      return hashes;
    }
    size_t size() const {
      if (starts.size() != hashes.size()) {
        throw std::logic_error("size of starts != size of hashes");
      }
      return starts.size();
    }
  };
  
  struct Interval {
    int start;
    int end;
  };

  enum class ChangeType {
    Addition = 'a',
    Change = 'c',
    Deletion = 'd'
  };
private:
  std::istream& oldFile;
  std::istream& newFile;
  Lines oldLines;
  Lines newLines;
  std::vector<int> indexes;
  
public:
  DiffManager(std::istream& oldfile, std::istream& newfile);
  void Print(std::ostream& os);
  
private:
  static DiffManager::Lines ReadLines(std::istream& input);
  void PrintStep(std::ostream& os, Interval Iold, Interval Inew);
  void PrintHeadLine(std::ostream& os, Interval Iold, Interval Inew, ChangeType mode);
  static void PrintLines(std::ostream& os, std::istream& is, std::vector<int> const& lineStarts, DiffManager::Interval I, char symbol);
};

namespace LCS {
  class Manager {
  private:
    std::vector<int> const& X;
    std::vector<int> const& Y;
    std::vector<std::vector<int>> C;

    static std::vector<std::vector<int>> LCS(std::vector<int> const& X, std::vector<int> const& Y);

    static void backtrack(
        std::vector<int>& idx, 
        std::vector<std::vector<int>> const& C, 
        std::vector<int> const& X, 
        std::vector<int> const& Y, 
        int i, int j);
  public:
    Manager(std::vector<int> const& X, std::vector<int> const& Y)
    : X(X)
    , Y(Y)
    {}

    std::vector<int> get_subsequence() {
      if (C.empty()) {
        C = LCS(X,Y);
      }
      std::vector<int> idx; 
      backtrack(idx, C, X, Y, X.size()-1, Y.size()-1);
      return idx;
    }
  };
}
