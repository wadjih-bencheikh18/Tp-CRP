#include <iostream>
#include <list>
#include <stack>
#define NIL -1
using namespace std;
 

class Graph {
    // nombre des sommets
    int V;
 
    // listes de contiguïté
    list<int>* adj;
 
    // a utiliser dans CFC
    void CFCInt(int s, int visit[],
                 int low[], stack<int>* pile,
                 bool empiler[]);
 
public:
    Graph(int V);
    void ajouterArete(int s1, int s2);
    void CFC();
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
// Ajouter un arête au graph
void Graph::ajouterArete(int s1, int s2)
{
    adj[s1].push_back(s2);
}
 
// trouver CFC en utilisant DFS
void Graph::CFCInt(int s, int visit[],
                    int low[], stack<int>* pile,
                    bool empiler[])
{
    static int t = 0;
 
    // Initialize temps et visit
    visit[s] = low[s] = ++t;
    pile->push(s);
    empiler[s] = true;
 
    // Parcourir tout les sommet adjacent de s
    list<int>::iterator i;
 
    for (i = adj[s].begin();
         i != adj[s].end(); ++i) {

        int v = *i;
 
        // si le sommet v n'est pas visité
        if (visit[v] == -1) {
            CFCInt(v, visit, low,
                    pile, empiler);
            low[s] = min(low[s], low[v]);
        }
 
        // MAJ temps si v est dans la pile
        else if (empiler[v] == true)
            low[s] = min(low[s], visit[v]);
    }
 
    // Écrire la CFC et vider la pile
    int sommet = 0;
    if (low[s] == visit[s]) {
        while (pile->top() != s) {
            sommet = (int)pile->top();
            pile->pop();
            empiler[sommet] = false;
            cout << sommet << " -> ";
        }
        sommet = (int)pile->top();
        pile->pop();
        empiler[sommet] = false;
        cout << sommet << "\n";
    }
}
 
// déterminer les CFC
void Graph::CFC()
{
    // temp de découverte
    int* visit = new int[V];
 
    // valeur de low-link
    int* low = new int[V];
 
    // si le sommets et deja empiler
    bool* empiler = new bool[V];
 
    // Pile des composantes fortement connexes
    stack<int>* pile = new stack<int>();
 
    // Initialiser les tableaux
    for (int i = 0; i < V; i++) {
        visit[i] = NIL;
        low[i] = NIL;
        empiler[i] = false;
    }
 
    // Trouver CFC dans la DFS
    for (int i = 0; i < V; i++) {
 
        // si n'est pas visité
        if (visit[i] == NIL) {
            CFCInt(i, visit, low,
                    pile, empiler);
        }
    }
}
 
int main()
{
    // Exemple de graph
    Graph g1(7);
    g1.ajouterArete(0, 1);
    g1.ajouterArete(1, 2);
    g1.ajouterArete(2, 0);
    g1.ajouterArete(1, 3);
    g1.ajouterArete(1, 4);
    g1.ajouterArete(1, 6);
    g1.ajouterArete(3, 5);
    g1.ajouterArete(4, 5);

    // Algorithm de Tarjan
    g1.CFC();
 
    return 0;
}