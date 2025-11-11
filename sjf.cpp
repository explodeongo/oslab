#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Process {
    public:
    int id;     // process number
    int at;     // arrival time
    int bt;     // burst time
    int ct;     // completion time
    int tat;    // turnaround time
    int wt;     // waiting time
    bool done;  // check if finished
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter Arrival Time for P" << p[i].id << ": ";
        cin >> p[i].at;
        cout << "Enter Burst Time for P" << p[i].id << ": ";
        cin >> p[i].bt;
        p[i].done = false;
    }

    int time = 0, completed = 0;
    vector<int> sequence; // execution order

    while (completed < n) {
        int idx = -1;
        int minBT = 1e9;

        // pick process with smallest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++; // if no process arrived yet, move time forward
        } else {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].done = true;
            completed++;
            sequence.push_back(p[idx].id);
        }
    }

    double avgWT = 0, avgTAT = 0;
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t" << p[i].at << "\t" << p[i].bt
             << "\t" << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << endl;
        avgWT += p[i].wt;
        avgTAT += p[i].tat;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << avgWT / n << endl;
    cout << "Average Turnaround Time: " << avgTAT / n << endl;

    cout << "\nExecution Order: ";
    for (int id : sequence) cout << "P" << id << " ";
    cout << endl;

    return 0;
}