#include<iostream>
#include<fstream>
#include<time.h>

using namespace std;
const int ROW_COUNT=1000;
const int COLUMN_COUNT=1000;
int main(){
    srand(time(NULL));
    ofstream myfile ("matrix.data");

    int rand_seed=ROW_COUNT*COLUMN_COUNT;
 
    if (myfile.is_open()){
        myfile<<ROW_COUNT<<" "<<COLUMN_COUNT<<"\n";
        for (int i=0; i<ROW_COUNT; i++)
        {
            for (int j=0; j<COLUMN_COUNT; j++){
                myfile<<rand() % rand_seed <<" ";
            }
            myfile<<"\n";
        }
    }
    else cout<<"unable to open file!";


    return 0;
}