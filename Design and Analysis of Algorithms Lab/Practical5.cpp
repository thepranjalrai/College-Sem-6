#include <iostream>
#include <utility>

#include <chrono>		// duration()
#include <stdlib.h>     // srand(), rand()

#include <unistd.h>

using namespace std;

#define edge pair< node*, int >

#define MAX_NODES 10
#define MAX_EDGES_PER_NODE 3   //Counts outgoing edges only
#define MAX_WEIGHT 10

class node
{
    unsigned id;                //Node id as integer starting from 1
    
    unsigned edge_count;
    edge* edges;

    static unsigned node_count;
    static node* nodes;
    
public:
    inline node()
    {
        id = ++node_count;
        edge_count = 0;

        //cout << "\nCreated..\n";
        //cout << "Node ID : " << id << endl;
    }

    inline ~node()
    {
        cout << "\n wth, Node : " << id << "was killed.";
    }

    static void create_graph()
    {
        for(int i = 0; i < MAX_NODES; i++)
        {
            node* ptr = new node;
            nodes[i] = *ptr;
        }

        for(int i = 0; i < MAX_NODES; i++)
        {
            nodes[i].set_random_edges();
        }
        //cout << "\nNode count is : " << node_count << endl;
    }

    static void print_graph()
    {
        for(int i=0; i < node_count; i++)
        {
            nodes[i].print_edges();
            cout << "\n.........\n";
        }
    }

    static void delete_graph()
    {
        for(int i = 0; i < MAX_NODES; i++)
            delete &nodes[i];
    }

    void print_edges()
    {
        cout << "\nEdges in Node : " << id << " are :-\n";

        if(!edge_count)
        {
            cout << "\nIsolated\n";
            return;
        }

        for(int i = 0; i < edge_count; i++)
        {
            cout << "To node : " << edges[i].first->id << " | " << "With " << edges[i].second << " units.\n";
        }
    }

    void set_random_edges()
    {
        edge_count = rand() % MAX_EDGES_PER_NODE + 1;
        edges = (edge*) malloc(edge_count * sizeof(edge));

        cout << "\nMaking " << edge_count << " edges in node : " << id << endl;
        //cout << "Memory alloted for edges : " << sizeof(edge) << 'x' << edge_count << '=' << sizeof(edges) << endl;

        //usleep(100000);
        unsigned k = 2;
        for(int i = 0; i < edge_count; i++)
        {
            edges[i].first = &nodes[(rand() * k*k + k/2 )% node_count + 1];
            edges[i].second = rand() % MAX_WEIGHT + 1;
            
            //check for uniqueness
            for(int j = 0; j < i; j++)
            {
                if(edges[j].first == edges[i].first)
                {
                    i--;
                    break;
                }
            }
            cout << "Connected to : " << edges[i].first->id << " at : " << edges[i].second << " units.\n";

            k *= 3.14;
        }
    }

};

unsigned node::node_count = 0;
node* node::nodes = (node*) malloc(MAX_NODES * sizeof(node));

int main()
{
    srand(time(NULL));
    node::create_graph();
    //node::print_graph();

    return 0;
}