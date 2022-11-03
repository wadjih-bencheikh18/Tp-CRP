
#include <iostream>
#include <list>
#include <stack>
using namespace std;
 
class Graph {

    // nombre des sommets
    int V;
 
    // listes de contiguïté
    list<int>* adj;
 
    // Member Functions
    void fillOrder(int v, bool visit[],
                   stack<int>& pile);

    // a utiliser dans écrire DFS
    void DFSInt(int v, bool visit[]);
 
public:
    Graph(int V);
    void ajouterArete(int s1, int s2);
    void ecrireCFC();
    Graph transpose();
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
// Écrire DFS
void Graph::DFSInt(int v, bool visit[])
{
    // marquer le sommet comme visité
    visit[v] = true;
    cout << v << " ";
 
    // Parcourir tout les sommet adjacent de v
    list<int>::iterator i;
    for (i = adj[v].begin();
         i != adj[v].end(); ++i) {
 
        // si le sommet n'est pas visité
        if (!visit[*i])
            DFSInt(*i, visit);
    }
}
 
// La transposé du graph
Graph Graph::transpose()
{
    Graph g(V);
    for (int v = 0; v < V; v++) {

        // Parcourir tout les sommet adjacent de v
        list<int>::iterator i;
        for (i = adj[v].begin();
             i != adj[v].end(); ++i) {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}
 
// Ajouter un arête au graph
void Graph::ajouterArete(int s1, int s2)
{
    adj[s1].push_back(s2);
}
 
// Remplir la pile avec les sommets en ordre de fin de DFS
void Graph::fillOrder(int v, bool visit[],
                      stack<int>& pile)
{
    visit[v] = true;
 
    // Parcourir tout les sommet adjacent de v
    list<int>::iterator i;
 
    for (i = adj[v].begin();
         i != adj[v].end(); ++i) {
        if (!visit[*i]) {
            fillOrder(*i, visit, pile);
        }
    }
 
    // Si tous les sommets adjacents sont visités
    pile.push(v);
}
 
// Écriture des CFC
void Graph::ecrireCFC()
{
    stack<int> pile;
 
    // sommets visités
    bool* visit = new bool[V];
    for (int i = 0; i < V; i++)
        visit[i] = false;
 
    // empiler les sommets dans la pile
    for (int i = 0; i < V; i++)
        if (visit[i] == false)
            fillOrder(i, visit, pile);
 
    // la transpose de graph
    Graph gt = transpose();
 
    // marquer les sommets comme non visités
    for (int i = 0; i < V; i++)
        visit[i] = false;
 
    while (pile.empty() == false) {
 
        // dépiler un sommet de pile
        int v = pile.top();
        pile.pop();
 
        // Ecrire CFC de sommet dépiler
        if (visit[v] == false) {
            gt.DFSInt(v, visit);
            cout << endl;
        }
    }
}
 
int main()
{
    // Example de graphe
    Graph g(5);
    g.ajouterArete(1, 0);
    g.ajouterArete(0, 2);
    g.ajouterArete(2, 1);
    g.ajouterArete(0, 3);
    g.ajouterArete(3, 4);
 
    // Algorithm de Kosaraju
    g.ecrireCFC();
 
    return 0;
}