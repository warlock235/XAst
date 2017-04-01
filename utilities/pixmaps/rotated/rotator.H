#ifndef _ROTATOR_H
#define _ROTATOR_H

#include<math.h>
#include<X11/Xlib.h>
#include"rotatorDisplayData.H"

class AngVel
 {friend class Rotator;
  public:
    operator double() const;
    AngVel& operator=(const AngVel&);
    AngVel& operator=(const double);

  private:
    AngVel();
    AngVel(const AngVel&);
    double angularVelocity,
          maxAngularVelocity;
 };

class Rotator
 {public:
    Rotator(const double mav);
    Rotator(const RotatorDisplayData* const,
              const double angularVelocity,
              const double maxLinearVelocity);
    Rotator& SetRotator(const RotatorDisplayData* const rddAddr,
                    const double av);
    const Vector2d* const
      GetVecsAtTime(const double time) const;
    const int
      GetNumVecs() const;
    const Pixmap&
      GetPixAtTime(const double time) const;
    GC&
      GetMaskGCAtTime(const double time);
    const Box&
      GetPixBox() const;
    const int
      PixWidth() const;
    const int
      PixHeight() const;
    const double
      Radius() const;
    const double
      Area() const;
    const double
      Angle() const;
    const double
      AngularVelocity() const;
    const double
      MaxAngularVelocity() const;
    double&
      Angle();
    AngVel&
      AngularVelocity();
    Rotator&
      UpdateAngle(const double time);
    Rotator&
      UpdateMaxLinearVelocity(const double maxLinearVelocity);
  private:
    const RotatorDisplayData* rotData;
    AngVel angularVelocity;
    double angle;
 };

inline AngVel::AngVel()
 {
 }

inline AngVel::operator double() const
 {return angularVelocity;
 }

inline AngVel& AngVel::operator=(const AngVel& av)
 {angularVelocity=av.angularVelocity;
  if (fabs(angularVelocity)>maxAngularVelocity)
    angularVelocity=angularVelocity<0 ? -maxAngularVelocity
                                      : maxAngularVelocity;
  return *this;
 }

inline AngVel& AngVel::operator=(const double fav)
 {angularVelocity=fav;
  if (fabs(angularVelocity)>maxAngularVelocity)
    angularVelocity=angularVelocity<0 ? -maxAngularVelocity
                                      : maxAngularVelocity;
  return *this;
 }

inline Rotator::Rotator(const double mav): rotData(NULL),
                                           angle(0)
 {angularVelocity.maxAngularVelocity=mav;
  angularVelocity.angularVelocity=0;
 }

inline Rotator::Rotator(const RotatorDisplayData* const rddAddr,
                        const double av,
			const double mlv): rotData(rddAddr),
                                          angle(0)
 {angularVelocity.maxAngularVelocity=mlv/(4*rotData->GetRadius());
  angularVelocity=av;
 }

inline Rotator& Rotator::SetRotator(const RotatorDisplayData* const rddAddr,
                                    const double av)
 {rotData=rddAddr;
  angle=0;
  angularVelocity=av;
  return *this;
 }

inline const Vector2d* const
Rotator::GetVecsAtTime(const double time) const
 {return rotData->GetVecs(angle+angularVelocity.angularVelocity*time);
 }

inline const int
Rotator::GetNumVecs() const
 {return rotData->GetNumVecs();
 }

inline const Pixmap&
Rotator::GetPixAtTime(const double time) const
 {return rotData->GetPixmap(angle+angularVelocity.angularVelocity*time);
 }

inline GC&
Rotator::GetMaskGCAtTime(const double time)
 {return rotData->GetGC(angle+angularVelocity.angularVelocity*time);
 }

inline const Box&
Rotator::GetPixBox() const
{return rotData->GetBox();
 }

inline const int
Rotator::PixWidth() const
 {return rotData->GetPixWidth();
 }

inline const int
Rotator::PixHeight() const
 {return rotData->GetPixHeight();
 }

inline const double
Rotator::Radius() const
 {return rotData->GetRadius();
 }

inline const double
Rotator::Area() const
 {return rotData->GetArea();
 }

inline const double
Rotator::Angle() const
 {return angle;
 }

inline const double
Rotator::AngularVelocity() const
 {return angularVelocity.angularVelocity;
 }

inline const double
Rotator::MaxAngularVelocity() const
 {return angularVelocity.maxAngularVelocity;
 }

inline double&
Rotator::Angle()
 {return angle;
 }

inline AngVel&
Rotator::AngularVelocity()
 {return angularVelocity;
 }

inline Rotator&
Rotator::UpdateAngle(const double time)
 {angle=fmod(angle+angularVelocity.angularVelocity*time,6.28318530717958);
  return *this;
 }

inline Rotator&
Rotator::UpdateMaxLinearVelocity(const double maxLinearVelocity)
 {angularVelocity.maxAngularVelocity=maxLinearVelocity/(4*rotData->GetRadius());
  angularVelocity=angularVelocity.angularVelocity;
  return *this;
 }

#endif
