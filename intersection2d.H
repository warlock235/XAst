class Intersector;

#ifndef _INTERSECTION2D_H
#define _INTERSECTION2D_H

#include<math.h>
#include<new>
#include"linkedArray.H"
#include"vector2d.H"
#include"box.H"
#include"liner.H"
#include"movableObject.H"

class IntersectorItem
 {typedef int Boolean;
  enum {off, on};
  friend class LinkedArrayItem<IntersectorItem>;
  friend class Intersector;

  friend IntersectorItem::Boolean
           operator!=(const IntersectorItem&,
                      const IntersectorItem&);
  friend IntersectorItem::Boolean
           operator<(const IntersectorItem&,
                     const IntersectorItem&);
  friend IntersectorItem::Boolean
           operator<=(const IntersectorItem&,
                      const IntersectorItem&);
  friend IntersectorItem::Boolean
           operator>(const IntersectorItem&,
                     const IntersectorItem&);

 private:

    IntersectorItem();
    IntersectorItem(const IntersectorItem&);
    IntersectorItem(Intersector* const,
                    MovableObject* const,
                    MovableObject* const,
                    const double intersectTime);
    static Boolean (IntersectorItem::*const StateFunction[3])();
    Boolean CircleIntersector();
    Boolean UnitIntersector();
    Boolean FinalIntersector();
    Boolean NextState();
    int state;
    Intersector* intersector;
    MovableObject* obj1,
                 * obj2;
    Vector2d center1,
             center2,
             centerDistance,
             intersectPoint;
    Liner obj1TimeNormalizedLiner,
          obj2TimeNormalizedLiner;
    double radiusSum,
           intersectTime;
 };

class Intersector
 {typedef int Boolean;
  enum {off, on};
  friend class IntersectorItem;

  public:
    Intersector(LinkedArray<MovableObject*>&,
                 LinkedArray<MovableObject*>&,
                 LinkedArray<MovableObject*>&);
    ~Intersector();
    Intersector&
      Intersect();
    Intersector&
      AddNonPermeable(MovableObject* const,
                      const double startTime);
    Intersector&
      AddSelfPermeable(MovableObject* const,
                       const double startTime);
    Intersector&
      AddPermeable(MovableObject* const,
                   const double startTime);
    Intersector&
      RemoveNonPermeable(MovableObject* const);
    Intersector&
      RemoveSelfPermeable(MovableObject* const);
    Intersector&
      RemovePermeable(MovableObject* const);

  private:
    static Boolean
      SidesPassEachOther(const double acceleration,
                         const double negativeVelocity,
                         const double distance,
                         const double frameEndTime,
                         double& sideIntersectTime);
    static Boolean
      SidesIntersect(const double side1Low,
                     const double side1High,
                     const double side2Low,
                     const double side2High);
    static Boolean
      Quad1BoxIntersect(const MovableObject&,
                        const MovableObject&,
                        const double frameEndTime,
                        double& intersectTime);
    static Boolean
      Quad2BoxIntersect(const MovableObject&,
                        const MovableObject&,
                        const double frameEndTime,
                        double& intersectTime);
    static Boolean
      Quad3BoxIntersect(const MovableObject&,
                        const MovableObject&,
                        const double frameEndTime,
                        double& intersectTime);
    static Boolean
      Quad4BoxIntersect(const MovableObject&,
                        const MovableObject&,
                        const double frameEndTime,
                        double& intersectTime);
    static Boolean
      (*const BoxIntersect[4])(const MovableObject&,
                               const MovableObject&,
                               const double frameEndTime,
			       double& intersectTime);
    void
      AddNonPerm(MovableObject* const,
                 const double startTime);
    void
      AddSelfPerm(MovableObject* const,
                  const double startTime);
    void
      AddPerm(MovableObject* const,
              const double startTime);
    inline const double
      ObjectCreateTime(const MovableObject* const) const;
    inline Intersector&
      Miss(MovableObject* const);
    inline Intersector&
      Hit(MovableObject* const,
          const double intersectTime,
          const Vector2d& intersectPoint);
    Boolean
      SetIntersectorItem(MovableObject* const,
                         MovableObject* const,
                         const double);
    LinkedArray<MovableObject*>* nonPermeableAddr;
    LinkedArray<MovableObject*>* selfPermeableAddr;
    LinkedArray<MovableObject*>* permeableAddr;
    LinkedArray<IntersectorItem>* intersectList;
    int** removeLists,
          numRemoveLists,
       ** recycledRemoveLists,
          numRecycledRemoveLists;
    Boolean intersecting;
 };

IntersectorItem::Boolean
(IntersectorItem::*const IntersectorItem::StateFunction[3])()=
                        {&IntersectorItem::CircleIntersector,
                         &IntersectorItem::UnitIntersector,
                         &IntersectorItem::FinalIntersector};

inline IntersectorItem::IntersectorItem() {}

inline IntersectorItem::
IntersectorItem(Intersector* const objLists,
                MovableObject* const o1,
                MovableObject* const o2,
                const double iTime): state(0),
                                     intersector(objLists),
                                     obj1(o1),
                                     obj2(o2),
                                     center1(obj1->ObjectLiner().Move(
                                             obj1->OldBox().Center(),
                                             iTime-objLists->ObjectCreateTime(obj1))),
                                     center2(obj2->ObjectLiner().Move(
                                             obj2->OldBox().Center(),
                                             iTime-objLists->ObjectCreateTime(obj2))),
                                     centerDistance(center2-center1),
                                     obj1TimeNormalizedLiner(obj1->ObjectLiner()),
                                     obj2TimeNormalizedLiner(obj2->ObjectLiner()),
                                     intersectTime(iTime)
 {obj1TimeNormalizedLiner.UpdateVelocity(intersectTime
                                        -objLists->ObjectCreateTime(obj1));
  obj2TimeNormalizedLiner.UpdateVelocity(intersectTime
                                        -objLists->ObjectCreateTime(obj2));
 }

inline IntersectorItem::Boolean
operator!=(const IntersectorItem& item1,
           const IntersectorItem& item2)
 {return item1.intersectTime!=item2.intersectTime;
 }

inline IntersectorItem::Boolean
operator<(const IntersectorItem& item1,
          const IntersectorItem& item2)
 {return item1.intersectTime<item2.intersectTime;
 }

inline IntersectorItem::Boolean
operator<=(const IntersectorItem& item1,
           const IntersectorItem& item2)
 {return item1.intersectTime<=item2.intersectTime;
 }

inline IntersectorItem::Boolean
operator>(const IntersectorItem& item1,
          const IntersectorItem& item2)
 {return item1.intersectTime>item2.intersectTime;
 }

IntersectorItem::Boolean
IntersectorItem::
CircleIntersector()
 {double centerDistMag=centerDistance.Magnitude();
  radiusSum=obj1->ObjectRotator().Radius()+obj2->ObjectRotator().Radius();
  if (centerDistMag>radiusSum)
   {double deltaDist=centerDistMag-radiusSum,
           velocityMag=obj1TimeNormalizedLiner.VelocityMagnitude()
                      +obj2TimeNormalizedLiner.VelocityMagnitude(),
           accelerationMag=obj1TimeNormalizedLiner.AccelerationMagnitude()
                          +obj2TimeNormalizedLiner.AccelerationMagnitude(),
           timeIncrement;
    if (accelerationMag)
      timeIncrement=(sqrt(velocityMag*velocityMag+2*accelerationMag*deltaDist)
                     -velocityMag)/accelerationMag;
    else
      if (velocityMag)
        timeIncrement=deltaDist/velocityMag;
      else
       {intersector->intersectList->RemoveAndSetNext();
        return off;
       }
    intersectTime+=timeIncrement;
    if (intersectTime>=1)
     {intersector->intersectList->RemoveAndSetNext();
      return off;
     }
    else
     {center1=obj1->ObjectLiner().Move(obj1->OldBox().Center(),
                                 intersectTime-intersector->ObjectCreateTime(obj1));
      center2=obj2->ObjectLiner().Move(obj2->OldBox().Center(),
                                 intersectTime-intersector->ObjectCreateTime(obj2));
      centerDistance=center2-center1;
      if (centerDistance.MagnitudeSquared()<centerDistMag*centerDistMag)
       {obj1TimeNormalizedLiner.UpdateVelocity(timeIncrement);
        obj2TimeNormalizedLiner.UpdateVelocity(timeIncrement);
       }
      else
       {intersector->intersectList->RemoveAndSetNext();
        return off;
       }
     }
   }
  return on;
 }

IntersectorItem::Boolean
IntersectorItem::
UnitIntersector()
 {enum IncrementType{noAcceleration,
                     obj1Acceleration,
                     obj2Acceleration,
                     obj12Acceleration};
  IncrementType incrementIndicator;
  double oldCDistSqrd,
         cDistSqrd=centerDistance.MagnitudeSquared(),
         rSumSqrd=radiusSum*radiusSum,
         timeIncrement,
         timeIncrement1,
         timeIncrement2;
  Vector2d centerIncrement1,
           centerIncrement2;
  if (!obj2TimeNormalizedLiner.AccelerationMagnitude())
    if (!obj1TimeNormalizedLiner.AccelerationMagnitude())
     {incrementIndicator=noAcceleration;
      timeIncrement=obj1TimeNormalizedLiner.TravelTime(.5);
      timeIncrement2=obj2TimeNormalizedLiner.TravelTime(.5);
      if (timeIncrement>timeIncrement2)
        timeIncrement=timeIncrement2;
      centerIncrement1=obj1TimeNormalizedLiner.DeltaMove(timeIncrement);
      centerIncrement2=obj2TimeNormalizedLiner.DeltaMove(timeIncrement);
     }
    else
     {incrementIndicator=obj1Acceleration;
      timeIncrement2=obj2TimeNormalizedLiner.TravelTime(.5);
      centerIncrement2=obj2TimeNormalizedLiner.DeltaMove(timeIncrement2);
     }
  else
    if (!obj1TimeNormalizedLiner.AccelerationMagnitude())
     {incrementIndicator=obj2Acceleration;
      timeIncrement1=obj1TimeNormalizedLiner.TravelTime(.5);
      centerIncrement1=obj1TimeNormalizedLiner.DeltaMove(timeIncrement1);
     }
    else
      incrementIndicator=obj12Acceleration;
  do
   {oldCDistSqrd=cDistSqrd;
    const Vector2d* const obj1VecAddr=obj1->ObjectRotator().GetVecsAtTime(intersectTime
                                      -intersector->ObjectCreateTime(obj1)),
                  * const obj2VecAddr=obj2->ObjectRotator().GetVecsAtTime(intersectTime
                                      -intersector->ObjectCreateTime(obj2));
    for (int i=0;i<obj1->ObjectRotator().GetNumVecs();++i)
     {Vector2d obj1Point1=obj1VecAddr[i]+center1,
               obj1Point2=obj1VecAddr[i+1==obj1->ObjectRotator().GetNumVecs() ? 0
                                                                              : i+1]
                          +center1;
      double obj1XDiff=obj1Point2.x-obj1Point1.x,
             obj1YDiff,
             obj1YInterceptNumerator;
      Boolean obj1SlopeExists;
      if (fabs(obj1XDiff)<.5)
       {obj1SlopeExists=off;
        intersectPoint.x=(obj1Point1.x+obj1Point2.x)/2;
       }
      else
       {obj1SlopeExists=on;
        obj1YDiff=obj1Point2.y-obj1Point1.y;
        obj1YInterceptNumerator=obj1Point2.x*obj1Point1.y
                                -obj1Point1.x*obj1Point2.y;
       }
      for (int j=0;j<obj2->ObjectRotator().GetNumVecs();++j)
       {Vector2d obj2Point1=obj2VecAddr[j]+center2,
                 obj2Point2=obj2VecAddr[j+1==obj2->ObjectRotator().GetNumVecs() ? 0
                                                                                : j+1]
                            +center2;
        double obj2XDiff=obj2Point2.x-obj2Point1.x;
        if (fabs(obj2XDiff)<.5)
          if (obj1SlopeExists)
	         {intersectPoint.x=(obj2Point1.x+obj2Point2.x)/2;
            intersectPoint.y=(obj1YDiff*intersectPoint.x
                              +obj1YInterceptNumerator)/obj1XDiff;
	         }
          else
            continue;
        else
	       {double obj2YDiff=obj2Point2.y-obj2Point1.y;
          if (obj1SlopeExists)
	         {double slopeDiffNumerator=obj2XDiff*obj1YDiff-obj1XDiff*obj2YDiff;
            if (slopeDiffNumerator)
	           {intersectPoint.x=(obj1XDiff*(obj2Point2.x*obj2Point1.y
                                           -obj2Point1.x*obj2Point2.y)
                                -obj2XDiff*obj1YInterceptNumerator)
                               /slopeDiffNumerator;
              intersectPoint.y=(obj1YDiff*intersectPoint.x
                                +obj1YInterceptNumerator)/obj1XDiff;
	           }
            else
              continue;
	         }
          else
            intersectPoint.y=(obj2YDiff*intersectPoint.x
                              +obj2Point2.x*obj2Point1.y
                              -obj2Point1.x*obj2Point2.y)
                             /obj2XDiff;
         }
        if ((obj1Point1.x<obj1Point2.x
             ? intersectPoint.x>=obj1Point1.x&&
               intersectPoint.x<=obj1Point2.x
             : intersectPoint.x>=obj1Point2.x&&
               intersectPoint.x<=obj1Point1.x)&&
            (obj1Point1.y<obj1Point2.y
             ? intersectPoint.y>=obj1Point1.y&&
               intersectPoint.y<=obj1Point2.y
             : intersectPoint.y>=obj1Point2.y&&
               intersectPoint.y<=obj1Point1.y)&&
            (obj2Point1.x<obj2Point2.x
             ? intersectPoint.x>=obj2Point1.x&&
               intersectPoint.x<=obj2Point2.x
             : intersectPoint.x>=obj2Point2.x&&
               intersectPoint.x<=obj2Point1.x)&&
            (obj2Point1.y<obj2Point2.y
             ? intersectPoint.y>=obj2Point1.y&&
               intersectPoint.y<=obj2Point2.y
             : intersectPoint.y>=obj2Point2.y&&
               intersectPoint.y<=obj2Point1.y))
          return on;
       }
     }
    switch (incrementIndicator)
     {case noAcceleration:
        center1+=centerIncrement1;
        center2+=centerIncrement2;
        break;
      case obj1Acceleration:
        timeIncrement1=obj1TimeNormalizedLiner.TravelTime(.5);
        if (timeIncrement1<timeIncrement2)
	       {timeIncrement=timeIncrement1;
          center2+=obj2TimeNormalizedLiner.DeltaMove(timeIncrement);
	       }
        else
	       {timeIncrement=timeIncrement2;
          center2+=centerIncrement2;
	       }
        center1+=obj1TimeNormalizedLiner.DeltaMove(timeIncrement);
        break;
      case obj2Acceleration:
        timeIncrement2=obj2TimeNormalizedLiner.TravelTime(.5);
        if (timeIncrement1<timeIncrement2)
	       {timeIncrement=timeIncrement1;
          center1+=centerIncrement1;
	       }
        else
	       {timeIncrement=timeIncrement2;
          center1+=obj1TimeNormalizedLiner.DeltaMove(timeIncrement);
	       }
        center2+=obj2TimeNormalizedLiner.DeltaMove(timeIncrement);
        break;
      case obj12Acceleration:
        timeIncrement1=obj1TimeNormalizedLiner.TravelTime(.5);
        timeIncrement2=obj2TimeNormalizedLiner.TravelTime(.5);
        if (timeIncrement1<timeIncrement2)
          timeIncrement=timeIncrement1;
        else
          timeIncrement=timeIncrement2;
        center1+=obj1TimeNormalizedLiner.DeltaMove(timeIncrement);
        center2+=obj2TimeNormalizedLiner.DeltaMove(timeIncrement);
     }
    intersectTime+=timeIncrement;
    obj1TimeNormalizedLiner.UpdateVelocity(timeIncrement);
    obj2TimeNormalizedLiner.UpdateVelocity(timeIncrement);
    cDistSqrd=(center2-center1).MagnitudeSquared();
   }
  while ((cDistSqrd<rSumSqrd || cDistSqrd<oldCDistSqrd) && intersectTime<1);
  intersector->intersectList->RemoveAndSetNext();
  return off;
 }

IntersectorItem::Boolean
IntersectorItem::
FinalIntersector()
 {MovableObject* iObj1=obj1,
               * iObj2=obj2;
  Vector2d iPoint(intersectPoint);
  double iTime=intersectTime;
  intersector->intersectList->RemoveAndSetNext();
  intersector->Hit(iObj1,iTime,iPoint)
              .Hit(iObj2,iTime,iPoint);
  return off;
 }

inline IntersectorItem::Boolean
IntersectorItem::
NextState()
 {return (this->*StateFunction[state++])();
 }

Intersector::Boolean
(*const Intersector::BoxIntersect[4])(const MovableObject&,
                                      const MovableObject&,
                                      const double frameEndTime,
	                                    double& intersectTime)={Quad1BoxIntersect, Quad2BoxIntersect,
                                                              Quad3BoxIntersect, Quad4BoxIntersect};

inline Intersector::
Intersector(LinkedArray<MovableObject*>& nonPermeable,
            LinkedArray<MovableObject*>& selfPermeable,
            LinkedArray<MovableObject*>& permeable): nonPermeableAddr(&nonPermeable),
                                                     selfPermeableAddr(&selfPermeable),
                                                     permeableAddr(&permeable),
                                                     intersecting(off)
 {intersectList=new LinkedArray<IntersectorItem>((nonPermeableAddr->GetNumAvailableItems()
                                                 *nonPermeableAddr->GetNumAvailableItems()
                                                 -nonPermeableAddr->GetNumAvailableItems())/2
                                                +nonPermeableAddr->GetNumAvailableItems()
                                                *selfPermeableAddr->GetNumAvailableItems());
  int numIntersectingItems=nonPermeableAddr->GetNumAvailableItems()
                           +selfPermeableAddr->GetNumAvailableItems();
  removeLists=new int*[numIntersectingItems];
  for(int i=0;i<numIntersectingItems;++i)
    removeLists[i]=new int[numIntersectingItems-1];
  recycledRemoveLists=new int*[numIntersectingItems];
 }

inline Intersector::
~Intersector()
 {delete [] recycledRemoveLists;
  for(int i=nonPermeableAddr->GetNumAvailableItems()
            +selfPermeableAddr->GetNumAvailableItems();i--;)
    delete [] removeLists[i];
  delete [] removeLists;
  delete intersectList;
 }

inline Intersector::Boolean
Intersector::
SidesPassEachOther(const double acceleration,
                   const double negativeVelocity,
                   const double distance,
                   const double frameEndTime,
                   double& sideIntersectTime)
 {if (!acceleration)
   {if (negativeVelocity)
     {sideIntersectTime=distance/negativeVelocity;
      return sideIntersectTime>=0&&sideIntersectTime<frameEndTime;
     }
   }
  else
   {double sqrtArg=negativeVelocity*negativeVelocity-2*acceleration*distance;
    if (sqrtArg>=0)
     {double radical=sqrt(sqrtArg);
      sideIntersectTime=(negativeVelocity+radical)/acceleration;
      if (sideIntersectTime>=0&&sideIntersectTime<frameEndTime)
        return on;
      else
       {sideIntersectTime=(negativeVelocity-radical)/acceleration;
        return sideIntersectTime>=0&&sideIntersectTime<frameEndTime;
       }
     }
   };
  return off;
 };

inline Intersector::Boolean
Intersector::
SidesIntersect(const double side1Low,
               const double side1High,
               const double side2Low,
               const double side2High)
 {return side1Low>=side2Low&&side1Low<=side2High||
         side1High>=side2Low&&side1High<=side2High||
         side2Low>=side1Low&&side2Low<=side1High;
 }

Intersector::Boolean
Intersector::
Quad1BoxIntersect(const MovableObject& movableObj1,
                  const MovableObject& movableObj2,
                  const double frameEndTime,
                  double& intersectTime)
 {double deltaDist1,
         deltaDist2;
  return SidesPassEachOther(movableObj2.ObjectLiner().XAcceleration()
                           -movableObj1.ObjectLiner().XAcceleration(),
                            movableObj1.ObjectLiner().XVelocity()
                           -movableObj2.ObjectLiner().XVelocity(),
                            movableObj2.OldBox().WestSide()
                           -movableObj1.OldBox().EastSide(),
                            frameEndTime,
                            intersectTime)&&
          (deltaDist1=movableObj1.ObjectLiner().DeltaYMove(intersectTime),
           deltaDist2=movableObj2.ObjectLiner().DeltaYMove(intersectTime),
           SidesIntersect(movableObj1.OldBox().NorthSide()+deltaDist1,
                          movableObj1.OldBox().SouthSide()+deltaDist1,
                          movableObj2.OldBox().NorthSide()+deltaDist2,
                          movableObj2.OldBox().SouthSide()+deltaDist2))||
         SidesPassEachOther(movableObj2.ObjectLiner().YAcceleration()
                           -movableObj1.ObjectLiner().YAcceleration(),
                            movableObj1.ObjectLiner().YVelocity()
                           -movableObj2.ObjectLiner().YVelocity(),
                            movableObj2.OldBox().NorthSide()
                           -movableObj1.OldBox().SouthSide(),
                            frameEndTime,
                            intersectTime)&&
          (deltaDist1=movableObj1.ObjectLiner().DeltaXMove(intersectTime),
           deltaDist2=movableObj2.ObjectLiner().DeltaXMove(intersectTime),
           SidesIntersect(movableObj1.OldBox().WestSide()+deltaDist1,
                          movableObj1.OldBox().EastSide()+deltaDist1,
                          movableObj2.OldBox().WestSide()+deltaDist2,
                          movableObj2.OldBox().EastSide()+deltaDist2));
 }

Intersector::Boolean
Intersector::
Quad2BoxIntersect(const MovableObject& movableObj1,
                  const MovableObject& movableObj2,
                  const double frameEndTime,
                  double& intersectTime)
 {double deltaDist1,
         deltaDist2;
  return SidesPassEachOther(movableObj2.ObjectLiner().XAcceleration()
                           -movableObj1.ObjectLiner().XAcceleration(),
                            movableObj1.ObjectLiner().XVelocity()
                           -movableObj2.ObjectLiner().XVelocity(),
                            movableObj2.OldBox().EastSide()
                           -movableObj1.OldBox().WestSide(),
                            frameEndTime,
                            intersectTime)&&
          (deltaDist1=movableObj1.ObjectLiner().DeltaYMove(intersectTime),
           deltaDist2=movableObj2.ObjectLiner().DeltaYMove(intersectTime),
           SidesIntersect(movableObj1.OldBox().NorthSide()+deltaDist1,
                          movableObj1.OldBox().SouthSide()+deltaDist1,
                          movableObj2.OldBox().NorthSide()+deltaDist2,
                          movableObj2.OldBox().SouthSide()+deltaDist2))||
         SidesPassEachOther(movableObj2.ObjectLiner().YAcceleration()
                           -movableObj1.ObjectLiner().YAcceleration(),
                            movableObj1.ObjectLiner().YVelocity()
                           -movableObj2.ObjectLiner().YVelocity(),
                            movableObj2.OldBox().NorthSide()
                           -movableObj1.OldBox().SouthSide(),
                            frameEndTime,
                            intersectTime)&&
          (deltaDist1=movableObj1.ObjectLiner().DeltaXMove(intersectTime),
           deltaDist2=movableObj2.ObjectLiner().DeltaXMove(intersectTime),
           SidesIntersect(movableObj1.OldBox().WestSide()+deltaDist1,
                          movableObj1.OldBox().EastSide()+deltaDist1,
                          movableObj2.OldBox().WestSide()+deltaDist2,
                          movableObj2.OldBox().EastSide()+deltaDist2));
 }

Intersector::Boolean
Intersector::
Quad3BoxIntersect(const MovableObject& movableObj1,
                  const MovableObject& movableObj2,
                  const double frameEndTime,
                  double& intersectTime)
 {double deltaDist1,
         deltaDist2;
  return SidesPassEachOther(movableObj2.ObjectLiner().XAcceleration()
                           -movableObj1.ObjectLiner().XAcceleration(),
                            movableObj1.ObjectLiner().XVelocity()
                           -movableObj2.ObjectLiner().XVelocity(),
                            movableObj2.OldBox().EastSide()
                           -movableObj1.OldBox().WestSide(),
                            frameEndTime,
                            intersectTime)&&
          (deltaDist1=movableObj1.ObjectLiner().DeltaYMove(intersectTime),
           deltaDist2=movableObj2.ObjectLiner().DeltaYMove(intersectTime),
           SidesIntersect(movableObj1.OldBox().NorthSide()+deltaDist1,
                          movableObj1.OldBox().SouthSide()+deltaDist1,
                          movableObj2.OldBox().NorthSide()+deltaDist2,
                          movableObj2.OldBox().SouthSide()+deltaDist2))||
         SidesPassEachOther(movableObj2.ObjectLiner().YAcceleration()
                           -movableObj1.ObjectLiner().YAcceleration(),
                            movableObj1.ObjectLiner().YVelocity()
                           -movableObj2.ObjectLiner().YVelocity(),
                            movableObj2.OldBox().SouthSide()
                           -movableObj1.OldBox().NorthSide(),
                            frameEndTime,
                            intersectTime)&&
          (deltaDist1=movableObj1.ObjectLiner().DeltaXMove(intersectTime),
           deltaDist2=movableObj2.ObjectLiner().DeltaXMove(intersectTime),
           SidesIntersect(movableObj1.OldBox().WestSide()+deltaDist1,
                          movableObj1.OldBox().EastSide()+deltaDist1,
                          movableObj2.OldBox().WestSide()+deltaDist2,
                          movableObj2.OldBox().EastSide()+deltaDist2));
 }

Intersector::Boolean
Intersector::
Quad4BoxIntersect(const MovableObject& movableObj1,
                  const MovableObject& movableObj2,
                  const double frameEndTime,
                  double& intersectTime)
 {double deltaDist1,
         deltaDist2;
  return SidesPassEachOther(movableObj2.ObjectLiner().XAcceleration()
                           -movableObj1.ObjectLiner().XAcceleration(),
                            movableObj1.ObjectLiner().XVelocity()
                           -movableObj2.ObjectLiner().XVelocity(),
                            movableObj2.OldBox().WestSide()
                           -movableObj1.OldBox().EastSide(),
                            frameEndTime,
                            intersectTime)&&
          (deltaDist1=movableObj1.ObjectLiner().DeltaYMove(intersectTime),
           deltaDist2=movableObj2.ObjectLiner().DeltaYMove(intersectTime),
           SidesIntersect(movableObj1.OldBox().NorthSide()+deltaDist1,
                          movableObj1.OldBox().SouthSide()+deltaDist1,
                          movableObj2.OldBox().NorthSide()+deltaDist2,
                          movableObj2.OldBox().SouthSide()+deltaDist2))||
         SidesPassEachOther(movableObj2.ObjectLiner().YAcceleration()
                           -movableObj1.ObjectLiner().YAcceleration(),
                            movableObj1.ObjectLiner().YVelocity()
                           -movableObj2.ObjectLiner().YVelocity(),
                            movableObj2.OldBox().SouthSide()
                           -movableObj1.OldBox().NorthSide(),
                            frameEndTime,
                            intersectTime)&&
          (deltaDist1=movableObj1.ObjectLiner().DeltaXMove(intersectTime),
           deltaDist2=movableObj2.ObjectLiner().DeltaXMove(intersectTime),
           SidesIntersect(movableObj1.OldBox().WestSide()+deltaDist1,
                          movableObj1.OldBox().EastSide()+deltaDist1,
                          movableObj2.OldBox().WestSide()+deltaDist2,
                          movableObj2.OldBox().EastSide()+deltaDist2));
 }

inline Intersector::Boolean
Intersector::
SetIntersectorItem(MovableObject* const movableObj1,
                   MovableObject* const movableObj2,
                   const double startTime)
 {if (::Intersect(movableObj1->moveBox,movableObj2->moveBox))
  {if (::Intersect(movableObj1->OldBox(),movableObj2->OldBox()))
     {new(&intersectList->GetData())
         IntersectorItem(this,movableObj1,movableObj2,startTime);
      return on;
     }
    else
     {double intersectTime;
      if (BoxIntersect[(movableObj2->OldBox().Center()
                       -movableObj1->OldBox().Center()).Quadrant()-1]
            (*movableObj1,*movableObj2,1-startTime,intersectTime))
       {new(&intersectList->GetData())
           IntersectorItem(this,movableObj1,movableObj2,
                                         startTime+intersectTime);
        return on;
       }
     }
   }
  return off;
 }

inline Intersector&
Intersector::
Intersect()
 {numRemoveLists=numRecycledRemoveLists=0;
  nonPermeableAddr->SetCurrentAtHead();
  for (int i=0;i<nonPermeableAddr->GetNumItems();++i)
   {nonPermeableAddr->GetData()->SetPositionBoxes(0).SetMoveBox()
                     .SetListIndex(nonPermeableAddr->GetItemIndex())
                     .SetRemoveData(removeLists[numRemoveLists++]);
    nonPermeableAddr->Next();
   }
  selfPermeableAddr->SetCurrentAtHead();
  for (int i=0;i<selfPermeableAddr->GetNumItems();++i)
   {selfPermeableAddr->GetData()->SetPositionBoxes(0).SetMoveBox()
                      .SetListIndex(selfPermeableAddr->GetItemIndex())
                      .SetRemoveData(removeLists[numRemoveLists++]);
    selfPermeableAddr->Next();
   }
  permeableAddr->SetCurrentAtHead();
  for (int i=0;i<permeableAddr->GetNumItems();++i)
   {permeableAddr->GetData()->SetPositionBoxes(0)
                  .SetListIndex(permeableAddr->GetItemIndex());
    permeableAddr->Next();
   }
  nonPermeableAddr->SetCurrentAtHead();
  intersectList->SetCurrentAtItem(0);
  for (int j=0,k=0;j<nonPermeableAddr->GetNumItems();++j)
   {int itemIndex=nonPermeableAddr->GetItemIndex();
    MovableObject* moveItemAddr=nonPermeableAddr->GetData();
    for (int i=j+1;i<nonPermeableAddr->GetNumItems();++i)
      if (SetIntersectorItem(moveItemAddr,nonPermeableAddr->Next().GetData(),0))
       {moveItemAddr->removeList[moveItemAddr->numRemoveListItems++]=k;
        nonPermeableAddr->GetData()
                        ->removeList[nonPermeableAddr->GetData()
                                                     ->numRemoveListItems++]=k;
        intersectList->SetInitialLink().SetCurrentAtItem(++k);
       }
    selfPermeableAddr->SetCurrentAtHead();
    for (int i=0;i<selfPermeableAddr->GetNumItems();++i)
     {if (SetIntersectorItem(moveItemAddr,selfPermeableAddr->GetData(),0))
       {moveItemAddr->removeList[moveItemAddr->numRemoveListItems++]=k;
        selfPermeableAddr->GetData()
                         ->removeList[selfPermeableAddr->GetData()
                                                       ->numRemoveListItems++]=k;
        intersectList->SetInitialLink().SetCurrentAtItem(++k);
       }
      selfPermeableAddr->Next();
     }
    nonPermeableAddr->SetCurrentAtItem(itemIndex).Next();
   }
  intersectList->Sort().SetListLinks();
  intersecting=on;
  while (intersectList->GetNumItems())
   {IntersectorItem* headAddr=&intersectList->SetCurrentAtHead()
                                             .SetMoveSource().GetData();
    if (headAddr->NextState()&&*headAddr>intersectList->Next().GetData())
     {while (*headAddr>intersectList->Next().GetData());
      intersectList->Prior().MoveNext();
     }
   }
  intersecting=off;
  nonPermeableAddr->SetCurrentAtHead();
  for (int i=0,
           numItems=nonPermeableAddr->GetNumItems();i<numItems;++i)
   {if (!nonPermeableAddr->GetData()->collided)
      Miss(nonPermeableAddr->GetData());
    nonPermeableAddr->Next();
   }
  selfPermeableAddr->SetCurrentAtHead();
  for (int i=0,
           numItems=selfPermeableAddr->GetNumItems();i<numItems;++i)
   {if (!selfPermeableAddr->GetData()->collided)
      Miss(selfPermeableAddr->GetData());
    selfPermeableAddr->Next();
   }
  permeableAddr->SetCurrentAtHead();
  for (int i=0,
           numItems=permeableAddr->GetNumItems();i<numItems;++i)
   {Miss(permeableAddr->GetData());
    permeableAddr->Next();
   }
  return *this;
 }

inline void
Intersector::
AddNonPerm(MovableObject* const addObj,
           const double startTime)
 {(nonPermeableAddr->SetCurrentAtHole().GetData()=addObj)
  ->SetListIndex(nonPermeableAddr->SetCurrentAtHead()
                 .AddPrior().Prior().GetItemIndex());
  if(intersecting)
   {addObj->SetPositionBoxes(startTime).SetMoveBox()
           .SetRemoveData(numRecycledRemoveLists
                          ? recycledRemoveLists[--numRecycledRemoveLists]
                          : removeLists[numRemoveLists++]);
    intersectList->SetCurrentAtHole();
    for (int i=1;i<nonPermeableAddr->GetNumItems();++i)
      if (SetIntersectorItem(addObj,nonPermeableAddr->Next().GetData(),startTime))
       {addObj->removeList[addObj->numRemoveListItems++]=intersectList->GetItemIndex();
        nonPermeableAddr->GetData()
                        ->removeList[nonPermeableAddr->GetData()
                                                     ->numRemoveListItems++]=
                          intersectList->GetItemIndex();
        IntersectorItem* addItem=&intersectList->GetData();
        if (!intersectList->GetNumItems()||
            *addItem<=intersectList->SetCurrentAtHead().GetData())
          intersectList->AddPrior().SetCurrentAtHole();
        else
         {for (int j=1;j<intersectList->GetNumItems();++j)
            if (*addItem<=intersectList->Next().GetData())
              break;
          intersectList->Prior().AddNext().SetCurrentAtHole();
         }
       }
    selfPermeableAddr->SetCurrentAtHead();
    for (int i=0;i<selfPermeableAddr->GetNumItems();++i)
     {if (SetIntersectorItem(addObj,selfPermeableAddr->GetData(),startTime))
       {addObj->removeList[addObj->numRemoveListItems++]=intersectList->GetItemIndex();
        selfPermeableAddr->GetData()
                         ->removeList[selfPermeableAddr->GetData()
                                                       ->numRemoveListItems++]=
                           intersectList->GetItemIndex();
        IntersectorItem* addItem=&intersectList->GetData();
        if (!intersectList->GetNumItems()||
            *addItem<=intersectList->SetCurrentAtHead().GetData())
          intersectList->AddPrior().SetCurrentAtHole();
        else
         {for (int j=1;j<intersectList->GetNumItems();++j)
             if (*addItem<=intersectList->Next().GetData())
               break;
          intersectList->Prior().AddNext().SetCurrentAtHole();
         }
       }
      selfPermeableAddr->Next();
     }
   }
 }

inline Intersector&
Intersector::
AddNonPermeable(MovableObject* const addObj,
                const double startTime)
 {if (nonPermeableAddr->GetNumItems())
   {int listPosition=nonPermeableAddr->GetItemIndex();
    AddNonPerm(addObj,startTime);
    nonPermeableAddr->SetCurrentAtItem(listPosition);
   }
  else
    AddNonPerm(addObj,startTime);
  return *this;
 }

inline void
Intersector::
AddSelfPerm(MovableObject* const addObj,
            const double startTime)
 {(selfPermeableAddr->SetCurrentAtHole().GetData()=addObj)
  ->SetListIndex(selfPermeableAddr->SetCurrentAtHead()
                 .AddPrior().Prior().GetItemIndex());
  if (intersecting)
   {addObj->SetPositionBoxes(startTime).SetMoveBox()
           .SetRemoveData(numRecycledRemoveLists
                          ? recycledRemoveLists[--numRecycledRemoveLists]
                          : removeLists[numRemoveLists++]);
    intersectList->SetCurrentAtHole();
    nonPermeableAddr->SetCurrentAtHead();
    for (int i=0;i<nonPermeableAddr->GetNumItems();++i)
     {if (SetIntersectorItem(nonPermeableAddr->GetData(),addObj,startTime))
       {nonPermeableAddr->GetData()
                        ->removeList[nonPermeableAddr->GetData()
                                                     ->numRemoveListItems++]=
                        intersectList->GetItemIndex();
        addObj->removeList[addObj->numRemoveListItems++]=intersectList->GetItemIndex();
        IntersectorItem* addItem=&intersectList->GetData();
        if (!intersectList->GetNumItems()||
            *addItem<=intersectList->SetCurrentAtHead().GetData())
          intersectList->AddPrior().SetCurrentAtHole();
        else
         {for (int j=1;j<intersectList->GetNumItems();++j)
            if (*addItem<=intersectList->Next().GetData())
              break;
          intersectList->Prior().AddNext().SetCurrentAtHole();
         }
       }
      nonPermeableAddr->Next();
     }
   }
 }

inline Intersector&
Intersector::
AddSelfPermeable(MovableObject* const addObj,
                 const double startTime)
 {if (selfPermeableAddr->GetNumItems())
   {int listPosition=selfPermeableAddr->GetItemIndex();
    AddSelfPerm(addObj,startTime);
    selfPermeableAddr->SetCurrentAtItem(listPosition);
   }
  else
    AddSelfPerm(addObj,startTime);
  return *this;
 }

inline void
Intersector::
AddPerm(MovableObject* const addObj,
        const double startTime)
 {(permeableAddr->SetCurrentAtHole().GetData()=addObj)
  ->SetListIndex(permeableAddr->SetCurrentAtHead()
                 .AddPrior().Prior().GetItemIndex());
  if (intersecting)
    addObj->SetPositionBoxes(startTime);
 }

inline Intersector&
Intersector::
AddPermeable(MovableObject* const addObj,
             const double startTime)
 {if (permeableAddr->GetNumItems())
   {int listPosition=permeableAddr->GetItemIndex();
    AddPerm(addObj,startTime);
    permeableAddr->SetCurrentAtItem(listPosition);
   }
  else
    AddPerm(addObj,startTime);
  return *this;
 }

inline Intersector&
Intersector::
RemoveNonPermeable(MovableObject* const remObj)
 {if (intersecting)
   {while (remObj->numRemoveListItems)
     {IntersectorItem* remItem=&intersectList->SetCurrentAtItem(remObj->
                                                 removeList[--remObj->numRemoveListItems])
                                              .GetData();
      if (remItem->obj1==remObj||remItem->obj2==remObj)
        intersectList->RemoveAndSetNext();
     }
    recycledRemoveLists[numRecycledRemoveLists++]=remObj->removeList;
   }
  nonPermeableAddr->SetCurrentAtItem(remObj->listIndex).RemoveAndSetPrior();
  return *this;
 }

inline Intersector&
Intersector::
RemoveSelfPermeable(MovableObject* const remObj)
 {if (intersecting)
   {while (remObj->numRemoveListItems)
     {IntersectorItem* remItem=&intersectList->SetCurrentAtItem(remObj->
                                                 removeList[--remObj->numRemoveListItems])
                                              .GetData();
      if (remItem->obj1==remObj||remItem->obj2==remObj)
        intersectList->RemoveAndSetNext();
     }
    recycledRemoveLists[numRecycledRemoveLists++]=remObj->removeList;
   }
  selfPermeableAddr->SetCurrentAtItem(remObj->listIndex).RemoveAndSetPrior();
  return *this;
 }

inline Intersector&
Intersector::
RemovePermeable(MovableObject* const remObj)
 {permeableAddr->SetCurrentAtItem(remObj->listIndex).RemoveAndSetPrior();
  return *this;
 }

inline const double
Intersector::
ObjectCreateTime(const MovableObject* const movObj) const
 {return movObj->createTime;
 }

inline Intersector&
Intersector::
Miss(MovableObject* const missObj)
 {missObj->MissScript(*this,missObj->createTime,1-missObj->createTime);
  return *this;
 }

inline Intersector&
Intersector::
Hit(MovableObject* const hitObj,
    const double intersectTime,
    const Vector2d& intersectPoint)
 {hitObj->collided=MovableObject::hit;
  hitObj->HitScript(*this,hitObj->createTime,
                          intersectTime-hitObj->createTime,intersectPoint);
  return *this;
 }

#endif
