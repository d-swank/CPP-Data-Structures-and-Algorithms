#include <iostream>
using namespace std;

class edge {
public:
    int vertex;
    //int id;
    edge* next;
    //edge *w;
    edge(int vertex) {
        this->vertex = vertex;
        this->next = NULL;
        //this->w = NULL;
        //this->id = id;
    }

    //edge() {
        //this->vertex = 0;
        //this->next = NULL;
        //this->w = NULL;
        //this->id = 0;
   // }
};

class LinkedList
{
public:
    int id;
    edge* w;
    edge* next;
    LinkedList(int id)
    {
        this->id = id;
        this->w = NULL;
        this->next = NULL;
    }

    LinkedList()
    {
        this->id = 0;
        this->w = NULL;
        this->next = NULL;
    }
};

class QNode
{
public:
    int data;
    QNode* next;

    QNode(int value)
    {
        this->data = value;
        this->next = NULL;
    }
};


class Queue {
public:
    QNode* front;
    QNode* rear;
    int count;
    Queue() {
        this->front = NULL;
        this->rear = NULL;
        this->count = 0;
    }

    int size()
    {
        return this->count;
    }

    int peek() {
        if (front == NULL) {
            cout << "Queue is Empty" << endl;
            return -1;
        }
        return this->front->data;
    }

    void pop_front()
    {
        if (this->isEmpty())
        {
            cout << "Queue is Empty" << endl;
        }
        QNode* temp = this->front;
        this->front = this->front->next;
        this->count--;
        if (this->front == NULL)
        {
            this->rear = NULL;
        }
        int data = temp->data;
        delete temp;
    }

    void push_back(int value) {
        QNode* node = new QNode(value);
        //temp->vertex = value;
        //temp->next = NULL;

        if (this->front == NULL)
        {
            this->front = node;
        }
        else
        {
            this->rear->next = node;
        }
        this->count++;
        this->rear = node;
    }

    bool isEmpty() {
        return this->count == 0;
    }
};

class Graph {
public:
    int V;
    //edge *adj;
    LinkedList* adjList;
    bool* visited;

    Graph(int V) {
        this->V = V;
        //this->adj = new edge[V];
        this->adjList = new LinkedList[V];
        //for (int i = 0; i < V; i++)
            //adj[i] = NULL;
    }

    void DFSUtil(bool visited[], int v);
    void DFS(int v);
    void BFS(int s);

    void addEdge(int v, int w)
    {
        if (v >= 0 && v < this->V &&
            w >= 0 && w < this->V) {
            edge* newEdge = new edge(w);
            if (this->adjList[v].next == NULL)
            {
                this->adjList[v].next = newEdge;
            }
            else
            {
                this->adjList[v].w->next = newEdge;
            }
            this->adjList[v].w = newEdge;
        }

        else
        {
            cout << "Error in adding edge!" << endl;
        }
    }

    bool hasCycleUtil(int v, bool visited[], bool* isRec) {
        if (visited[v] == false) {
            visited[v] = true;
            isRec[v] = true;
            edge* index = this->adjList[v].next;
            while (index != NULL) {
                if (!visited[index->vertex] && hasCycleUtil(index->vertex, visited, isRec))
                    return true;
                else if (isRec[index->vertex])
                    return true;
            }

        }
        isRec[v] = false;
        return false;
    }

    bool hasCycle() {
        bool* visited = new bool[V];
        bool* isRec = new bool[V];

        for (int i = 0; i < V; i++) {
            visited[i] = false;
            isRec[i] = false;
        }

        for (int i = 0; i < V; i++)
            if (!visited[i] && hasCycleUtil(i, visited, isRec))
                return true;

        return false;
    }

    /*void DFSUtil(int v, bool visited[]) {
        visited[v] = true;
        cout << v << " ";
        edge* i = adj[v];

        while (i != NULL)
            if (!visited[i->vertex])
                DFSUtil(i->vertex, visited);
        i++;
    }

    void DFS(int v) {
        bool* visited = new bool[V];

        for (int i = 0; i < V; i++)
            visited[i] = false;

        DFSUtil(v, visited);
    }*/
    /*void BFS(int s) {
        bool* visited = new bool[V];

        for (int i = 0; i < V; i++)
            visited[i] = false;

        Queue queue;
        visited[s] = true;
        queue.push_back(s);

        while (!queue.isEmpty()) {
            s = queue.peek();
            cout << s << " ";
            queue.pop_front();

            edge* i = adj[s];

            while(i != NULL) {
                if (!visited[i->vertex]) {
                    visited[i->vertex] = true;
                    queue.push_back(i->vertex);
                }
                i++;
            }
        }
    }*/

    void printGraph()
    {
        if (this->V > 0)
        {
            for (int i = 0; i < this->V; i++)
            {
                cout << "\nAdjacency list : " << i;
                edge* k = this->adjList[i].next;
                while (k != NULL)
                {
                    //display graph node
                    cout << " " << this->adjList[k->vertex].id;
                    //visit next edge
                    k = k->next;
                }
            }

        }
    }
};

void Graph::DFSUtil(bool visited[], int v)
{
    if (visited[v])
    {
        return;
    }
    visited[v] = true;
    cout << " " << v;
    edge* temp = this->adjList[v].next;
    while (temp != NULL)
    {
        this->DFSUtil(visited, temp->vertex);
        temp = temp->next;
    }
}

void Graph::DFS(int v)
{
    if (this->V <= 0 || v < 0 || v >= this->V)
    {
        return;
    }
    //node visitor
    bool visited[this->V];
    //no inital node visiting
    for (int i = 0; i < this->V; i++)
    {
        visited[i] = false;
    }
    //call the recursive helper function to print DFS traversal
    this->DFSUtil(visited, v);
}

void Graph::BFS(int s)
{
    if (s > this->V || this->V <= 0)
    {
        return;
    }
    Queue* queue = new Queue();
    edge* temp = NULL;
    //set false to each element
    bool visited[this->V];
    queue->pop_front();
    cout << "\n BFS :";
    while (queue->isEmpty() == false)
    {
        temp = this->adjList[queue->peek()].next;
        while (temp != NULL)
        {
            if (!visited[temp->vertex])
            {
                visited[temp->vertex] = true;
                queue->pop_front();
            }
            //visit next edge
            temp = temp->next;
        }
        visited[queue->peek()] = true;
        cout << " " << queue->peek();
        queue->push_back(s);
    }
}

int main() {

    Graph* graph = new Graph(5);
    graph->addEdge(1, 1);
    graph->addEdge(1, 7);
    graph->addEdge(2, 2);
    graph->addEdge(3, 2);
    graph->addEdge(4, 0);

    graph->printGraph();
    cout << "\nDepth first traversal for the given graph: " << endl;
    graph->DFS(3);
    cout << "\nBreadfth first traversal for the given graph: " << endl;
    graph->BFS(4);
    graph->hasCycle();

    return 0;
}
