#include "Vec3.h"
#include "Cluster.h"
#include "Distance.h"

#include <iostream>

#include <fstream>
#include <vector>
#include <string>
#include <chrono>

#include <ctime>


using namespace std;

int VerboseMode = 0;

float randomFloat(float j)
{
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/j));
}

void coutVectors(std::vector<art::Vec3F> & p)
{
    for(int i = 0; i < p.size(); i++)
    {
        std::cout << p[i].getX() << ", " << p[i].getY() << ", " << p[i].getZ() << std::endl;
    }
}

bool compareClusters(std::vector<Cluster> & a, std::vector<Cluster> & b)
{
    
    for(int i = 0; i < a.size(); i++)
    {
        if(a[i] != b[i])
            return false;
    }

    return true;
}

void calcularClusters(std::vector<Cluster> & clustersAntigos, std::vector<art::Vec3F> & p_gravidade, std::vector<art::Vec3F> pontos, int iteracao = 0);

void escreverArquivo(std::vector<Cluster> & clusters, std::vector<art::Vec3F> & p_gravidade, std::string nomeArquivo, float r = 1, float rG = 3)
{
    ofstream arquivoFinal(nomeArquivo.c_str());
    for(int i = 0; i < clusters.size(); i++)
    {
        for(int j = 0; j < clusters[i].size(); j++)
        {
            arquivoFinal << "ESFERA_CLUSTER_" << i << "_" << j << endl;
            arquivoFinal << clusters[i][j].getX() << endl;
            arquivoFinal << clusters[i][j].getY() << endl;
            arquivoFinal << clusters[i][j].getZ() << endl;
            arquivoFinal << r << endl;
        }
    }

    for(int i = 0; i < p_gravidade.size(); i++)
    {
        arquivoFinal << "PONTO_DE_GRAVIDADE_" << i << endl;
        arquivoFinal << p_gravidade[i].getX() << endl;
        arquivoFinal << p_gravidade[i].getY() << endl;
        arquivoFinal << p_gravidade[i].getZ() << endl;
        arquivoFinal << rG << endl;
    }

    arquivoFinal.close();
}

void removerClustersVazios(std::vector<Cluster> & clusters)
{
    for(int i = 0; i < clusters.size(); i++)
    {
        if(clusters[i].size() == 0)
            clusters.erase(clusters.begin() + i);
    }
}

int main()
{
    srand(time(NULL));
    int numeroDeClusters = 0;
    std::cout << "K-Means (Número de Clusters): ";
    std::cin >> numeroDeClusters;

    int numeroDePontos = 0;
    std::cout << "Número de pontos: ";
    std::cin >> numeroDePontos;

    float raio = 0.0;
    std::cout << "Raio dos pontos normais: ";
    std::cin >> raio;

    float raioG = 0.0;
    std::cout << "Raio dos pontos de gravidade: ";
    std::cin >> raioG;

    std::string nomeArquivoFinal;
    std::cout << "Nome do arquivo final: ";
    std::cin >> nomeArquivoFinal;

    std::string nomeArquivoInicial;
    std::cout << "Nome do arquivo inicial: ";
    std::cin >> nomeArquivoInicial;

    
    std::cout << "Verbose? 0 ou 1: ";
    std::cin >> VerboseMode;

    //Receber um numero K Means
    //receber um monte de pontos
    //Randomizar estes pontos numeroDeClusters vezes e criar numeroDeClusters pontos de gravidade aleatoriamente
    //criar numeroDeClusters grupos
    //calcular a distancia euclidiana de numeroDeClusters pontos de gravidade para todos os outros
    //ir trocando os pontos de grupos
    //recalcular os pontos
    //e trocar os pontos de grupos ate terminar

    vector<art::Vec3F> pontos;
    for(int i = 0; i < numeroDePontos; i++)
    {
        pontos.push_back(art::Vec3F(randomFloat(100), randomFloat(100), randomFloat(100)));
    }

    vector<art::Vec3F> p_gravidade; //guardar os pontos de gravidade
    {
        vector<art::Vec3F> clonePontos = pontos;
        for(int i = 0; i < numeroDeClusters; i++)
        {
            int j = rand() % (( clonePontos.size() + 1 )); 
            p_gravidade.push_back(clonePontos[j]);
            clonePontos.erase(clonePontos.begin()+j);
        }
    }

    if(VerboseMode==1)
    {
        cout << "[MOSTRANDO TODOS OS PONTOS]" << endl;
        coutVectors(pontos);
        cout << "\n[MOSTRANDO OS PONTOS DE GRAVIDADE]" << endl;
        coutVectors(p_gravidade);
        cout << "[FIM]" << endl;
    }
    
    
    std::vector<Cluster> clusters;
    for(int i = 0; i < numeroDeClusters; i++)
    {
        clusters.push_back(Cluster());
    }
    
    vector<Distance> distancias;
    for(int i = 0; i < pontos.size(); i++) //Iterar por todos os pontos
    {
        for(int j = 0; j < p_gravidade.size(); j++) //Iterar por todos os pontos de gravidade
        {
            distancias.push_back(Distance(p_gravidade[j].distance(pontos[i]), j));
        }

        //Encontrar a menor distância
        int m = distancias[0].getNum();
        float n = distancias[0].getDistance();
        for(int j = 0; j < distancias.size(); j++)
        {
            if(distancias[j].getDistance() < n)
            {
                n = distancias[j].getDistance();
                m = distancias[j].getNum();
            }
        }

        //Adicionar o ponto ao cluster de menor distância
        clusters[m].push_back(pontos[i]);

    }

    if(VerboseMode==1)
    {
        std::cout << "\n[MOSTRANDO OS CLUSTERS INICIAIS]\n" << std::endl;
        for(int i = 0; i < clusters.size(); i++)
        {
            std::cout << "Cluster: " << i << std::endl;
            clusters[i].mostrar();
            std::cout << std::endl;
        }
    }
    

    //Escreve arquivo inicial
    escreverArquivo(clusters, p_gravidade, nomeArquivoInicial, 3, 7.5);
    //Tempo inicial
    auto comecoAlgoritmoTempo = chrono::steady_clock::now();
    //Começa o calculo
    calcularClusters(clusters, p_gravidade, pontos);
    //Escreve a duração do algoritmo
    auto FinalAlgoritmoTempo = chrono::steady_clock::now();
    auto diferencaTempo = FinalAlgoritmoTempo - comecoAlgoritmoTempo;
    std::cout << "O algoritmo durou " << chrono::duration <double, milli> (diferencaTempo).count() << " ms" << std::endl;
    
    if(VerboseMode==1)
    {
        std::cout << "\n[MOSTRANDO OS CLUSTERS FINAIS]\n" << std::endl;
        for(int i = 0; i < clusters.size(); i++)
        {
            std::cout << "Cluster: " << i << std::endl;
            clusters[i].mostrar();
            std::cout << std::endl;
        }

        std::cout << "\n[MOSTRANDO OS PONTOS DE GRAVIDADE FINAIS]" << std::endl;
        coutVectors(p_gravidade);
    }
    
    
    
    //Escrever arquivo:
    escreverArquivo(clusters, p_gravidade, nomeArquivoFinal, 3, 7.5);
    


    return 0;
}

void calcularClusters(std::vector<Cluster> & clustersAntigos, std::vector<art::Vec3F> & p_gravidade, std::vector<art::Vec3F> pontos, int iteracao)
{
    std::cout << "Começando a iteraçao número " << iteracao << endl;

    if(VerboseMode==1)
        std::cout << "Clonando clusters... " << endl;
    

    std::vector<Cluster> clusters;
    for(int i = 0; i < clustersAntigos.size(); i++)
    {
        clusters.push_back(Cluster());
    }
    //recalcular os pontos de gravidade
    if(VerboseMode==1)
        std::cout << "Recalculando pontos de gravidade... " << endl;

    for(int i = 0; i < p_gravidade.size(); i++)
    {
        p_gravidade[i] = clustersAntigos[i].calcularPontoGravidade();
    }

    //iterar por todos os pontos
    //calcular cada ponto com cada ponto de gravidade
    //ver o menor tamanho
    //adicionar o ponto no respectivo cluster
    vector<Distance> distancias;
    for(int i = 0; i < pontos.size(); i++)
    {
        distancias.clear();
        //calcular cada ponto com cada ponto de gravidade
        for(int j = 0; j < p_gravidade.size(); j++)
        {
            distancias.push_back(Distance(p_gravidade[j].distance(pontos[i]), j));
        }

        int m = distancias[0].getNum();
        float n = distancias[0].getDistance();
        for(int j = 0; j < distancias.size(); j++)
        {
            if(distancias[j].getDistance() < n)
            {
                n = distancias[j].getDistance();
                m = distancias[j].getNum();
            }
        }

        clusters[m].push_back(pontos[i]);


    }
    
    bool calcularDeNovo = !compareClusters(clusters, clustersAntigos);
    if(calcularDeNovo)
    {
        clustersAntigos = clusters; 
        calcularClusters(clustersAntigos, p_gravidade, pontos, iteracao+1);
    }
        
    else
    {
        std::cout << "Término do programa" << std::endl;
        std::cout << "Foram iteradas " << iteracao << " vezes" << std::endl;
    }
        
    //ver se os clusters novos e antigos mudaram, caso mudarem calcular de novo!

}

