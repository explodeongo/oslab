#include <iostream>
#include <vector>
#include <queue>      // For FIFO
#include <unordered_map> // For LRU
#include <unordered_set> // For finding items in frames
#include <climits>   // For INT_MAX

using namespace std;

// Helper function to print the result
void printFaults(const string& algorithm, int pageFaults) {
    cout << "--- " << algorithm << " ---" << endl;
    cout << "Total Page Faults: " << pageFaults << endl << endl;
}

/**
 * 1. FIFO (First-In-First-Out)
 *
 * Uses a queue to track which page has been in memory the longest.
 */
int FIFO(const vector<int>& requests, int numFrames) {
    int pageFaults = 0;
    unordered_set<int> frames; // To check if a page is in a frame
    queue<int> fifoQueue;    // To track the order of arrival

    for (int page : requests) {
        // Check if page is NOT in frames (a "miss")
        if (frames.find(page) == frames.end()) {
            pageFaults++;

            // Check if frames are full
            if (frames.size() == numFrames) {
                // Frames are full, need to replace
                int victim = fifoQueue.front(); // Get the "first-in" page
                fifoQueue.pop();
                frames.erase(victim); // Remove victim
            }

            // Add the new page
            frames.insert(page);
            fifoQueue.push(page);
        }
    }
    return pageFaults;
}

/**
 * 2. LRU (Least Recently Used)
 *
 * Replaces the page that has not been *used* for the longest time.
 */
int LRU(const vector<int>& requests, int numFrames) {
    int pageFaults = 0;
    unordered_set<int> frames;
    // Map to store {page_number -> last_used_index}
    unordered_map<int, int> lruTracker;

    for (int i = 0; i < requests.size(); ++i) {
        int page = requests[i];

        // Check if page is NOT in frames (a "miss")
        if (frames.find(page) == frames.end()) {
            pageFaults++;

            // Check if frames are full
            if (frames.size() == numFrames) {
                // Frames are full, find the LRU page
                int lruPage = -1;
                int oldestTime = INT_MAX;

                for (int framePage : frames) {
                    if (lruTracker[framePage] < oldestTime) {
                        oldestTime = lruTracker[framePage];
                        lruPage = framePage;
                    }
                }
                
                // Remove victim
                frames.erase(lruPage);
                lruTracker.erase(lruPage);
            }
            
            // Add the new page
            frames.insert(page);
        }

        // ALWAYS update the "last used" time for the current page
        lruTracker[page] = i; 
    }
    return pageFaults;
}

/**
 * 3. Optimal (OPT)
 *
 * Replaces the page that will not be used for the *longest time in the future*.
 */
int Optimal(const vector<int>& requests, int numFrames) {
    int pageFaults = 0;
    unordered_set<int> frames;

    for (int i = 0; i < requests.size(); ++i) {
        int page = requests[i];

        // Check if page is NOT in frames (a "miss")
        if (frames.find(page) == frames.end()) {
            pageFaults++;

            // Check if frames are full
            if (frames.size() == numFrames) {
                // Frames are full, find the optimal victim
                int victim = -1;
                int farthestUse = -1; // Index of the farthest future use

                for (int framePage : frames) {
                    int nextUse = INT_MAX; // Assume never used again
                    
                    // Look into the future requests
                    for (int j = i + 1; j < requests.size(); ++j) {
                        if (requests[j] == framePage) {
                            nextUse = j;
                            break; // Found the *next* use
                        }
                    }

                    if (nextUse > farthestUse) {
                        farthestUse = nextUse;
                        victim = framePage;
                    }
                }
                
                // Remove victim
                frames.erase(victim);
            }
            
            // Add the new page
            frames.insert(page);
        }
    }
    return pageFaults;
}


int main() {
    // Reference string from your exam paper (Q9)
    vector<int> requests = {1, 2, 3, 4, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6};
    
    // You can change this value to test 5, 6, or 7
    int numFrames = 5; 

    cout << "Running Page Replacement Algorithms with " << numFrames << " frames." << endl;
    cout << "Reference String: 1, 2, 3, 4, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6" << endl << endl;

    printFaults("FIFO", FIFO(requests, numFrames));
    printFaults("LRU", LRU(requests, numFrames));
    printFaults("Optimal", Optimal(requests, numFrames));

    // Example for 6 frames
    numFrames = 6;
    cout << "--- Running again with " << numFrames << " frames ---" << endl;
    printFaults("FIFO", FIFO(requests, numFrames));
    printFaults("LRU", LRU(requests, numFrames));
    printFaults("Optimal", Optimal(requests, numFrames));

    return 0;
}