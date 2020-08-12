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
        return  dict.at(lhs.pos.name) < dict.at(rhs.pos.name);
    });

    return itin;
}

vector<Itinerary> sortItin(vector<Itinerary> itin){
    sort( itin.begin(), itin.end(), []( Itinerary lhs, Itinerary rhs )
    {
        return  lhs > rhs;
    });

    return itin;
//    vector<Itinerary> sorted;
//    int size = itin.size();
//
//    for(int i=0; i<size; i++){
//        sorted.push_back(itin[i]);
//        for(int j=0; j<size; j++){
//            if(itin[j].requests_satisfied.size() > sorted.back().requests_satisfied.size()){
//                sorted.pop_back();
//                sorted.push_back(itin[j]);
//            }
//        }
//    }

}



void CarpoolAlgorithm(vector<Request> r, Organization o1,ODMatrix od){
    int itin_no=0;

    if(o1.is_empty()== 0){
//        cout<<"weeeeeeeeeee areeeeeeee hereeeeeeeeeeeee";
    }

    map<string, int> dict = od.getDict();
    vector<Itinerary > all_its;
    vector<Itinerary> return_trip_its;
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
            cout<<"Priting position"<<endl;

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
        cout<<"\n\n\nlist of itin"<<endl;
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

//    for(int i=0; i<all_its.size(); i++){
//        all_its[i].validateTimeWindow(dict, od);
//    }

    vector<Itinerary> combIts;
    vector<ItinPoints> combItPnts;
      for(int i=0; i<all_its.size(); i++){
          for(int j=0; j<all_its.size();j++){
//              cout<<"id i "<<all_its[i].getID()<<endl;
              if(i!=j){

//              cout<<" id j "<<all_its[j].getID()<<endl;
                  if(all_its[i].can_combine(all_its[j],request_demand_validated,od)==true){
                      cout<<"here";
                      Itinerary combined_it=all_its[i].combine(all_its[i],all_its[j],od);
                      for(int a:all_its[i].requests_satisfied){
                          combined_it.requests_satisfied.push_back(a);
                      }
                      for(int b:all_its[j].requests_satisfied){
                          combined_it.requests_satisfied.push_back(b);
                      }
                      combIts.push_back(combined_it);

                  }

                  cout<<"\n\n"<<endl;
              }
          }
      }

      if(combIts.size()!=0){
          for(int i=0;i<combIts.size();i++){
              all_its.push_back(combIts[i]);
          }

      }

//    vector<Itinerary> return_trip_its;
    for(int i=0; i<all_its.size(); i++){
        for(int j=0; j<all_its.size();j++){
//              cout<<"id i "<<all_its[i].getID()<<endl;
            if(i!=j){

                if(all_its[i].ret_trip_poss(all_its[j],request_demand_validated,od)==true){


                    Itinerary return_trip_it=all_its[i].createReturnTrip(all_its[j],request_demand_validated);
                    cout<<"size of returned trip -> "<<return_trip_it.getReturnSize()<<endl;
//                    return_trip_its.push_back(return_trip_it);
                    return_trip_its.push_back(Itinerary(return_trip_it));
                    cout<<"size of ret trip vector -> "<<return_trip_its.back().getReturnSize()<<endl;

                }

                cout<<"\n\n"<<endl;
            }
        }
    }
    for(int i=0;i<return_trip_its.size();i++){
//        cout<<"adding to all its with return trip size ->"<<return_trip_its[i].returnTrip.size()<<endl;
        all_its.push_back(return_trip_its[i]);
    }

    cout<<"list of itin before valid"<<endl;
    for(Itinerary iit:all_its){
        iit.print_itin();
        cout<<endl;

//        iit.showSatisfiedRequests();
    }


    cout<<endl;
    cout<<endl;
    cout<<endl;

    cout<<"list of itin after valid"<<endl;
    for(Itinerary iit:all_its){
        iit.validateTimeWindow(dict, od);
        iit.print_itin();
        cout<<endl;

//        iit.showSatisfiedRequests();
    }

    int total_itineraries=all_its.size();
    int deleted_itineraries=0;

    std::sort(all_its.begin(), all_its.end(), greater <>());

  cout<<"Itineraries no request done"<<endl;
    for(int i=0;i<all_its.size();i++){

        if(all_its[i].requests_satisfied.size()<=1){
            deleted_itineraries=total_itineraries-i;
            all_its.erase(all_its.begin()+i,all_its.end());
            break;
//
        }
    }
    cout<<endl<<"The total itineraies were "<<total_itineraries<<endl;
    cout<<endl<<"the deleted itineraries were"<<deleted_itineraries<<endl;

    cout<<"List of itineraries:"<<endl;
    for(Itinerary iit:all_its){

        iit.print_itin();
        cout<<endl;
    }


//

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


