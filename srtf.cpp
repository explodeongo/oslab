#include <iostream>
#include <vector>
#include <iomanip>
#include <climits> 

using namespace std;

class Process {
    public:
    int id;    
    int at;     
    int bt;     

    int rt;    
    
    int ct;     
    int tat;    
    int wt;     
   
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
        p[i].rt = p[i].bt; 
    }

    int time = 0, completed = 0;
    vector<int> sequence;

    while (completed < n) {
        int idx = -1;
        int minRT = INT_MAX; 

        
        for (int i = 0; i < n; i++) {
            
            if (p[i].at <= time && p[i].rt > 0) { 
                if (p[i].rt < minRT) {
                    minRT = p[i].rt;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++; 
        } else {
            
            p[idx].rt--; 
            
            
            if (p[idx].rt == 0) {
                p[idx].ct = time + 1; 
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                
                completed++;
                sequence.push_back(p[idx].id);
            }
            
            time++; 
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

   
    cout << "\nCompletion Order: ";
    for (int id : sequence) cout << "P" << id << " ";
    cout << endl;

    return 0;
}