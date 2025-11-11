#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

class process{
    public:
        int id;
        int at;
        int bt;
        int wt;
        int ct;
        int tat;
        int rt;

        void completed(int t){
            ct=t;
            tat=ct-at;
            wt=tat-bt;
        }


};

void sortProcesses(vector<process>&procs){
    int n=procs.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(procs[j].at > procs[j+1].at){
                swap(procs[j],procs[j+1]);
            }
        }
    }
}
int main(){
    int n;
    int tq;
    cout<<"Enter the no of processes : ";
    cin>>n;
    cout<<"Enter the time quantum : ";
    cin>>tq;

    vector<process> procs(n);
    for(int i=0;i<n;i++){
        procs[i].id=i+1;
        cout<<"Enter the AT & BT for process "<<i+1<<" : ";
        cin>>procs[i].at>>procs[i].bt;
        procs[i].rt=procs[i].bt;

    }
    cout<<endl;
    sortProcesses(procs);
    int time=procs[0].at;
    int completed=0;
    while(completed<n){
        for(int i=0;i<n;i++){
            if(procs[i].at >time){
                time++;
                break;
            }
            if(procs[i].rt<=0) continue;
            
            int burst=min(tq,procs[i].rt);
            procs[i].rt-=burst;
            cout<<"Time: "<<time<<" - ";
            cout<<"Process "<<procs[i].id<<"executes"<<burst<<" time."<<endl; 
            time += burst;
            if(procs[i].rt <=0){
                completed++;
                procs[i].completed(time);
            }
        }
    }
    cout<< endl;
    cout<< setw(5)<<"ID";
    cout<< setw(5)<<"AT";
    cout<< setw(5)<<"BT";
    cout<< setw(5)<<"TAT";
    cout<< setw(5)<<"WT";
    cout<<endl;
    int totalTAT=0,totalWT=0;
    for(int i=0;i<n;i++){
        cout<<setw(5) << procs[i].id;
        cout<<setw(5) << procs[i].at;
        cout<<setw(5) << procs[i].bt;
        cout<<setw(5) << procs[i].tat;
        cout<<setw(5) << procs[i].wt;
        cout<<endl;
        totalTAT+=procs[i].tat;
        totalWT+=procs[i].wt;

    }
    cout<<endl;
    cout<<"avg tat: "<<(float)totalTAT/n<<endl;
    cout<<"avg wt: "<<(float)totalWT/n<<endl;
    return 0;
}
