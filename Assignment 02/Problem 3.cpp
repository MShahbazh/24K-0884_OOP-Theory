/* 
Name: Muhammad Shahbaz Hassan
Roll Number: 24K-0884
Class: BCS_2C
*/

#include<iostream>
using namespace std;

class Vehicle{
    int id;
    static int total;
    int speed;
    int capacity;
    int energyEfficiency;
    public:
    Vehicle(){}
    Vehicle(int x,int y, int z, int i):id(x),speed(y),capacity(z),energyEfficiency(i){}
    virtual void calculateRoute(string s){}
    virtual void command(string a,int b ){
        cout<<"Package "<<a<<" with package id "<<b<<" will be delivered"<<endl;
    }
    virtual void command(string a,int b , string c){
        cout<<"Package "<<a<<" with package id "<<b<<" and urgency level "<<c<<" will be delivered"<<endl;
        total++;
    }
    
    bool operator==(const Vehicle& v){
        if(v.speed==this->speed&&v.energyEfficiency==this->energyEfficiency&&v.capacity==this->capacity) return true;
        else return false;
    }
    int get_id(){
        return id;
    }
    int get_total(){
        return total;
    }
    int get_speed(){
        return speed;
    }
    int get_efficiency(){
        return energyEfficiency;
    }
    int get_capacity(){
        return capacity;
    }
    void add_total(){
        total++;
    }
    
    friend ostream& operator << (ostream& out,const Vehicle& v);
    friend Vehicle compareEfficieny(Vehicle& v1, Vehicle& v2);
};

int Vehicle::total=0;

class RamzanDrone: public Vehicle{
    public:
    RamzanDrone(){}
    RamzanDrone(int x,int y, int z, int i):Vehicle(x,y,z,i){}
    void calculateRoute(string s){
        cout<<"Calculating Aerial Route to "<<s<<endl;
    }
    void command(string a, int b, string c) override {
        if(c=="urgent"){
            cout<<"Activating High Speed for the package delivery"<<endl;
            this->add_total();
        }
        else{
            Vehicle::command(a,b,c);
        }
    }
};

class RamzanTimeShip: public Vehicle{
    public:
    RamzanTimeShip(){}
    RamzanTimeShip(int x,int y, int z, int i):Vehicle(x,y,z,i){}
    void calculateRoute(string s){
        cout<<"Verfying Date... "<<s<<endl;
        cout<<"Date Verified. Now the Time ship can deliver"<<endl;
    }
    void command(string a, int b, string c){
        if(c=="urgent"){
            cout<<"Confirming Historical Accuracy before moving"<<endl;
            this->add_total();
        }
        else{
            Vehicle::command(a,b,c);
        }
    }
};

class RamzanHyperPod: public Vehicle{
    public:
    RamzanHyperPod(){}
    RamzanHyperPod(int x,int y, int z, int i):Vehicle(x,y,z,i){}
    void calculateRoute(string s){
        cout<<"Navigating an Underground Route to "<<s<<endl;
    }
};

Vehicle compareEfficieny(Vehicle& v1, Vehicle& v2){
    Vehicle temp(-1,-1,-1,-1);
    if(v1==v2){
        return temp;
    }
    else{
        if(v1.energyEfficiency>v2.energyEfficiency) return v1;
        else return v2;
    }
}

ostream& operator << (ostream& out, Vehicle& v){
    out<<"Vehicle id: "<<v.get_id()<<endl;
    out<<"Vehicle Speed: "<<v.get_speed()<<endl;
    out<<"Vehicle Capacity: "<<v.get_capacity()<<endl;
    out<<"Vehicle Efficiency: "<<v.get_efficiency()<<endl;
    out<<"Packages: "<<v.get_total()<<endl;

    return out;
}


int main(){
    Vehicle** vehicle = new Vehicle*[3];
    vehicle[0]=new RamzanDrone(1,200,45,400);
    vehicle[1]=new RamzanTimeShip(1,200,45,400);
    vehicle[2]=new RamzanHyperPod(1,100,30,400);

    vehicle[0]->calculateRoute("Dubai");
    vehicle[0]->command("Dubai",101,"urgent");
    
    vehicle[1]->calculateRoute("London");
    vehicle[1]->command("London",102,"urgent");

    vehicle[2]->calculateRoute("Berlin");

    if(*vehicle[0]==*vehicle[1]){
        cout<<"Vehicle 0 and Vehicle 1 are same"<<endl;
    }

    Vehicle v3=compareEfficieny(*vehicle[0],*vehicle[2]);
    cout<<v3;

}