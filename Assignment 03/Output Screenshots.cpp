#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;

class Person;
class Driver ;
class Student;
class Faculty;
class Transporter;
class Vehicle;
class Route;
class Seat;
class Booking;

class Route{
    int id;
    string start;
    string end;
    float distance;
    public:
    Route(){}
    Route(int id,string a, string b, int c):id(id),start(a),end(b),distance(c){}
    friend ostream& operator<<(ostream& out,Route& r){
        out<<"\nRoute ID: "<<r.id<<endl;
        out<<"Start Destination: "<<r.start<<endl;
        out<<"End Destination: "<<r.end<<endl;
        out<<"Distance: "<<r.distance<<endl;
        return out;
    }
    void display_route(){
        cout<<start<<" -----> "<<end<<endl;
    }
    int get_id(){return id;}
};

class Person{
    int id;
    string name;
    int age;
    string type;
    bool paid=false;
    public:
    Person(){}
    Person(int id,string a, int b,string d):id(id),name(a),age(b),type(d){}
    virtual void print(ostream& out){
        out<<"\nID: "<<id<<endl;
        out<<"Name: "<<name<<endl;
        out<<"Age: "<<age<<endl;
        out<<"Type: "<<type<<endl;
        if(type!="Driver"){
            if(paid==true) out<<"Payment: Paid"<<endl;
            else out<<"Payment: Not Paid"<<endl;
        }

    }
    friend ostream& operator<<(ostream& out,Person& object){
        object.print(out);
        return out;
    }
    void set_name(string a){name=a;}
    void set_age(int a){age=a;}
    void set_paid(bool a){paid=a;}
    int get_id(){return id;}
    bool get_pay_status(){return paid;}
    string get_type(){return type;}
    string get_name(){return name;}

    virtual int get_fare(){return -1;};
    virtual bool get_has_vehicle(){return false;};
    virtual void add_vehicle(Vehicle* v){}
    virtual void add_seat(Seat* s){}
    virtual bool get_is_bus_ac(){return false;}
    virtual void set_is_bus_ac(bool a){}


};

class Seat{
    int number;
    bool available=true;
    Person* person;
    string type;
    public:
    Seat(){}
    Seat(int a, string c):number(a),type(c),person(nullptr){}
    void set_available(bool a){available=a;}
    bool get_available(){return available;}
    string get_type(){return type;}
    void add_person(Person* p){person=p;}
    int get_number(){return number;}
    friend ostream& operator<<(ostream& out, Seat& s){
        out<<"\nSeat Number: "<<s.number<<endl;
        if(s.available==true){
            out<<"Available= Yes"<<endl;
            out<<"No Person has booked it yet";
        }
        else{
            out<<"Available: No"<<endl;
            out<<"Person Info: ";
            s.person->print(out);
        }
        return out;
    }

};

class Vehicle{
    int id;
    string type;
    string number; 
    bool is_AC;
    int student_seats;
    int faculty_seats;
    int seats;
    vector<Seat*> seating;
    Route* route;
    Person* driver;
    public:
    Vehicle(Person* drive):driver(drive){}
    Vehicle(int id,string type,string a, bool b, int s, int ss, int fs,Person* drive):id(id),type(type),number(a),is_AC(b),seats(s),student_seats(ss),faculty_seats(fs),route(nullptr),driver(drive){
        for(int i=0;i<faculty_seats;i++){
            seating.push_back(new Seat(i+1,"Faculty"));
        }
        for(int i=0;i<student_seats;i++){
            seating.push_back(new Seat(i+1,"Student"));
        }
    }
    bool get_AC(){return is_AC;}
    string get_type(){return type;}
    int get_id(){return id;}
    int get_total_seats(){return seats;}
    int get_student_seats(){return student_seats;}
    int get_faculty_seats(){return faculty_seats;}
    void add_route(Route* r){route=r;}
    Route* get_route(){return route;}
    vector<Seat*> get_seat(){return seating;}
    void print(ostream& out){
        out<<"\nID: "<<id<<endl;
        out<<"Type: "<<type<<endl;
        if(is_AC==true) out<<"AC: Yes"<<endl;
        else cout<<"AC: No"<<endl;
        out<<"Total Seats: "<<seats<<endl;
        out<<"Student Seats: "<<student_seats<<endl;
        out<<"Faculty Seats: "<<faculty_seats<<endl;
        out<<"----- Driver Info: ";
        driver->print(out);
        cout<<"----- Route Info: ";
        if(route!=nullptr) out<<*route;
        else out<<"No Route Added"<<endl;
    }
    friend ostream& operator<<(ostream& out,Vehicle& object){
        object.print(out);
        return out;
    }
    int count_remain_student_seats(){
        int count=0;
        for(int i=0;i<seating.size();i++){
            if(seating[i]->get_type()=="Student"&&seating[i]->get_available()==true){
                count++;
            }
        }
        return count;
    }

    int count_remain_faculty_seats(){
        int count=0;
        for(int i=0;i<seating.size();i++){
            if(seating[i]->get_type()=="Faculty"&&seating[i]->get_available()==true){
                count++;
            }
        }
        return count;
    }
};

class Bus:public Vehicle{
    public:
    Bus(Person* drive):Vehicle(drive){}
    Bus(int id, string a, bool b, int ss,Person* drive):Vehicle(id,"Bus",a,b,52,ss,52-ss,drive){}
};

class Coaster:public Vehicle{
    public:
    Coaster(Person* drive):Vehicle(drive){}
    Coaster(int id, string a, bool b, int ss,Person* drive):Vehicle(id,"Coaster",a,b,32,ss,32-ss,drive){}
};

class Driver:public Person{
    int License;
    Vehicle* vehicle;
    bool has_vehicle;
    public:
    Driver(){}
    Driver(int id,string a, int b, int c):Person(id,a,b,"Driver"),License(c),vehicle(nullptr),has_vehicle(false){}
    void print(ostream& out) override{
        Person::print(out);
        cout<<"License: "<<License<<endl;
        if(has_vehicle==false) cout<<"Vehicle: Not Assigned"<<endl;
        else cout<<"Vehicle: Assigned"<<endl;
    }
    bool get_has_vehicle() override {return has_vehicle;}
    void add_vehicle(Vehicle* v){
        vehicle=v;
        has_vehicle=true;
    }
    
};

class Student:public Person{
    Vehicle* vehicle;
    Seat* seat;
    bool is_bus_ac;
    public:
    static int fare;
    Student (){}
    Student (int id,string a, int b):Person(id,a,b,"Student"),vehicle(nullptr),is_bus_ac(false){}
    void print(ostream& out) override{
        Person::print(out);
        if(vehicle!=nullptr){
            out<<"Vehicle Id: "<<vehicle->get_id()<<endl;
            if(seat!=nullptr){
                out<<"Seat Number Booked: "<<seat->get_number()<<endl;
            }
        }
    }
    int get_fare() override {
        return fare;
    }
    void add_vehicle(Vehicle* v)override {vehicle=v;}
    void add_seat(Seat* s)override {seat=s;}
    bool get_is_bus_ac()override {return is_bus_ac;}
    void set_is_bus_ac(bool a)override {is_bus_ac=a;}
    
};

class Faculty:public Person{
    Vehicle* vehicle;
    Seat* seat;
    bool is_bus_ac;
    public:
    static int fare;
    Faculty (){}
    Faculty (int id,string a, int b):Person(id,a,b,"Faculty"),vehicle(nullptr),is_bus_ac(false){}
    void print(ostream& out) override{
        Person::print(out);
        if(vehicle!=nullptr) {
            out<<"Vehicle Id: "<<vehicle->get_id()<<endl;
            if(seat!=nullptr){
                out<<"Seat Number Booked: "<<seat->get_number()<<endl;
            }
        }
    }
    int get_fare() override {
        return fare;
    }
    void add_vehicle(Vehicle* v)override {vehicle=v;}
    void add_seat(Seat* s)override {seat=s;}
    bool get_is_bus_ac()override {return is_bus_ac;}
    void set_is_bus_ac(bool a)override {is_bus_ac=a;}
    
};

int Student::fare=1500;
int Faculty::fare=1000;

class Booking{
    int number;
    Seat* seat;
    Person* person;
    Vehicle* vehicle;
    Route* route;
    public:
    Booking():seat(nullptr),person(nullptr),vehicle(nullptr),route(nullptr){}
    Booking(int i,Seat* s,Person* p, Vehicle* v):number(i),seat(s),person(p),vehicle(v){
        route=vehicle->get_route();
    }
    friend ostream& operator<<(ostream& out, Booking& b){
        out<<"\nBooking Number: "<<b.number<<endl;
        out<<"Person ID: "<<b.person->get_id()<<endl;
        out<<"Person Name: "<<b.person->get_name()<<endl;
        out<<"Seat Number: "<<b.seat->get_number()<<endl;
        out<<"Vehicle ID: "<<b.vehicle->get_id()<<endl;
        out<<"Route ID: "<<b.route->get_id()<<endl;
        b.route->display_route();
        return out;
    }
};

class Transporter{
    string name;
    vector<Route*> routes;
    vector<Person*> drivers;
    vector<Vehicle*> vehicles;
    vector<Booking*>booking;
    public:
    Transporter(){}
    Transporter(string a):name(a){}
    string get_name(){return name;}

    vector<Person*> get_drivers(){return drivers;}
    vector<Vehicle*> get_vehicle(){return vehicles;}
    vector<Route*> get_route(){return routes;}
    vector<Booking*> get_booking(){return booking;}

    void add_driver(string name, int age, int license){
        drivers.push_back(new Driver(drivers.size()+10,name,age,license));
    }

    void add_vehicles(string number,bool ac ,int ss, int d,Person* driver){
        if(d==1){
            vehicles.push_back(new Bus(vehicles.size()+20,number,ac,ss,driver));
        }
        else{
            vehicles.push_back(new Coaster(vehicles.size()+20,number,ac,ss,driver));
        }
    }

    void add_route(string a, string b,float c){
        routes.push_back(new Route(routes.size()+30,a,b,c));
    }

    void add_booking(Seat* s,Person* p, Vehicle* v){
        booking.push_back(new Booking(booking.size()+1,s,p,v));
    }
};


class File_Handler{
    fstream file;
    public:
    File_Handler(){
        fstream test("User.txt",ios::in);
        if(!test.is_open()){
            file.open("User.txt",ios::out);
            file.close();
        }
        test.close();
    }

    void add_person(vector<Person*> person){
        remove("User.txt");
        file.open("User.txt",ios::out);
        for(int i=0;i<person.size();i++){
            file<<*person[i];
        }
        file.close();
    }

    void give_data(vector<Person*>* person){
        file.open("User.txt");
        string str;
        while(getline(file,str)){
            if(str.size()==0){
                string name,type;
                int age,id;
                getline(file,str);
                if(str.find("ID: ")!=-1){
                    int n=str.find(":");
                    str=str.substr(n+2,str.size());
                    id=stoi(str);
                }
    
                getline(file,str);
                if(str.find("Name: ")!=-1){
                    int n=str.find(":");
                    str=str.substr(n+2,str.size());
                    name=str;
                }
    
                getline(file,str);
                if(str.find("Age: ")!=-1){
                    int n=str.find(":");
                    str=str.substr(n+2,str.size());
                    age=stoi(str);
                }
    
                getline(file,str);
                if(str.find("Type: ")!=-1){
                    int n=str.find(":");
                    str=str.substr(n+2,str.size());
                    type=str;
                }

                string extra;
                getline(file,extra);
                if(extra.size()!=0){
                    int n=extra.find(":");
                    extra=extra.substr(n+2,extra.size());
                }

                if(type=="Student"){
                    person->push_back(new Student(id,name,age));
                }
                else if(type=="Faculty"){
                    person->push_back(new Faculty(id,name,age));
                }
                if(extra=="Paid"){
                    (*person)[person->size()-1]->set_paid(true);
                }
            }
        }
        file.close();
    }
};

int main(){
    //declarations
    vector<Person*> person;
    vector<Transporter*> transporter;
    File_Handler file;
    int a;

    transporter.push_back(new Transporter("Nadeem"));
    transporter.push_back(new Transporter("Zulfiqar"));
    file.give_data(&person);

    // main menu loop
    while(1){
        cout<<"\n----- MAIN MENU -----\n1. Users(Student or Faculty)\n2. Transporter\n3. Exit\nEnter the Corresponding number for the option: ";
        cin>>a;
        //User Menu
        if(a==1){
            int b;
            while(1){
                cout<<"\n----- MAIN MENU > USER -----\n1. Add a User\n2. Display All Users\n3. Update a User Info\n4. Pay a fee\n5. Book a Seat\n9. Exit\nEnter the Corresponding number for the option: ";
                cin>>b;
                //Adding a user 
                if(b==1){
                    string name,type;
                    int age,c;
                    cout<<"\nYou want to Register:\n1. Student ?\n2. Faculty ?\nEnter the Corresponding number to the option: ";
                    cin>>c;
                    if(c==1||c==2){
                        cout<<"Enter the Name of the User: ";
                        cin>>name;
                        cout<<"Enter the Age of the User: ";
                        cin>>age;
                        if(c==1){
                            person.push_back(new Student(person.size()+1000,name,age));
                            cout<<"New Student Added Successfully"<<endl;
                            file.add_person(person);
                        }
                        else{
                            person.push_back(new Faculty(person.size()+1000,name,age));
                            cout<<"New Faculty Added Successfully"<<endl;
                            file.add_person(person);
                        }
                    }
                    else{
                        cout<<"Invalid Option | Selection terminated"<<endl;
                    }
                }
                //Display all users
                else if(b==2){
                    if(person.size()!=0){
                        for(int i=0;i<person.size();i++){
                            cout<<*person[i];
                            cout<<endl;
                        }
                    }
                    else{
                        cout<<"No User Added Yet"<<endl;
                    }
                }
                //Update a user info
                else if(b==3){
                    int i,c;
                    bool check=false;
                    cout<<"Enter the id of the user whose info to be updated: ";
                    cin>>c;
                    for(i=0;i<person.size();i++){
                        if(person[i]->get_id()==c){
                            check=true;
                            break;
                        }
                    }
                    if(check==true){
                        cout<<"Update:\n1. Name ?\n2. Age ?\nEnter the Corresponding number for the option: ";
                        cin>>c;
                        if(c==1){
                            string name;
                            cout<<"Enter the new name: ";
                            cin>>name;
                            person[i]->set_name(name);
                            cout<<"Updated Info: "<<endl;
                            cout<<*person[i];
                        }
                        else if(c==2){
                            int age;
                            cout<<"Enter the new Age: ";
                            cin>>age;
                            person[i]->set_age(age);
                            cout<<"Updated Info: "<<endl;
                            cout<<*person[i];
                        }
                        else{
                            cout<<"Wrong Option | Updation Terminated"<<endl;
                        }
                    }
                    else{
                        cout<<"No User of this Id Found"<<endl;
                    }
                }
                // pay the fee
                else if(b==4){
                    int id,i,ac,fare;
                    bool check=false;
                    cout<<"Enter the ID of the Person whose seat is to be registered: ";
                    cin>>id;
                    for(i=0;i<person.size();i++){
                        if(person[i]->get_id()==id){
                            check=true;
                            break;
                        }
                    }
                    if(check==true){ 
                        cout<<"You want AC bus seat? (0 for No and 1 for Yes): ";
                        cin>>ac;
                        if(ac==0){
                        cout<<"You need to Pay the Fee of "<<person[i]->get_fare()<<endl;
                        cout<<"Press 1 to pay the fee: ";
                        cin>>fare;
                        if(fare==1){
                            person[i]->set_paid(true);
                            person[i]->set_is_bus_ac(false);
                            cout<<"Fee Paid"<<endl;
                            file.add_person(person);

                        }
                        else cout<<"Invald Output"<<endl;
                        }
                        else if(ac==1){
                        cout<<"You need to Pay the Fee of "<<person[i]->get_fare()+2000<<endl;
                        cout<<"Press 1 to pay the fee: ";
                        cin>>fare;
                        if(fare==1){
                            person[i]->set_paid(true);
                            person[i]->set_is_bus_ac(true);
                            cout<<"Fee Paid"<<endl;
                            file.add_person(person);

                        }
                        else cout<<"Invald Output"<<endl;
                        }
                        else cout<<"Invalid Output"<<endl;
                    }
                    else cout<<"No Person of this ID found"<<endl;
                }
                //register for a seat
                else if(b==5){
                    int id,i,j,transport;
                    bool check=false,check2=false;
                    bool  zul=false, nad=false;
                    cout<<"Enter the ID of the Person whose seat is to be registered: ";
                    cin>>id;
                    for(i=0;i<person.size();i++){
                        if(person[i]->get_id()==id){
                            check=true;
                            break;
                        }
                    }
                    if(check==true){ 
                        try{
                            if(person[i]->get_pay_status()==false){
                                throw runtime_error("Booking Failed | No Payment ");
                            }
                            if(transporter[0]->get_vehicle().size()!=0||transporter[1]->get_vehicle().size()!=0){
                                if(transporter[0]->get_route().size()!=0||transporter[1]->get_route().size()!=0){
                                    cout<<"The list of Transporters with Active Vehicles: ";

                                    // nadeem printing
                                    for(int j=0;j<transporter[0]->get_vehicle().size();j++){
                                        if(transporter[0]->get_vehicle()[j]->get_route()!=nullptr){
                                            nad=true;
                                            break;
                                        }
                                    }
                                    if(transporter[0]->get_route().size()!=0&&nad==true){
                                        cout<<"NADEEM TRANSPORTER: "<<endl;
                                        for(int j=0;j<transporter[0]->get_vehicle().size();j++){
                                            if(person[i]->get_is_bus_ac()==transporter[0]->get_vehicle()[j]->get_AC()){
                                                cout<<*transporter[0]->get_vehicle()[j]<<endl;
                                            }
                                        }
                                    }
                                    else if(transporter[0]->get_route().size()!=0&&nad==false) cout<<" Nadeem Transporter have No Vehicles with defined Routes | Give Routes to the Vehicles"<<endl;
                                    else cout<<"Nadeem Transporter have No Routes at all"<<endl;

                                    // zulfiqar printing
                                    for(int j=0;j<transporter[1]->get_vehicle().size();j++){
                                        if(transporter[1]->get_vehicle()[j]->get_route()!=nullptr){
                                            zul=true;
                                            break;
                                        }
                                    }
                                    if(transporter[1]->get_route().size()!=0&&zul==true){
                                        cout<<"ZULFIQAR TRANSPORTER: "<<endl;
                                        for(int j=0;j<transporter[1]->get_vehicle().size();j++){
                                            if(person[i]->get_is_bus_ac()==transporter[1]->get_vehicle()[j]->get_AC()){
                                                cout<<*transporter[0]->get_vehicle()[j]<<endl;
                                            }
                                        }
                                    }
                                    else if(transporter[1]->get_route().size()!=0&&zul==false) cout<<" Zulfiqar Transporter have No Vehicles with defined Routes | Give Routes to the Vehicles"<<endl;
                                    else cout<<"Zulfiqar Transporter have No Routes at all"<<endl;

                                    // seat booking
                                    if(zul==true||nad==true){
                                        vector<int> arr;
                                        if(nad==true){
                                            arr.push_back(0);
                                        }
                                        if(zul==true){
                                            arr.push_back(1);
                                        }
                                        if(arr.size()==1){
                                            if(arr[0]==0){
                                                transport=0;
                                            }
                                            if(arr[0]==1) {
                                                transport=1;
                                            }
                                        }
                                        else if(arr.size()>0){
                                            cout<<"Choose one of the Transporters whom to register to\n1. Nadeem\n2. Zulfiqar\nEnter: ";
                                            cin>>transport;
                                            if(transport==0||transport==1){}
                                            else cout<<"Invalid Option"<<endl;
                                        }
                                        if(transport==0||transport==1){
                                            int j;
                                            check2=false;
                                            cout<<"Enter the Id of the Vehicle you want to register to: ";
                                            cin>>id;
                                            for(j=0;j<transporter[transport]->get_vehicle().size();j++){
                                                if(transporter[transport]->get_vehicle()[j]->get_id()==id){
                                                    check2=true;
                                                    break;
                                                }
                                            }
                                            if(check2==true){
                                                cout<<"Everything good"<<endl;
                                                check=false;
                                                if(person[i]->get_type()=="Student"){
                                                    if(transporter[transport]->get_vehicle()[j]->get_student_seats()>0){
                                                        for(int k=0;k<transporter[transport]->get_vehicle()[j]->get_seat().size();k++){
                                                            if(transporter[transport]->get_vehicle()[j]->get_seat()[k]->get_available()==true&&transporter[transport]->get_vehicle()[j]->get_seat()[k]->get_type()==person[i]->get_type()){
                                                                person[i]->add_seat(transporter[transport]->get_vehicle()[j]->get_seat()[k]);
                                                                transporter[transport]->get_vehicle()[j]->get_seat()[k]->add_person(person[i]);
                                                                person[i]->add_vehicle(transporter[transport]->get_vehicle()[j]);
                                                                transporter[transport]->add_booking(transporter[transport]->get_vehicle()[j]->get_seat()[k],person[i],transporter[transport]->get_vehicle()[j]);
                                                                transporter[transport]->get_vehicle()[j]->get_seat()[k]->set_available(false);
                                                                cout<<"Seat Booked Successfully"<<endl;
                                                                cout<<*transporter[transport]->get_booking()[transporter[transport]->get_booking().size()-1];
                                                                check=true;
                                                                break;
                                                            }
                                                        }
                                                        if(check==false) cout<<"No Seat Available"<<endl;
                                                    }
                                                }                                                
                                                else if(person[i]->get_type()=="Faculty"){
                                                    if(transporter[transport]->get_vehicle()[j]->get_faculty_seats()>0){
                                                        for(int k=0;k<transporter[transport]->get_vehicle()[j]->get_seat().size();k++){
                                                            if(transporter[transport]->get_vehicle()[j]->get_seat()[k]->get_available()==true&&transporter[transport]->get_vehicle()[j]->get_seat()[k]->get_type()==person[i]->get_type()){
                                                                person[i]->add_seat(transporter[transport]->get_vehicle()[j]->get_seat()[k]);
                                                                transporter[transport]->get_vehicle()[j]->get_seat()[k]->add_person(person[i]);
                                                                person[i]->add_vehicle(transporter[transport]->get_vehicle()[j]);
                                                                transporter[transport]->add_booking(transporter[transport]->get_vehicle()[j]->get_seat()[k],person[i],transporter[transport]->get_vehicle()[j]);
                                                                transporter[transport]->get_vehicle()[j]->get_seat()[k]->set_available(false);
                                                                cout<<"Seat Booked Successfully"<<endl;
                                                                cout<<*transporter[transport]->get_booking()[transporter[transport]->get_booking().size()-1];
                                                                check=true;
                                                                break;
                                                            }
                                                        }
                                                        if(check==false) cout<<"No Seat Available"<<endl;
                                                    }
                                                }
                                                else cout<<"No "<<person[i]->get_type()<<" Seat available in this "<<transporter[transport]->get_vehicle()[j]->get_type() <<" now"<<endl;
                                            }
                                            else cout<<"No Vehicle of this ID found"<<endl;
                                        }
                                    }
                                }
                                else cout<<"Transporters have No Routes Assigned"<<endl;
                            }
                            else cout<<"Transporters have No Active Vehicles right now"<<endl;
                        }
                        catch(runtime_error& e){
                            cout<<e.what()<<endl;
                        }
                    }
                    else cout<<"No Person of this ID found"<<endl;
                }
                else if(b==9) break;
                else cout<<"Invalid Number"<<endl;
                file.add_person(person);
            }
        }
        // Transporter Menu
        else if(a==2){
            int b;
            int transport;
            string transport_name;
            while(1){
                cout<<"\n----- MAIN MENU > TRANSPORTER -----\n1. Nadeem\n2. Zulfiqar\n3. Exit\nEnter the Corresponding number for the option: ";
                cin>>b;
                if(b==1||b==2){
                    if(b==1) {
                        transport=0;
                        transport_name="NADEEM";
                    }
                    else{ 
                        transport=1;
                        transport_name="ZULFIQAR";
                    }
                    while(1){
                        int c;
                        cout<<"\n----- MAIN MENU > TRANSPORTER > "<<transport_name<<" -----\n1. Add a Driver\n2. Display All Drivers\n3. Add a Vehicle\n4. Display All Vehicles\n5. Add a Route\n6. Display All Routes\n7. Added Route to a Vehicle\n8. Display all bookings\n9. Exit\nEnter the Corresponding number for the option: ";
                        cin>>c;
                        //Add a driver
                        if(c==1){
                            string name;
                            int age, license;
                            cout<<"Enter the Name of Driver: ";
                            cin>>name;
                            cout<<"Enter the Age of the Driver: ";
                            cin>>age;
                            cout<<"Enter the License number of the Driver: ";
                            cin>>license;
                            transporter[transport]->add_driver(name,age,license);
                            cout<<"Driver Added Successfully"<<endl;
                            cout<<*transporter[transport]->get_drivers()[transporter[transport]->get_drivers().size()-1];
                        }
                       // display all drivers
                        else if(c==2){
                            if(transporter[transport]->get_drivers().size()!=0){
                                for(int i=0;i<transporter[transport]->get_drivers().size();i++){
                                    cout<<*transporter[transport]->get_drivers()[i]<<endl;
                                }
                            }
                            else cout<<"Drivers have not been added"<<endl;
                        }
                        // add vehicle
                        else if(c==3){
                            if(transporter[transport]->get_drivers().size()!=0){
                                string number;
                                bool ac;
                                int d,ss,type,e,i;
                                cout<<"Which type of Vehicle you are adding:\n1. Bus\n2. Coaster\nEnter the Corresponding number for the option: ";
                                cin>>d;
                                if(d==1||d==2){
                                    cout<<"Enter the Plate number of the Vehicle: ";
                                    cin>>number;
                                    if(d==1){
                                        do{
                                            cout<<"Enter the number of student seats out of 52(others are faculty ones): ";
                                            cin>>ss;
                                            if(52-ss<0) cout<<"Enter Again"<<endl;
                                        }while(52-ss<0);
                                    }
                                    else{
                                        do{
                                            cout<<"Enter the number of student seats out of 32(others are faculty ones): ";
                                            cin>>ss;
                                            if(32-ss<0) cout<<"Enter Again"<<endl;
                                        }while(32-ss<0);
                                    }
                                    do{
                                        cout<<"Is the Bus AC ? (0 for No and 1 for Yes): ";
                                        cin>>ac;
                                        if(ac==0||ac==1) break;
                                        else cout<<"Enter Again | Only 0 or 1 "<<endl;
                                    }while(1);
                                    cout<<"Now you need to choose the driver for the Vehicle\nHere is the list of these available: ";
                                    for(i=0;i<transporter[transport]->get_drivers().size();i++){
                                        if(transporter[transport]->get_drivers()[i]->get_has_vehicle()==false){
                                            cout<<*transporter[transport]->get_drivers()[i];
                                        }
                                    }
                                    cout<<"Enter the ID of the driver from the above list: ";
                                    cin>>e;
                                    bool check=false;
                                    for(i=0;i<transporter[transport]->get_drivers().size();i++){
                                        if(transporter[transport]->get_drivers()[i]->get_has_vehicle()==false&&transporter[transport]->get_drivers()[i]->get_id()==e){
                                            check=true;
                                            break;
                                        }
                                    }
                                    if(check==true){
                                        transporter[transport]->add_vehicles(number,ac,ss,d,transporter[transport]->get_drivers()[i]);
                                        transporter[transport]->get_drivers()[i]->add_vehicle(transporter[transport]->get_vehicle()[transporter[transport]->get_vehicle().size()-1]);
                                        cout<<"Vehicle added successfully"<<endl;
                                        cout<<*transporter[transport]->get_vehicle()[transporter[transport]->get_vehicle().size()-1];
                                    }
                                    else cout<<"No ID Found | Vehicle Adding Failed"<<endl;
                                    
                                }
                                else cout<<"Invalid Option"<<endl;
                            }
                            else cout<<"You do not have Drivers | Added them first"<<endl;
                        }
                        //display all vehicles 
                        else if(c==4){
                            if(transporter[transport]->get_vehicle().size()!=0){
                                for(int i=0;i<transporter[transport]->get_vehicle().size();i++){
                                    cout<<*transporter[transport]->get_vehicle()[i]<<endl;
                                }
                            }
                            else cout<<"Empty | Add Vehicles first"<<endl;
                        }
                        // Add routes
                        else if(c==5){
                            string start,end;
                            float distance; 
                            cout<<"Enter the Start Location: ";
                            cin>>start;
                            cout<<"Enter the End Location: ";
                            cin>>end;
                            cout<<"Enter the Distance between them: ";
                            cin>>distance;
                            transporter[transport]->add_route(start,end,distance);
                            cout<<"Route Added Successfully"<<endl;
                            cout<<*transporter[transport]->get_route()[transporter[transport]->get_route().size()-1];
                        }
                        // display all routes
                        else if(c==6){
                            if(transporter[transport]->get_route().size()!=0){
                                for(int i=0;i<transporter[transport]->get_route().size();i++){
                                    cout<<*transporter[transport]->get_route()[i]<<endl;
                                }
                            }
                            else cout<<"Empty | Add Routes first"<<endl;
                        }
                        // add route to a vehicle
                        else if(c==7){
                            if(transporter[transport]->get_vehicle().size()!=0){
                                if(transporter[transport]->get_route().size()!=0){
                                    int id,id2,i,j;
                            bool check=false,check2=false;
                            cout<<"Enter the Vehicle to which the route is to be added: ";
                            cin>>id2;
                            for(j=0;j<transporter[transport]->get_vehicle().size();j++){
                                if(transporter[transport]->get_vehicle()[j]->get_id()==id2){
                                    check2=true;
                                    break;
                                }
                            }
                            if(check2==true){
                                for(i=0;i<transporter[transport]->get_route().size();i++){
                                    cout<<*transporter[transport]->get_route()[i]<<endl;
                                }
                                cout<<"Choose from the above. Enter the ID of the route: ";
                                cin>>id;
                                for(i=0;i<transporter[transport]->get_route().size();i++){
                                    if(transporter[transport]->get_route()[i]->get_id()==id){
                                        check=true;
                                        break;
                                    }
                                }
                                if(check==true){
                                    transporter[transport]->get_vehicle()[j]->add_route(transporter[transport]->get_route()[i]);
                                    cout<<"Route Added Successfully";
                                }
                                else cout<<"No Route of this ID Found"<<endl;
                            }
                            else cout<<"No Vehicle Found"<<endl;
                                }
                                else cout<<"Add Routes First"<<endl;
                            }
                            else cout<<"Add Vehicles First"<<endl;
                        }
                        // display all booking 
                        else if(c==8){
                            if(transporter[transport]->get_booking().size()!=0){
                                for(int i=0;i<transporter[transport]->get_booking().size();i++){
                                    cout<<*transporter[transport]->get_booking()[i]<<endl;
                                }
                            }
                            else cout<<"Empty | Add booking first"<<endl;
                        }
                        else if(c==9) break;
                        else cout<<"Invalid Option"<<endl;
                    }
                }
                else if(b==3) break;
                else cout<<"Invalid Option" <<endl;
            }
        }
        else if(a==3) break;
        else cout<<"Invaid Number"<<endl;
    }
    return 0;
}
