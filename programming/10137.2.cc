#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

enum Status {
  OK,             // Sucessfully processed input.
  END_OF_INPUT,   // End of input stream.
  ERROR_BAD_INPUT // Error: Bad Input.
};

struct Trip {
  vector<int> expenses;
};

Status ReadTrip(Trip *trip);
void ProcessTrip(Trip *trip);

int main() {
  while (true) {
    Trip trip;
    Status status = ReadTrip(&trip);
    if (status == END_OF_INPUT) {
      return 0;
    }
    if (status == ERROR_BAD_INPUT) {
      cout << "Bad input" << endl;
      return 1;
    }
    ProcessTrip(&trip);
  }
}

Status ReadTrip(Trip *trip) {
  int students;
  cin >> students;
  if (cin.eof()) {
    return END_OF_INPUT;
  }
  if (!cin) {
    return ERROR_BAD_INPUT;
  }
  if (students == 0) {
    return END_OF_INPUT;
  }
  for (int i = 0; i < students; ++i) {
    float expense;
    cin >> expense;
    int money = round(expense * 100);
    trip->expenses.push_back(money);
  }
  if (!cin) {
    return ERROR_BAD_INPUT;
  }
  return OK;
}

void ProcessTrip(Trip *trip) {
  long sum = 0;
  for (int expense : trip->expenses) {
    sum += expense;
  }
  int average = sum / trip->expenses.size();
  int balance = 0;
  long pos = 0;
  long neg = 0;
  for (int i = 0; i < trip->expenses.size(); ++i) {
    int expense = trip->expenses[i];
    if (expense > average + 1) {
      int change = expense - (average + 1);
      trip->expenses[i] = average + 1;
      balance -= change;
      pos += change;
    } else if (expense < average) {
      int change = average - expense;
      trip->expenses[i] = average;
      balance += change;
      neg += change;
    }
  }

  int newSum = 0;
  for (int i = 0; i < trip->expenses.size(); ++i) {
    int expense = trip->expenses[i];
    newSum += expense;
  }

  long result = pos;
  if (neg > pos) {
    result = neg;
  }
  //printf("%d %d %d %d %d\n", pos, neg, balance, sum, newSum);

  float printMoney = (double)result / 100.0f;
  printf("$%.2f\n", printMoney);
}
