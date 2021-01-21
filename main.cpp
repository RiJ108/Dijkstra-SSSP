#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

double inf = numeric_limits<double>::infinity();

class Graph{
public:
    Graph(){
        if(!import())
            exit(EXIT_FAILURE);
        run(false);
        logPath();
    }
    ~Graph(){
        free(grid);
        free(visited);
        free(origin);
        free(cost);
    }
    void set_nbrOfState(int nbr){
        nbrOfState = nbr;
    }
    void alloc(){
        // Allocate the matrix containing the transition between states
        grid = (float**) malloc(sizeof(float*) * nbrOfState);
        for(int i = 0 ; i < nbrOfState ; i++){
            grid[i] = (float*) malloc(sizeof(float) * nbrOfState);
            for(int j = 0 ; j < nbrOfState ; j++)
                grid[i][j] = inf;
        }

        // Allocate state related variable
        visited = (bool*) malloc(sizeof(bool) * nbrOfState);
        origin = (int*) malloc(sizeof(int) * nbrOfState);
        cost = (float*) malloc(sizeof(float) * nbrOfState);
        for(int i = 0 ; i  < nbrOfState ; i++){
            visited[i] = false;
            origin[i] = 0;
            cost[i] = inf;
        }
    }
    void logGridValueAt(int i, int j){
        cout << "Value at [" << i << "][" << j << "] = " << grid[i][j] << endl;
    }
    void logGrid(){
        for(int i = 0 ; i < nbrOfState ; i++){
            for(int j = 0 ; j < nbrOfState ; j++){
                if(j != 0)
                    cout << "|";
                cout << grid[i][j];
            }
            cout << endl;
        }
    }
    void setGridValueAt(int i, int j, float value){
        grid[i][j] = value;
    }
    void setInitialState(int i){
        initialState = i;
    }
    void setGoalState(int i){
        goalState = i;
    }
    bool getVisited(int i){
        return visited[i];
    }
    void setVisited(int i){
        visited[i] = true;
    }
    void setOriginOfAt(int i, int j){
        origin[i] = j;
    }
    int getOriginOf(int i){
        return origin[i];
    }
    void setCostOf(int i, float value){
        cost[i] = value;
    }
    float getCostOf(int i){
        return cost[i];
    }
    void run(bool debug){
        setCostOf(initialState, 0.0f);
        int currentState;
        bool done = false;
        while(!done){
            currentState = getLowestUnvisitedState();
            if(debug) cout << "Lowest is " << currentState << endl;
            for(int i = 0 ; i  < nbrOfState ; i++){
                if(grid[currentState][i] != inf){
                    if(debug) cout << "-|to " << i << endl;
                    if(getCostOf(currentState) + grid[currentState][i] < cost[i]){
                        setCostOf(i, getCostOf(currentState) + grid[currentState][i]);
                        setOriginOfAt(i, currentState);
                        if(debug) cout << "--|relaxing needed. Is at " << cost[i] << " and can relax to " << getCostOf(currentState) + grid[currentState][i] << "\n--|" << i << " got is origin change to " << currentState << endl;
                    }
                }
            }
            if(debug) cout << currentState << " has been visited.\n------------------------------------------" << endl;
            setVisited(currentState);
            if(getVisited(goalState))
                done = true;
        }
        setPath();
    }
    int getLowestUnvisitedState(){
        float min;
        int index;
        for(int i = 0 ; i < nbrOfState ; i++){
            if(!getVisited(i)){
                min = getCostOf(i);
                index = i;
                break;
            }
        }
        for(int i = 0 ; i < nbrOfState ; i++){
            if(getCostOf(i) < min && !getVisited(i)){
                min = getCostOf(i);
                index = i;
            }
        }
        return index;
    }
    void logCosts(){
        for(int i = 0 ; i < nbrOfState ; i++)
            cout << "C[" << i << "] = " << getCostOf(i) << endl;
    }
    void logOrigins(){
        for(int i = 0 ; i < nbrOfState ; i++)
            cout << "Origin[" << i << "] = " << getOriginOf(i) << endl;
    }
    void logPath(){
        cout << "Path found : ";
        for(int i = 0 ; i < path.size() ; i++){
            if(i != 0)
                cout << " -> ";
            cout << path[i];
        }
        cout << endl;
    }
    void setPath(){
        int currentState = goalState;
        path.push_back(currentState);
        do{
            currentState = getOriginOf(currentState);
            path.insert(path.begin(),currentState);
        }while(currentState != initialState);
    }
    bool import(){
        ifstream file;
        file.open("data.txt");
        if(!file.is_open()){
            cout << "FAILURE!! unable to access file data.txt\n Exiting." << endl;
            return false;
        }
        string str,tmp;
        int a,b,index;
        float c;
        char ch;
        getline(file, str);
        tmp = "";
        index = 0;
        for(int i = 0 ; i < str.size() ; i++){
            ch = str.at(i);
            if(ch != '-')
                tmp += ch;
            else{
                if(index == 0){
                    a = stoi(tmp);
                    tmp = "";
                    index++;
                }else if(index == 1){
                    b = stoi(tmp);
                    tmp = "";
                }
            }
        }
        c = stoi(tmp);
        nbrOfState = a;
        initialState = b;
        goalState = c;
        alloc();
        while(getline(file, str)){
            tmp = "";
            index = 0;
            for(int i = 0 ; i < str.size() ; i++){
                ch = str.at(i);
                if(ch != '/')
                    tmp += ch;
                else{
                    if(index == 0){
                        a = stoi(tmp);
                        tmp = "";
                        index ++;
                    }else if(index == 1){
                        c = stoi(tmp);
                        tmp ="";
                    }
                }
            }
            b = stoi(tmp);
            setGridValueAt(a,b,c);
        }
        return true;
    }
private:
    string name;
    int nbrOfState;
    float **grid;
    bool *visited;
    int *origin;
    float *cost;
    int initialState;
    int goalState;
    vector<int> path;
};

int main(void){
    cout << "Dijkstra Single Source Shortest Path" << endl;
    Graph graph;
    return 0;
}