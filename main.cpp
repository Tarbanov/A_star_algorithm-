#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

//struct Node{
//    int x; //X coordinate
//    int y; //Y coordinate
//    int g; // Cost from the starting point
//    int h; //Distance estimation
//    int f; //f=g+h
//
//};



int main() {
    int x=0;
    int y=0;

    string line;
    vector<vector<char>> vecMap;

    ifstream map("map1.txt");
    while(getline(map,line)){
        vector<char> row;
        for(char &c : line){
            row.push_back(c);
        }
        vecMap.push_back(row);
    }

    int rows=0;
    int columns =0;
    for(vector<char> &row : vecMap){
        columns=0;
        for(char &c: row){

            if(c=='1'){
                c='#';
            }
            if(c=='0'){
                c='.';
            }
            cout << c;
            columns++;
        }
        rows++;
        cout << endl;
    }

    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(vecMap[i][j]=='F'){
                x=i;
                y=j;
                break;
            }
        }
    }

    cout<< x << " " << y << endl;







    




}