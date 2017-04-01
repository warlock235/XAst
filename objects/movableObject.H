class MovableObject;

#include"../utilities/intersection2d.H"

#ifndef _MOVABLEOBJECT_H
#define _MOVABLEOBJECT_H

#include<X11/Xlib.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include"../utilities/box.H"
#include"../utilities/vector2d.H"
#include"../utilities/liner.H"
#include"../utilities/pixmaps/rotated/rotator.H"

class MovableObject
 {typedef int Boolean;
  enum {off, on};
  enum {miss, hit};
  friend class Intersector;

  public:
    MovableObject();
    MovableObject(const Vector2d& center, const double width, const double height,
                  const Vector2d& velocity, const double maxVelocity, const Vector2d& acceleration);
    virtual ~MovableObject();
    MovableObject&
    SetMovableObject(const Vector2d& center, const double width, const double height,
                     const Vector2d& velocity, const double maxVelocity, const Vector2d& acceleration);
    const Box& OldBox() const;
    Box& OldBox();
    const Box& CurrentBox() const;
    Box& CurrentBox();
    const Liner& ObjectLiner() const;
    Liner& ObjectLiner();
    MovableObject& SetToIntercept(const MovableObject& interceptee, const double objectVelocity);
    virtual Rotator& ObjectRotator();
    const Rotator& ObjectRotator() const;
    virtual void MissScript(Intersector&, const double createTime,
                                          const double existTime);
    virtual void HitScript(Intersector&, const double createTime,
                                         const double existTime, const Vector2d& intersectPoint);

  private:
    Box oldBox,
        currentBox;
    Liner objectLiner;

    MovableObject& SetPositionBoxes(const double);
    MovableObject& SetMoveBox();
    MovableObject& SetListIndex(const int);
    MovableObject& SetRemoveData(int* const);

    Box moveBox;
    int* removeList,
         numRemoveListItems,
         listIndex;
    Boolean collided;
    double createTime;
 };

inline MovableObject::
MovableObject()
 {
 }

inline MovableObject::~MovableObject()
 {
 }

inline MovableObject::
MovableObject(const Vector2d& center, const double width, const double height,
              const Vector2d& velocity, const double maxVelocity, const Vector2d& acceleration):
                                     oldBox(width,height,center),
                                     currentBox(oldBox),
                                     objectLiner(velocity,maxVelocity,acceleration)
 {
 }


inline MovableObject& MovableObject::
SetMovableObject(const Vector2d& center, const double width, const double height,
                 const Vector2d& velocity, const double maxVelocity, const Vector2d& acceleration)
 {oldBox.SetBox(width,height,center);
  currentBox=oldBox;
  objectLiner.SetLiner(velocity,maxVelocity,acceleration);
  return *this;
 }

inline const Box& MovableObject::OldBox() const
 {return oldBox;
 }

inline Box& MovableObject::OldBox()
 {return oldBox;
 }

inline const Box& MovableObject::CurrentBox() const
 {return currentBox;
 }

inline Box& MovableObject::CurrentBox()
 {return currentBox;
 }

inline const Liner& MovableObject::ObjectLiner() const
 {return objectLiner;
 }

inline Liner& MovableObject::ObjectLiner()
 {return objectLiner;
 }

inline MovableObject& MovableObject::SetToIntercept(const MovableObject& interceptee,
                                                    const double objectVelocity)
 {Vector2d objectDeltaVec(interceptee.currentBox.Center()-currentBox.Center());
  double maxVelSquared=objectVelocity*objectVelocity,
         numeratorLeft=-interceptee.objectLiner.XVelocity()*objectDeltaVec.x
                       -interceptee.objectLiner.YVelocity()*objectDeltaVec.y,
         temp=objectDeltaVec.x*interceptee.objectLiner.YVelocity()
              +objectDeltaVec.y*interceptee.objectLiner.XVelocity();
  temp=maxVelSquared*(objectDeltaVec.x*objectDeltaVec.x
                      +objectDeltaVec.y*objectDeltaVec.y)-temp*temp;
  Vector2d interceptVec;
  if (temp<0)
    interceptVec=interceptee.objectLiner.Move(interceptee.currentBox.Center(),1)
                 -currentBox.Center();
  else
   {double numeratorRight=sqrt(temp),
           denominator=interceptee.objectLiner.XVelocity()*interceptee.objectLiner.XVelocity()
                      +interceptee.objectLiner.YVelocity()*interceptee.objectLiner.YVelocity()
                      -maxVelSquared,
           time1=(numeratorLeft+numeratorRight)/denominator,
           time2=(numeratorLeft-numeratorRight)/denominator,
           timeToIntercept;
    if (time1>=0)
      if (time1<time2)
        timeToIntercept=time1;
      else
        if (time2>=0)
          timeToIntercept=time2;
        else
          timeToIntercept=time1;
    else
      timeToIntercept=time2;
    interceptVec=objectDeltaVec
                 +interceptee.objectLiner.Velocity()*timeToIntercept;
   }
  objectLiner.Velocity()=objectVelocity*interceptVec/interceptVec.Magnitude();
  return *this;
 }

Rotator& MovableObject::ObjectRotator()
 {cout<<endl<<"Reference made to nonexistent MovableObject::ObjectRotator virtual function.  Execution terminated."<<endl;
  abort();
  return *(Rotator*)NULL;
 }

inline const Rotator& MovableObject::ObjectRotator() const
 {return ((MovableObject*)this)->ObjectRotator();
 }

void MovableObject::MissScript(Intersector& i, const double createTime,
                                     const double existTime)
 {cout<<endl<<"Reference made to nonexistent MovableObject::MissScript virtual function.  Execution terminated."<<endl;
  abort();
 }

void MovableObject::HitScript(Intersector& i, const double createTime,
		                     const double existTime, const Vector2d& intersectPoint)
 {cout<<endl<<"Reference made to nonexistent MovableObject::HitScript virtual function.  Execution terminated."<<endl;
  abort();
 }

inline MovableObject& MovableObject::SetPositionBoxes(const double cTime)
 {createTime=cTime;
  oldBox=currentBox;
  currentBox.MoveBox(objectLiner.DeltaMove(1-cTime));
  return *this;
 }

inline MovableObject& MovableObject::SetMoveBox()
 {moveBox.SetBox(oldBox,currentBox);
  return *this;
 }

inline MovableObject& MovableObject::SetListIndex(const int lIndex)
 {listIndex=lIndex;
  return *this;
 }

inline MovableObject& MovableObject::SetRemoveData(int* const rLAddr)
 {removeList=rLAddr;
  numRemoveListItems=0;
  collided=miss;
  return *this;
 }

#endif
