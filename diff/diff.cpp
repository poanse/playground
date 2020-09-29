#include "diff.h"

#include <algorithm>

using namespace std;

DiffManager::DiffManager(istream& oldfile, istream& newfile, ostream& os) 
  :oldFile(oldfile)
  ,newFile(newfile)
  ,os(os)
{
  oldLines = _ReadLines(oldFile);
  newLines = _ReadLines(newFile);
  oldHashes = _ComputeHashes(oldLines);
  newHashes = _ComputeHashes(newLines);
  LCS_table = LCS(oldHashes, newHashes);
  backtrack(indexes, LCS_table, oldHashes, newHashes, oldHashes.size()-1, newHashes.size()-1);
  reverse(begin(indexes), end(indexes));
}

void DiffManager::Print() {
  int oldIdxPrev = 0;
  int newIdxPrev = 0;
  auto GetNewIdx = [&](int oldIdx_){
    auto hash = oldHashes[oldIdx_];
    auto it = find(newHashes.begin() + newIdxPrev, newHashes.end(), hash);
    return distance(newHashes.begin(), it);
  };
  for (auto oldIdx : indexes) {
    int newIdx = GetNewIdx(oldIdx);
    PrintStep(oldIdx, newIdx, oldIdxPrev, newIdxPrev);
    oldIdxPrev = oldIdx + 1;
    newIdxPrev = newIdx + 1;
  }
  PrintStep(oldLines.size(), newLines.size(), oldIdxPrev, newIdxPrev);
}

void DiffManager::PrintStep(int oldIdx, int newIdx, int oldIdxPrev, int newIdxPrev) {
  if ((oldIdxPrev == oldIdx) && (newIdxPrev == newIdx)) {
    // noop
  } else if (oldIdxPrev==oldIdx) {
    PrintAddition(oldIdx, newIdx, oldIdxPrev, newIdxPrev);
  } else if (newIdxPrev == newIdx) {
    PrintDeletion(oldIdx, newIdx, oldIdxPrev, newIdxPrev);
  } else {
    PrintChange(oldIdx, newIdx, oldIdxPrev, newIdxPrev);
  }
}

void DiffManager::PrintHeadLine(int oldIdxPrev, int idx, int newIdxPrev, int new_idx, char mode){
  os << (oldIdxPrev+1);
  if (oldIdxPrev+1 != idx) {
    os << ',' << idx;
  }
  os << mode;
  os << (newIdxPrev+1);
  if (newIdxPrev+1 != new_idx) {
    os << ',' << new_idx;
  }
  os << '\n';
}

void PrintLines(ostream& os, std::vector<std::string> const& lines, int from, int to, char symbol) {
  for (auto i=from; i<to; ++i){
    os << symbol << " " << lines[i] << '\n';
  }
}


void DiffManager::PrintAddition(int oldIdx, int newIdx, int oldIdxPrev, int newIdxPrev) {
  PrintHeadLine(oldIdxPrev-1, oldIdx, newIdxPrev, newIdx, 'a');
  PrintLines(os, newLines, newIdxPrev, newIdx, '>');
}
void DiffManager::PrintDeletion(int oldIdx, int newIdx, int oldIdxPrev, int newIdxPrev) {
  PrintHeadLine(oldIdxPrev, oldIdx, newIdxPrev-1, newIdx, 'd');
  PrintLines(os, oldLines, oldIdxPrev, oldIdx, '<');
}
void DiffManager::PrintChange(int oldIdx, int newIdx, int oldIdxPrev, int newIdxPrev) {
  PrintHeadLine(oldIdxPrev, oldIdx, newIdxPrev, newIdx, 'c');
  PrintLines(os, oldLines, oldIdxPrev, oldIdx, '<');
  os << "---\n";
  PrintLines(os, newLines, newIdxPrev, newIdx, '>');
}

vector<string> DiffManager::_ReadLines(istream& input) {
  vector<string> strings;
  string str;
  while (getline(input, str)) {
    strings.push_back(std::move(str));
  }
  return strings;
}

  vector<int> DiffManager::_ComputeHashes(const vector<string>& strings){
    vector<int> hashes;
    hashes.reserve(strings.size());
    auto hasher = hash<string>();
    for (const auto& str : strings) {
      hashes.push_back(hasher(str));
    }
    return hashes;
  }

vector<vector<int>> DiffManager::LCS(vector<int> const& X, vector<int> const& Y) {
  size_t m = X.size();
  size_t n = Y.size();
  vector<vector<int>> C(m + 1);
  for (auto& row : C) {
    row.resize(n + 1);
  }
  for (size_t i = 0; i < m; ++i){
    for (size_t j = 0; j < n; ++j){
      if (X[i] == Y[j]) { //i-1 and j-1 if reading X & Y from zero
        C[i+1][j+1] = C[i][j] + 1;
      } else {
        C[i+1][j+1] = max(C[i+1][j], C[i][j+1]);
      }
    }
  }
  return C;
}

void DiffManager::backtrack(vector<int>& idx, vector<vector<int>> const& C, vector<int> const& X, vector<int> const& Y, int i, int j) {
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
