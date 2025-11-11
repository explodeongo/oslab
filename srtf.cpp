#include <iostream>
#include <vector>
#include <iomanip>
#include <climits> // <-- ADDED (for INT_MAX)

using namespace std;

class Process {
    public:
    int id;     // process number
    int at;     // arrival time
    int bt;     // burst time

    int rt;     // <-- ADDED (remaining time)
    
    int ct;     // completion time
    int tat;    // turnaround time
    int wt;     // waiting time
    // 'done' boolean is no longer needed, rt=0 is our check
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
        p[i].rt = p[i].bt; // <-- ADDED (initialize remaining time)
    }

    int time = 0, completed = 0;
    vector<int> sequence; // execution order

    while (completed < n) {
        int idx = -1;
        int minRT = INT_MAX; // <-- CHANGED (find min *Remaining* Time)

        // pick process with smallest *remaining* time that has arrived
        for (int i = 0; i < n; i++) {
            // <-- CHANGED (check rt > 0 instead of !done)
            if (p[i].at <= time && p[i].rt > 0) { 
                if (p[i].rt < minRT) {
                    minRT = p[i].rt;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++; // if no process arrived yet, CPU is idle
        } else {
            // A process runs for one time unit
            p[idx].rt--; // <-- CHANGED (decrement remaining time)
            
            // Check if the process just finished
            if (p[idx].rt == 0) {
                p[idx].ct = time + 1; // <-- CHANGED (finishes at end of this tick)
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                
                completed++;
                sequence.push_back(p[idx].id);
            }
            
            time++; // <-- CHANGED (time always moves forward)
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

    // This sequence shows the order of *completion*
    cout << "\nCompletion Order: ";
    for (int id : sequence) cout << "P" << id << " ";
    cout << endl;

    return 0;
}