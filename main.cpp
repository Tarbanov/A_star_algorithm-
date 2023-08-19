#include <iostream>
#include <vector>
#include <string>

#include "a_star_func.h"

int main() {
    int x_start, y_start, x_finish, y_finish, menu_num, menu_map;

    string line;
    vector<vector<char>> vecMap;

    system("clear");

    //menu
    cout << "A* algorithm:" << endl;
    cout << "1) Select a map" << endl;
    cout << endl ;

    cout << "Choose an action: ";
    cin >> menu_num;

    while(menu_num!=1){
        cout << "There is no such number, please enter the correct number:";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> menu_num;
    }

    system("clear");
    cout << "Maps: " << endl;
    cout << "1) Map1(size: 18*42)" << endl;
    cout << "2) Map2(size: 25*30)" << endl;
    cout << "3) Map3(size: 39*74)" << endl;
    cout << "4) Choose my own map" << endl;
    cout << endl;

    cout << "Choose a map: ";
    cin >> menu_map;

    while(menu_map!=1 && menu_map!=2 && menu_map!=3 && menu_map!=4){
        cout << "There is no such number, please enter the correct number:";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> menu_map;
    }

    string menu_map_name;

    switch (menu_map) {
        case 1:
            menu_map_name="map1.txt";
            break;
        case 2:
            menu_map_name="map2.txt";
            break;
        case 3:
            menu_map_name="map3.txt";
            break;
    }

    //reading .txt and writing up to 2D vector
    ifstream map(menu_map_name);
    while(getline(map,line)){
        vector<char> row;
        for(char &c : line){
            if(c==' '){
                continue;
            }
            row.push_back(c);
        }
        vecMap.push_back(row);
    }



    if(menu_map==4){
        system("clear");
        string name_own_map;
        cout << "Enter file name:" <<endl;
        cin >> name_own_map;
        string file_name[8] ={"cmake-build-debug","a.out","CMakeLists.txt","documentation.txt","main.cpp","map1.txt","map2.txt","map3.txt"};
        bool flag2 = true;

        for (const auto & l : file_name){
            if (name_own_map == l)
                flag2 = false;
        }

        bool flag = false;

        while(!flag) {
            ifstream iff(name_own_map);
            if (iff.good() and flag2){
                flag= true;
            } else {
                cout << "There is no such name, please enter the correct name:";
                cin.clear();
                cin >> name_own_map;
                flag2= true;
                for (const auto & l : file_name){
                    if (name_own_map == l)
                        flag2 = false;
                }
            }
        }

        ifstream map(name_own_map);
        while(getline(map,line)){
            vector<char> row;
            for(char &c : line){
                if(c==' '){
                    continue;
                }
                row.push_back(c);
            }
            vecMap.push_back(row);
        }
    }



//Replacing numbers with signs 1==# , 0==.
    int rows=0;
    int columns =0;
    if(menu_map!=4) {
        for (vector<char> &row: vecMap) {
            columns = 0;
            for (char &c: row) {
                if (c == '1') {
                    c = '#';
                }
                if (c == '0') {
                    c = '.';
                }
                cout << c << " ";
                columns++;
            }
            rows++;
            cout << endl;
        }
        //find Start coordinates
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (vecMap[i][j] == 'S') {
                    x_start = j;
                    y_start = i;
                    break;
                }
            }
        }

        //find Finish coordinates
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (vecMap[i][j] == 'F') {
                    x_finish = j;
                    y_finish = i;
                    break;
                }
            }
        }
    }

    else{
        system("clear");

        for (vector<char> &row: vecMap) {
            columns = 0;
            for (char &c: row) {
                if (c == '1') {
                    c = '#';
                }
                if (c == '0') {
                    c = '.';
                }
                cout << c << " ";
                columns++;
            }
            rows++;
            cout << endl;
        }


        cout << rows << columns << endl;
        cout << "set start coordinates" << endl;
        cout << "x-axis: ";
        cin >> x_start;
        x_start=right_coordinates_x(x_start,columns);
        cout << "y-axis: ";
        cin >> y_start;
        y_start=right_coordinates_y(y_start,rows);
        cout << "set finish coordinates" << endl;
        cout << "x-axis: ";
        cin >> x_finish;
        x_finish=right_coordinates_x(x_finish,columns);
        cout << "y-axis: ";
        cin >> y_finish;
        y_finish=right_coordinates_y(y_finish,rows);

        vecMap[y_start][x_start]='S';
        vecMap[y_finish][x_finish]='F';
    }


    path(x_start,y_start,x_finish,y_finish,vecMap,rows,columns);

}