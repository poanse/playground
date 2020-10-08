#include "diff.h"

#include <algorithm>
#include <functional>

using namespace std;

DiffManager::DiffManager(istream& oldfile, istream& newfile) 
  :oldFile(oldfile)
  ,newFile(newfile)
{
  oldLines = ReadLines(oldFile);
  newLines = ReadLines(newFile);
  LCS::Manager lcsManager(oldLines.get_hashes(), newLines.get_hashes());
  indexes = lcsManager.get_subsequence();
  reverse(begin(indexes), end(indexes));
}

DiffManager::Lines DiffManager::ReadLines(istream& input) {
  DiffManager::Lines lines;
  string str;
  auto hasher = hash<string>();
  int start = 0;
  while (getline(input, str)) {
    int hash = hasher(str);
    lines.emplace_back(start, hash);
    if (input.peek() == EOF) break;
    start = input.tellg();
  }
  input.clear();
  return lines;
}

std::vector<std::vector<int>> LCS::Manager::LCS(std::vector<int> const& X, 
  std::vector<int> const& Y)
{
  size_t m = X.size();
  size_t n = Y.size();
  std::vector<std::vector<int>> C(m + 1);
  for (auto& row : C) {
    row.resize(n + 1);
  }
  for (size_t i = 0; i < m; ++i){
    for (size_t j = 0; j < n; ++j){
      if (X[i] == Y[j]) { //i-1 and j-1 if reading X & Y from zero
        C[i+1][j+1] = C[i][j] + 1;
      } else {
        C[i+1][j+1] = std::max(C[i+1][j], C[i][j+1]);
      }
    }
  }
  return C;
}

void LCS::Manager::backtrack(vector<int>& idx, vector<vector<int>> const& C, vector<int> const& X, vector<int> const& Y, int i, int j) {
  if ((i < 0) || (j < 0)) {
    return;
  } else if (X[i] == Y[j]) {
    idx.push_back(i);
    backtrack(idx, C, X, Y, i-1, j-1);
  } else if (C[i+1][j] >= C[i][j+1]) {
    backtrack(idx, C, X, Y, i, j-1);
  } else {
    backtrack(idx, C, X, Y, i-1, j);
  }
}

void DiffManager::Print(ostream& os) {
  auto const& oldHashes = oldLines.get_hashes();
  auto const& newHashes = newLines.get_hashes();
  auto GetNewIdx = [&](int oldIdx_, int newIdxPrev){
    auto hash = oldHashes[oldIdx_];
    auto it = find(newHashes.begin() + newIdxPrev, newHashes.end(), hash);
    return distance(newHashes.begin(), it);
  };
  Interval Iold = {0, 0};
  Interval Inew = {0, 0};
  for (auto i=0; i<indexes.size(); ++i) {
    Iold.end = indexes[i];
    Inew.end = GetNewIdx(Iold.end, Inew.start);
    PrintStep(os, Iold, Inew);
    Iold.start = Iold.end + 1;
    Inew.start = Inew.end + 1;
  }
  Iold.end = int(oldLines.size());
  Inew.end = int(newLines.size());
  PrintStep(os, Iold, Inew);
}

void DiffManager::PrintStep(ostream& os, Interval Iold, Interval Inew) {
  bool empty_old = (Iold.start == Iold.end);
  bool empty_new = (Inew.start == Inew.end);
  if (empty_old && empty_new) {
    // noop
  } else if (empty_old) {
    PrintHeadLine(os, Iold, Inew, ChangeType::Addition);
    PrintLines(os, newFile, newLines.get_starts(), Inew, '>');
  } else if (empty_new) {
    PrintHeadLine(os, Iold, Inew, ChangeType::Deletion);
    PrintLines(os, oldFile, oldLines.get_starts(), Iold, '<');
  } else {
    PrintHeadLine(os, Iold, Inew, ChangeType::Change);
    PrintLines(os, oldFile, oldLines.get_starts(), Iold, '<');
    os << "---\n";
    PrintLines(os, newFile, newLines.get_starts(), Inew, '>');
  }
}

void DiffManager::PrintHeadLine(ostream& os, Interval Iold, Interval Inew, ChangeType mode){
  if (mode == ChangeType::Addition) {
    --Iold.start;
  } else if (mode == ChangeType::Deletion) {
    --Inew.start;
  }
  os << (Iold.start+1);
  if (Iold.start+1 != Iold.end) {
    os << ',' << Iold.end;
  }
  os << static_cast<char>(mode);
  os << (Inew.start+1);
  if (Inew.start+1 != Inew.end) {
    os << ',' << Inew.end;
  }
  os << '\n';
}

string ReadLine(istream& is, int pos) {
  is.seekg(pos);
  string str;
  getline(is, str);
  return str;
}

void DiffManager::PrintLines(ostream& os, istream& is, std::vector<int> const& lineStarts, DiffManager::Interval I, char symbol) {
  for (auto i=I.start; i<I.end; ++i){
    os << symbol << " " << ReadLine(is, lineStarts[i]) << '\n';
  }
}
