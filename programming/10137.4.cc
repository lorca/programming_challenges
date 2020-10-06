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


  int N = trip->expenses.size();

        int lowAverage = sum / N;
        int highAverage = lowAverage + ((sum % N) ? 1 : 0);
        int sumAbove = 0;

        for (int i = 0; i < N; ++i)
        {
            if (trip->expenses[i] > highAverage)
                sumAbove += trip->expenses[i] - highAverage;
        }

        int sumBelow = 0;
        for (int i = 0; i < N; ++i)
        {
            if (trip->expenses[i] < lowAverage)
                sumBelow += lowAverage - trip->expenses[i];
        }


        int usedSum = max(sumAbove, sumBelow);

       cout << '$' << (usedSum / 100) << '.' << setw(2) << setfill('0') << (usedSum % 100) << '\n';

}
