#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#define infinit 10000

using namespace std;

struct Muchie{
    int xi,xf,cost;
};

int *tata,*d,*viz;

void Dijkstra(int sursa,int nrNoduri, int nrMuchii,vector<pair<int,int> > *la){
    tata=new int[nrNoduri+1];
    d=new int [nrNoduri+1];
    viz=new int [nrNoduri+1];
    for(int i=0;i<nrNoduri;i++){
        tata[i]=0;
        viz[i]=0;
        d[i]=infinit;
    }

    d[sursa]=0;
    priority_queue<pair<int,int>> myqueue;
    myqueue.push({-d[sursa],sursa});
    pair<int,int>nodCurent,y;

    while(!myqueue.empty()){
        nodCurent=myqueue.top();
        myqueue.pop();
        viz[nodCurent.second]++;
        if(viz[nodCurent.second]==1){ ///pentru a fi extras doar o data, fiind o coada de prioritati
                ///daca este extras o data nodul este clar ca este val minima

            for(int i=0;i<la[nodCurent.second].size();i++){
                y=la[nodCurent.second][i];
                if(d[y.first]>d[nodCurent.second]+y.second){
                    myqueue.push({-(d[nodCurent.second]+y.second),y.first});
                    d[y.first]=d[nodCurent.second]+y.second;
                    tata[y.first]=nodCurent.second;
                }
            }

        }
    }
}

int main()
{
    ifstream fin("grafpond.in");
    int nrNoduri, nrMuchii,x,y,cost;
    fin>>nrNoduri>>nrMuchii;
    vector<pair<int,int>> *la;
    la=new vector<pair<int,int> > [nrNoduri+1];
    for(int i=0;i<nrMuchii;i++){
        fin>>x>>y>>cost;
        la[x].push_back({y,cost});
        la[y].push_back({x,cost}); ///reprezentate asa
    }

    fin.close();

    Dijkstra(1,nrNoduri,nrMuchii,la);

    for(int i=0;i<=nrNoduri;i++){
        cout<<tata[i]<<" "<<d[i]<<endl;
    }
    cout<<"Destinatia?"<<endl;
    int destinatie,drumMinim=0;
    cin>>destinatie;

    while(tata[destinatie]!=0){
        cout<<destinatie<<" ";
        drumMinim+=d[destinatie];
        destinatie=tata[destinatie];
    }
    cout<<destinatie<<endl;

    drumMinim+=d[destinatie];
    cout<<"Drumul minim este "<<drumMinim<<endl;

    return 0;
}
