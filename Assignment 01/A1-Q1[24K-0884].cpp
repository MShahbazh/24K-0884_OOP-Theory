#include<iostream>
#include<string>
using namespace std;

class Mentor;

class Skill{
    int skillID;
    string name;
    string description;
    public: 
    Skill(){
        this->skillID=-1;
        this->name="NULL";
        this->description="NULL";
    }

    Skill(int id, string name, string description){
        this->skillID=id;
        this->name=name;
        this->description=description;
    }

    void view_Skill(){
        cout<<"\nSkill ID: "<<this->skillID<<endl;
        cout<<"Skill Name: "<<this->name<<endl;
        cout<<"Skill Description: "<<this->description<<endl;
    }

    void updateSKillDescription(string newDescription){
        this->description=newDescription;
    }

    int get_skillID(){
        return this->skillID;
    }
};

class Sport{
    int sportID;
    string name;
    string description;
    Skill requiredSkill[100];
    public:
    Sport(){
        int i;
        this->sportID=-1;
        this->name="NULL";
        this->description="NULL";
        for(i=0;i<100;i++){
            requiredSkill[i]=Skill();
        }
    }

    Sport(int id, string name, string description){
        this->sportID=id;
        this->name=name;
        this->description=description;
    }

    void view_Sport(){
        cout<<"\nSport ID: "<<this->sportID<<endl;
        cout<<"Sport Name: "<<this->name<<endl;
        cout<<"Sport Description: "<<this->description<<endl;
    }

    void add_Skill(Skill s){
        int i;
        for(i=0;i<100;i++){
            if(requiredSkill[i].get_skillID()==-1){
                requiredSkill[i]=s;
                break;
            }
        }
    }

    void remove_Skill(Skill s){
        int i,j;
        for(i=0;i<100;i++){
                if(requiredSkill[i].get_skillID()==s.get_skillID()){
                    requiredSkill[i]=Skill();
                    for(j=i;requiredSkill[j+1].get_skillID()!=-1;j++){
                        requiredSkill[j]=requiredSkill[j+1];
                        cout<<"Hello"<<endl;
                        requiredSkill[j+1]=Skill();
                    }
                }
        }
    }

    void view_RequiredSkill(){
        int i;
        bool check=false;
        for(i=0;i<100;i++){
            if(requiredSkill[i].get_skillID()!=-1){                
                requiredSkill[i].view_Skill();
                check=true;
            }
            else{
                break;
            }
        }
        if(check==false){
            cout<<"\nSkills List Empty"<<endl;
        }
    }

    Skill get_requiredSkill(int i){
        return requiredSkill[i];
    }

    int get_sportID(){
        return this->sportID;
    }

};

class Student{
    int studentID;
    string name;
    int age;
    Sport* sportsInterests[100];
    public:
    Mentor* mentor;
    Student(){
        this->studentID=-1;
        this->name="NULL";
        this->age=-1;
        this->mentor=nullptr;
        int i;
        for(i=0;i<100;i++){
            sportsInterests[i]=nullptr;
        }
    }

    Student(int id,string name, int age){
        this->studentID=id;
        this->name=name;
        this->age=age;
        this->mentor=nullptr;
    }

    Sport* get_sportsInterest(int i){
        return sportsInterests[i];
    }

    void view_Student(){
        cout<<"\nStudent ID: "<<this->studentID<<endl;
        cout<<"Student Name: "<<this->name<<endl;
        cout<<"Student Age: "<<this->age<<endl;
        this->view_mentorInfo();
    }

    void add_SportsInterests(Sport s){
        int i;
        for(i=0;i<100;i++){
            if(sportsInterests[i]==nullptr){
                sportsInterests[i]=new Sport(s);
                break;
            }
        }
    }

    void remove_SportsInterests(Sport s){
        int i,j;
        for(i=0;sportsInterests[i]!=nullptr;i++){
            if(sportsInterests[i]->get_sportID()==s.get_sportID()){
                sportsInterests[i]=nullptr;
                for(j=i;sportsInterests[j+1]!=nullptr;j++){
                    sportsInterests[j]=sportsInterests[j+1];
                    sportsInterests[j+1]=nullptr;
                }
            }
        }
    }

 
    void view_SportsInterests(){
        int i;
        bool check=false;
        for(i=0;sportsInterests[i]!=nullptr;i++){
            sportsInterests[i]->view_Sport();
            check=true;
        }
        if(check==false){
            cout<<"\nSports Interest List Empty"<<endl;
        }
    }

    int get_studentID(){
        return this->studentID;
    }

    void registerForMentorship(Mentor &m);
    void view_mentorInfo();
    

};

class Mentor{
    int mentorID;
    string name;
    int maxLearners;
    Sport* sportsExpertise[100];
    Student* assignedLearners[100];
    public:
    Mentor(){
        this->mentorID=-1;
        this->name="NULL";
        this->maxLearners=-1;
        int i;
        for(i=0;i<100;i++){
            sportsExpertise[i]=nullptr;
            assignedLearners[i]=nullptr;
        }
    }

    Mentor(int id, string name, int max){
        this->mentorID=id;
        this->name=name;
        this->maxLearners=max;
    }

    int get_mentorID(){
        return this->mentorID;
    }

    int get_max(){
        return this->maxLearners;
    }

    Student* get_Learners(int i){
        return assignedLearners[i];
    }
    
    void provide_guidance(){
        cout<<"\nGuidance Provided"<<endl;
    }

    void assignLearners(Student& s){
        int i;
        for(i=0;i<maxLearners;i++){
            if(assignedLearners[i]==nullptr){
                assignedLearners[i]=&s;
                s.mentor=this;
                break;
            }
        }
    }

    void removeStudent(Student s){
        int i,j;
        for(i=0;i<maxLearners;i++){
            if(assignedLearners[i]->get_studentID()==s.get_studentID()){
                assignedLearners[i]=nullptr;
                for(j=i;assignedLearners[j+1]!=nullptr;j++){
                    assignedLearners[j]=assignedLearners[j+1];
                    assignedLearners[j+1]=nullptr;
                    s.mentor=nullptr;
                }
            }
        }
    }

    void view_assignedLearners(){
        int i;
        bool check=false;
        for(i=0;assignedLearners[i]!=nullptr;i++){
            assignedLearners[i]->view_Student();
            check=true;
        }
        if(check==false){
            cout<<"\nAssigned Learners List Empty"<<endl;
        }
    }

    void add_sportsExpertise(Sport s){
        int i;
        for(i=0;i<100;i++){
            if(sportsExpertise[i]==nullptr){
                sportsExpertise[i]=new Sport(s);
                 break;
            }
        }
    }

    void remove_sportsExpertise(Sport s){
        int i,j;
        for(i=0;sportsExpertise[i]!=nullptr;i++){
            if(sportsExpertise[i]->get_sportID()==s.get_sportID()){
                sportsExpertise[i]=nullptr;
                for(j=i;sportsExpertise[j+1]!=nullptr;j++){
                    sportsExpertise[j]=sportsExpertise[j+1];
                    sportsExpertise[j+1]=nullptr;
                }
            }
        }
    }

    void view_sportsExpertise(){
        int i;
        bool check=false;
        for(i=0;i<100;i++){
            if(sportsExpertise[i]!=nullptr){
                sportsExpertise[i]->view_Sport();
                check=true;
            }
            else{
                break;
            }
        }
        if(check==false){
            cout<<"\nSports Expertise List Empty"<<endl;
        }
    }

    Sport* get_sportsExpertise(int i){
        return sportsExpertise[i];
    }

    void view_mentor(){
        cout<<"\nMentor ID: "<<this->mentorID<<endl;
        cout<<"Mentor Name: "<<this->name<<endl;
        cout<<"Max Learners: "<<this->maxLearners<<endl;
    }

};

void Student::registerForMentorship(Mentor &m){
    int i,size=0;
    for(i=0;i<100;i++){
        if(m.get_Learners(i)==nullptr){
            break;
        }
        size++;                
    }
    if(size<m.get_max()){
        mentor=&m;
        m.assignLearners(*this);
        cout<<"\nMentor added"<<endl;
    }
    else{
        cout<<"Limit reached | can't apply for mentorship"<<endl;
    }
}

void Student::view_mentorInfo(){
    if(this->mentor!=nullptr){
        this->mentor->view_mentor();
    }
    else{
        cout<<"Mentor Not Chosen"<<endl;
    }
    
}

int main(){
    int a,b,c,i,j,k,x,z,l,q,w,e,r,t,y;
    string name1,name2,str1,str2;
    cout<<"Enter the number of Mentors the system will handle: ";
    cin>>a;
    cout<<"Enter the number of Students the system will handle: ";
    cin>>b;
    cout<<"Enter the number of Sports the system will handle: ";
    cin>>c;
    
    Sport sport[c];
    Student student[b];
    Mentor mentor[a];

    cout<<"\n--- Sport Info ---"<<endl;
    for(i=0;i<c;i++){
        cout<<"\nSport "<<i+1<<" Info"<<endl;
        bool check=true;
        do{
            cout<<"Enter the Sport ID: ";
            cin>>x;
            if(x<=0){
                cout<<"ID Cannot be negative or zero"<<endl;
            }
            else{
            bool check2=false;
            for(j=0;j<c;j++){
                if(x==sport[j].get_sportID()){
                    check2=true;
                    cout<<"ID Already Used for different sport"<<endl;
                    break;
                }
            }
            if(check2==false) break;
            }
        }while(1);
        
        cout<<"Enter the Name of the sport: ";
        cin>>name1;
        cin.ignore();
        cout<<"Enter the Description: ";
        getline(cin,name2);
        sport[i]= Sport(x,name1,name2);
        cout<<"How many Skills are required for this Sport: ";
        cin>>l;
        for(j=0;j<l;j++){
                do{
                    cout<<"\nEnter the Skill ID for Skill number "<<j+1<<": ";
                    cin>>x;
                    if(x<=0){
                        cout<<"ID cannot be negative or zero"<<endl;
                    }
                    else{
                        bool check2=false;
                        for(k=0;k<l;k++){
                            if(sport[i].get_requiredSkill(k).get_skillID()==x){
                                check2=true;
                                cout<<"ID Already in use for another skill of the same sport"<<endl;
                                break;
                            }
                        }
                        if(check2==false) break;
                    }
                }while(1);
                cout<<"Enter the name of the Skill: ";
                cin>>name1;
                cin.ignore();
                cout<<"Enter the Skill Description: ";
                getline(cin,name2);
                Skill s(x,name1,name2);
                sport[i].add_Skill(s);
        }
    }
    
    int x1;
    cout<<"\n--- Mentor Info ---"<<endl;
    for(i=0;i<a;i++){
        cout<<"\nMentor "<<i+1<<" Info: "<<endl;
        do{
            cout<<"Enter the mentor ID: ";
            cin>>x;
            if(x<=0){
                cout<<"ID cannot be zero or negative"<<endl;
            }
            else{
                bool check2=false;
                for(j=0;j<a;j++){
                    if(mentor[j].get_mentorID()==x){
                        check2=true;
                        cout<<"ID Already in use"<<endl;
                        break;
                    }
                }
                if(check2==false) break;
            }
        }while(1);
        cout<<"Enter the mentor name: ";
        cin>>name1;
        cout<<"Enter the maximum Learners the mentor can handle: ";
        cin>>l;
        Mentor m(x,name1,l);
        mentor[i]=m;
        cout<<"How many sports the mentor is expert: ";
        cin>>x;
        if(x!=0){
            cout<<"Here is the list to choose from: "<<endl;
        for(j=0;j<c;j++){
            sport[j].view_Sport();
            cout<<"\n";
            }
        }
        j=0;
        do{
            if(j<x){
                cout<<"\nEnter the sport ID for Sport number "<<j+1<<" : ";
            cin>>x1;
            bool check=false;
            for(k=0;k<c;k++){
                if(x1==sport[k].get_sportID()){
                    mentor[i].add_sportsExpertise(sport[k]);
                    check=true;
                    cout<<"\nSport is Added to the Mentor Expertise"<<endl;
                    j++;
                }
            }
            if(check==false){
                cout<<"\nWrong ID Entered"<<endl;
            }
            }
            else{
                break;
            }
        }while(1);
    }
    
    cout<<"\n--- Student Info ---"<<endl;
    for(i=0;i<b;i++){
        cout<<"\nStudent "<<i+1<<" Info: "<<endl;
        do{
        cout<<"Enter the Student ID: ";
        cin>>x;
        if(x<=0){
            cout<<"ID cannot be zero or negative"<<endl;
        }
        else{
            bool check=false;
            for(j=0;j<b;j++){
                if(student[j].get_studentID()==x){
                    cout<<"ID Already in use"<<endl;
                    check=true;
                    break;
                }
            }
            if(check==false) break;
        }
        }while(1);
        cout<<"Enter the Student name: ";
        cin>>name1;
        cout<<"Enter the Student age: ";
        cin>>l;
        Student s(x,name1,l);
        student[i]=s;
        cout<<"How many sports the Student has interest: ";
        cin>>x;
        if(x!=0){
            cout<<"Here is the list to choose from: "<<endl;
        for(j=0;j<c;j++){
            sport[j].view_Sport();
            cout<<"\n";
            }
        }
        j=0;
        do{
            if(j<x){
                cout<<"Enter the sport ID: ";
                cin>>x1;
                bool check=false;
                for(k=0;k<c;k++){
                    if(x1==sport[k].get_sportID()){
                    student[i].add_SportsInterests(sport[k]);
                    check=true;
                    cout<<"\nSport is Added to Student's Interest"<<endl;
                    j++;
                    }
                }
                if(check==false){
                    cout<<"\nWrong ID Entered"<<endl;
                }
            }
            else{
                break;
            }
        }while(1);

    }
    
    do{
        cout<<"\n--- MAIN Section ---\n1. Mentors\n2. Sport\n3. Student\n4. Exit\nEnter the corresponding number: ";
        cin>>q;
       if(q==1){
            do{
                cout<<"\nMAIN > MENTORS:\n1. Display Mentors Info\n2. Sports Expertise\n3. Assigned Learners\n4. Provide Guidance \n5. Exit\nEnter the Corresponding Number: ";
                cin>>w;
                if(w==1){
                    for(i=0;i<a;i++){
                        mentor[i].view_mentor();
                    }
                }
                else if(w==2){
                    cout<<"\nEnter the Mentor ID: ";
                    cin>>e;
                    bool check=false;
                    for(i=0;i<a;i++){
                        if(mentor[i].get_mentorID()==e){
                            check=true;
                            do{
                                cout<<"\nMAIN > MENTORS > SPORTS EXPERTISE:\n1. Display\n2. Add a sport\n3. Remove a Sport\n4. Exit\nEnter the Corresponding number: ";
                                cin>>r;
                                if(r==1){
                                   mentor[i].view_sportsExpertise();
                                }
                                else if(r==2){
                                    cout<<"Enter the Sport ID: ";
                                    cin>>t;
                                    bool check=false;
                                    for(j=0;j<c;j++){
                                        if(sport[j].get_sportID()==t){
                                            mentor[i].add_sportsExpertise(sport[j]);
                                            check=true;
                                            cout<<"\nSport Added to the Expertise"<<endl;
                                        }
                                    }
                                    if(check==false){
                                        cout<<"\nNo Sport of this ID exist"<<endl;
                                    }
                                }
                                else if(r==3){
                                    cout<<"Enter the Sport ID: ";
                                    cin>>t;
                                    bool check=false;
                                    for(j=0;j<c;j++){
                                        if(sport[j].get_sportID()==t){
                                            mentor[i].remove_sportsExpertise(sport[j]);
                                            check=true;
                                            cout<<"\nSport Removed"<<endl;
                                        }
                                    }
                                    if(check==false){
                                        cout<<"\nNo Sport of this ID exist"<<endl;
                                    }
                                }
                                else if(r==4){
                                    break;
                                }
                            }while(1);
                        }
                    }
                    if(check==false){
                        cout<<"\nNo Mentor of this ID exist"<<endl;
                    }
                }
                else if(w==3){
                    cout<<"\nEnter the Mentor ID: ";
                    cin>>e;
                    bool check=false;
                    for(i=0;i<a;i++){
                        if(mentor[i].get_mentorID()==e){
                            check=true;
                            do{
                                cout<<"\nMAIN > MENTORS > ASSIGNED LEARNERS:\n1. Display\n2. Add A learner\n3. Remove a learner\n4. Exit\nEnter the Corresponding number: ";
                                cin>>r;
                                if(r==1){
                                    mentor[i].view_assignedLearners();
                                }
                                else if(r==2){
                                    cout<<"Enter the Student ID: ";
                                    cin>>t;
                                    int size=0;
                                    for(j=0;j<100;j++){
                                        if(mentor[i].get_Learners(j)!=nullptr){
                                            size++;
                                        }
                                    }
                                    if(size<mentor[i].get_max()){
                                    bool check=false;
                                    for(j=0;j<b;j++){
                                        if(student[j].get_studentID()==t){
                                            mentor[i].assignLearners(student[j]);
                                            check=true;
                                            cout<<"\nStudent Added"<<endl;
                                        }
                                    }
                                    if(check=false){
                                        cout<<"\nNo Student with this ID Exist"<<endl;
                                    }
                                    }
                                    else{
                                        cout<<"\nMaximum Capacity"<<endl;
                                    }
                                }
                                else if(r==3){
                                    cout<<"Enter the Student ID: ";
                                    cin>>t;
                                    for(j=0;j<b;j++){
                                        if(student[j].get_studentID()==t){
                                            mentor[i].removeStudent(student[j]);
                                        }
                                    }
                                }
                                else if(r==4){
                                    break;
                                }
                            }while(1);
                        }
                    }
                    if(check==false){
                        cout<<"\nMentor with such ID does not exist"<<endl;
                    }
                }
                else if(w==4){
                    cout<<"\nEnter the Mentor ID: ";
                    cin>>e;
                    bool check=false;
                       for(i=0;i<a;i++){
                           if(mentor[i].get_mentorID()==e){
                                mentor[i].provide_guidance();
                                check=true;
                           }
                       }
                    if(check==false){
                        cout<<"\nNo Mentor of this ID Exist"<<endl;
                    }
                }
                else if(w==5){
                    break;
                }
            }while(1);
       }
      
       else if(q==2){
        do{
            cout<<"\nMAIN > SPORTS:\n1. Sports Info\n2. Required Skills\n3. Exit\nEnter the Corresponding number: ";
            cin>>w;
            if(w==1){
                for(i=0;i<c;i++){
                    sport[i].view_Sport();
                }
            }
            else if(w==2){
                cout<<"\nEnter the Sport ID: ";
                cin>>e;
                bool check=false;
                for(i=0;i<c;i++){
                    if(e==sport[i].get_sportID()){
                        check=true;
                        do{
                            cout<<"\nMAIN > SPORTS > REQUIRED SKILLS:\n1. Display\n2. Add a Skill\n3. Remove a Skill\n4. Exit\nEnter the Corresponding number: ";
                            cin>>r;
                            if(r==1){
                                sport[i].view_RequiredSkill();
                            }
                            else if(r==2){
                                cout<<"Enter the Skill ID to add: ";
                                cin>>t;
                                cout<<"Enter the Skill Name: ";
                                cin>>str1;
                                cout<<"Enter the Skill Description: ";
                                cin>>str2;
                                Skill s(t,str1,str2);
                                sport[i].add_Skill(s);
                                cout<<"\nSkill Added"<<endl;
                            }
                            else if(r==3){
                                cout<<"Enter the Skill ID to remove: ";
                                cin>>t;
                                bool check2=false;
                                for(j=0;sport[i].get_requiredSkill(j).get_skillID()!=-1;j++){
                                    if(sport[i].get_requiredSkill(j).get_skillID()==t){

                                        sport[i].remove_Skill(sport[i].get_requiredSkill(j));
                                        check2=true;
                                        cout<<"\nSkill Removed"<<endl;
                                    }
                                }
                                if(check2==false){
                                    cout<<"\nSkill with this ID does not Exist"<<endl;
                                }
                            }
                            else if(r==4){
                                break;
                            }
                        }while(1);
                    }
                }
                if(check==false){
                    cout<<"\nSport ID does not Exist"<<endl;
                }
            }
            else if(w==3){
                break;
            }
        }while(1);
       }

       else if(q==3){
        do{
            cout<<"\nMAIN > STUDENT: \n1. Display Student Info\n2. Sports Interest\n3. Register\n4. Exit\nEnter the Corresponding number: ";
            cin>>w;
            if(w==1){
                for(i=0;i<b;i++){
                    student[i].view_Student();
                }
            }
            else if(w==2){
                cout<<"\nEnter the Student ID: ";
                cin>>e;
                bool check=false;
                for(i=0;student[i].get_studentID()!=-1;i++){
                    if(student[i].get_studentID()==e){
                        check=true;
                        do{
                            cout<<"\nMAIN > STUDENT > SPORTS INTEREST:\n1. Display\n2. Add Interest\n3. Remove Interest\n4. Exit\nEnter the Corresponding number: ";
                            cin>>r;
                            if(r==1){
                                for(i=0;i<b;i++){
                                    student[i].view_SportsInterests();
                                }
                            }
                            else if(r==2){
                                cout<<"Enter the Sport ID to add: ";
                                cin>>t;
                                bool check=false;
                                for(j=0;j<c;j++){
                                    if(sport[j].get_sportID()==t){
                                        student[i].add_SportsInterests(sport[j]);
                                        check=true;
                                        cout<<"\nSport Added"<<endl;
                                    }
                                }
                                if(check==false){
                                    cout<<"\nNo Sport with this ID exist"<<endl;
                                }
                            }
                            else if(r==3){
                                cout<<"Enter the Sport ID to remove: ";
                                cin>>t;
                                bool check=false;
                                for(j=0;j<b;j++){
                                    if(student[i].get_sportsInterest(j)->get_sportID()==t){  
                                        
                                        check=true;
                                        student[i].remove_SportsInterests(*student[i].get_sportsInterest(j));
                                        cout<<"\nSport Removed"<<endl;
                                    }
                                }
                                if(check==false){
                                    cout<<"\nWrong ID Entered"<<endl;
                                }
                            }
                            else if(r==4){
                                break;
                            }
                        }while(1);
                    }
                }
                if(check=false){
                    cout<<"\nNo Student with this ID exist"<<endl;
                }
            }
            else if(w==3){
                cout<<"\nEnter the student ID: ";
                cin>>e;
                for(i=0;i<b;i++){
                    if(student[i].get_studentID()==e){
                        cout<<"Enter the Mentor's ID: ";
                        cin>>r;
                        bool check=false;
                        for(j=0;j<a;j++){
                            if(mentor[j].get_mentorID()==r){
                                student[i].registerForMentorship(mentor[j]);
                                check=true;
                            }
                        }
                        if(check==false){
                            cout<<"\nNo Mentor with this ID Exist"<<endl;
                        }
                        else{
                        cout<<"Mentor: ";
                        student[i].view_mentorInfo();
                        }
                    }
                    else{
                        cout<<"\nNo Student with this ID Exist"<<endl;
                    }
                }
            }
            else if(w==4){
                break;
            }
        }while(1);
       }

       else if(q==4){
        break;
       }
    }while(1);
}