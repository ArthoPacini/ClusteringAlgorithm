#ifndef VECTOR3_H_
#define VECTOR3_H_
 
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdint>
 
namespace art
{
    template<typename T>
    class Vector
    {
        private:
            T x, y, z;
        public:
            Vector():
                x(0.0), y(0.0), z(0.0){}
            Vector(const T &n):
                x(n), y(n), z(n){}
            Vector(const T &s, const T &t, const T &u):
                x(s), y(t), z(u){}
            T getX() const { return x; }
            T getY() const { return y; }
            T getZ() const { return z; }
            Vector<T> operator + (const T &n) const
            {
                return Vector<T>(x+n, y+n, z+n);
            }
            Vector<T> operator + (const Vector<T> &n) const
            {
                return Vector<T>(x+n.x, y+n.y, z+n.z);
            }
            Vector<T> operator - (const T &n) const
            {
                return Vector<T>(x-n, y-n, z-n);
            }
            Vector<T> operator - (const Vector<T> &n) const
            {
                return Vector<T>(x-n.x,y-n.y,z-n.z);
            }
            Vector<T> operator * (const T &n) const
            {
                return Vector<T>(x*n, y*n, z*n);
            }
            Vector<T> operator * (const Vector<T> &n) const
            {
                return Vector<T>(x*n.x, y*n.y, z*n.z);
            }
            Vector<T> operator / (const T &n) const
            {
                if(n < 0)
                {
                    std::cerr << "Error: divide by zero." << std::endl;
                    exit(101);
                }
                return Vector<T>(x/n,y/n,z/n);
            }
            Vector<T> operator / (const Vector<T> &n) const
            {
                if(n.x < 0 || n.y < 0 || n.z < 0)
                {
                    std::cerr << "Error: divide by zero." << std::endl;
                    exit(101);
                }
                return Vector<T>(x/n.x,y/n.y,z/n.z);
            }
            Vector<T> operator += (const T &n)
            {
                return Vector<T>(x += n, y += n,z += n);
            }
            Vector<T> operator += (const Vector<T> &n)
            {
                return Vector<T>(x += n.x, y += n.y, z += n.z);
            }
            bool operator == (const Vector<T> &n)
			{
                return (x == n.x and y == n.y and z == n.z);
			}
            bool operator != (const Vector<T> &n)
			{
                return !(x == n.x and y == n.y and z == n.z);
			}
            friend std::ostream & operator << (std::ostream &os, const Vector<T> &v)
            {
                os << +v.x << " " << +v.y << " " << +v.z;
                return os;
            }
            T dotProduct(const Vector<T> &v) const
            {
                return (x*v.x + y*v.y + z*v.z);
            }
            Vector<T> crossProduct(const Vector<T> &v) const
            {
                return Vector<T>((y*v.z) - (z*v.y),
                                 (z*v.x) - (x*v.z),
                                 (x*v.y) - (y*v.x));
            }
            T magnitude(void) const
            {
                return sqrt(x*x + y*y + z*z);
            }
            Vector<T> &normalize(void)
            {
                T magInv = 1/magnitude();
                x*=magInv, y*=magInv, z*=magInv;
                return *this;
            }
            T sum() const
            {
                return x+y+z;
            }

            float distance(const Vector<T> &v) const
            {
                return sqrt((x-v.x)*(x-v.x) + (y-v.y)*(y-v.y) + (z-v.z)*(z-v.z)); 
            }
           
    };
   
    typedef Vector<float> Vec3F;
    typedef Vector<double> Vec3D;
    typedef Vector<int> Vec3i;
    typedef Vector<unsigned char> Vec3UC;
}
   
   
#endif