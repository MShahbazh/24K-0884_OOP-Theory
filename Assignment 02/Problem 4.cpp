/* 
Name: Muhammad Shahbaz Hassan
Roll Number: 24K-0884
Class: BCS_2C
*/

#include<iostream>
#include<vector>
using namespace std;

class User;
bool authenticateAndPerformAction(User* user, string action);

long long generate_hashes(string a){
    long long hash=5381;
    for(int i=0;i<a.size();i++){
        hash=hash*33+a[i];
    }
    return hash;
}

class User{
    string name;
    int id;
    vector<string> permissions;
    string email;
    long long hashed_password;
    public:
    User(){}
    User(int d, string a, string b,string c):id(d),name(a),email(b){
        this->hashed_password=generate_hashes(c);
    }
    void add_permissions(string a){
        permissions.push_back(a);
    }
    int get_id(){
        return id;
    }
    string get_name(){
        return name;
    }
    string get_email(){
        return email;
    }
    long long get_hash(){
        return hashed_password;
    }
    vector<string> get_permission(){
        return permissions;
    }
    string get_permission_index(int i){
        return permissions[i];
    }
    void authenticate(string a){
        if(generate_hashes(a)==this->hashed_password){
            cout<<"Correct Password.\nAuthentication Provided"<<endl;
        }
        else{
            cout<<"Incorrect Password"<<endl;
        }
    }

    virtual void Display(){
        cout<<"User Id: "<<id<<endl;
        cout<<"User name: "<<name<<endl;
        cout<<"Email: "<<email<<endl;
        cout<<"Hashed Password: "<<hashed_password<<endl;
        if(permissions.size()==0) cout<<"No Permissions have been given to this User"<<endl;
        else{
            cout<<"List of Permissions: "<<endl;
            for(int i=0;i<permissions.size();i++){
                cout<<"  "<<permissions[i]<<endl;
            }    
        }
    }
    void access_lab(){
        if( authenticateAndPerformAction(this,"Lab Access")==true) cout<<"Lab Access Granted"<<endl;
        else cout<<"Lab Access not granted"<<endl;
    }
    virtual void give_assignment(){}
    virtual void submit_assignment(){}
    
};

bool authenticateAndPerformAction(User* user, string action){
    bool check=false;
    vector<string> permission=user->get_permission();
    for(int i=0;i<permission.size();i++){
        if(permission[i]==action){
            check=true;
            break;
        }
    }
    if(check==false) return false;
    else return true;
}

class Student:public User{
    vector<bool> assignments;
    public:
    Student(){};
    Student(int d,string a, string b, string c):User(d,a,b,c){};
    void Display() override{
        cout<<"\nStudent Id: "<<this->get_id()<<endl;
        cout<<"Student name: "<<this->get_name()<<endl;
        cout<<"Email: "<<this->get_email()<<endl;
        cout<<"Hashed Password: "<<this->get_hash()<<endl;
        if(this->get_permission().size()==0) cout<<"No Permissions have been given to this User"<<endl;
        else{
            cout<<"List of Permissions: "<<endl;
            for(int i=0;i<this->get_permission().size();i++){
                cout<<"  "<<this->get_permission_index(i)<<endl;
            }    
        }
        if(assignments.size()==0) cout<<"No Assignments Provided Yet"<<endl;
        else{
            cout<<"Assignments Submitted: "<<endl;
            for(int i=0;i<assignments.size();i++){
                cout<<"  Assignment "<<i+1<<": "<<assignments[i]<<endl;
            }  
        }
    }
    void give_assignment() override{
        assignments.push_back(false);
    }
    void submit_assignment(){
        int j;
        bool check=false;
        if(assignments.size()==0){
            cout<<"No Assignment have been Provided Yet"<<endl;
        }
        else{
            cout<<"Enter the Sequence Number of Assignment: ";
            cin>>j;
            
            for(int i=0;i<assignments.size();i++){
                if(j==i+1){
                    cout<<"Assignment Submitted"<<endl;
                    assignments[i]=true;
                    check=true;
                    break;
                }
            }
        }
        if(check==false) cout<<"No Assignment of this Index Exist"<<endl;
    }
};

class TA: public Student{
    vector<Student> assigned_student;
    vector<string> projects;
    public:
    TA(){}
    TA(int d,string a, string b, string c):Student(d,a,b,c){}
    void Display() override{
        cout<<"\nTA Id: "<<this->get_id()<<endl;
        cout<<"TA name: "<<this->get_name()<<endl;
        cout<<"Email: "<<this->get_email()<<endl;
        cout<<"Hashed Password: "<<this->get_hash()<<endl;
        if(this->get_permission().size()==0) cout<<"No Permissions have been given to this User"<<endl;
        else{
            cout<<"List of Permissions: "<<endl;
            for(int i=0;i<this->get_permission().size();i++){
                cout<<"  "<<this->get_permission_index(i)<<endl;
            }    
        }

        if(assigned_student.size()==0) cout<<"No Students have been Assigned yet"<<endl;
        else{
            cout<<"Assigned Students: "<<endl;
            for(int i=0;i<assigned_student.size();i++){
                cout<<assigned_student[i].get_name()<<endl;
            }  
        }
    }

    void assign_Student(Student& s){
        bool check=false;
        if(this->get_permission().size()>=10) cout<<"Limit Reached!\nNot more than 10 Students can be Assigned"<<endl;
        else{
            if(authenticateAndPerformAction(this,"Assigning")==true){
                assigned_student.push_back(s);
                cout<<"Student Added"<<endl;
            }
            else cout<<"You have not the permission to Assign the Student"<<endl;
        }
    }
    void view_projects(){
        if(projects.size()==0) cout<<"Project List Empty";
        else{
            for(int i=0;i<projects.size();i++){
                cout<<"Project "<<i+1<<": "<<projects[i]<<endl;
            }
        }
    }
    void new_project(string s){
        if(projects.size()>=2) cout<<"Limit Reached"<<endl;
        else{
            projects.push_back(s);
            cout<<"Project Added"<<endl;
        }
    }
    int get_projects_no(){return projects.size();}
    // string get_name(){return name;}
};

class Professor: public User{
    public:
    Professor(){}
    Professor(int d, string a, string b, string c):User(d,a,b,c){}
    virtual void Display(){
        cout<<"\nProfessor Id: "<<this->get_id()<<endl;
        cout<<"Professor name: "<<this->get_name()<<endl;
        cout<<"Email: "<<this->get_email()<<endl;
        cout<<"Hashed Password: "<<this->get_hash()<<endl;
        if(this->get_permission().size()==0) cout<<"No Permissions have been given to this User"<<endl;
        else{
            cout<<"List of Permissions: "<<endl;
            for(int i=0;i<this->get_permission().size();i++){
                cout<<"  "<<this->get_permission_index(i)<<endl;
            }    
        }
    }
    void assign_TA(TA& a, string b){
        if(authenticateAndPerformAction(this,"Assigning TA")==true){
            if(a.get_projects_no()>=2) cout<<"TA Cannot be assigned to this Project, Max limit reached"<<endl;
            else{
                a.new_project(b);
                cout<<"Professor "<<this->get_name()<<" Assigned this "<<b<<" to "<<a.get_name()<<endl;
            }
        }
        else{
            cout<<"Professor does not have permission to Assign Projects to TA"<<endl;
        }
    }
};

int main(){
    Student* users=new Student[4];
    users[0]=Student(101,"Ali","Ali@gmail.com","AliPass");
    users[1]=Student(102,"Ahmed","Ahmed@gmail.com","AhmedPass");
    users[2]=Student(103,"Akbar","Akbar@gmail.com","AkbarPass");
    users[3]=Student(104,"Jake","Jake@gmail.com","JakePass");

    for(int i=0;i<4;i++){
        for(int j=0;j<3;j++){
            users[i].give_assignment();
        }
    }

    // users[0].submit_assignment();

    for(int i=0;i<4;i++){
        users[i].Display();
    }

    TA* ta1=new TA(201,"John","John@gmail.com","JohnPass");
    ta1->add_permissions("Assigning");
    ta1->assign_Student(users[0]);
    ta1->new_project("Project 1 CS");
    
    Professor* p1=new Professor(301,"Dr Adil","Adil@gmail.com","AdilPass");
    p1->add_permissions("Assigning TA");
    p1->assign_TA(*ta1,"Project 2 EE");
    p1->assign_TA(*ta1,"Project 3 EE");
    p1->Display();

    ta1->Display();
    ta1->view_projects();
}