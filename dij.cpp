// Implementação Lucas Camilo e Matheus Henrique

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Grafo
{
private:
  int nVertices;

  list< pair<int, int> > * vizinhos;

public:

  Grafo (int nVertices)
  {

    this->nVertices = nVertices;

    this->vizinhos = new list< pair <int, int> >[nVertices]; // Lista de pairs, vertice e custo

  }

  void toString()
  {



      for(int i = 0; i < nVertices ; i++)
    {
        cout << endl;
        cout << i << endl;

        for (auto j = vizinhos[i].begin(); j != vizinhos[i].end(); j++)
        {
          int v = j->first;
          int peso = j->second;
          cout << "vertice " << v << " peso " << peso << endl;
        }
        cout << "-------------------" << endl;
    }
  }

  void addAresta(int v1, int v2, int peso)
  {
    // Peso da aresta que sai de v1 até v2
    vizinhos[v1].push_back(make_pair(v2, peso));
  }

  int dij(int orig, int dest)
  {

    int dist[nVertices];
    int visitados[nVertices]; // salva vertices visitados

    /*
        distancia e vertice
        Para mudar de distancia maxima para distancia minima
    */

    priority_queue < pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > filaP;

    for (int cont = 0; cont < nVertices; cont++)
    {
      dist[cont] = INT_MAX;
      visitados[cont] = false;
    }
    dist[orig] = 0;

    filaP.push(make_pair (dist[orig], orig));

    while (!filaP.empty())
    {

      int vert = filaP.top().second; // pega o vertice do topo da fila
      filaP.pop();

      //visita vertice
        if(visitados[vert] == false)
        {
          // se não foi vizitado, percorrerá todos os vertices vizinhos de "vert"
          for(auto i = vizinhos[vert].begin(); i != vizinhos[vert].end(); i++)
          {
            int v = i->first;
            int peso = i->second;

            // se a nova distanca calculada  é menor do que a anterior
            if(dist[v] > (dist[v] + peso))
            {
              dist[v] = dist[vert] + peso;
              filaP.push(make_pair (dist[v], v));
            }
          }

          visitados[vert] = true;
        }

    }

    //distancia até o destino
    return dist[dest];
}

};

int quantVertices(ifstream & file);
void preencherLista(ifstream & file, Grafo & grafo);

int  main(int argc, char const *argv[])
{

  ifstream file;
  int vertices = quantVertices(file);

  Grafo grafo = Grafo(vertices);
  preencherLista(file, grafo);
  grafo.toString();

  int destino, origem;

  cout << "Digite apenas o vertice de origem" << endl;
  cout << "(valor está entre 0 e " << vertices - 1 << ")" << endl;
  cin >> origem;
  cout << endl <<"Digite apenas o vertice de destino" << endl;
  cin >> destino;
	cout << endl << grafo.dij(origem, destino) << endl;


  return 0;
}

int quantVertices(ifstream & file)
{

  file.open("grafo.txt");
  int numVertices = 0;

  if (file.is_open())
  {
    string maiorS1;
    string maiorS2;
    string lixo;

    while (getline(file, maiorS1, ' ') && getline(file, maiorS2, ' ') && getline(file, lixo))
    {
      int maiorI1 = stoi(maiorS1);
      int maiorI2 = stoi(maiorS2);

      if(maiorI1 > maiorI2 && maiorI1 > numVertices)
      {
        numVertices = maiorI1;
      } else if(maiorI2 > maiorI1 && maiorI2 > numVertices)
        numVertices = maiorI2;
    }

  }else{
    cout << "nao foi possivel abrir o arquivo" << endl;
  }
  file.close();

  return numVertices + 1;
}

void preencherLista(ifstream & file, Grafo & grafo)
{
  file.open("grafo.txt");

  if (file.is_open())
  {
    string orig;
    string dest;
    string peso;


    while (getline(file, orig, ' ') && getline(file, dest, ' ') && getline(file, peso))
    {
      int origem = stoi(orig);
      int destino = stoi(dest);
      int pesoV = stoi(peso);

      /*
        cout << "origem " << origem << endl;
        cout << "dest " << destino << endl;
        cout << "peso " << pesoV << endl << "---" << endl;
      */

      	grafo.addAresta(origem, destino, pesoV);
    }
  }else{
    cout << "nao foi possivel abrir o arquivo" << endl;
  }
  file.close();
}
