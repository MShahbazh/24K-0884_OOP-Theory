#include<iostream>
using namespace std;

class Bus{
    int id;
    int n;
    string* routes;
    public:

    Bus(){
        this->id=0;
        this->n=0;
        this->routes=nullptr;
    }
    
    Bus(int i){
        int j;
        this->n=i;
        this->id=0;
        routes=new string[i];
        for(j=0;j<i;j++){
            routes[j]="NULL";
        }
    }

    int get_size(){
        return this->n;
    }

    void set_id(int i){
        this->id=i;
    }

    int get_id(){
       return this->id;
    }

    string get_route(int i){
        return this->routes[i];
    }

    void update_route(int i,string route){
        this->routes[i]=route;
    }

    void set_routes(){
        int i;
        for(i=0;i<this->n;i++){
            if(i==n-1){
                cout<<"Last Stop will be: FAST University"<<endl;
                this->routes[i]="FAST University";
            }
            else{
                cout<<"Enter the "<<i+1<<" Stop: ";
                cin>>this->routes[i];
            }
        }
        cout<<"\nRemember: These routes are one way. For Dropoff, same buses will follow same route just opposite"<<endl;
    }

    void view_info(){
        int i;
        cout<<"\nID: "<<this->id<<endl;
        cout<<"Routes: "<<endl;
        for(i=0;i<this->n;i++){
            if(i==n-1){
                cout<<this->routes[n-1]<<endl;
            }
            else{
                cout<<this->routes[i]<<" ---> ";
            }
        }
        cout<<"\nSame but opposite route will be followed in afternoon for dropping off"<<endl;
    }

};

class Student{
    int id;
    string name;
    int age;
    bool fee;
    string pickup;
    string dropoff; 
    bool attendance;
    bool transportation_card;
    Bus bus;
    public:
    Student(){
        this->age=0;
        this->id=0;
        this->fee=false;
        this->name="NULL";
        this->pickup="NULL";
        this->dropoff="NULL";
        this->attendance=false;
        this->transportation_card=false;
        this->bus=Bus();
    }
    Student(string name, int age){
        this->name=name;
        this->age=age;
        this->id=0;
        this->fee=false;
        this->pickup=pickup;
        this->dropoff=dropoff;
        this->attendance=false;
        this->transportation_card=false;
        this->bus=Bus();
    }

    void set_bus(Bus b){
        this->bus=b;
    }

    void update_id(int id){
        this->id=id;
    }

    void update_pickup(string p){
        this->pickup=p;
    }

    void update_dropoff(string d){
        this->dropoff=d;
    }

    void pay_fee(){
        this->fee=true;
        this->transportation_card=true;
    }

    bool get_card(){
        return this->transportation_card;
    }

    bool fee_payed(){
    return this->fee;
    }

    int get_id(){
        return this->id;
    }

    bool get_attendance(){
        return this->attendance;
    }

    void mark_attendance(bool card){
        if(card==true){
            this->attendance=true;
            cout<<"Attendance Marked"<<endl;
        }
        else{
            cout<<"Card not Active Yet"<<endl;
        }
    }

    void view_student(){
        cout<<"\nID: "<<this->id<<endl;
        cout<<"Name: "<<this->name<<endl;
        cout<<"Age: "<<this->age<<endl;
        cout<<"Pickup: "<<this->pickup<<endl;
        cout<<"Drop off: "<<this->dropoff<<endl;
        if(this->fee==true){
            cout<<"Fee Paid: Yes"<<endl;
        }
        else{
            cout<<"Fee Paid: No"<<endl;
        }
        if(this->transportation_card==true){
            cout<<"Card Active: Yes"<<endl;
        }
        else{
            cout<<"Card Active: No"<<endl;
        }
        if(this->attendance==true){
            cout<<"Attendance: Yes"<<endl;
        }
        else{
            cout<<"Attendance: No"<<endl;
        }
        cout<<"Bus Info: "<<endl;
        if(this->bus.get_id()==0){
            cout<<"Not Registered Yet"<<endl;
        }
        else{
            this->bus.view_info();
        }
    }
};

int main(){
    int s,i,n,b;
    cout<<"Enter the number of Students the system will handle: ";
    cin>>s;
    cout<<"Enter the number of buses the university operates: ";
    cin>>b;
    Student* student=new Student[s];
    Bus* buses=new Bus[b];
    for(i=0;i<s;i++){
        student[i]=Student();
    }
    for(i=0;i<b;i++){
        buses[i]=Bus();
    }
    do{
        cout<<"\n1. Register Student\n2. Display Students\n3. Add a Bus\n4. View all buses\n5. Register for a Bus\n6. Pay Fee\n7. Mark Attendance\n8. Exit\nEnter the Corresponding number: ";
        cin>>n;
        if(n==1){
            int age;
            string name;
            bool check=false;
            for(i=0;i<s;i++){
                if(student[i].get_id()==0){
                    check=true;
                    break;
                }
            }
            if(check==false){
                cout<<"\nSorry Maximum Space Reached | Cannot Register"<<endl;
            }
            else{
                cout<<"\n--- Student "<<i+1<<" Info ---"<<endl;
                cout<<"User ID is System Generated"<<endl;
                cout<<"Enter the name: ";
                cin>>name;
                cout<<"Enter the age: ";
                cin>>age;
                student[i]=Student(name,age);
                if(i==0){
                    student[i].update_id(1000);
                }
                else{
                    student[i].update_id((i+1)*1000);
                }
                cout<<"Student Registered in the system| Remember the Student need to choose the routes separately"<<endl;
                cout<<"\nRegistered Student Info"<<endl;
                student[i].view_student();
            }
        }
        else if(n==2){
            bool check=false;
            for(i=0;i<s;i++){
                if(student[i].get_id()!=0){
                    check=true;
                }
            }
            if(check==false){
                cout<<"\nList Empty"<<endl;
            }
            else if(check==true){
                cout<<"\n--- Users Info ---"<<endl;
                for(i=0;i<s;i++){
                    if(student[i].get_id()!=0){
                        student[i].view_student();
                    }
                }
            }
        }
        else if(n==3){
        int n,i;
        bool check=false;
        for(i=0;i<b;i++){
            if(buses[i].get_id()==0){
                    check=true;
                    break;
                }
            }
            if(check==false){
                cout<<"\nSorry Max Space Reached"<<endl;
            }
            else{
                cout<<"Enter the Number of routes the bus will have Including the Uni: ";
                cin>>n;
                buses[i]=Bus(n);
                if(i==0){
                    buses[i].set_id(1);
                }
                else{
                    buses[i].set_id(buses[i-1].get_id()+1);
                }
                buses[i].set_routes();
                cout<<"\nBus Info: "<<endl;
                buses[i].view_info();
            }
        }
        else if(n==4){
            bool check=false;
            for(i=0;i<b;i++){
                if(buses[i].get_id()!=0){
                    check=true;
                }
            }
            if(check==false){
                cout<<"\nList Empty"<<endl;
            }
            else{
                cout<<"\n--- Bus Info ---"<<endl;
                for(i=0;i<b;i++){
                    if(buses[i].get_id()!=0){
                        buses[i].view_info();
                    }
                }
            }
        }
        else if(n==5){
            int n,i,j,k,z;
            bool check=false,check2=false;
            string p1,p2;
            cout<<"Enter the Student ID: ";
            cin>>n;
            for(i=0;i<s;i++){
                if(student[i].get_id()==n){
                    check=true;
                    if(student[i].get_card()==false && student[i].fee_payed()==false){
                        cout<<"\nYour Transportation is not active. First Pay the Semester Fee to active the card and then you will be eligible to register for the courses"<<endl;
                    }
                    else{
                        int arr[b];
                        cout<<"Enter your Pick up point: ";
                        cin>>p1;
                        cout<<"Enter the Dropoff point: ";
                        cin>>p2;
                        student[i].update_pickup(p1);
                        student[i].update_dropoff(p2);
                        for(j=0;j<b;j++){
                            arr[j]=-1;
                        }
                        for(j=0,z=0;j<b;j++){
                            bool pick=false;
                            bool drop=false;
                            for(k=0;k<buses[j].get_size();k++){
                                if(buses[j].get_route(k)==p1){
                                    pick=true;
                                }
                                if(buses[j].get_route(k)==p2){
                                    drop=true;
                                }
                            }
                            if(pick==true && drop==true){
                                arr[z]=i;
                                z++;   
                            }
                        }
                        if(arr[0]!=-1){
                            cout<<"\n--- Suitable Buses ---"<<endl;
                            for(j=0;arr[j]!=-1;j++){
                                buses[arr[j]].view_info();
                            }
                        }
                        cout<<"\nEnter the ID of the bus: ";
                        cin>>n;
                        for(j=0;arr[j]!=-1;j++){
                            if(buses[arr[j]].get_id()==n){
                                student[i].set_bus(buses[arr[j]]);
                                check2=true;
                            }
                        }
                        if(check2==false){
                            cout<<"\nEnter the Correct ID"<<endl;
                        }
                    }
                }
            }
            if(check==false){
                cout<<"\nSorry this id doesn't exist"<<endl;
            }
        }
        else if(n==6){
            int n,i;
            bool check=false;
            cout<<"Enter the Student ID: ";
            cin>>n;
            for(i=0;i<s;i++){
                if(student[i].get_id()==n){
                    check=true;
                    if(student[i].get_card()==false){
                        student[i].pay_fee();
                        cout<<"Fee Payed | Card Activated"<<endl;
                    }
                    else{
                        cout<<"Fee Already Paid"<<endl;
                    }
                }
            }
            if(check==false){
                cout<<"Student with such ID does not Exist"<<endl;
            }
        }
        else if(n==7){
            int n,i;
            bool check=false;
            cout<<"Enter the Student ID: ";
            cin>>n;
            for(i=0;i<s;i++){
                if(student[i].get_id()==n){
                    check=true;
                   if(student[i].get_attendance()==false){
                    student[i].mark_attendance(student[i].get_card());
                   }
                }
            }
            if(check==false){
                cout<<"Student with such ID does not Exist"<<endl;
            }
        }
        else if(n==8){
            break;
            }
    }while(1);
}