#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <vector>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <iomanip>

#define cell_size 25
#define filler ' '

using namespace std;
using namespace chrono;

void print_number(long num, string terminator = "")  //To print numbers formatted by commas
{
    string s = std::to_string(num);
    int n = s.length() - 3;
    while (n > 0) {
        s.insert(n, ",");
        n -= 3;
    }
    cout << setw(cell_size-5) << s << terminator;
}

const int MAX = 99999;
int id[MAX], nodes, edges;
pair<long long, pair<int, int>> p[MAX];

void initialize()
{
    for (int i = 0; i < MAX; ++i)
        id[i] = i;
}

int root(int x)
{
    while (id[x] != x)
    {
        id[x] = id[id[x]];
        x = id[x];
    }
    return x;
}

void union1(int x, int y)
{
    int p = root(x);
    int q = root(y);
    id[p] = id[q];
}

long long kruskal(pair<long long, pair<int, int>> p[])
{
    int x, y;
    long long cost, minimumCost = 0;
    for (int i = 0; i < edges; ++i)
    {
        x = p[i].second.first;
        y = p[i].second.second;
        cost = p[i].first;

        if (root(x) != root(y))
        {
            minimumCost += cost;
            //cout << cost << '\t';
            union1(x, y);
            //cout << x << "," << y << "\n";
        }
    }

    return minimumCost;
}

void GenRandomGraphs(int NOEdge, int NOVertex, int max_weight = 100)
{
   int i, j, edge[NOEdge][3], count;
   i = 0;

   while(i < NOEdge)
   {
      edge[i][0] = rand()%NOVertex+1;
      edge[i][1] = rand()%NOVertex+1;
      edge[i][2] = rand()%max_weight+1;

      p[i] = make_pair(edge[i][2], make_pair(edge[i][0], edge[i][1]));

      if(edge[i][0] == edge[i][1])  //If self loop, ignore
         continue;
      else                          //Check for repeated edge
      {
         for(j = 0; j < i; j++)
         {
            if((edge[i][0] == edge[j][0] &&
            edge[i][1] == edge[j][1]) || (edge[i][0] == edge[j][1] &&
            edge[i][1] == edge[j][0]))
            i--;                    //If repeated, scrap it
         }
      }
      i++;
   }
/*
   cout<<"\nThe generated random graph is: ";
   for(i = 0; i < NOVertex; i++)
   {
      count = 0;
      cout<<"\n\t"<<i+1<<"-> { ";
      for(j = 0; j < NOEdge; j++)
      {
         if(edge[j][0] == i+1)
         {
            cout<<edge[j][1]<<":"<<edge[j][2]<<" ";
            count++;
         } else if(edge[j][1] == i+1)
         {
            cout<<edge[j][0]<<":"<<edge[j][2]<<" ";
            count++;
         } else if(j== NOEdge-1 && count == 0)
         cout<<"Isolated Vertex!"; //Print “Isolated vertex” for the vertex having no degree.

         //p[i] = make_pair(edge[j][2], make_pair(edge[j][0], edge[j][1]));
      }
      cout<<" }";
   }
*/
}

void analyse(int iterations)
{
    int x, y;
    long long weight, cost, minimumCost;

    cout << "\nNode count: ";
    cin >> nodes;
    cout << "\nEdge count : ";
    cin >> edges;

    cout << "\n\n";
    cout << setfill(filler) << setw(cell_size-10) << "Iteration";
    cout << setfill(filler) << setw(cell_size-5) << "Minimum Cost";
    cout << setfill(filler) << setw(cell_size) << "Time Taken";
    cout << "\n";

    long sum = 0;

    for(int i = 0; i < iterations; i++)
    {
        cout << setw(cell_size-11) << i << "]";
        
        initialize();
        GenRandomGraphs(edges, nodes);

        sort(p, p + edges);
        //cout << "\n\n MST:-\n";
        //cout << "Cost\tEdges\n";

        auto start = high_resolution_clock::now();					//Start timing
            minimumCost = kruskal(p);
        auto stop = high_resolution_clock::now();					//Stop timing
        auto duration_first = duration_cast<nanoseconds>(stop - start);

        print_number(minimumCost);
        print_number(duration_first.count(), " (ns)\n");

        sum += duration_first.count();
    }

    cout << endl;
    cout << setfill(filler) << setw(cell_size-10) << "Avg Time";
    print_number(sum/iterations, " (ns)\n");
}

int main()
{
    analyse(5);

    return 0;
}

/*
unsigned int node_count = 0;
unsigned int edge_count = 0;
int* edges;

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

int fact(int n) 
{ 
    int res = 1; 
    for (int i = 2; i <= n; i++) 
        res = res * i; 
    return res; 
}

int nCr(int n, int r) 
{ 
    return fact(n) / (fact(r) * fact(n - r)); 
}

void read_input(string filename)
{
    ifstream file(filename, fstream::in);

    //Getting the first line
    string line_1;
    getline(file, line_1);
    vector<string> line_1_tokens = split (line_1, ',');

    if(line_1_tokens.size() != 1)
    {
        cout << "Error in Input : Line 1";
        exit(1);
    }

    node_count = stoi(line_1_tokens[0]);
    cout << "No of nodes : " << node_count << "\n";

    edge_count = nCr(node_count, 2);
    edges = (int*) malloc(edge_count * sizeof(int));

    //Getting the second line
    string line_2;
    getline(file, line_2);
    vector<string> line_2_tokens = split (line_2, ',');

    if(line_2_tokens.size() != edge_count)
    {
        cout << "Error in Input : Line 2";
        exit(1);
    }

    for (auto i : line_2_tokens) cout << i << "\t";
}

int main()
{
    read_input("graph.csv");

    return 0;
}

*/