#include "diff.h"

#include <fstream>

using namespace std;

int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "diff requires 2 parameters: old file and new file\n";
    exit(1);
  }
  ifstream file_old (argv[1]);
  ifstream file_new (argv[2]);
  DiffManager dm(file_old, file_new);
  dm.Print(cout);
}
