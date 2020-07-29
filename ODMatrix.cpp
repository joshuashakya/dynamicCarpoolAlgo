//
// Created by user on 27/07/2020.
//



#include "ODMatrix.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <sstream>

using namespace std;

vector<float> readfile(string FILENAME){

    vector <float> data;
    ifstream in(FILENAME);

    if(!in) {
        cout << "Cannot open input file.\n";
    }

    string od_data;
    float odata;

    while (getline(in, od_data)) {
//        cout << od_data << endl;
//        ss << od_data;
//        ss >> odata;
        odata = stof(od_data);


        data.push_back(odata);

    }
    in.close();

    return data;
}

vector<array<float, 2>> make_pair(vector<float> pre_data){
    vector<array<float, 2>> od_data;
    array<float, 2> data{};

    for (int i=0; i<pre_data.size(); i+=2){
        data[0] = pre_data[i];
        data[1] = pre_data[i+1];

        od_data.push_back(data);
    }

    return od_data;
}

void ODMatrix::loadDict(){
    dict.insert(pair<string, int>("montbeliard", 0));
    dict.insert(pair<string, int>("hericourt", 1));
    dict.insert(pair<string, int>("fontaine", 2));
    dict.insert(pair<string, int>("dannemarie", 3));
    dict.insert(pair<string, int>("altkirch", 4));
    dict.insert(pair<string, int>("mulhouse", 5));
    dict.insert(pair<string, int>("basel", 6));
}

map<string, int> ODMatrix::getDict(){
    return dict;

}
vector<vector<array <float ,2>>> ODMatrix::getOD(){
    return matrix;
}

ODMatrix::ODMatrix() {
    loadDict();

    string fname = "../odmatrix_data.txt";
    vector <float> pre_data = readfile(fname);

//    cout<<"size of predata is "<<pre_data.size()<<endl;

    vector<array<float, 2>> od_data = make_pair(pre_data);

//    for(int i=0; i<od_data.size(); i++){
//        cout << "od data is (" << od_data[i].at(0) << " , "<< od_data[i].at(1)<<")" << endl;
//    }


    int size = 7;
    matrix.resize(size);
    int index = 0;

    for (int i=0; i<matrix.size(); ++i){
        for(int j=0; j<matrix.size(); ++j){
//            vector<array<int *, 2>> row;
            index = i*size + j;
            matrix[i].push_back(od_data[index]);
        }
    }

//    for (int i=0; i<matrix.size(); ++i){
//        for(int j=0; j<matrix[i].size(); ++j){
//            cout<<"the matrix data is ["<<matrix[i][j].at(0)<<", "<<matrix[i][j].at(1)<<"]";
//        }
//        cout<<endl;
//    }







};