//
// Created by Ishan Gautam on 7/26/2020.
//

#ifndef CARPOOL_ODMATRIX_H
#define CARPOOL_ODMATRIX_H

#include <map>
#include <vector>
#include <array>
#include <string>

using namespace std;

class ODMatrix {
private:
    vector<vector<array <float ,2>>> matrix;
    map<string, int> dict;
public:
    ODMatrix();
    void loadDict();
    map<string, int> getDict();
    vector<vector<array <float ,2>>> getOD();

};


#endif //CARPOOL_ODMATRIX_H
