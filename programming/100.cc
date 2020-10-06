#include <iostream>
#include <unordered_map>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::unordered_map;

const int MIN_IN = 0;
const int MAX_IN = 10000001;   // 1000000;
const int LENGTH_MAX = 100001; // 1000000;

struct Range {
  int start_;
  int end_;

  int start() {
    if (start_ <= end_) {
      return start_;
    } else {
      return end_;
    }
  }

  int end() {
    if (start_ <= end_) {
      return end_;
    } else {
      return start_;
    }
  }
};

bool ReadRange(Range *range) {
  int start = -1, end = -1;
  if (cin >> start >> end) {
    if (cin.fail()) {
      cout << "Invalid input" << endl;
      return false;
    }
    if (start <= MIN_IN) {
      cout << "Invalid input" << endl;
      return false;
    }
    if (end >= MAX_IN) {
      cout << "Invalid input" << endl;
      return false;
    }
    range->start_ = start;
    range->end_ = end;
    return true;
  } else {
    return false;
  }
}

bool IsEven(int n) { return n % 2 == 0; }

long Compute(long n) {
  if (n == 1) {
    return 1;
  } else if (IsEven(n)) {
    return n / 2;
  } else {
    return (n * 3) + 1;
  }
}

int GetLength(long n, unordered_map<int, int>& lengths) {
// int GetLength(long n, int *lengths) {
  if (n == 1) {
    return 1;
  }
  if (n >= LENGTH_MAX - 1) {
    long next = Compute(n);
    return 1 + GetLength(next, lengths);
  } else {
    // cerr << "Yo " << n << endl;
    if (lengths[n] != 0) {
      return lengths[n];
    }
    long next = Compute(n);
    lengths[n] = 1 + GetLength(next, lengths);
    return lengths[n];
  }
}

int main() {
  Range range;
  //int lengths[LENGTH_MAX + 1];
  unordered_map<int, int> lengths;
  //for (int i = 0; i < LENGTH_MAX; ++i) {
  //  lengths[i] = 0;
  //}
  while (ReadRange(&range)) {
    int maxLength = -1;
    for (int i = range.start(); i <= range.end(); ++i) {
      // cerr << "XXXX" << endl;
      int length = GetLength(i, lengths);
      if (length > maxLength) {
        maxLength = length;
      }
    }
    cout << range.start_ << " " << range.end_ << " " << maxLength << endl;
    // printf("%d %d %d\n", range.start_, range.end_, maxLength);
  }
}
