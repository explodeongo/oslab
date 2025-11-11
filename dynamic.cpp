#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

void compaction(vector<int>& memory,int num_mem){
    vector<int> compacted_memory;
    for(int i=0;i<num_mem;i++){
        if(memory[i]>0){
            compacted_memory.push_back(memory[i]);

        }
    }
    while(compacted_memory.size()<num_mem){
        compacted_memory.push_back(0);

    }
    memory=compacted_memory;
    cout<<"Memory after compaction: [";
    for(int i=0;i<num_mem;i++){
        cout<<memory[i];
        if(i<num_mem-1) cout<< ", ";

    }
    cout<<"]"<<endl;
}

void first_fit(vector<int>&memory,vector<int>& process,int num_mem,int num_proc){
    cout<<setw(10)<<"Proc"<<setw(10)<<"Size"<<setw(10)<<"Alloc"<<setw(10)<<"Rem."<<endl;
    for (int i = 0; i < num_proc; i++){
        string to_print = "P";
        to_print += (char)('1' + i);
        cout<<setw(10)<<to_print<<setw(10)<<process[i];
        bool done = false;
        for(int j=0;j<num_mem;j++){
            if(memory[j]>=process[i]){
                done=true;
                cout << setw(10) << memory[j];
                memory[j] -= process[i];
                cout << setw(10) << memory[j];
                break;
            }
        }
        if(!done){
        cout<<setw(20)<<"Not allocated!";
        }
    
    cout<<endl;
    char compaction_choice;
    cout<<"Do you want to perform compaction?(Y/N): ";
    cin>>compaction_choice;
    if(compaction_choice=='Y' || compaction_choice=='y'){
        compaction(memory,num_mem);
        break;
    }
    int rem_mem=0;
    for(auto el : memory) rem_mem+=el;
    cout<<"Remaining Block sizes : ";
    cout<<"[";
    for(int i=0;i<num_mem;i++){
        cout<<memory[i];
        if(i<num_mem-1)cout<<", ";
    }
    cout<<"]"<<endl;
}
}
void worst_fit(vector<int>&memory,vector<int>& process,int num_mem,int num_proc){
     cout<<setw(10)<<"Proc"<<setw(10)<<"Size"<<setw(10)<<"Alloc"<<setw(10)<<"Rem."<<endl;
    for(int i=0;i<num_proc;i++){
        string to_print="P";
        to_print +=(char)('1'+i);
        cout<<setw(10)<<to_print<<setw(10)<<process[i];
        int diff=-1;
        int ind=-1;
        for(int j=0;j<num_mem;j++){
            if(memory[j]>= process[i]){
                int curdiff=memory[j]-process[i];
                if(curdiff<=diff)continue;
                diff=curdiff;
                ind=j;

            }
        }
        if(ind==-1){
            cout<<setw(20)<<"Not allocated!";
            }
        else{
            cout<<setw(10)<<memory[ind];
            memory[ind]-=process[i];
            cout<<setw(10)<<memory[ind];

        }
        cout<<endl;
    char compaction_choice;
    cout<<"Do you want to perform compaction?(Y/N): ";
    cin>>compaction_choice;
    if(compaction_choice=='Y' || compaction_choice=='y'){
        compaction(memory,num_mem);
        break;
    }
    int rem_mem=0;
    for(auto el : memory) rem_mem+=el;
    cout<<"Remaining Block sizes : ";
    cout<<"[";
    for(int i=0;i<num_mem;i++){
        cout<<memory[i];
        if(i<num_mem-1)cout<<", ";
    }
    cout<<"]"<<endl;
    }

}
void best_fit(vector<int>&memory,vector<int>& process,int num_mem,int num_proc){
 cout<<setw(10)<<"Proc"<<setw(10)<<"Size"<<setw(10)<<"Alloc"<<setw(10)<<"Rem."<<endl;
    for(int i=0;i<num_proc;i++){
        string to_print="P";
        to_print +=(char)('1'+i);
        cout<<setw(10)<<to_print<<setw(10)<<process[i];
        int diff=1e8;
        int ind=-1;
        for(int j=0;j<num_mem;j++){
            if(memory[j]>=process[i]){
                int curdiff=memory[j]-process[i];
                if(curdiff>=diff)continue;
                diff=curdiff;
                ind=j;

            }
        }
        if(ind==-1){
            cout<<setw(20)<<"Not allocated!";

        }
        else{
            cout<<setw(10)<<memory[ind];
            memory[ind]-=process[i];
            cout<<setw(10)<<memory[ind];
        }
      cout<<endl;
    char compaction_choice;
    cout<<"Do you want to perform compaction?(Y/N): ";
    cin>>compaction_choice;
    if(compaction_choice=='Y' || compaction_choice=='y'){
        compaction(memory,num_mem);
        break;
    }
    int rem_mem=0;
    for(auto el : memory) rem_mem+=el;
    cout<<"Remaining Block sizes : ";
    cout<<"[";
    for(int i=0;i<num_mem;i++){
        cout<<memory[i];
        if(i<num_mem-1)cout<<", ";
    }
    cout<<"]"<<endl;
    }
}

int main(){
    int num_mem,num_proc;
    cout<<"Enter the number of memory blocks : ";
    cin>>num_mem;
    cout<<"Enter the number of processes : ";
    cin>>num_proc;
    vector<int> memory(num_mem),process(num_proc);
    cout<<"Enter the size of all memory block : ";
    for(int i=0;i<num_mem;i++) cin>>memory[i];
    cout<<"Enter the size of all processes : ";
    for(int i=0;i<num_proc;i++) cin>>process[i];
    
    int strategy;
    cout<<"Enter the allocation strategy  : "<<endl;
    cout<<"1. First Fit"<<endl;
    cout<<"2. Best Fit"<<endl;
    cout<<"3. Worst Fit"<<endl;
    cin>>strategy;

    switch(strategy){
        case 1:
            first_fit(memory,process,num_mem,num_proc);
            break;
        case 2:
            best_fit(memory,process,num_mem,num_proc);
            break;
        case 3:
            worst_fit(memory,process,num_mem,num_proc);
            break;
        default:
            cout<<"Invalid Input!"<<endl;
            break;
    }
    return 0;   
}
