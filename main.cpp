#include <iostream>
#include <vector>
#include <fstream>
#include "Organization.h"
#include "Request.h"
#include "ODMatrix.h"
using namespace std;
int main() {
    vector<Organization> orgs_list;
    std::vector<Request> request_demand_list;

    string FILENAME = "../requests.txt";

    ifstream in(FILENAME);

    if(!in) {
        cout << "Cannot open input file.\n";
        return 1;
    }

    string request_demand;
    int i=0;
    while (getline(in, request_demand)) {
//        std::cout << request_demand << std::endl;
        request_demand_list.push_back(Request(request_demand));
    }
    in.close();
    for(Request i : request_demand_list){
        i.findtw();
        cout<<endl;
    }

//    ODMatrix od;

    return 0;
}
