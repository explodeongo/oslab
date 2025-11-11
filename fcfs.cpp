#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int main() {
int n;
cout << "Enter the number of processes: ";
cin >> n;
vector<string> processID(n);
vector<int> burstTime(n);
vector<int> waitingTime(n, 0);
vector<int> turnaroundTime(n);
for (int i = 0; i < n; i++) {
cout << "Enter Process ID for process " << i + 1 << ": ";
cin >> processID[i];
cout << "Enter Burst Time for " << processID[i] << ": ";
cin >> burstTime[i];
}
for (int i = 1; i < n; i++) {
waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
}
for (int i = 0; i < n; i++) {
turnaroundTime[i] = waitingTime[i] + burstTime[i];
}

cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
for (int i = 0; i < n; i++) {
cout << processID[i] << "\t" << burstTime[i] << "\t\t"<< waitingTime[i] << "\t\t" << turnaroundTime[i] <<endl;
}
double avgWaitingTime = 0;
for (int i = 0; i < n; i++) {
avgWaitingTime += waitingTime[i];
}
avgWaitingTime /= n;
cout<<fixed<<setprecision(2);
cout << "\nAverage Waiting Time: " << avgWaitingTime << "units\n";

return 0;
}