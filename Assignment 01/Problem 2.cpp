#include<iostream>
using namespace std;

class Robot{
    string name;
    int hits=0;
    public:
    Robot(){
        this->name="NULL";
        
    }
    Robot(string name){
        this->name=name;
    }
    int get_hits(){
        return this->hits;
    }
    void Hitball(int &ballX,int &ballY, string direction){
        if(direction=="u"){
            ballX--;
        }
        else if(direction=="d"){
            ballX++;
        }
        else if(direction=="l"){
            ballY--;
        }
        else if(direction=="r"){
            ballY++;
        }
       hits++;
    }
};

class Ball{
    int x;
    int y;
    Robot* robot=nullptr;
    public:
    Ball(){
        this->x=0;
        this->y=0;
        this->robot=nullptr;
    }
    Ball(int x, int y){
        this->x=x;
        this->y=y;
    }
    int getX(){
        return this->x;
    }
    int getY(){
        return this->y;
    }
    void move(int dx, int dy){
        x=x+dx;
        y=y+dy;
    }
    void getPosition(){
        cout<<"("<<this->x<<","<<this->y<<")\n"<<endl;
    }
};

class Goal{
    int x;
    int y;
    public:
    Goal(){
        this->x=0;
        this->y=0;
    }
    Goal(int x, int y){
        this->x=x;
        this->y=y;
    }
    bool isGoalReached(int ballX, int ballY){
        if(ballX==this->x&&ballY==this->y){
            return true;
        }
        else{
            return false;
        }
    }
};

class Team{
    string teamName;
    Robot* robot;
    public:
    Team(){
        this->teamName="NULL";
        this->robot=nullptr;
    }

    Team(string name, Robot* robo){
        this->teamName=name;
        this->robot=robo;
    }

    string get_name(){
        return this->teamName;
    }

    Robot* get_robot(){
        return this->robot;
    }
};

class Game{
    Team teamOne;
    Team teamTwo;
    Ball ball;
    Goal goal;
    int initiial_ball_x;
    int initial_ball_y;
    public:
    Game(Team one, Team two, Ball ball, Goal goal, int ball_x, int ball_y){
        this->teamOne=one;
        this->teamTwo=two;
        this->goal=goal;
        this->initiial_ball_x=ball_x;
        this->initial_ball_y=ball_y;
    }

    void play(Team* team){
        string direc;
        int x,y;
        this->ball=Ball(initiial_ball_x, initial_ball_y);
        cout<<"\nTeam "<<team->get_name()<<" turn"<<endl;
        do{
            cout<<"Enter the Direction: ";
            cin>>direc;
            x=ball.getX();
            y=ball.getY();
            team->get_robot()->Hitball(x,y,direc);
            if(direc=="Up"){
                ball.move(-1,0);
            }
            else if(direc=="Down"){
                ball.move(1,0);
            }
            else if(direc=="Left"){
                ball.move(0,-1);
            }
            else if(direc=="Right"){
                ball.move(0,1);
            }
            else{
                cout<<"\nEnter only 4 directions : Up, Down, Left, Right"<<endl;
            }
            ball.getPosition();
          
            if(goal.isGoalReached(ball.getX(),ball.getY())==true){
                cout<<"Hits by Team "<<team->get_name()<<": "<<  team->get_robot()->get_hits()<<endl;
                break;
            }
        }while(1);
    }

    void declareWinner(){
        cout<<"\n--- LeaderBoard ---"<<endl;
        cout<<"\nHits by team "<<teamOne.get_name()<<" is: "<<teamOne.get_robot()->get_hits()<<endl;
        cout<<"\nHits by team "<<teamTwo.get_name()<<" is: "<<teamTwo.get_robot()->get_hits()<<endl;
        if(teamOne.get_robot()->get_hits()>teamTwo.get_robot()->get_hits()){
            cout<<"\nTeam "<<teamTwo.get_name()<<" Wins"<<endl;
        }
        else if(teamOne.get_robot()->get_hits()<teamTwo.get_robot()->get_hits()){
            cout<<"\nTeam "<<teamOne.get_name()<<" Wins"<<endl;
        }
        else if(teamOne.get_robot()->get_hits()==teamTwo.get_robot()->get_hits()){
            cout<<"\nTie!"<<endl;
        }
    }

    void startGame(){
        cout<<"\n--- Football Simulation ---"<<endl;
        play(&teamOne);
        play(&teamTwo);
        declareWinner();
    }
};

int main(){
    string team1, team2, r1, r2;
    cout<<"\nEnter the name of Team 1: ";
    cin>>team1;
    cout<<"Enter the name of the Robot given of Team "<<team1<<": ";
    cin>>r1;
    cout<<"\nEnter the name of Team 2: ";
    cin>>team2;
    cout<<"Enter the name of the Robot given of Team "<<team2<<": ";
    cin>>r2;

    Robot* robot1=new Robot(r1);
    Robot* robot2=new Robot(r2);
    Team Team1(team1,robot1);
    Team Team2(team2,robot2);
    Ball ball(0,0);
    Goal goal(3,3);
    Game game(Team1,Team2,ball,goal,ball.getX(),ball.getY());
    game.startGame();
    game.declareWinner();
}