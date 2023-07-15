#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct Node{




};

int main() {

    string line;
    char arrMap[200];

    //чтение файла-карты

    ifstream map("map1.txt");
    if (map.is_open())
    {
        while(getline(map, line)) {
            strcpy( arrMap, line.c_str() );
            int i=0;
            while(arrMap[i]){
                if(arrMap[i]=='1'){
                    arrMap[i]='#';
                }
                if(arrMap[i]=='0'){
                    arrMap[i]='.';
                }
                cout << arrMap[i];
                i++;
            }
            cout << endl;
        }
        map.close();
    }
    else cout << "Unable to open map1";







}