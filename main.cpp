#include <iostream>
#include <vector>
#include <fstream>
#include "Organization.h"
#include "Request.h"
#include "ODMatrix.h"
using namespace std;
vector<Organization> orgs_list;
std::vector<Request> request_demand_list;

void CarpoolAlgorithm(vector<Request> r, Organization o1,ODMatrix od){


    if(o1.is_empty()== 0){
        cout<<"weeeeeeeeeee areeeeeeee hereeeeeeeeeeeee";
    }

    for(Request i : request_demand_list){
//        i.v;
//        cout<<"before validation => "<<i.validated<<endl;
////        _sleep(1);
        i.validateRequestTw(od);
//        cout<<"after validation => "<<i.validated<<endl;
//        cout<<endl;
        i.r.print_role();
    }



}
int main() {
    ODMatrix od;



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
    Organization o1;
    CarpoolAlgorithm(request_demand_list, o1, od);

//    request_demand_list[0].validateRequestTw(od);

//    for(Request i : request_demand_list){
////        i.v;
////        cout<<"before validation => "<<i.validated<<endl;
////        _sleep(1);
//        i.validateRequestTw(od);
//        cout<<"after validation => "<<i.validated<<endl;
//        cout<<endl;
//    }

//    ODMatrix od;

    return 0;
}


