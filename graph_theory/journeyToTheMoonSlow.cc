#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <set>
#include <map>
using namespace std;

set<int> dfs(int i, map<int, set<int> > nodes, map<int, bool> &visited){
    set<int> component;
    visited[i] = true;
    component.insert(i);
    
    set<int> neighbors = nodes[i];
    for(int neighbor : neighbors){
        if(!visited[neighbor]){
            set<int> oneLevelDown = dfs(neighbor, nodes, visited);
            component.insert(oneLevelDown.begin(), oneLevelDown.end());
        }
    }
    return component;
}

int main() {
    int n, p;
    string line;
    getline(cin, line);
    stringstream s(line);
    s >> n >> p;
    map<int, set<int> > nodes;
    for(int i = 0; i < n; i++){
        set<int> empty;
        nodes[i] = empty;
    }
    for(int i = 0; i < p; i++){
        int id1, id2;
        getline(cin, line);
        stringstream ss(line);
        ss >> id1 >> id2;
        nodes[id1].insert(id2);
        nodes[id2].insert(id1);
    }
    
    vector<set<int> > connectedComponents;
    map<int, bool> visited;
    for(int i = 0; i < n; i++){
        visited[i] = false;
    }
    
    for(int i = 0; i < n; i++){
        if(!visited[i]){
            set<int> component = dfs(i, nodes, visited);
            connectedComponents.push_back(component);
        }
    }
    
//    for(auto component : connectedComponents){
//        for(auto node : component){
//            cout << node << " ";
//        }
//        cout << endl;
//    }
    
    int total = 0;
    int temp = 0;
    for(auto component : connectedComponents){
        total += temp * component.size();
        temp = temp + component.size();
    }
    
    cout << total << endl;
    
    return 0;
}
