#include <bits/stdc++.h>

// defining the random number generation within MAX and MIN values
#define GEN_RAND_NUM ((rand() % (MAX - MIN + 1)) + MIN)

using namespace std;

// Assigns randomly generated number to the adjacency matrix of the graph

void rand_gen_graph(int n, vector<vector<int>> &graph)
{
    int MAX = 10, MIN = 1; // max and min values of the weights
    int row = 0;
    while (row < n)
    {
        int col = 0;
        while (col < row)
        {
            int val = GEN_RAND_NUM; // generates the random number
            if (row != col)         // Value at i==j will be 0
            {
                graph[row][col] = val;
                graph[col][row] = val; // allocates both for [i][j] and [j][i] since it is undirected graph
            }
            col++;
        }
        row++;
    }
}

void display_adj_matrix(int n, vector<vector<int>> &adj_matrix)
{
    cout << "random matrix:" << endl
         << endl;

    int row = 0;
    while (row < n)
    {
        int col = 0;
        while (col < n)
        {
            cout << "\t" << adj_matrix[row][col];
            col++;
        }
        cout << endl;
        row++;
    }
    cout << endl;
}


// Displays the Minimum Spamming tree
void display_mst(int n, vector<int> prev, vector<vector<int>> &adj_matrix) {
    vector<vector<int>> prim_matrix(n, vector<int>(n, 0));
    int i = 1;
    while (i < n) {
        prim_matrix[i][prev[i]] = adj_matrix[i][prev[i]];
        prim_matrix[prev[i]][i] = adj_matrix[i][prev[i]];
        i++;
    }

    cout << "Prim's matrix:" << endl;
    int row = 0;
    while (row < n) {
        int col = 0;
        while (col < n) {
            cout << "\t" << prim_matrix[row][col];
            col++;
        }
        cout << endl;
        row++;
    }

    cout << "Prim's MST:" << endl;
    i = 1;
    while (i < n) {
        cout << "V" << i + 1 << "-V" << prev[i] + 1 << ": " << adj_matrix[i][prev[i]] << endl;
        i++;
    }
}


// implements the Prim algorithm
void prim_algo_MST(int n, vector<vector<int>> &adj_matrix){
    vector<int> cost(n,INT_MAX);
    vector<int> prev(n,-1);
    vector<bool> MST(n,false);

    cost[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> p_q;
    p_q.push({0,0});

    while(!p_q.empty()){
        int u = p_q.top().second;
        p_q.pop();

        if(MST[u]==false){
            MST[u] = true;

            for(int v=0;v<n;v++){
                if(adj_matrix[u][v]!=0){
                    if(MST[v]==false && cost[v] > adj_matrix[u][v]){
                        cost[v] = adj_matrix[u][v];
                        p_q.push({cost[v],v});
                        prev[v] = u;
                    }
                }
            }

        }
    }

    display_mst(n,prev,adj_matrix);
}

// Finds the parent to the current node
int search_parent(int x,vector<int>&parent){
    if(parent[x]==-1) return x;
    parent[x] = search_parent(parent[x], parent);
    return parent[x];
}

// merges two sets to make one
void merge_sets(int p1, int p2,vector<int>& set_id,vector<int>& parent){
    if(set_id[p1]<set_id[p2]){
        parent[p1] = p2;
    }
    else if (set_id[p1] > set_id[p2])
    {
        parent[p2] = p1;
    }
    else
    {
        parent[p2] = p1;
        set_id[p1] += 1;
    }
}

//  implements the kruskal algorithm
void kruskal_algo_MST(int n, vector<vector<int>>& adj_matrix){
    vector<int> parent(n,-1);
    vector<int> set_id(n,1);
    vector<vector<int>> kruskal_matrix(n,vector<int>(n,0));

    vector<vector<int>> edges;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(adj_matrix[i][j]!=0){
                edges.push_back({adj_matrix[i][j],i,j});
            }
        }
    }

    sort(edges.begin(),edges.end());

    for(auto edge: edges){
        int w=edge[0], u = edge[1],v = edge[2];
        int p1 = search_parent(u,parent);
        int p2 = search_parent(v,parent);

        if(p1!=p2){
            merge_sets(p1,p2,set_id,parent);
            kruskal_matrix[u][v] = w;
            kruskal_matrix[v][u] = w;
        }
    }

    cout << "Kruskal's matrix:" << endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<"\t"<<kruskal_matrix[i][j];
        }
        cout<<endl;
    }

    cout << "Kruskal's MST:" << endl;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(kruskal_matrix[i][j]!=0){
                cout << "V" << i + 1 << "-V" << j + 1 << ": " << kruskal_matrix[i][j] << endl;
            }
        }
    }
    
}

int main(){

    srand(time(0));
    int MAX = 10, MIN = 5;
    int n = GEN_RAND_NUM;

    cout << "randomly selected "<<n<<" vertices"<< endl;

    vector<vector<int>> adj_matrix(n, vector<int>(n, 0));

    rand_gen_graph(n, adj_matrix);

    display_adj_matrix(n, adj_matrix);

    string type;
    cout << "select the algorithm: "; 
    cin >> type;
    transform(type.begin(), type.end(), type.begin(), ::tolower);
    if(type=="prim"){
        prim_algo_MST(n,adj_matrix);
    }else if(type == "kruskal"){
        kruskal_algo_MST(n,adj_matrix);
    }
    else{
        cout<<"Give correct algorithm name"<<endl;
    }
    return 0;
}