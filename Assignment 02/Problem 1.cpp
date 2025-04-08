#include<iostream>
#include<vector>
using namespace std;

class Bus;
class Person;
class Route;


class Route{
    int id;
    vector<string> stops;
    Bus* bus;
    public:
    Route(){}
    Route(int x):id(x),bus(nullptr){}
    void add_stop(string s){
        stops.push_back(s);
    }
    void remove_stop(string s){
        for(int i=0;i<stops.size();i++){
            if(s==stops[i]){
                stops.erase(stops.begin()+i);
            }
        }
    }
    void add_bus(Bus* b){
        bus=b;
    }

    int get_id(){
        return id;
    }

    void display(){
        cout<<"\nRoute ID: "<<this->id<<" | ";
        if(stops.size()!=0){
            for(int j=0;j<this->stops.size();j++){
                cout<<this->stops[j];
                if(j<stops.size()-1){
                    cout<<" --> ";
                }
            }
            cout<<endl;
        }
        else{
            cout<<"Stops are not Assigned"<<endl;
        }
    }

    bool operator==(Route& r){
        bool check=false;
        if(this->stops.size()==r.stops.size()){
            for(int i=0,j=0;i<this->stops.size();i++,j++){
                if(this->stops[i]==r.stops[j]){
                    check=true;
                }
                else{
                    check=false;
                    break;
                }
            }  
        }
        if(check==true) return true;
        else return false;
    }
    friend ostream& operator<<(ostream& out, Route& r);
};


class Bus{
    int busId;
    Route* route;
    vector<Person*> passenger;
    public:
    Bus(){}
    Bus(int x):busId(x),route(nullptr){}
    void add_route(Route* a){
        route=a;
    }
    void display_bus();

    void add_passenger(Person* p){
        passenger.push_back(p);
    }
    int get_id(){
        return busId;
    }
    Route* get_route(){
            return route;
    }
};

class Person{
    string person_type;
    int id;
    string name;
    int age;
    string pickup;
    string dropoff;
    Bus* bus;
    Route* r;
    bool transportation_card;
    bool pay_fee;
    bool attendance;
    public:
    Person(){}
    Person(string t,int a, string b, int c,string p, string d):person_type(t),id(a),name(b),age(c),pickup(p),dropoff(d),bus(nullptr),transportation_card(false),pay_fee(false),attendance(false),r(nullptr){}
    void add_bus(Bus* b){
        bus=b;    
        b->add_passenger(this);
    }

    void add_route_person(Route* r){
        this->r=new Route(*r);
    }
    
    virtual void fee_pay(){
        pay_fee=true;
        transportation_card=true;
    }

    int get_id(){
        return id;
    }

    string get_name(){
        return name;
    }

    string get_type(){
        return person_type;
    }

    bool get_transportation_card(){
        return transportation_card;
    }

    Route* get_route(){
        return r;
    }

    virtual void display(ostream& out){
        out<<"\nType: "<<person_type<<endl;
        out<<"ID: "<<id<<endl;
        out<<"Name: "<<name<<endl;
        out<<"Age: "<<age<<endl;
        out<<"Pickup Stop: "<<pickup<<endl;
        out<<"Dropoff Stop: "<<dropoff<<endl;
        cout<<"Attendance: ";
        if(attendance==false) cout<<"Not Marked"<<endl;
        else cout<<"Marked"<<endl;
        if(bus!=nullptr) bus->display_bus();
        else cout<<"Bus: Not Assigned"<<endl;
        if(r!=nullptr){
            out<<r;
        }
        out<<"Fee Status: ";
        if(pay_fee==true){
            out<<"Payed"<<endl;
        }
        else{
            out<<"Not Payed"<<endl;
        }
        cout<<"Transportation Card: ";
        if(transportation_card==true){
            out<<"Active"<<endl;
        }
        else{
            out<<"Not Active"<<endl;
        }
    }

    void mark_attendance(){
        if(this->transportation_card==true){
            attendance=true;
            cout<<"Attendance Marked"<<endl;
        }
        else{
            cout<<"Card not Active Yet | Pay your fee"<<endl;
        }
    }

    friend ostream& operator<<(ostream& out, Person& p);
};


class Student: public Person{
    float bus_semester_fee;
    public:
    Student(){}
    Student(int a, string b, int c,string p, string d, int fee):Person("Student",a,b,c,p,d),bus_semester_fee(fee){}

    void fee_pay() override{
        cout<<"Semester fee of "<<bus_semester_fee<<" payed"<<endl;
        Person::fee_pay();
    }

    void display_student(ostream& out){
        Person::display(out);
        cout<<"Semester Fee: "<<bus_semester_fee<<endl;
    }
}; 

class Teacher: public Person{
    float bus_monthly_fee;
    public:
    Teacher(){}
    Teacher(int a, string b, int c,string p, string d, int fee):Person("Teacher",a,b,c,p,d),bus_monthly_fee(fee){}

    void fee_pay() override{
        cout<<"Monthly fee of "<<bus_monthly_fee<<" payed"<<endl;
        Person::fee_pay();
    }

    void display_teacher(ostream& out){
        Person::display(out);
        cout<<"Monthly Fee: "<<bus_monthly_fee<<endl;
    }
}; 

class Staff: public Person{
    float bus_annual_fee;
    public:
    Staff(){}
    Staff(int a, string b, int c,string p, string d, int fee):Person("Staff",a,b,c,p,d),bus_annual_fee(fee){}

    void fee_pay() override{
        cout<<"Annual fee of "<<bus_annual_fee<<" payed"<<endl;
        Person::fee_pay();
    }

    void display_staff(ostream& out){
        Person::display(out);
        cout<<"Annual Fee: "<<bus_annual_fee<<endl;
    }
}; 


ostream& operator<<(ostream& out,Route& r){
    out<<"\nRoute ID: "<<r.id<<endl;
    if(r.bus!=nullptr)  cout<<"Bus ID: "<<r.bus->get_id()<<endl;
    else cout<<"Currently Not Assigned to any Bus"<<endl;
    if(r.stops.size()!=0){
        for(int i=0;i<r.stops.size();i++){
            out<<r.stops[i];
            if(i<r.stops.size()-1){
                out<<" --> ";
            }
        }
        out<<endl;
    }
    else{
        out<<"Stops are not Assigned"<<endl;
    }
    return out;
}

ostream& operator<<(ostream& out, Person& p){
    p.display(out);
    return out;
}

void Bus::display_bus(){
    cout<<"\nBus ID: "<<busId<<endl;
    if(route!=nullptr){
        route->display();
    }
    else{
        cout<<"No Routes Assigned to this Bus"<<endl;
    }
    if(passenger.size()==0){
        cout<<"No Passengers alloted to this Bus"<<endl;
    }
    else{
        cout<<"Passenger Name with ID: "<<endl;
        for(int i=0;i<passenger.size();i++){
            cout<<"ID: "<<passenger[i]->get_id()<<" Name: "<<passenger[i]->get_name()<<" Passenger Type: "<<passenger[i]->get_type()<<endl;
        }
    }
}



int main(){
    int n,n1,n2,age,fee,i,j;
    string name,pick,drop,type;
    bool check,check2,check3;

    Bus** bus=new Bus*[100];
    Person** person=new Person*[100];
    Route** route=new Route*[100];
    for(int i=0;i<100;i++){
        bus[i]=nullptr;
        person[i]=nullptr;
        route[i]=nullptr;
    }

    while(1){
        cout<<"\n1. Person\n2. Routes\n3. Bus\n4. Exit\nEnter the Corresponding Number: ";
        cin>>n;
        if(n==1){
            while(1){
                cout<<"\nMAIN -> PERSON\n1. Add a Person\n2. Display complete info of a Person\n3. Display ID, Name of All\n4. Pay Semester Fee\n5. Mark Attendance\n6. Select Route\n7. Select a Bus\n8. Exit\nEnter the Corresponding Number: ";
                cin>>n1;
                if(n1==1){
                    cout<<"Enter the Person Age: ";
                    cin>>age;
                    cout<<"Enter the Person Name: ";
                    cin>>name;
                    cout<<"Enter the Pickup Stop: ";
                    cin>>pick;
                    cout<<"Enter the Dropoff Stop: ";
                    cin>>drop;
                    while(1){
                        cout<<"Is the Person a:\n1. Teacher\n2. Student\n3. Staff Member\nEnter the Corresponding Number: ";
                        cin>>n2;
                        for(i=0;i<100;i++){
                            if(person[i]==nullptr) break;
                        }
                        if(n2==1){
                            cout<<"Enter the Monthly Bus Fee for the Teacher: ";
                            cin>>fee;
                            person[i]=new Teacher(i+1000,name,age,pick,drop,fee);
                            break;   
                        }
                        else if(n2==2){
                            cout<<"Enter the Semester Bus Fee for the Student: ";
                            cin>>fee;
                            person[i]=new Student(i+1000,name,age,pick,drop,fee);
                            break;
                        }
                        else if(n2==3){
                            cout<<"Enter the Annual Bus Fee for the Staff Member: ";
                            cin>>fee;
                            person[i]=new Staff(i+1000,name,age,pick,drop,fee);
                            break;
                        }
                        else cout<<"Enter the Valid Number"<<endl;
                    }
                    cout<<"Person Added into the System"<<endl;
                    cout<<"\n --- Added Person Info ---";
                    cout<<*person[i];
                }
                else if(n1==2){
                    check=false;
                    cout<<"Enter the ID of the Person whose Info to be Displayed: ";
                    cin>>age;
                    for(i=0;person[i]!=nullptr;i++){
                        if(age==person[i]->get_id()){
                            check=true;
                            break;
                        }
                    }
                    if(check==true) cout<<*person[age-1000];
                    else cout<<"No ID Found"<<endl;
                }
                else if(n1==3){
                    check=false;
                    for(i=0;person[i]!=nullptr;i++){
                        cout<<"Type: "<<person[i]->get_type()<<" | ID: "<<person[i]->get_id()<<" | Name: "<<person[i]->get_name()<<endl;
                        check=true;
                    }
                    if(check==false) cout<<"Persons List Empty"<<endl;
                }
                else if(n1==4){
                    check=false;
                    cout<<"Enter the ID of the Person whose Fee is to be Payed: ";
                    cin>>age;
                    for(i=0;person[i]!=nullptr;i++){
                        if(i==age-1000){
                            check=true;
                            break;
                        }
                    }
                    if(check==true) person[age-1000]->fee_pay();
                    else cout<<"No ID Found"<<endl;
                }
                else if(n1==5){
                    check=false;
                    cout<<"Enter the ID of the Person whose Fee is to be Payed: ";
                    cin>>age;
                    cout<<"Card Tapped..."<<endl;
                    for(i=0;person[i]!=nullptr;i++){
                        if(i==age-1000){
                            check=true;
                            break;
                        }
                    }
                    if(check==true) person[age-1000]->mark_attendance();
                    else cout<<"No ID Found"<<endl;
                }
                else if(n1==6){
                    check=false;
                    cout<<"Enter the ID of the Person to select the route: ";
                    cin>>age;
                    for(i=0;person[i]!=nullptr;i++){
                        if(i==age-1000){
                            check=true;
                            break;
                        }
                    }
                    if(check==true){
                        if(person[i]->get_transportation_card()==1){
                            check=false;
                            check2=false;
                            for(j=0;route[j]!=nullptr;j++){
                                check=true;
                            }
                            if(check==true){
                                cout<<"Here is the Total List of Routes FAST Buses go to: ";
                                for(j=0;route[j]!=nullptr;j++){
                                    cout<<*route[j];
                                }
                                cout<<"Enter the ID of the Route you chose: ";
                                cin>>age;
                                for(j=0;route[j]!=nullptr;j++){
                                    if(age==route[j]->get_id()){
                                        person[i]->add_route_person(route[j]);
                                        cout<<"Route added to the person"<<endl;
                                    }
                                }
                            }
                            else cout<<"Routes are not Added in the System"<<endl;
                        }
                        else cout<<"Transportation Card Not Active Yet | Pay Fee"<<endl;
                    }
                    else cout<<"No ID Found"<<endl;
                }
                else if(n1==7){
                    check=false;
                    check2=false;
                    cout<<"Enter the ID of the Person to assign the bus: ";
                    cin>>age;
                    for(i=0;person[i]!=nullptr;i++){
                        if(i==age-1000){
                            check=true;
                            break;
                        }
                    }
                    if(check==true){
                        // Route* temp=person[i]->get_route();
                        if(person[i]->get_transportation_card()==1){
                            // Route* temp1=bus[j]->get_route();
                            cout<<"Here is the List of Buses Available to your route: "<<endl;
                            for(j=0;bus[j]!=nullptr;j++){
                                cout<<"\n";
                                bus[j]->display_bus();
                                check2=true;
                            }
                            if(check2==true){
                                cout<<"Enter the ID of the Bus you want: ";
                                cin>>age;
                                for(j=0;bus[j]!=nullptr;j++){
                                    if(age==bus[j]->get_id()){
                                            person[i]->add_bus(bus[j]);
                                            cout<<"Bus Alloted to the Person"<<endl;
                                        
                                    }
                                }
                            }
                            else cout<<"No Bus Available for your Route"<<endl;
                        }
                        else cout<<"Transportation Card Not Active Yet | Pay Fee"<<endl;
                    }
                    else cout<<"No ID Found"<<endl;
                }
                else if(n1==8) break;
                else cout<<"Enter a Valid Number"<<endl;
            }
        }
        else if(n==2){
            while(1){
                cout<<"\nMAIN -> ROUTES\n1. Add a Route\n2. Display a Route Complete Information\n3. Display All Routes Id and stops\n4. Add a Stop\n5. Alot the route to a bus\n6. Exit\nEnter the Corresponding Number: ";
                cin>>n1;
                if(n1==1){
                    for(i=0;route[i]!=nullptr;i++){}
                    route[i] = new Route(i+1000);
                    cout<<"--- Stops to the Route ---"<<endl;
                    while(1){
                        cout<<"Enter the Stop name to add or enter zero to terminate stops adding: ";
                        cin>>name;
                        route[i]->add_stop(name);
                        if(name=="0") break;
                    }
                    cout<<"Route Added to the System"<<endl;
                    cout<<*route[i];
                }
                else if(n1==2){
                    check=false;
                    cout<<"Enter the Route ID: ";
                    cin>>age;
                    for(i=0;route[i]!=nullptr;i++){
                        if(age==route[i]->get_id()){
                            check=true;
                            break;
                        }
                    }
                    if(check==true){
                        cout<<*route[i];
                    }
                    else{
                        cout<<"No Route of this ID found"<<endl;
                    }
                }
                else if(n1==3){
                    check=false;
                    for(i=0;route[i]!=nullptr;i++){
                        route[i]->display();
                        check=true;
                    }
                    if(check==false) cout<<"Routes List Empty"<<endl;
                }
                else if(n1==4){
                    check=false;
                    cout<<"Enter the ID of the route in which to add a stop: ";
                    cin>>age;
                    for(i=0;route[i]!=nullptr;i++){
                        if(age==route[i]->get_id()){
                            check=true;
                            break;
                        }
                    }
                    if(check==true){
                        cout<<"Enter the Name of the Stop to add: ";
                        cin>>name;
                        route[i]->add_stop(name);
                        cout<<"Stop "<<name<<" Added to the Route"<<endl;
                    }
                    else cout<<"No Route of this ID found"<<endl;
                }
                else if(n1==5){
                    check=false;
                    check2=false;
                    cout<<"Enter the ID of the route: ";
                    cin>>age;
                    for(i=0;route[i]!=nullptr;i++){
                        if(age==route[i]->get_id()){
                            check=true;
                            break;
                        }
                    }
                    if(check==true){
                        cout<<"Enter the ID of the bus: ";
                        cin>>age;
                        for(j=0;bus[j]!=nullptr;j++){
                            if(age==bus[j]->get_id()){
                                check2=true;
                                break;
                            }
                        }
                        if(check2==true){
                            route[i]->add_bus(bus[j]);
                            bus[j]->add_route(route[i]);
                            cout<<"Bus added to the Route\nHere is the Complete Information of the Route"<<endl;
                            cout<<*route[i];
                        }
                        else cout<<"No Bus of this ID found"<<endl;
                    }
                    else cout<<"No Route of this ID found"<<endl;
                }
                else if(n1==6) break;
                else cout<<"Enter a Valid Number"<<endl;
            }
        }
        else if(n==3){
           while(1){
                cout<<"\nMAIN -> BUS\n1. Add a Bus\n2. Display A Bus Complete Information\n3. Display All buses Id and route\n4. Exit\nEnter the Corresponding Number: ";
                cin>>n1;
                if(n1==1){
                    for(i=0;bus[i]!=nullptr;i++){}
                    bus[i]= new Bus(i+1000);
                    bus[i]->display_bus();
                    cout<<"Note: The Passenger and Route is added to the Bus from the Route and Person Side"<<endl;
                }
                else if(n1==2){
                    check=false;
                    cout<<"Enter the Bus ID: ";
                    cin>>age;
                    for(i=0;bus[i]!=nullptr;i++){
                        if(age==bus[i]->get_id()){
                            check=true;
                            break;
                        }
                    }
                    if(check==true){
                        bus[i]->display_bus();
                    }
                    else{
                        cout<<"No Bus of this ID found"<<endl;
                    }
                }
                else if(n1==3){
                    for(i=0;bus[i]!=nullptr;i++){
                        cout<<"\nBus ID: "<<bus[i]->get_id()<<endl;
                        if(bus[i]->get_route()!=nullptr){
                            bus[i]->get_route()->display();
                        }
                        else{
                            cout<<"No Route Alloted to the Bus"<<endl;
                        }
                    }
                }
                else if(n1==4) break;
                else cout<<"Enter a Valid Number"<<endl;

            } 
        }
        else if(n==4) break;
        else cout<<"Enter a Valid Number"<<endl;
    }
}
