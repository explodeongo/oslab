#include<iostream>
#include<vector>
using namespace std;
bool allDone(vector<bool>&done) {
    bool flag = true;
    for (auto el: done) flag = (flag && el);
    return flag;
}
bool isResourceAvailable(vector<int>&needed,vector<int>&available, int&m) {
    bool flag = true;
    for (int i=0; i<m; i++) {
        flag = (flag && needed[i] <= available[i]);
    }
    return flag;
}
int main() {
int n, m;
cout << "Enter number of processes: ";
cin >> n;
cout << "Enter number of resource types: ";
cin >> m;
vector<int> available(m);
cout << "Enter available vector: ";
for (int i=0; i<m; i++) cin >> available[i];
   
vector<vector<int>> maxi(n, vector<int>(m));
vector<vector<int>> allocation(n, vector<int>(m));
vector<vector<int>> need(n, vector<int>(m));

cout << "Enter Max. values for all processes:" << endl;
for (int i=0; i<n; i++) {
    cout << "Process " << i+1 << ":" << endl;
    for (int j=0; j<m; j++) {

    cin >> maxi[i][j];
}
}
cout << "Enter Allocation values for all processes:" << endl;
for (int i=0; i<n; i++) {
cout << "Process " << i+1 << ":" << endl;
for (int j=0; j<m; j++) {

cin >> allocation[i][j];
available[j] -= allocation[i][j];
}
}
for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
    need[i][j] = maxi[i][j] - allocation[i][j];
    }
}
vector<bool> done(n, false);
vector<int> seq;
while (!allDone(done)) {
    bool changes = false;
    for (int i=0; i<n; i++) {
        if (done[i]) continue;
        if (isResourceAvailable(need[i], available, m)) {
            done[i] = true;
            changes = true;
            seq.push_back(i);
            for (int j=0; j<m; j++) {
             available[j] += allocation[i][j];
            }
        }
    }
if (!changes) break;
}
if (!allDone(done)) {

cout << "\n\nSystem is not in safe state!" << endl;
return 0;
}
cout << "\n\nSystem is in safe state!\n\n";
cout << "Valid sequence of processes:" << endl;
for (int i=0; i<n; i++) {
cout << "P" << seq[i];
if (i < n-1) cout << " -> ";
}
cout << endl;
return 0;
}