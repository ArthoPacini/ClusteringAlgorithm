#ifndef CLUSTER_H_
#define CLUSTER_H_

#include "Vec3.h"
#include <vector>
#include <algorithm> 

class Cluster
{

public:

    std::vector<art::Vec3F> pontos;

    Cluster (){}

    void push_back(art::Vec3F p)
    {
        pontos.push_back(p);
    }

    void clear()
    {
        pontos.clear();
    }

    void erase(int i)
    {
        pontos.erase(pontos.begin() + i);
    }

    void erase(int i, int j)
    {
        pontos.erase(pontos.begin() + i,pontos.begin() + j);
    }

    art::Vec3F operator[](int i) const
    {
        return pontos[i];
    }
/*
    void organizeZ()
    {
        std::sort(pontos.begin(),
          pontos.end(),
          [](const art::Vector& lhs, const art::Vector& rhs)
            {
                return lhs.getZ() < rhs.getZ();
            });
    }

    void organizeX()
    {
        std::sort(pontos.begin(),
          pontos.end(),
          [](const art::Vector& lhs, const art::Vector& rhs)
            {
                return lhs.getX() < rhs.getX();
            });
    }
*/
    int size() const { return pontos.size(); }

    void organize()
    {
        std::sort(pontos.begin(),
          pontos.end(),
          [](const art::Vector<float>& lhs, const art::Vector<float>& rhs)
            {
                return (lhs.getX() + lhs.getY() + lhs.getZ()) < (rhs.getX() + rhs.getY() + rhs.getZ());
            });
    }

    void mostrar()
    {
        for(int i = 0; i < pontos.size(); i++)
        {
            std::cout << pontos[i].getX() << ", " << pontos[i].getY() << ", " << pontos[i].getZ() << std::endl;
        }
    }

    bool operator == (const Cluster &n) 
			{
                if(size() != n.size())
                    return false;

                for(int i = 0; i < pontos.size(); i++)
                {
                    if(pontos[i] != n[i])
                        return false;
                }

                return true;
			}

    bool operator != (const Cluster &n) 
    {
        return !(*this == n);
    }

    art::Vec3F calcularPontoGravidade()
    {
        art::Vec3F pontoGravidade(0.0, 0.0, 0.0);
        for(int i = 0; i < pontos.size(); i++)
        {
            pontoGravidade += pontos[i];
        }
        return (pontoGravidade / (int)pontos.size());
    }

};


#endif 