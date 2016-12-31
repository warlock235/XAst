#ifndef _LINER_H
#define _LINER_H


#include<math.h>
#include"vector2d.H"


class MaxLinerVecMag;
class LinerVec
 {friend class Liner;
  friend class MaxLinerVecMag;
  public:
    inline operator Vector2d() const;
    LinerVec& operator=(const LinerVec&);
    LinerVec& operator=(const Vector2d&);

  private:
    LinerVec();
    LinerVec(const LinerVec&);
    Vector2d linerVec;
    double linerVecMagnitude;
    MaxLinerVecMag* maxLinerVecMagAddr;
 };

class MaxLinerVecMag
 {friend class Liner;
  friend class LinerVec;
  public:
    inline operator double() const;
    MaxLinerVecMag& operator=(const MaxLinerVecMag&);
    MaxLinerVecMag& operator=(const double);

  private:
    MaxLinerVecMag();
    MaxLinerVecMag(const MaxLinerVecMag&);
    double maxLinerVecMagnitude;
    LinerVec* linerVecAddr;
 };

class Liner
 {public:
    Liner(const Vector2d& v=Vector2d(), const double m=0, const Vector2d& a=Vector2d());
    Liner(const Liner&);
    Liner& SetLiner(const Vector2d& v=Vector2d(), const double m=0, const Vector2d& a=Vector2d());
    Liner& operator=(const Liner&);
    const Vector2d& Velocity() const;
    const double& XVelocity() const;
    const double& YVelocity() const;
    const double& MaxVelocityMagnitude() const;
    const Vector2d& Acceleration() const;
    const double& MaxAccelerationMagnitude() const;
    const double& XAcceleration() const;
    const double& YAcceleration() const;
    LinerVec& Velocity();
    MaxLinerVecMag& MaxVelocityMagnitude();
    LinerVec& Acceleration();
    MaxLinerVecMag& MaxAccelerationMagnitude();
    const double& VelocityMagnitude() const;
    const double& AccelerationMagnitude() const;
    double DeltaXMove(const double) const;
    double DeltaYMove(const double) const;
    Vector2d DeltaMove(const double) const;
    double XMove(const double, const double) const;
    double YMove(const double, const double) const;
    Vector2d Move(const Vector2d&, const double) const;
    double TravelTime(const double) const;
    Liner& UpdateVelocity(const double);

  private:
    LinerVec velocity,
             acceleration;
    MaxLinerVecMag maxVelocityMagnitude,
                   maxAccelerationMagnitude;
 };

inline LinerVec::LinerVec() {}

inline LinerVec::operator Vector2d() const
 {return linerVec;
 }

inline LinerVec& LinerVec::operator=(const LinerVec& lv)
 {linerVec=lv.linerVec;
  linerVecMagnitude=lv.linerVecMagnitude;
  if (linerVecMagnitude>maxLinerVecMagAddr->maxLinerVecMagnitude)
   {linerVec=linerVec/linerVecMagnitude*maxLinerVecMagAddr->maxLinerVecMagnitude;
    linerVecMagnitude=maxLinerVecMagAddr->maxLinerVecMagnitude;
   }
  return *this;
 }

inline LinerVec& LinerVec::operator=(const Vector2d& v)
 {linerVec=v;
  linerVecMagnitude=linerVec.Magnitude();
  if (linerVecMagnitude>maxLinerVecMagAddr->maxLinerVecMagnitude)
   {linerVec=linerVec/linerVecMagnitude*maxLinerVecMagAddr->maxLinerVecMagnitude;
    linerVecMagnitude=maxLinerVecMagAddr->maxLinerVecMagnitude;
   }
  return *this;
 }

inline MaxLinerVecMag::MaxLinerVecMag() {}

inline MaxLinerVecMag::operator double() const
 {return maxLinerVecMagnitude;
 }

inline MaxLinerVecMag& MaxLinerVecMag::operator=(const MaxLinerVecMag& m)
 {maxLinerVecMagnitude=m.maxLinerVecMagnitude;
  if (linerVecAddr->linerVecMagnitude>maxLinerVecMagnitude)
   {linerVecAddr->linerVec=linerVecAddr->linerVec/linerVecAddr->linerVecMagnitude*maxLinerVecMagnitude;
    linerVecAddr->linerVecMagnitude=maxLinerVecMagnitude;
   }
  return *this;
 }

inline MaxLinerVecMag& MaxLinerVecMag::operator=(const double m)
 {maxLinerVecMagnitude=m;
  if (linerVecAddr->linerVecMagnitude>maxLinerVecMagnitude)
   {linerVecAddr->linerVec=linerVecAddr->linerVec/linerVecAddr->linerVecMagnitude*maxLinerVecMagnitude;
    linerVecAddr->linerVecMagnitude=maxLinerVecMagnitude;
   }
  return *this;
 }

inline Liner& Liner::SetLiner(const Vector2d& v, const double m, const Vector2d& a)
 {maxVelocityMagnitude.maxLinerVecMagnitude=maxAccelerationMagnitude.maxLinerVecMagnitude=m;
  velocity=v;
  acceleration=a;
  return *this;
 }

inline Liner::Liner(const Vector2d& v, const double m, const Vector2d& a)
 {velocity.maxLinerVecMagAddr=&maxVelocityMagnitude;
  maxVelocityMagnitude.linerVecAddr=&velocity;
  acceleration.maxLinerVecMagAddr=&maxAccelerationMagnitude;
  maxAccelerationMagnitude.linerVecAddr=&acceleration;
  SetLiner(v,m,a);
 }

inline Liner::Liner(const Liner& l)
 {velocity.maxLinerVecMagAddr=&maxVelocityMagnitude;
  maxVelocityMagnitude.linerVecAddr=&velocity;
  acceleration.maxLinerVecMagAddr=&maxAccelerationMagnitude;
  maxAccelerationMagnitude.linerVecAddr=&acceleration;
  velocity.linerVec=l.velocity.linerVec;
  velocity.linerVecMagnitude=l.velocity.linerVecMagnitude;
  maxVelocityMagnitude.maxLinerVecMagnitude=l.maxVelocityMagnitude.maxLinerVecMagnitude;
  acceleration.linerVec=l.acceleration.linerVec;
  acceleration.linerVecMagnitude=l.acceleration.linerVecMagnitude;
  maxAccelerationMagnitude.maxLinerVecMagnitude=l.maxAccelerationMagnitude.maxLinerVecMagnitude;
 }

inline Liner& Liner::operator=(const Liner& l)
 {velocity.linerVec=l.velocity.linerVec;
  velocity.linerVecMagnitude=l.velocity.linerVecMagnitude;
  maxVelocityMagnitude.maxLinerVecMagnitude=l.maxVelocityMagnitude.maxLinerVecMagnitude;
  acceleration.linerVec=l.acceleration.linerVec;
  acceleration.linerVecMagnitude=l.acceleration.linerVecMagnitude;
  maxAccelerationMagnitude.maxLinerVecMagnitude=l.maxAccelerationMagnitude.maxLinerVecMagnitude;
  return *this;
 }

inline const Vector2d& Liner::Velocity() const
 {return velocity.linerVec;
 }

inline const double& Liner::XVelocity() const
 {return velocity.linerVec.x;
 }

inline const double& Liner::YVelocity() const
 {return velocity.linerVec.y;
 }

inline const double& Liner::MaxVelocityMagnitude() const
 {return maxVelocityMagnitude.maxLinerVecMagnitude;
 }

inline const Vector2d& Liner::Acceleration() const
 {return acceleration.linerVec;
 }

inline const double& Liner::MaxAccelerationMagnitude() const
 {return maxAccelerationMagnitude.maxLinerVecMagnitude;
 }

inline const double& Liner::XAcceleration() const
 {return acceleration.linerVec.x;
 }

inline const double& Liner::YAcceleration() const
 {return acceleration.linerVec.y;
 }

inline LinerVec& Liner::Velocity()
 {return velocity;
 }

inline MaxLinerVecMag& Liner::MaxVelocityMagnitude()
 {return maxVelocityMagnitude;
 }

inline LinerVec& Liner::Acceleration()
 {return acceleration;
 }

inline MaxLinerVecMag& Liner::MaxAccelerationMagnitude()
 {return maxAccelerationMagnitude;
 }

inline const double& Liner::VelocityMagnitude() const
 {return velocity.linerVecMagnitude;
 }

inline const double& Liner::AccelerationMagnitude() const
 {return acceleration.linerVecMagnitude;
 }

inline double Liner::DeltaXMove(const double time) const
 {return acceleration.linerVec.x ? acceleration.linerVec.x*time*time/2
                                          +velocity.linerVec.x*time
                                       : velocity.linerVec.x*time;
 }

inline double Liner::DeltaYMove(const double time) const
 {return acceleration.linerVec.y ? acceleration.linerVec.y*time*time/2
                                          +velocity.linerVec.y*time
                                        : velocity.linerVec.y*time;
 }

inline Vector2d Liner::DeltaMove(const double time) const
 {return acceleration.linerVecMagnitude ? acceleration.linerVec*time*time/2
                                          +velocity.linerVec*time
                                        : velocity.linerVec*time;
 }

inline double Liner::XMove(const double position, const double time) const
 {return DeltaXMove(time)+position;
 }

inline double Liner::YMove(const double position, const double time) const
 {return DeltaYMove(time)+position;
 }

inline Vector2d Liner::Move(const Vector2d& position, const double time) const
 {return DeltaMove(time)+position;
 }

inline double Liner::TravelTime(const double deltaDistance) const
 {if (acceleration.linerVecMagnitude)
    return (sqrt(velocity.linerVecMagnitude*velocity.linerVecMagnitude
            +2*acceleration.linerVecMagnitude*deltaDistance)
            -velocity.linerVecMagnitude)/acceleration.linerVecMagnitude;
  else
    if (velocity.linerVecMagnitude)
      return deltaDistance/velocity.linerVecMagnitude;
    else
      // This constant is one year in seconds and should approximate
      // infinite time relative to this game without incurring any overflows.
      return 3.1576E7;
 }

inline Liner& Liner::UpdateVelocity(const double time)
 {velocity=velocity.linerVec+acceleration.linerVec*time;
  return *this;
 }
 
#endif
