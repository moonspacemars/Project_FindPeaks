#include<iostream>
#include<fstream>
#include<limits.h>
#include<vector>
#include<stdio.h>
#include<time.h>
#include<stdexcept>
#include<exception>

using namespace std;

class peakLocation{
    public:
        int row;
        int column;
};


void createTestCase(){
    const int ROW_COUNT=1000;
    const int COLUMN_COUNT=1000;
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
}






int main(int argc, char *argv[]){
    clock_t start_time, end_time;
    double init_time,readFile_time,ouput_time;
    int temp,matrixRowCount=0,matrixColumnCount=0,rowCount=0, columnCount=0;
    createTestCase();
    
  

    string filePath;
    filePath.assign(argv[1]);
    filePath=filePath+"/matrix.data";
    vector<peakLocation> peakGroup;
    peakLocation singlePeak;
    //cout<<filePath<<endl;
    ifstream inputFile(filePath);
    if (!inputFile){
        cout<<"Cannot open file.\n";
        //return -1;
    }
    inputFile>>rowCount;
    inputFile>>columnCount;
    matrixColumnCount=columnCount+2;
    matrixRowCount=rowCount+2;
    //cout<<matrixRowCount<<endl;

    try{
        vector< vector<int> > field;//(matrixRowCount ,vector<int>(matrixColumnCount,INT_MIN) );
  
    start_time=clock();
    //int peakField[matrixRowCount][matrixColumnCount];
    field.resize(matrixRowCount);
    for (int i=0; i<matrixRowCount; i++){
        field[i].resize(matrixColumnCount);
        for (int j=0; j<matrixColumnCount; j++){
            field[i][j]=INT_MIN;
            //field[i].push_back(INT_MIN);
            //peakField[i][j]=0;
        }
    }
    end_time=clock();
    init_time=(double)(end_time-start_time)/CLOCKS_PER_SEC;

    //cout<<"finish init"<<endl;
    //input value from test case file

    start_time=clock();
    for (int i=1; i<matrixRowCount-1; i++){
        for (int j=1; j<matrixColumnCount-1; j++){
            inputFile>>field[i][j];
        }
    }
    inputFile.close();
    end_time=clock();
    readFile_time=(double)(end_time-start_time)/CLOCKS_PER_SEC;
    //cout<<"finish loading"<<endl;

   
    //show on terminal
    /*for (int i=0; i<matrixRowCount; i++){
        for (int j=0; j<matrixColumnCount; j++){
            cout<<field[i][j]<<" ";
        }
        cout<<"\n";
    }*/

    //int peakCount=0;
    start_time=clock();
    for (int i=1;i<matrixRowCount-1;i++){
        for(int j=1;j<matrixColumnCount-1;j++){
            if ((field[i][j]>=field[i-1][j]) && (field[i][j]>=field[i][j-1])&&
               (field[i][j]>=field[i+1][j]) && (field[i][j]>=field[i][j+1]))
               {
                   //peakField[i][j]=1;
                   //peakCount++;
                   singlePeak.row=i;
                   singlePeak.column=j;
                   peakGroup.push_back(singlePeak);


               }
        }
    }

    end_time=clock();
    double costTime=(double)(end_time-start_time)/CLOCKS_PER_SEC;
    //cout<<"size:"<<peakGroup.size()<<"\n";
    //cout<<"capcity:"<<peakGroup.capacity()<<"\n";

  
start_time=clock();
    string outputFile;
    outputFile.assign(argv[1]);
    outputFile=outputFile+"/final.peak";
    ofstream answerOutput (outputFile);
    if (answerOutput.is_open()){        
        answerOutput<<peakGroup.size()<<"\n";
        for(int i=0; i<peakGroup.size();i++)
        {
            answerOutput<<peakGroup[i].row<<" "<<peakGroup[i].column<<"\n";
        }
    }
    else cout<<"unable to open file!";
    end_time=clock();
        
    
    double ouputTime=(double)(end_time-start_time)/CLOCKS_PER_SEC;
    cout<<"init:"<<init_time<<endl;
    cout<<"read file:"<<readFile_time<<endl;
    cout<<"cal:"<<costTime<<endl;
    cout<<"output:"<<ouputTime<<endl;
    //cout<<

    //delete[] field;

    }
    catch(...){
        cout<<"error";
       // cerr<<e.what();
    }

    return 0;
}