/* 
Name: Muhammad Shahbaz Hassan
Roll Number: 24K-0884
Class: BCS_2C
*/

#include<iostream>
#include<string>
using namespace std;

class Ghost;
class HauntedHouse;
class Visitor;

class Ghost{    
    string name;
    int level;
    public:
    Ghost(){}
    Ghost(string a, int b):name(a){
        if(b>=0&&b<=10){
            level=b;
        }
        else {
            cout<<"Enter the Level in the valid range 0-10\nIn this Case the Scare level of the ghost will be considered as 5"<<endl;
            level=5;
        }
    }
    virtual void Haunting(){}
    Ghost operator + (const Ghost& g){
        return Ghost(this->name+g.name,this->level+g.level);
    }
    string get_name(){
        return name;
    }
    int get_level(){
        return level;
    }
    friend ostream& operator << (ostream& out,const Ghost& g);
};

class Poltergeists: virtual public Ghost{
    public:
    Poltergeists(){}
    Poltergeists(string a, int b):Ghost(a,b){}
    void Haunting() override{
        cout<<"Move Objects"<<endl;
    }
};

class Banshees: public Ghost{
    public:
    Banshees(){}
    Banshees(string a, int b):Ghost(a,b){}
    void Haunting() override{
        cout<<"Scream Loudly"<<endl;
    }
};

class ShadowGhosts: virtual public Ghost{
    public:
    ShadowGhosts(){}
    ShadowGhosts(string a, int b):Ghost(a,b){}
    void Haunting() override{
        cout<<"Whisper Creeply"<<endl;
    }
};

class ShadowPoltergeist:public Poltergeists, public ShadowGhosts{
    public:
    ShadowPoltergeist(){}
    ShadowPoltergeist(string a, int b):Poltergeists(a,b),ShadowGhosts(a,b){}
    void Haunting(){
        Poltergeists::Haunting();
        ShadowGhosts::Haunting();
    }
};


class HauntedHouse{
    Ghost** ghosts;
    int size;
    public:
    HauntedHouse(){}
    HauntedHouse(int n):size(n){
        ghosts=new Ghost*[size];
    }
    void add_ghosts(){
        int a,b;
        string name;
        cout<<"--- Ghosts Information ---"<<endl;
        for(int i=0;i<size;i++){
            cout<<"\nGhost number: "<<i+1<<endl;
            cout<<"Enter the name of the Ghost: ";
            cin>>name;
            while(1){
                cout<<"Enter the scare Level of the ghost: ";
                cin>>b;
                if(b>=1&&b<=10) break;
                else{
                    cout<<"Scare Level must be between 1 and 10 inclusive"<<endl;
                }
            }
            while(1){
                cout<<"1. Poltergeists\n2. Banshees\n3. Shadow Ghosts\n4. ShadowPoltergeist"<<endl;
                cout<<"Enter the corresponding number: ";
                cin>>a;
                if(a==1){
                     ghosts[i]=new Poltergeists(name,b);
                     break;
                }
                else if(a==2){
                     ghosts[i]=new Banshees(name,b);
                     break;
                }
                else if(a==3){
                     ghosts[i]=new ShadowGhosts(name,b);
                     break;
                }
                else if(a==4){
                     ghosts[i]= new ShadowPoltergeist(name,b);
                     break;
                }
                else cout<<"Enter the Valid ghost type"<<endl;
            }
        }
    }
    void display_ghosts(){
        cout<<"Ghosts Information: "<<endl;
        for(int i=0;i<size;i++){
            cout<<"Ghost Name: "<<ghosts[i]->get_name()<<endl;
            cout<<"Ghost Scare level: "<<ghosts[i]->get_level()<<endl;
        }
    }
    int get_size(){
        return size;
    }
    friend void Visit(HauntedHouse& h, Visitor v[], int size);
};

class Visitor{
    string name;
    int bravery;
    public:
    Visitor(){}
    Visitor(string a, int b):name(a),bravery(b){}
    friend void Visit(HauntedHouse& h, Visitor v[], int size);
};


ostream& operator << (ostream& out, Ghost& g){
    out<<"Ghost Name: "<<g.get_name()<<endl;
    out<<"Ghost Level: "<<g.get_level()<<endl;
    return out;
}


void Visit(HauntedHouse& h, Visitor v[], int size) {
    int x,y;
    for(int i=0;i<size;i++){
        if(v[i].bravery>=1&&v[i].bravery<=4){
            x=1;
            y=4;
        }
        else if(v[i].bravery>=5 && v[i].bravery<=7 ){
            x=5;
            y=7;
        }
        else if(v[i].bravery>=8&& v[i].bravery<=10){
            x=8;
            y=10;
        }
        for(int j=0;j<h.size;j++){
            h.ghosts[j]->Haunting();
            if(h.ghosts[j]->get_level()<x){
                cout<<"\nVisitor "<<v[i].name<<" laughs at the Ghost "<<h.ghosts[j]->get_name()<<endl;
            }
            else if(h.ghosts[j]->get_level()>=x&&h.ghosts[j]->get_level()<=y){
                cout<<"\nVisitor "<<v[i].name<<" have a shaky voice but stays"<<endl;
            }
            else{
                cout<<"\nVisitor "<<v[i].name<<" screamed and Ran away"<<endl;
            }
        }
    }
}


int main(){
    Ghost* g1=new Poltergeists("Jake",1);
    Ghost* g2=new Banshees("John",2);
    Ghost g3 = *g1+*g2;
    cout<<g3;

    Visitor* visitor=new Visitor[5];
    visitor[0]=Visitor("Jake",4);
    visitor[1]=Visitor("Jim",9);
    visitor[2]=Visitor("John",1);
    visitor[3]=Visitor("Kim",3);
    visitor[4]=Visitor("Tim",10);


    HauntedHouse h1(5);
    h1.add_ghosts();
    h1.display_ghosts();

    
    Visit(h1,visitor,5);

}