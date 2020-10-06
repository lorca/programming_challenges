#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

enum Status {
  OK,             // Sucessfully processed input.
  END_OF_INPUT,   // End of input stream.
  ERROR_BAD_INPUT // Error: Bad Input.
};

struct Location;
struct Minefield;

Status ReadMinefield(Minefield *f, int fieldNumber);
bool IsValidLocation(Minefield *f, Location location);
void IncrementGridCell(Minefield *f, Location location);
void IncrementGridCellsAdjacentToMine(Minefield *f, Location mine_location);
// void CountAdjacentMines(Minefield *f);
void PrintMinefield(const Minefield &f);

const int MAX_ROWS = 101;
const int MAX_COLS = 100;
const char MINE_SYMBOL = '*';
const char SAFE_SYMBOL = '.';
const std::array<int, 3> TRANSFORMS = {-1, 0, 1};

struct Location {
  Location(int row_, int col_) : row(row_), col(col_) {}
  int row;
  int col;
};

struct Minefield {
  // The field #.
  int fieldNumber;

  // The # of rows in the grid.
  int rows;

  // The # of columns in the grid.
  int cols;

  // Locations for each mine.
  // vector<Location> mineLocations;

  // A row-column grid that represents the field.
  //  - '*' represents a mine.
  // - '0' through '8' represent # of mines adjecent to a grid cell.
  char grid[MAX_ROWS][MAX_COLS];
};

int main() {
  int fieldNumber = 1;
  while (true) {
    Minefield f;
    Status status = ReadMinefield(&f, fieldNumber++);
    if (status == END_OF_INPUT) {
      return 0;
    }
    if (status == ERROR_BAD_INPUT) {
      cout << "Bad input" << endl;
      return 1;
    }
    // CountAdjacentMines(&f);
    PrintMinefield(f);
  }
  return 0;
}

Status ReadMinefield(Minefield *f, int fieldNumber) {
  int rows, cols;
  cin >> rows >> cols;
  if (cin.eof()) {
    return END_OF_INPUT;
  }
  if (rows == 0 && cols == 0) {
    return END_OF_INPUT;
  }
  if (!cin) {
    return ERROR_BAD_INPUT;
  }
  if (rows <= 0 || rows > MAX_ROWS) {
    return ERROR_BAD_INPUT;
  }
  if (cols <= 0 || cols > MAX_COLS) {
    return ERROR_BAD_INPUT;
  }
  f->fieldNumber = fieldNumber;
  f->rows = rows;
  f->cols = cols;
  memset(f->grid, '0', sizeof(f->grid));
  char c;
  for (int row = 0; row < f->rows; ++row) {
    for (int col = 0; col < f->cols; ++col) {
      cin >> c;
      if (!cin) {
        return ERROR_BAD_INPUT;
      }
      if (c == MINE_SYMBOL) {
        f->grid[row][col] = c;
        IncrementGridCellsAdjacentToMine(f, Location(row, col));       
        // f->mineLocations.push_back(Location(row, col));
      } else if (c == SAFE_SYMBOL) {
        // f->grid[row][col] = '0';
      } else {
        return ERROR_BAD_INPUT;
      }
    }
  }
  return OK;
}

bool IsValidLocation(Minefield *f, Location location) {
  if (location.row < 0 || location.row >= f->rows) {
    return false;
  }
  if (location.col < 0 || location.col >= f->cols) {
    return false;
  }
  return true;
}

void IncrementGridCell(Minefield *f, Location location) {
  if (!IsValidLocation(f, location)) {
    return;
  }
  char symbol = f->grid[location.row][location.col];
  if (symbol != MINE_SYMBOL) {
    // Add 1 to symbol '0', '1', '2', etc.
    // Note that max value should be '8', so no overflow should occur.
    f->grid[location.row][location.col] = symbol + 1;
  }
}

// void CountAdjacentMines(Minefield *f) {
//  for (Location mine_location : f->mineLocations) {
//    IncrementGridCellsAdjacentToMine(f, std::move(mine_location));
//  }
// }

void IncrementGridCellsAdjacentToMine(Minefield *f, Location mine_location) {
  for (int row_transform : TRANSFORMS) {
    for (int col_transform : TRANSFORMS) {
      if (row_transform == 0 && col_transform == 0) {
        continue;
      }
      IncrementGridCell(f, Location(mine_location.row + row_transform,
                                    mine_location.col + col_transform));
    }
  }
}

void PrintMinefield(const Minefield &f) {
  if (f.fieldNumber > 1) {
    cout << endl;
  }
  cout << "Field #" << f.fieldNumber << ":" << endl;
  for (int row = 0; row < f.rows; ++row) {
    for (int col = 0; col < f.cols; ++col) {
      cout << f.grid[row][col];
    }
    cout << endl;
  }
}

