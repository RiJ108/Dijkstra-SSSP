#include <iostream>
#include <string>
#include <limits>
#include <vector>

using namespace std;

double inf = numeric_limits<double>::infinity();

class Graph{
public:
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
    void run(){
        setCostOf(initialState, 0.0f);
        int currentState;
        bool done = false;
        while(!done){
            currentState = getLowestUnvisitedState();
            cout << "Lowest is " << currentState << endl;
            for(int i = 0 ; i  < nbrOfState ; i++){
                if(grid[currentState][i] != inf){
                    cout << "-|to " << i << endl;
                    if(getCostOf(currentState) + grid[currentState][i] < cost[i]){
                        setCostOf(i, getCostOf(currentState) + grid[currentState][i]);
                        setOriginOfAt(i, currentState);
                        cout << "--|relaxing needed. Is at " << cost[i] << " and can relax to " << getCostOf(currentState) + grid[currentState][i] << endl;
                        cout << "--|" << i << " got is origin change to " << currentState << endl;
                    }
                }
            }
            cout << currentState << " has been visited.\n------------------------------------------" << endl;
            setVisited(currentState);
            if(getVisited(goalState))
                done = true;
        }
        setPath();
    }
    int getLowestCostState(){
        float min = getCostOf(0);
        int lowest = 0;
        for(int i = 0 ; i < nbrOfState ; i++){
            if(getCostOf(i) < min){
                min = getCostOf(i);
                lowest = i;
            }
        }
        return lowest;
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
        for(int i = 0 ; i < path.size() ; i++){
            if(i != 0)
                cout << " -> ";
            cout << path[i];
        }
    }
    void setPath(){
        int currentState = goalState;
        path.push_back(currentState);
        do{
            //cout << " <- " << getOriginOf(currentState);

            currentState = getOriginOf(currentState);
            path.insert(path.begin(),currentState);
        }while(currentState != initialState);
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
    graph.set_nbrOfState(6);
    graph.alloc();
    graph.setInitialState(0);
    graph.setGoalState(5);
    graph.setGridValueAt(0,1,2);
    graph.setGridValueAt(0,2,4);
    graph.setGridValueAt(1,2,1);
    graph.setGridValueAt(1,3,7);
    graph.setGridValueAt(2,4,3);
    graph.setGridValueAt(4,3,2);
    graph.setGridValueAt(4,5,5);
    graph.setGridValueAt(3,5,1);
    /*graph.logGrid();
    graph.logCosts();*/
    graph.run();
    /*graph.logCosts();
    graph.logOrigins();*/
    graph.logPath();
    return 0;
}