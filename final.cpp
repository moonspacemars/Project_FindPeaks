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


int main(int argc, char *argv[]){    
    int matrixRowCount=0,matrixColumnCount=0,rowCount=0, columnCount=0;
    string filePath;
    filePath.assign(argv[1]);
    filePath=filePath+"/matrix.data";
    vector<peakLocation> peakGroup;
    peakLocation singlePeak;
    ifstream inputFile(filePath);
    if (!inputFile){
        cout<<"Cannot open file.\n";
    }
    inputFile>>rowCount;
    inputFile>>columnCount;
    matrixColumnCount=columnCount+2;
    matrixRowCount=rowCount+2;
    try{
    vector< vector<int> > field;
  
 
    field.resize(matrixRowCount);
    for (int i=0; i<matrixRowCount; i++){
        field[i].resize(matrixColumnCount);
        for (int j=0; j<matrixColumnCount; j++){
            field[i][j]=INT_MIN;
        }
    }


    for (int i=1; i<matrixRowCount-1; i++){
        for (int j=1; j<matrixColumnCount-1; j++){
            inputFile>>field[i][j];
        }
    }
    inputFile.close();


    for (int i=1;i<matrixRowCount-1;i++){
        for(int j=1;j<matrixColumnCount-1;j++){
            if ((field[i][j]>=field[i-1][j]) && (field[i][j]>=field[i][j-1])&&
               (field[i][j]>=field[i+1][j]) && (field[i][j]>=field[i][j+1]))
               {                  
                   singlePeak.row=i;
                   singlePeak.column=j;
                   peakGroup.push_back(singlePeak);
               }
        }
    }  
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
    peakGroup.clear();
    vector<peakLocation>().swap(peakGroup);
    vector<vector<int>>().swap(field);



    }
    catch(...){
        cout<<"error";

    }

    return 0;
}