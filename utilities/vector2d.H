#ifndef _H_VECTOR2D
#define _H_VECTOR2D



#include<math.h>


class Vector2d
 {typedef int Boolean;
  enum {off, on};
  friend Vector2d operator+(const Vector2d&, const Vector2d&);
  friend Vector2d operator-(const Vector2d&, const Vector2d&);
  friend Vector2d operator*(const Vector2d&, const double);
  friend Vector2d operator*(const double, const Vector2d&);
  friend Vector2d operator/(const Vector2d&, const double);
  friend double DotProduct(const Vector2d&, const Vector2d&);
  friend Vector2d CrossProduct(const Vector2d&);
  friend Boolean operator==(const Vector2d&, const Vector2d&);
  friend Boolean operator!=(const Vector2d&, const Vector2d&);
  public:
    Vector2d(const double xin=0, const double yin=0);
    const Vector2d& SetVector2d(const double xin=0, const double yin=0);
    const Vector2d& operator+() const;
    Vector2d operator-() const;
    Vector2d& operator+=(const Vector2d&);
    Vector2d& operator-=(const Vector2d&);
    Vector2d& operator*=(const double);
    Vector2d& operator/=(const double);
    Vector2d Rotate(const double) const;
    double MagnitudeSquared() const;
    double Magnitude() const;
    int Quadrant() const;
    double Slope() const;
    double x, y;
 };


inline Vector2d::Vector2d(const double xin, const double yin): x(xin), y(yin) {}

inline const Vector2d& Vector2d::SetVector2d(const double xin, const double yin)
 {x=xin;
  y=yin;
  return *this;
 } 

inline const Vector2d& Vector2d::operator+() const
 {return *this;
 }

inline Vector2d Vector2d::operator-() const
 {return Vector2d(-x,-y);
 }

inline Vector2d& Vector2d::operator+=(const Vector2d& v)
 {x+=v.x;
  y+=v.y;
  return *this;
 }

inline Vector2d& Vector2d::operator-=(const Vector2d& v)
 {x-=v.x;
  y-=v.y;
  return *this;
 } 

inline Vector2d& Vector2d::operator*=(const double f)
 {x*=f;
  y*=f;
  return *this;
 }

inline Vector2d& Vector2d::operator/=(const double f)
 {x/=f;
  y/=f;
  return *this;
 }

inline Vector2d Vector2d::Rotate(const double angle) const 
 {return Vector2d(x*cos(angle)-y*sin(angle),y*cos(angle)+x*sin(angle));
 }

inline double Vector2d::MagnitudeSquared() const
 {return x*x+y*y;
 } 

inline double Vector2d::Magnitude() const
 {return sqrt(MagnitudeSquared());
 }

inline int Vector2d::Quadrant() const
 {if (x<0)
    if (y<0)
      return 3;
    else            
      return 2;
  else
    if (x==0)
      if (y<0)
        return 3;
      else
        if (y==0)
          return 0;
        else
          return 1;
    else
      if (y<0)
        return 4;
      else
        return 1;
 }

inline double Vector2d::Slope() const
 {return y/x;
 }

inline Vector2d operator+(const Vector2d& v1, const Vector2d& v2)
 {return Vector2d(v1.x+v2.x,v1.y+v2.y);
 }  

inline Vector2d operator-(const Vector2d& v1, const Vector2d& v2)
 {return Vector2d(v1.x-v2.x,v1.y-v2.y);
 }

inline Vector2d operator*(const Vector2d& v, const double f)
 {return Vector2d(v.x*f,v.y*f);
 }

inline Vector2d operator*(const double f, const Vector2d& v)
 {return Vector2d(f*v.x,f*v.y);
 }

inline Vector2d operator/(const Vector2d& v, const double f)
 {return Vector2d(v.x/f,v.y/f);
 }

inline double DotProduct(const Vector2d& v1, const Vector2d& v2)
 {return v1.x*v2.x+v1.y*v2.y;
 }

inline Vector2d CrossProduct(const Vector2d& v)
 {return Vector2d(v.y,-v.x);
 }

inline Vector2d::Boolean operator==(const Vector2d& v1, const Vector2d& v2)
 {return v1.x==v2.x&&v1.y==v2.y;
 }

inline Vector2d::Boolean operator!=(const Vector2d& v1, const Vector2d& v2)
 {return v1.x!=v2.x||v1.y!=v2.y;
 }



#endif
