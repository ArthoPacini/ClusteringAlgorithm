#ifndef DISTANCE_H_
#define DISTANCE_H_ 

class Distance
{
    public:

    float distance;
    int num;

    Distance(float d, int n)
    {
        distance = d;
        num = n;
    }

    Distance(){}

    float getDistance(){return distance;}
    int getNum(){return num;}
    void setDistance(float d){distance = d; }
    void setNum(int n){num = n; }


};

#endif