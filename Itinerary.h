//
// Created by user on 29/07/2020.
//

#ifndef CARPOOL_ITINERARY_H
#define CARPOOL_ITINERARY_H


#include <vector>

#include "ItinPoints.h"
#include "Request.h"
#include "ODMatrix.h"

//using namespace std;

class Itinerary {
public:
    std::vector<ItinPoints> itinpts;
    int satisfied_requests;

    Itinerary(){

    }
    Itinerary(Itinerary const &it_copy){
        for(int i=0;i<it_copy.itinpts.size();i++){
            itinpts.push_back(it_copy.itinpts[i]);
        }
    }
    void addPoint(ItinPoints ip){
        itinpts.push_back(ip);
    }
    void print_itin(){
        for(int i=0;i<itinpts.size();i++){
            itinpts[i].print_itpts();
        }
        cout<<endl;

    }

    float getTime(string stime){
        string h = stime.substr(0, stime.find(":"));
        stime.erase(0,  h.length()+1);
        string m = stime;
        float time = stof(h) * 60 + stof(m);

        return time;
    }

    bool satisfies(Request r, ODMatrix od){
//        cout<<"hello"<<endl;
        bool checked = false;
        map<string, int> dict = od.getDict();
        vector<vector<array <float, 2>>> matrix = od.getOD();

        cout<<"size of via in request - "<<r.start.name<<endl;
        vector<ItinPoints> copyItinpoints;
//        vector<ItinPoints> copyItinpoints2 = itinpts;

//        cout<<"size of itinpoints => "<<itinpts.size()<<"and front /back are "
//          <<itinpts.front().pos.name<<","<<itinpts.back().pos.name<<endl;
        for(int i=itinpts.size()-1; i >=0; i--){
            copyItinpoints.push_back(itinpts[i]);

        }

        int sP = dict.at(r.start.name);
        int dP = dict.at(r.dest.name);
        int itinSP = dict.at(itinpts.front().pos.name);
        int itinDP = dict.at(itinpts.back().pos.name);

        if(sP >= itinSP && dP <= itinDP)
            float itinST = getTime(itinpts.front().pos.time_at_least);
            float itinDT = getTime(itinpts.back().pos.time_at_least);
            float timeST = getTime(r.start.time_at_least);
            float timeDT = getTime(r.dest.time_at_least);

            if(timeST >= itinST && timeDT <= itinDT)
                return true;

        return false;

//        cout<<"size of copy => "<<copyItinpoints.size()<<"and front /back are "
//            <<copyItinpoints.front().pos.name<<","<<copyItinpoints.back().pos.name<<endl;
//        cout<<"lets check the vector"<<endl;

    }


};


#endif //CARPOOL_ITINERARY_H
