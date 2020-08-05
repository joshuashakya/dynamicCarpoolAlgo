#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Organization.h"
#include "Request.h"
#include "ODMatrix.h"

using namespace std;
vector<Organization> orgs_list;
std::vector<Request> request_demand_list;

vector<ItinPoints> sortAscending(vector<ItinPoints> itin,  map<string, int> dict){
    sort( itin.begin( ), itin.end( ), [dict]( auto& lhs, auto& rhs )
    {
        return  dict.at(lhs.pos.name)< dict.at(rhs.pos.name);
    });

    return itin;
}


void CarpoolAlgorithm(vector<Request> r, Organization o1,ODMatrix od){
    int itin_no=0;

    if(o1.is_empty()== 0){
//        cout<<"weeeeeeeeeee areeeeeeee hereeeeeeeeeeeee";
    }

    map<string, int> dict = od.getDict();
    vector<Itinerary > all_its;
    vector<Request> request_demand_only;
    vector<Request> request_demand_validated;
    vector<Request> offers_to_combine;
    for(Request i : request_demand_list) {
        i.validateRequestTw(od);
//        cout<<"is validated? =>"<<i.validated<<endl;
        if(i.validated && i.start_as_driver == 0){
//            cout<<"hello i'm here"<<endl;
            request_demand_only.push_back(i);
        }
        if(i.validated && i.r.role_name=="Mdr"||i.r.role_name=="Odr"){
//            cout<<"hello i'm here"<<endl;
            offers_to_combine.push_back(i);
        }
        request_demand_validated.push_back(i);

    }
    for(Request k:offers_to_combine){
        k.printrequest();
    }
    int itinID = 0;
    for(Request i : request_demand_validated){

//        i.validateRequestTw(od);

//        cout<<"hereeeeeee"<<i.start_as_driver<<" and "<<i.validated<<endl;

        if(i.validated && i.start_as_driver){

            Itinerary new_it;

            itinID++;
            itin_no=itin_no+1;
            ItinPoints ip_start(i.start,10,0);
            new_it.addPoint(ip_start);
            for(int j=0;j<i.via.size();j++){
                new_it.addPoint(ItinPoints(i.via[j],4,0));

            }
            ItinPoints ip_dest(i.dest,10,0);
            new_it.addPoint(ip_dest);
//            itin_no=itin_no+1;
//            new_it.setItineraryNumber(itin_no);
            new_it.print_itin();

//            cout<<new_it.itinerary_no;

            new_it.requests_satisfied.push_back(i.request_no);
            new_it.showSatisfiedRequests();
//            cout<<"Itinerary_number"<<new_it.itineraryId;
            all_its.push_back(new_it);

//            if(i.modality_report==">1") {
//                cout<<"here";
//                for (Request l:offers_to_combine) {
//                    if(new_it.combine(l,od)==true){
//
//                    }
//
//                }
//            }

            for(Request k: request_demand_only) {

//                k.printrequest();
//                cout<<endl;

                if(new_it.satisfies(k, od)){
//                    cout<<"hello";


//                    map<string, int> dict = od.getDict();

                    vector<ItinPoints> itin;


                    for(int j=0; j< new_it.itinpts.size(); j++){
                        itin.push_back(new_it.itinpts[j]);

                    }
                    ItinPoints ip0(k.start, 10, 0);
                    itin.push_back(ip0);

                    ItinPoints ip1(k.dest, 10, 0);
                    itin.push_back(ip1);



                    itin = sortAscending(itin, dict);


                    Itinerary new_it2;

                    itinID++;
                    for(auto & x : itin){
                        new_it2.addPoint(x);

                    }


                    new_it2.print_itin();
                    new_it2.requests_satisfied.push_back(i.request_no);
                    new_it2.requests_satisfied.push_back(k.request_no);
                    new_it2.showSatisfiedRequests();
                    all_its.push_back(new_it2);


                }

            }





        }


    }


//    for(Itinerary it:all_its){
        cout<<"list of itin"<<endl;
        for(Itinerary iit:all_its){
           iit.print_itin();
           cout<<endl;
           cout<<endl;
           iit.showSatisfiedRequests();
        }
//
//
//        }
//    }

    for(int i=0; i<all_its.size(); i++){
        all_its[i].validateTimeWindow(dict, od);
    }

      for(int i=0; i<all_its.size(); i++){
          for(int j=0; j<all_its.size();j++){
//              cout<<"id i "<<all_its[i].getID()<<endl;
              if(all_its[j].getID()!=all_its[i].getID()){
//              cout<<" id j "<<all_its[j].getID()<<endl;
                  if(all_its[i].can_combine(all_its[j],request_demand_validated,od)==true){
//                      all_its[i].combine(all_its[i],all)

                  }

                  cout<<"\n\n"<<endl;
              }
          }
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
//    request_demand_list[1].validateRequestTw(od);

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


