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
  int adjustments = 0;
  long exchange = 0;
  long credits = 0;
  long debits = 0;
  for (int i = 0; i < trip->expenses.size(); ++i) {
    int expense = trip->expenses[i];
    if (expense > average) {
      adjustments += expense - average;
      exchange += expense - average;
    } else {
      adjustments += average - expense;
      //debits += average - expense;
    }
  }
  int avgAdjustment = adjustments / trip->expenses.size();
  for (int i = 0; i < trip->expenses.size(); ++i) {
    int expense = trip->expenses[i];
    int adjustedExpense;
    if (expense > average) {
      // credit
      adjustedExpense = expense - average;
      while (adjustedExpense < avgAdjustment) {
        adjustedExpense += 1;
        credits += 1;
      }
      while (adjustedExpense > avgAdjustment + 1) {
        adjustedExpense -= 1;
        credits -= 1; 
      }
    } else {
      // debit
      adjustedExpense = average - expense;
      while (adjustedExpense > avgAdjustment + 1) {
        adjustedExpense -= 1;
        debits -= 1;
      }
      while (adjustedExpense < avgAdjustment) {
        adjustedExpense += 1;
        debits += 1;
      }
    }
  }
  exchange += abs(debits - credits);
  float printMoney = (double)exchange / 100.0f;
  printf("$%.2f\n", printMoney);
}
