#include<iostream>
using namespace std;


class Vehicle{
    int ID;
    string model;
    float rental_Price;
    string eligibility;
    bool availibility;
    public:
    Vehicle(){
        this->ID=0;
        this->model="NULL";
        this->rental_Price=0.0;
        this->eligibility="NULL";
        this->availibility=true;
    }
    Vehicle(string a, int b, string c, int d){
        this->model=a;
        this->rental_Price=b;
        this->eligibility=c;
        this->ID=d;
        this->availibility=true;
    }

    void update_model(string a){
        this->model=a;
    }

    void update_rental(float a){
        this->rental_Price=a;
    }

    void update_eligiblity(string c){
        this->eligibility=c;
    }
    
    int get_carID(){
        return this->ID;
    }

    string get_model(){
        return this->model;
    }

    int get_price(){
        return this->rental_Price;
    }

    bool get_availibility(){
        return this->availibility;
    }

    string get_license(){
        return this->eligibility;
    }

    void update_availibility(int a){
        if(a==0) this->availibility=false;
        else this->availibility=true;
    }

    void update_ID(int ID){
        this->ID=ID;
    }
    
    void view_Vehicle(){
        cout<<"\nVehicle ID: "<<this->get_carID()<<endl;
        cout<<"Model: "<<this->get_model()<<endl;
        cout<<"Rental Price per day: "<<this->get_price()<<endl;
        cout<<"License Eligibility: "<<this->get_license()<<endl;
        if(this->get_availibility()==true){
            cout<<"Availibility Status: Available"<<endl;
        }
        else{
            cout<<"Availibility Status: Not Available"<<endl;
        }
    }

};  

class Users{
    int user_ID;
    int age;
    string license_Type;
    int contact_Info;
    Vehicle* v;
    public:
    Users(){
        this->user_ID=0;
        this->age=0;
        this->license_Type="NULL";
        this->contact_Info=0;
        this->v=nullptr;
    }
    Users(int a, string b, int c){
        this->age=a;
        this->license_Type=b;
        this->contact_Info=c;
    }
    
    void update_ID(int ID){
        this->user_ID=ID;
    }

    void update_age(int a){
        this->age=a;
    }

    void update_license(string b){
        this->license_Type=b;
    }

    void update_contact(int c){
        this->contact_Info=c;
    }

    int get_userID(){
        return this->user_ID;
    }

    string get_license(){
        return this->license_Type;
    }

    int get_age(){
        return this->age;
    }

    int get_info(){
        return this->contact_Info;
    }

    void rent_Vehicle(Vehicle& b){
        if(b.get_availibility()==1){
            bool available=false;
            if(this->get_license()==b.get_license()&&this->get_license()=="Learner"){
                available=true;
            }
            else if(this->get_license()=="Intermediate" && (b.get_license()=="Intermediate" || b.get_license()=="Learner")){
                available=true;
            }
            else if(this->get_license()=="Full"){
                available=true;
            }
            else{
                cout<<"\nYour License is the problem"<<endl;
                available=false;
            }
            if(available==true){
                v=&b;
                cout<<"\nYour License type matched so you got the Car"<<endl;
                b.update_availibility(false);
                v->update_availibility(false);
            }
        }
        else{
            cout<<"\nVehicle is not available right now"<<endl;
        }
    }

    void view_Rented(){
            if(this->v==nullptr){
                cout<<"No Vehicle Rented Yet"<<endl;
            }
            else{
                this->v->view_Vehicle();
            }
    }

    bool view_suitablecars(Vehicle* b){
        if(b->get_availibility()==true){
            if(this->get_license()=="Learner"&&b->get_license()=="Learner"){
                return true;
                }
                else if(this->get_license()=="Intermediate"&&(b->get_license()=="Learner"||b->get_license()=="Intermediate")){
                    return true;
                }
                else if(this->get_license()=="Full"){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
            return false;
        }

    }

    void view_User(){
        cout<<"\nUser ID: "<<this->get_userID()<<endl;
        cout<<"User Age: "<<this->get_age()<<endl;
        cout<<"License Type: "<<this->get_license()<<endl;
        cout<<"Contact Info: "<<this->get_info()<<endl;
        if(this->v==nullptr){
            cout<<"No Vehicle Rented Yet"<<endl;
        }
        else{
            cout<<"Vehicle Rented: "<<endl;
            this->view_Rented();
        }
    }
};

int main(){
    int s,v,i,n,j;
    cout<<"Enter the number of Max Students the system will manage: ";
    cin>>s;
    cout<<"Enter the number of Max Vehicles the System will manage: ";
    cin>>v;
    Users* user=new Users[s];
    Vehicle** vehicles=new Vehicle*[v];
    for(i=0;i<s;i++){
        user[i]=Users();
    }
    for(i=0;i<v;i++){
        vehicles[i]=new Vehicle();
    }
    do{
        cout<<"\n1. Register a User\n2. Add a Vehicle\n3. Display Users\n4. Display all Vehicles\n5. Rent a Vehicle\n6. Update User Info\n7. Exit\nEnter the Corresponding Number: ";
        cin>>n;
        if(n==1){
            int age,info;
            string type;
            bool check=false;
            bool suitable=true;
            cout<<"\n--- User Registration ---"<<endl;
            for(i=0;i<s;i++){
                if(user[i].get_userID()==0){
                    check=true;
                }
            }            
            if(check==false){
                cout<<"\nSorry Max Space Reached No user can be registered"<<endl;
            }
            else{
                cout<<"--- User ID will be pre Assigned by the system ---"<<endl;
                cout<<"Enter the User age: ";
                cin>>age;
                do{
                    cout<<"Enter the User License Type: ";
                    cin>>type;
                    if(type=="Learner"||type=="Intermediate"||type=="Full"){
                        break;
                    }
                    else{
                        cout<<"\nLicense can only be Learner, Intermediate, Full"<<endl;
                    }
                }while(1);
                cout<<"Enter the User's Contact Info: ";
                cin>>info;
                for(i=0;i<s;i++){
                    if(user[i].get_userID()==0){
                        user[i]=Users(age,type,info);
                        if(i==0){
                            user[i].update_ID(1000);
                        }
                        else{
                            user[i].update_ID(user[i-1].get_userID()+1000);
                        }
                        break;
                    }
                }
                cout<<"Want to Rent a Car Now(Y or N)?[Note: You can also do it later]: ";
                cin>>type;
                if(type=="Y"){
                    for(j=0;j<v;j++){
                        if(vehicles[j]->get_carID()!=0){
                            suitable=false;
                        }
                    }
                    if(suitable==false){
                        int k=0;
                       for(j=0;j<v;j++){
                           if(user[i].view_suitablecars(vehicles[j])==1){
                            k++;
                        }
                       }
                       if(k==0){
                           cout<<"\nSorry No vehicle of your type available right now"<<endl;
                       }
                       else{
                           cout<<"\nThe Suitable Cars according to your license type are:  ";
                            for(j=0;j<v;j++){
                                if(user[i].view_suitablecars(vehicles[j])==true){
                                    vehicles[j]->view_Vehicle();
                                }
                            }
                       }
                    }
                    else{
                        cout<<"\nVehicles List Empty | No Data Entered Yet"<<endl;
                    }
                }
                cout<<"\nUser Registered. Here is the Registered Info"<<endl;
                user[i].view_User();
            }
        }
        else if(n==2){
            int id,price;
            string model,eligible;
            bool check=false;
            cout<<"\n--- Vehicle Registration ---"<<endl;
            for(i=0;i<v;i++){
                if(vehicles[i]->get_carID()==0){
                    check=true;
                }
            }
            if(check==false){
                cout<<"\nSorry Max Space Reached | No Vehicle can be added"<<endl;
            }
            else{
                cout<<"Enter the Vehicle model: ";
                cin>>model;
                cout<<"Enter the Rental Price of Vehicle per day: ";
                cin>>price;
                do{
                    cout<<"Enter the License Type: ";
                    cin>>eligible;
                    if(eligible=="Learner"||eligible=="Intermediate"||eligible=="Full"){
                        break;
                    }
                    else{
                        cout<<"\nLicense can only be Learner, Intermediate, Full"<<endl;
                    }
                }while(1);
                for(i=0;i<v;i++){
                    if(vehicles[i]->get_carID()==0){
                        if(i==0){
                            vehicles[i]->update_ID(1000);
                        }
                        else{
                            vehicles[i]->update_ID(vehicles[i-1]->get_carID()+1000);
                        }
                        *vehicles[i]=Vehicle(model,price,eligible,vehicles[i]->get_carID());
                        break;
                    }
                }
                cout<<"\nVehicle Registered Successfully\nHere is the Info of the registered Vehicle "<<endl;
                vehicles[i]->view_Vehicle();
            }
        }
        else if(n==3){
            bool present=false;
            for(i=0;i<s;i++){
                if(user[i].get_userID()!=0){
                    present=true;
                    break;
                }
            }
            if(present==true){
                cout<<"\n--- Users Data ---"<<endl;
                for(i=0;user[i].get_userID()!=0&&i<s;i++){
                    user[i].view_User();
                }
            }
            else{
                cout<<"\nList Empty"<<endl;
            }
            
        }
        else if(n==4){
            bool present=false;
            for(i=0;i<v;i++){
                if(vehicles[i]->get_carID()!=0){
                    present=true;
                    break;
                }
            }
            if(present==true){
                cout<<"\n--- Vehicles Data ---"<<endl;
                for(i=0;i<v;i++){
                    if(vehicles[i]->get_carID()!=0){
                        vehicles[i]->view_Vehicle();
                    }
                }
            }
            else{
                cout<<"\nList Empty"<<endl;
            }
        }
        else if(n==5){
            int id,age,info;
            string type;
            bool exist=false;
            cout<<"\n--- Login User ---"<<endl;
            cout<<"Enter the User ID: ";
            cin>>id;
            for(i=0;i<s;i++){
                if(user[i].get_userID()==id){
                    exist=true;
                    break;
                }
            }
            if(exist==false){
                cout<<"No User of this id exist"<<endl;
            }
            else{
                bool suitable=true;
                for(j=0;j<v;j++){
                    if(vehicles[j]->get_carID()!=0){
                        suitable=false;
                    }
                }
                if(suitable==false){
                    int k=0;
    
                   for(j=0;j<v;j++){
                       if(user[i].view_suitablecars(vehicles[j])==true){
                        k++;
                    }
                   }
                   if(k==0){
                       cout<<"\nSorry No vehicle of your type available right now"<<endl;
                   }
                   else{
                       cout<<"\nThe Suitable Cars according to your license type are:  ";
                        for(j=0;j<v;j++){
                            if(user[i].view_suitablecars(vehicles[j])==1){
                                vehicles[j]->view_Vehicle();
                            }
                        }
                        cout<<"\nEnter the ID of Vehicle you want to rent: ";
                        cin>>id;
                        bool present=false;
                        for(j=0;j<v;j++){
                            if(vehicles[j]->get_carID()==id){
                                present=true;
                                break;
                            }
                        }
                        if(present==true){
                            user[i].rent_Vehicle(*vehicles[j]);
                            
                        }
                        else{
                            cout<<"\nSorry this type of vehicle is not in our system"<<endl;
                        }
                   }
                }
                else{
                    cout<<"\nVehicles List Empty | No Data Entered Yet"<<endl;
                }
            }
        }
        else if(n==6){
            int i,j,a,b,c;
            string l;
            bool empty=false;
            for(i=0;i<s;i++){
                if(user[i].get_userID()!=-1){
                    empty=true;
                    break;
                }
            }
            if(empty==false){
                cout<<"\nUser List Empty | Register Users First"<<endl;
            }
            else{
                cout<<"\nEnter the ID of the User whose data you want to update: ";
                cin>>a;
                bool check=false;
                for(i=0;i<s;i++){
                    if(user[i].get_userID()==a){
                        check=true;
                        cout<<"\n --- User "<<user[i].get_userID()<<" Info Update ---"<<endl;
                        do{
                            cout<<"\n1. User Age\n2. License Type\n3. Contact Info\n4. All\n5. Exit\nEnter the corresponding Number: ";
                            cin>>b;
                            if(b==1){
                                cout<<"\nEnter the User new age: ";
                                cin>>c;
                                user[i].update_age(c);
                                cout<<"\nUpdated User Info: "<<endl;
                                user[i].view_User();
                            }
                            else if(b==2){
                                cout<<"\nEnter the new License Type: ";
                                cin>>l;
                                user[i].update_license(l);
                                cout<<"\nUpdated User Info: "<<endl;
                                user[i].view_User();
                            }
                            else if(b==3){
                                cout<<"\nEnter the new Contact Info: ";
                                cin>>c;
                                user[i].update_contact(c);
                                cout<<"\nUpdated User Info: "<<endl;
                                user[i].view_User();
                            }
                            else if(b==4){
                                cout<<"\nEnter the User new age: ";
                                cin>>c;
                                user[i].update_age(c);
                                cout<<"\nEnter the new License Type: ";
                                cin>>l;                                
                                user[i].update_license(l);
                                cout<<"\nEnter the new Contact Info: ";
                                cin>>c;
                                user[i].update_contact(c);
                                cout<<"\nUpdated User Info: "<<endl;
                                user[i].view_User();
                            }
                            else if(b==5){
                                break;
                            }
                        }while(1);
                    }
                }
                if(check==false){
                    cout<<"\nWrong ID Entered"<<endl;
                }
            }
        }
        else if(n==7){
            break;
        }
        else{
            cout<<"\nEnter a Valid Option"<<endl;
        }
    }while(1);
};