#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>       // <-- ADDED: for std::queue
#include <algorithm> // <-- ADDED: for std::min

using namespace std;

class Process {
public:
    int id, at, bt, ct, tat, wt, rt, priority;
    void completed(int time) {
        ct = time;
        tat = ct - at;
        wt = tat - bt;
    }
};

// --- Your Bubble Sort function (unchanged) ---
void sortByArrivalTime(vector<Process>& procs) {
    int n = procs.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (procs[j].at > procs[j + 1].at) {
                swap(procs[j], procs[j + 1]);
            }
        }
    }
}

// --- Your print function (unchanged) ---
void printProc(Process& p) {
    cout << setw(4) << "P" << p.id;
    cout << setw(5) << p.at;
    cout << setw(5) << p.bt;
    cout << setw(5) << p.priority;
    cout << setw(5) << p.wt;
    cout << setw(5) << p.tat;
}

int main() {
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum (for high-priority queue): ";
    cin >> tq;

    vector<Process> procs(n); // This vector holds all processes

    // We will store the *index* of the process in the queues
    queue<int> q1; // q1 = High-Priority (Round Robin)
    queue<int> q2; // q2 = Low-Priority (FCFS)

    for (int i = 0; i < n; i++) {
        int id, at, bt, priority;
        cout << "Enter ID, AT, BT, Priority for P" << i + 1 << ": ";
        cin >> id >> at >> bt >> priority;
        procs[i].id = id;
        procs[i].at = at;
        procs[i].bt = bt;
        procs[i].rt = bt; // Initialize remaining time
        procs[i].priority = priority;
    }

    // Sort all processes by arrival time using your function
    sortByArrivalTime(procs);

    int curProcInd = 0; // The index of the *next* process to arrive
    int time = 0;       // The main simulation clock
    int done = 0;       // Counter for completed processes

    cout << "\nExecution Sequence: ";

    // --- MAIN SIMULATION LOOP (Simplified) ---
    while (done < n) {

        // 1. Add any newly arrived processes to the correct priority queue
        while (curProcInd < n && procs[curProcInd].at <= time) {
            if (procs[curProcInd].priority == 1) {
                q1.push(curProcInd); // Push the *index*
            } else {
                q2.push(curProcInd); // Push the *index*
            }
            curProcInd++;
        }

        // --- SCHEDULER LOGIC ---

        // 2. --- HIGH-PRIORITY QUEUE (Round Robin) ---
        // Always check q1 first (fixed-priority).
        if (!q1.empty()) {
            int i = q1.front(); // Get index of process to run
            q1.pop();

            // Run for one quantum or its remaining time, whichever is smaller
            int burst = min(procs[i].rt, tq);
            time += burst;
            procs[i].rt -= burst;

            cout << "P" << procs[i].id; // Print the process that just ran

            // 3. Add any processes that arrived *during* this burst
            while (curProcInd < n && procs[curProcInd].at <= time) {
                 if (procs[curProcInd].priority == 1) q1.push(curProcInd);
                 else q2.push(curProcInd);
                 curProcInd++;
            }
            
            // 4. Handle the process that just ran
            if (procs[i].rt > 0) {
                // Not finished, add it back to the end of its queue
                q1.push(i);
            } else {
                // Finished
                procs[i].completed(time);
                done++;
            }
            if (done < n) cout << " -> ";
        }

        // 3. --- LOW-PRIORITY QUEUE (FCFS) ---
        // This *only* runs if the high-priority queue (q1) is EMPTY.
        else if (!q2.empty()) {
            int i = q2.front(); // Get index of process to run
            q2.pop();
            
            // This is FCFS, so it runs for its *entire* remaining time
            int burst = procs[i].rt;
            
            // If CPU was idle, jump time to this process's arrival
            if (time < procs[i].at) {
                time = procs[i].at;
            }
            
            time += burst;
            procs[i].rt = 0; // It's now finished

            cout << "P" << procs[i].id; // Print the process that just ran

            // This process is now complete
            procs[i].completed(time);
            done++;
            
            if (done < n) cout << " -> ";
        }

        // 4. --- CPU IDLE ---
        // If both queues are empty but we're not done, CPU is idle.
        else {
            // Jump time to the next process arrival
            if (curProcInd < n) {
                time = procs[curProcInd].at;
            } else {
                // Should not happen if done < n, but as a safeguard
                time++;
            }
        }
    }

    // --- FINAL RESULTS ---
    cout << endl;
    cout << "--------------------------------" << endl;
    cout << setw(5) << "ID";
    cout << setw(5) << "AT";
    cout << setw(5) << "BT";
    cout << setw(5) << "Pr";
    cout << setw(5) << "WT";
    cout << setw(5) << "TAT";
    cout << endl;

    int totalWT = 0, totalTAT = 0;
    
    // We must re-sort by ID here to print P1, P2, P3... in order,
    // since we originally sorted by arrival time.
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n-i-1; ++j) {
            if(procs[j].id > procs[j+1].id) {
                swap(procs[j], procs[j+1]);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        printProc(procs[i]);
        totalWT += procs[i].wt;
        totalTAT += procs[i].tat;
        cout << endl;
    }

    cout << "--------------------------------" << endl;
    cout << fixed << setprecision(2);
    cout << "Average Waiting Time: " << (float)totalWT / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTAT / n << endl;
    cout << endl;
    return 0;
}