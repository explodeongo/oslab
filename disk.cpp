#include <iostream>
#include <vector>
#include <algorithm> 
#include <cmath>    
#include <climits>   

using namespace std;

void printResults(const string& algorithm, int totalMovement, const vector<int>& sequence) {
    cout << "--- " << algorithm << " ---" << endl;
    cout << "Seek Sequence: ";
    int n=sequence.size();
    for (int i = 0; i < n; ++i) {
        cout << sequence[i];
        if(i<n-1){
            cout<<" -> ";
        }
    }
    cout << "\nTotal Head Movement: " << totalMovement << " cylinders" << endl << endl;
}

void FCFS(vector<int> requests, int head) {
    int totalMovement = 0;
    vector<int> sequence;
    sequence.push_back(head); 

    for (int request : requests) {
        totalMovement += abs(request - head); 
        head = request;                       
        sequence.push_back(head);
    }

    printResults("FCFS", totalMovement, sequence);
}

/**
 * 2. SSTF (Shortest Seek Time First)
 *
 * Selects the request closest to the current head position.
 */
void SSTF(vector<int> requests, int head) {
    int totalMovement = 0;
    vector<int> sequence;
    sequence.push_back(head);

    int numRequests = requests.size();
    for (int i = 0; i < numRequests; ++i) {
        int shortestSeek = INT_MAX;
        int nextRequestIndex = -1;

        // Find the closest request
        for (int j = 0; j < requests.size(); ++j) {
            int seek = abs(requests[j] - head);
            if (seek < shortestSeek) {
                shortestSeek = seek;
                nextRequestIndex = j;
            }
        }

        int nextRequest = requests[nextRequestIndex];
        totalMovement += shortestSeek;
        head = nextRequest;
        sequence.push_back(head);

        // Remove the serviced request
        requests.erase(requests.begin() + nextRequestIndex);
    }

    printResults("SSTF", totalMovement, sequence);
}

/**
 * 3. SCAN (Elevator Algorithm)
 *
 * Moves from one end of the disk to the other, servicing requests.
 * Reverses direction when it hits the end.
 */
void SCAN(vector<int> requests, int head, string direction, int diskSize) {
    int totalMovement = 0;
    vector<int> sequence;
    sequence.push_back(head);

    // Sort requests to make scanning easy
    sort(requests.begin(), requests.end());

    // Find the point to split the requests
    vector<int> left, right;
    for (int req : requests) {
        if (req < head) {
            left.push_back(req);
        } else {
            right.push_back(req);
        }
    }

    // Service requests based on direction
    if (direction == "up") {
        // Move up, servicing requests
        for (int req : right) {
            totalMovement += abs(req - head);
            head = req;
            sequence.push_back(head);
        }
        
        // Move to the end of the disk
        if (head != diskSize - 1) {
             totalMovement += abs((diskSize - 1) - head);
             head = diskSize - 1;
             sequence.push_back(head);
        }

        // Move down, servicing remaining requests
        // sort left in descending order
        sort(left.rbegin(), left.rend()); 
        for (int req : left) {
            totalMovement += abs(req - head);
            head = req;
            sequence.push_back(head);
        }
    } else { // direction == "down"
        // Move down, servicing requests (in reverse sorted order)
        sort(left.rbegin(), left.rend());
        for (int req : left) {
            totalMovement += abs(req - head);
            head = req;
            sequence.push_back(head);
        }

        // Move to the beginning of the disk (cylinder 0)
        if (head != 0) {
            totalMovement += abs(0 - head);
            head = 0;
            sequence.push_back(head);
        }

        // Move up, servicing remaining requests
        for (int req : right) {
            totalMovement += abs(req - head);
            head = req;
            sequence.push_back(head);
        }
    }

    printResults("SCAN", totalMovement, sequence);
}

/**
 * 4. C-SCAN (Circular SCAN)
 *
 * Moves from one end to the other, servicing requests.
 * When it hits the end, it "jumps" back to the beginning and
 * starts moving in the same direction again.
 */
void CSCAN(vector<int> requests, int head, string direction, int diskSize) {
    int totalMovement = 0;
    vector<int> sequence;
    sequence.push_back(head);

    sort(requests.begin(), requests.end());

    vector<int> left, right;
    for (int req : requests) {
        if (req < head) {
            left.push_back(req);
        } else {
            right.push_back(req);
        }
    }

    if (direction == "up") {
        // Move up, servicing requests
        for (int req : right) {
            totalMovement += abs(req - head);
            head = req;
            sequence.push_back(head);
        }

        // Move to the end of the disk
        if (head != diskSize - 1) {
            totalMovement += abs((diskSize - 1) - head);
            head = diskSize - 1;
            sequence.push_back(head);
        }
        
        // Jump to the beginning
        if (!left.empty()) { // Only jump if there are requests on the other side
            totalMovement += (diskSize - 1); // Full sweep
            head = 0;
            sequence.push_back(head);
        }

        // Move up from the beginning, servicing remaining requests
        for (int req : left) {
            totalMovement += abs(req - head);
            head = req;
            sequence.push_back(head);
        }
    } else { // direction == "down"
        // Move down, servicing requests (in reverse sorted order)
        sort(left.rbegin(), left.rend());
        for (int req : left) {
            totalMovement += abs(req - head);
            head = req;
            sequence.push_back(head);
        }

        // Move to the beginning (cylinder 0)
        if (head != 0) {
            totalMovement += abs(0 - head);
            head = 0;
            sequence.push_back(head);
        }

        // Jump to the end
        if (!right.empty()) {
            totalMovement += (diskSize - 1);
            head = diskSize - 1;
            sequence.push_back(head);
        }

        // Move down from the end, servicing remaining requests
        sort(right.rbegin(), right.rend());
        for (int req : right) {
            totalMovement += abs(req - head);
            head = req;
            sequence.push_back(head);
        }
    }

    printResults("C-SCAN", totalMovement, sequence);
}


/**
 * 5. C-LOOK (Circular LOOK)
 *
 * Like C-SCAN, but only goes as far as the last request in
 * each direction, then "jumps" to the first request on the
 * other side.
 */
void CLOOK(vector<int> requests, int head, string direction) {
    int totalMovement = 0;
    vector<int> sequence;
    sequence.push_back(head);

    sort(requests.begin(), requests.end());

    vector<int> left, right;
    for (int req : requests) {
        if (req < head) {
            left.push_back(req);
        } else {
            right.push_back(req);
        }
    }

    if (direction == "up") {
        // Move up, servicing requests
        for (int req : right) {
            totalMovement += abs(req - head);
            head = req;
            sequence.push_back(head);
        }

        // Jump to the lowest request
        if (!left.empty()) {
            totalMovement += abs(left.front() - head);
            head = left.front();
            sequence.push_back(head);
        }

        // Move up from the lowest, servicing remaining requests
        for (int i = 1; i < left.size(); ++i) { // Start from 1, as we're at front()
            totalMovement += abs(left[i] - head);
            head = left[i];
            sequence.push_back(head);
        }
    } else { // direction == "down"
        // Move down, servicing requests (in reverse sorted order)
        sort(left.rbegin(), left.rend());
        for (int req : left) {
            totalMovement += abs(req - head);
            head = req;
            sequence.push_back(head);
        }

        // Jump to the highest request
        if (!right.empty()) {
            totalMovement += abs(right.back() - head);
            head = right.back();
            sequence.push_back(head);
        }

        // Move down from the highest, servicing remaining requests
        sort(right.rbegin(), right.rend());
        for (int i = 1; i < right.size(); ++i) { // Start from 1
            totalMovement += abs(right[i] - head);
            head = right[i];
            sequence.push_back(head);
        }
    }

    printResults("C-LOOK", totalMovement, sequence);
}

int main() {
    // Data from your exam paper (Q10)
    vector<int> requests = {86, 1470, 913, 1774, 948, 1509, 1022, 1750, 130};
    int head = 143;
    int diskSize = 5000; // Cylinders 0-4999
    string direction = "up"; // Implied by previous move 125 -> 143

    cout << "Initial Head Position: " << head << endl;
    cout << "Request Queue: 86, 1470, 913, 1774, 948, 1509, 1022, 1750, 130" << endl << endl;

    // Run all algorithms
    FCFS(requests, head);
    SSTF(requests, head);
    
    // Note: SCAN and C-SCAN go to the *ends* of the disk (0 and 4999)
    SCAN(requests, head, direction, diskSize);
    CSCAN(requests, head, direction, diskSize);
    
    // Note: LOOK and C-LOOK only go to the *last request* in each direction
    // (This implementation is for C-LOOK, as requested)
    CLOOK(requests, head, direction);

    return 0;
}