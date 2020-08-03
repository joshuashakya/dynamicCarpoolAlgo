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
private:
    static int newUID;
    const int uid;
public:
    std::vector<ItinPoints> itinpts;
    int satisfied_requests;
    vector<int> requests_satisfied;

    Itinerary():uid(newUID++){

    }


//    Itinerary(Itinerary const &it_copy){
//
//        for(int i=0;i<it_copy.itinpts.size();i++){
//            itinpts.push_back(it_copy.itinpts[i]);
//        }
//    }
    void addPoint(ItinPoints ip){
        itinpts.push_back(ip);
    }
    void print_itin(){
        for(int i=0;i<itinpts.size();i++){
            itinpts[i].print_itpts();
        }
//        cout<<"id is "<<itineraryId<<endl;

    }
//    void setItineraryNumber(int no){
//        itinerary_no=no;
//    }

    float getTime(string stime){
        string h = stime.substr(0, stime.find(":"));
        stime.erase(0,  h.length()+1);
        string m = stime;
        float time = stof(h) * 60 + stof(m);

        return time;
    }

    int getID(){
        return uid;
    }

    bool satisfies(Request r, ODMatrix od){

        bool checked = false;
        map<string, int> dict = od.getDict();
        vector<vector<array <float, 2>>> matrix = od.getOD();

        int sP = dict.at(r.start.name);

        int dP = dict.at(r.dest.name);

        int itinSP = dict.at(itinpts.front().pos.name);

        int itinDP = dict.at(itinpts.back().pos.name);

        if(sP >= itinSP && dP <= itinDP){

            float itinST = getTime(itinpts.front().pos.time_at_least);
            float itinDT = getTime(itinpts.back().pos.time_at_least);
            float timeST = getTime(r.start.time_at_least);
            float timeDT = getTime(r.dest.time_at_least);

            if(timeST >= itinST && timeDT <= itinDT)
                return true;
        }

        return false;

    }

//    bool combine(Request r,ODMatrix od){
//        int total_passenger=0;
//        map<string, int> dict = od.getDict();
//        vector<vector<array <float, 2>>> matrix = od.getOD();
//        for(int i=0;i<this->itinpts.size();i++){
//            if(dict.at(this->itinpts[i].pos.name)<dict.at(r.start.name)) {
//                total_passenger = total_passenger + (this->itinpts[i].pos.pickup) + (this->itinpts[i].pos.delivery);
//            }
//        }
//        cout<<"Total passenger is"+total_passenger;
//
//    }
    void showSatisfiedRequests(){
        for(int i:requests_satisfied){
            cout<<"satisfied requests"<<i<<",";
        }
    }

    bool combine(Itinerary it,vector<Request> request_demand_list){
        bool can_change_veh=false;
        for(Request k:request_demand_list){

            for(int request_id: requests_satisfied){
                if(k.request_no==request_id){
                    if(k.modality_report==">1"){
                        can_change_veh=true;
                    }
                    else{
                        can_change_veh=false;
                        goto label;
                    }
                }
            }

        }
        label:
        cout<<"This req modality report is:"<<can_change_veh<<endl;

    }


};


#endif //CARPOOL_ITINERARY_H
