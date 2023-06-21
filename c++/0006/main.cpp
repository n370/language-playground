#include <iostream>

using namespace std;

int main() {
  enum WEEKDAY {Mon,Tue,Wed,Thu,Fri,Sat,Sun};

  WEEKDAY day;

  day = Mon;

  if (day == Mon) {
    cout<<"Monday\n";
  }

  return 0;
}
