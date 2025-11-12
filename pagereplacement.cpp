#include <iostream>
#include <vector>
#include <queue>      
#include <unordered_map> 
#include <unordered_set>
#include <climits>   

using namespace std;

int FIFO(vector<int>& requests, int numFrames) {
    int pageFaults = 0;
    unordered_set<int> frames; 
    queue<int> fifoQueue;    

    for (int page : requests) {
       
        if (frames.find(page) == frames.end()) {
           
            pageFaults++;
                
             if (frames.size() == numFrames) {
                
                int victim = fifoQueue.front(); 
                fifoQueue.pop();
                frames.erase(victim); 
            }

            frames.insert(page);
            fifoQueue.push(page);
        }
    }
    return pageFaults;
}

 
int LRU(vector<int>& requests, int numFrames) {
    int pageFaults = 0;
    unordered_set<int> frames;
    unordered_map<int, int> lruTracker;

    for (int i = 0; i < requests.size(); ++i) {
        int page = requests[i];

        if (frames.find(page) == frames.end()) {
            pageFaults++;

          
            if (frames.size() == numFrames) {
                
                int lruPage = -1;
                int oldestTime = INT_MAX;

                for (int framePage : frames) {
                    if (lruTracker[framePage] < oldestTime) {
                        oldestTime = lruTracker[framePage];
                        lruPage = framePage;
                    }
                }
                
               
                frames.erase(lruPage);
                lruTracker.erase(lruPage);
            }
            
            
            frames.insert(page);
        }

       
        lruTracker[page] = i; 
    }
    return pageFaults;
}

int Optimal(vector<int>& requests, int numFrames) {
    int pageFaults = 0;
    unordered_set<int> frames;

    for (int i = 0; i < requests.size(); ++i) {
        int page = requests[i];

        if (frames.find(page) == frames.end()) {
            pageFaults++;

            if (frames.size() == numFrames) {
               
                int victim = -1;
                int farthestUse = -1; 

                for (int framePage : frames) {
                    int nextUse = INT_MAX; 
                    
                  
                    for (int j = i + 1; j < requests.size(); ++j) {
                        if (requests[j] == framePage) {
                            nextUse = j;
                            break; 
                        }
                    }

                    if (nextUse > farthestUse) {
                        farthestUse = nextUse;
                        victim = framePage;
                    }
                }
                
                
                frames.erase(victim);
            }
            
           
            frames.insert(page);
        }
    }
    return pageFaults;
}


int main() {
   
    vector<int> requests = {1, 2, 3, 4, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6};

    int numFrames = 5; 

    cout << "Running Page Replacement Algorithms with " << numFrames << " frames." << endl;
    cout << "Reference String: 1, 2, 3, 4, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6" << endl << endl;
    cout<<"Total Page Faults in FIFO :"<<FIFO(requests, numFrames)<<endl; 
    cout<<"Total Page Faults in LRU :"<<LRU(requests, numFrames)<<endl; 
    cout<<"Total Page Faults in Optimal :"<<Optimal(requests, numFrames)<<endl; 

    return 0;
}