#include<stdlib.h>
#include<X11/Xlib.h>
#include"vector2d.H"
#include"box.H"
#include"rotatorDisplayData.H"
#include"rotator.H"
#include"frameList.H"
#include"frameTimer.H"
#include"movableObject.H"
#include"intersection2d.H"
#include"bullet.H"
#include"explosion.H"
#include"stage.H"
#include"shipBulletDecor.xbm"

#ifndef _SHIPBULLETGROUP_H
#define _SHIPBULLETGROUP_H

class ShipBulletGroup;
class ShipBullet: public Bullet
 {friend class ShipBulletGroup;
  public:
    ShipBullet(BulletExplosion* const);
    virtual void MissScript(Intersector&, const double createTime,
                                          const double existTime);
    virtual void HitScript(Intersector&, const double createTime,
                                         const double existTime,
                                         const Vector2d& intersectPoint);
    static int numFrames;

    static double velocity;

 private:

    void PositionBullet(Intersector&, const double creationTime);

 };

class ShipBulletGroup
 {friend class ShipBullet;

  public:
    typedef int Boolean;
    enum {off, on};

    ShipBulletGroup();
    inline void Fire(Intersector& intersector,
                     const double creationTime);
    inline void Reset();
    inline void ResetVelocity(const double newVelocity);
    inline void ResetVelocityLimits(const double newVelocityLimit);
    inline void ResetBulletDuration(const int newDuration);
    inline void AdjustFramesPerSec(const double frameRatio);

    Boolean fireThisFrame;

    static Boolean autoFire;

    static int numBullets;

  private:

    static const Vector2d vectors[4];

    static XColor color;

    NonRotVectorData graphic;

    Rotator rotator;

    ShipBullet bullet1,
               bullet2,
               bullet3,
               bullet4,
               bullet5,
               bullet6,
               bullet7,
               bullet8,
               bullet9,
               bullet10,
               bullet11,
               bullet12,
               bullet13,
               bullet14,
               bullet15,
               bullet16;

    BulletExplosion explosion1,
                    explosion2,
                    explosion3,
                    explosion4,
                    explosion5,
                    explosion6,
                    explosion7,
                    explosion8,
                    explosion9,
                    explosion10,
                    explosion11,
                    explosion12,
                    explosion13,
                    explosion14,
                    explosion15,
                    explosion16;

    FrameTimer reloadTimer;

 };

extern ShipBulletGroup shipBulletGroup;

#include"playingField.H"

int ShipBullet::numFrames=28;

double ShipBullet::velocity=.57*PlayingField::maxLinearVelocity;

inline ShipBullet::ShipBullet(BulletExplosion* const explosion): Bullet(&shipBulletGroup.rotator,
									                                                      numFrames, explosion)
 {
 }

void ShipBullet::MissScript(Intersector& intersector, const double createTime,
                                                   const double existTime)
 {playingField.framesSinceLastBullet=0;
  if (frameTimer.TimerAlarm())
   {intersector.RemoveNonPermeable(this);
    inactive=on;
   }
  else
   {if (PlayingField::universalGravitationalConst)
      ObjectLiner().UpdateVelocity(existTime);
    XCopyArea(stage.display,
              rotator->GetPixAtTime(0),
              playingField.pixmap,
              playingField.gc,
              0,0,
              rotator->PixWidth(),
              rotator->PixHeight(),
              CurrentBox().WrapMovingBox(PlayingField::playArea,
                                         ObjectLiner().Velocity())
                          .NorthWestCorner().x+.5,
              CurrentBox().NorthWestCorner().y+.5);
   }
 }

void ShipBullet::HitScript(Intersector& intersector, const double createTime,
                                                  const double existTime,
                                                  const Vector2d& intersectPoint)
 {intersector.RemoveNonPermeable(this);
  explosion->CurrentBox().MoveBox(intersectPoint
                                 -explosion->CurrentBox().Center());
  explosion->frameList.Reset();
  explosion->frameTimer.Reset();
  intersector.AddPermeable(explosion,createTime+existTime);
  if (playingField.lastHitScore)
   {score.CurrentScore()+=playingField.lastHitScore;
    playingField.lastHitScore=0;
   }
  else
    playingField.lastHitFromAlly=!playingField.lastHitFromAlly;
 }

inline void ShipBullet::PositionBullet(Intersector& intersector,
                                       const double creationTime)
 {Vector2d shipNose=shipGroup.ship->ObjectRotator().GetVecsAtTime(0)[0],
           velocityDirection=shipNose/shipNose.Magnitude();
  CurrentBox().MoveBox(shipNose+shipGroup.ship->CurrentBox().Center()
                       +ObjectRotator().Radius()*velocityDirection
                       +velocityDirection/2
                       -CurrentBox().Center());
  ObjectLiner().Velocity()=shipGroup.ship->ObjectLiner().Velocity()
                           +velocity*velocityDirection;
  inactive=off;
  intersector.AddNonPermeable(this,creationTime);
  XCopyArea(stage.display,
            rotator->GetPixAtTime(0),
            playingField.pixmap,
            playingField.gc,
            0,0,
            rotator->PixWidth(),
            rotator->PixHeight(),
            CurrentBox().WrapMovingBox(PlayingField::playArea,
                                       ObjectLiner().Velocity())
                        .NorthWestCorner().x+.5,
            CurrentBox().NorthWestCorner().y+.5);
  frameTimer.Reset().TimerAlarm();
 }

ShipBulletGroup::Boolean ShipBulletGroup::autoFire=off;

int ShipBulletGroup::numBullets=4;

const Vector2d ShipBulletGroup::vectors[4]={Vector2d(0,-2),
                                            Vector2d(2,0),
                                            Vector2d(0,2),
                                            Vector2d(-2,0)};

XColor ShipBulletGroup::color={0,
                               65535,//255
                               0,
                               0,
                               DoRed|DoGreen|DoBlue};

inline ShipBulletGroup::ShipBulletGroup(): fireThisFrame(off),
                                           graphic(stage.display,stage.window,color,
                                                   vectors,sizeof(vectors)/sizeof(Vector2d),
                                                   shipBulletDecor_bits,
                                                   shipBulletDecor_width,shipBulletDecor_height),
                                           rotator(&graphic,0,PlayingField::maxLinearVelocity),
                                           bullet1(&explosion1),
                                           bullet2(&explosion2),
                                           bullet3(&explosion3),
                                           bullet4(&explosion4),
                                           bullet5(&explosion5),
                                           bullet6(&explosion6),
                                           bullet7(&explosion7),
                                           bullet8(&explosion8),
                                           bullet9(&explosion9),
                                           bullet10(&explosion10),
                                           bullet11(&explosion11),
                                           bullet12(&explosion12),
                                           bullet13(&explosion13),
                                           bullet14(&explosion14),
                                           bullet15(&explosion15),
                                           bullet16(&explosion16),
                                           explosion1(&bullet1),
                                           explosion2(&bullet2),
                                           explosion3(&bullet3),
                                           explosion4(&bullet4),
                                           explosion5(&bullet5),
                                           explosion6(&bullet6),
                                           explosion7(&bullet7),
                                           explosion8(&bullet8),
                                           explosion9(&bullet9),
                                           explosion10(&bullet10),
                                           explosion11(&bullet11),
                                           explosion12(&bullet12),
                                           explosion13(&bullet13),
                                           explosion14(&bullet14),
                                           explosion15(&bullet15),
                                           explosion16(&bullet16),
                                           reloadTimer(1)
 {
 }

inline void ShipBulletGroup::Fire(Intersector& intersector,
                                  const double creationTime)
 {if (fireThisFrame)
   {if (!autoFire||reloadTimer.TimerAlarm())
     {reloadTimer.Reset();
      switch (numBullets)
       {case 16: if (bullet16.inactive)
                  {bullet16.PositionBullet(intersector,creationTime);
                   break;
                  }
        case 15: if (bullet15.inactive)
                  {bullet15.PositionBullet(intersector,creationTime);
                   break;
                  }
        case 14: if (bullet14.inactive)
                  {bullet14.PositionBullet(intersector,creationTime);
                   break;
                  }
        case 13: if (bullet13.inactive)
                  {bullet13.PositionBullet(intersector,creationTime);
                   break;
                  }
        case 12: if (bullet12.inactive)
                  {bullet12.PositionBullet(intersector,creationTime);
                   break;
                  }
        case 11: if (bullet11.inactive)
                  {bullet11.PositionBullet(intersector,creationTime);
                   break;
                  }
        case 10: if (bullet10.inactive)
                  {bullet10.PositionBullet(intersector,creationTime);
                   break;
                  }
        case  9: if (bullet9.inactive)
                  {bullet9.PositionBullet(intersector,creationTime);
                   break;
                  }
        case  8: if (bullet8.inactive)
                  {bullet8.PositionBullet(intersector,creationTime);
                   break;
                  }
        case  7: if (bullet7.inactive)
                  {bullet7.PositionBullet(intersector,creationTime);
                   break;
                  }
        case  6: if (bullet6.inactive)
                  {bullet6.PositionBullet(intersector,creationTime);
                   break;
                  }
        case  5: if (bullet5.inactive)
                  {bullet5.PositionBullet(intersector,creationTime);
                   break;
                  }
        case  4: if (bullet4.inactive)
                  {bullet4.PositionBullet(intersector,creationTime);
                   break;
                  }
        case  3: if (bullet3.inactive)
                  {bullet3.PositionBullet(intersector,creationTime);
                   break;
                  }
        case  2: if (bullet2.inactive)
                  {bullet2.PositionBullet(intersector,creationTime);
                   break;
                  }
        case  1: if (bullet1.inactive)
                  {bullet1.PositionBullet(intersector,creationTime);
                   break;
                  }
         case  0: ;
       }
     }
    fireThisFrame=off;
   }
 }

inline void ShipBulletGroup::Reset()
 {bullet16.inactive=ShipBullet::on;
  bullet15.inactive=ShipBullet::on;
  bullet14.inactive=ShipBullet::on;
  bullet13.inactive=ShipBullet::on;
  bullet12.inactive=ShipBullet::on;
  bullet11.inactive=ShipBullet::on;
  bullet10.inactive=ShipBullet::on;
  bullet9.inactive=ShipBullet::on;
  bullet8.inactive=ShipBullet::on;
  bullet7.inactive=ShipBullet::on;
  bullet6.inactive=ShipBullet::on;
  bullet5.inactive=ShipBullet::on;
  bullet4.inactive=ShipBullet::on;
  bullet3.inactive=ShipBullet::on;
  bullet2.inactive=ShipBullet::on;
  bullet1.inactive=ShipBullet::on;
  fireThisFrame=off;
 }

inline void ShipBulletGroup::ResetVelocity(const double newVelocity)
 {bullet1.ObjectLiner().Velocity()=newVelocity
                                   *bullet1.ObjectLiner().Velocity()
                                   /bullet1.ObjectLiner().VelocityMagnitude();
  bullet2.ObjectLiner().Velocity()=newVelocity
                                   *bullet2.ObjectLiner().Velocity()
                                   /bullet2.ObjectLiner().VelocityMagnitude();
  bullet3.ObjectLiner().Velocity()=newVelocity
                                   *bullet3.ObjectLiner().Velocity()
                                   /bullet3.ObjectLiner().VelocityMagnitude();
  bullet4.ObjectLiner().Velocity()=newVelocity
                                   *bullet4.ObjectLiner().Velocity()
                                   /bullet4.ObjectLiner().VelocityMagnitude();
  bullet5.ObjectLiner().Velocity()=newVelocity
                                   *bullet5.ObjectLiner().Velocity()
                                   /bullet5.ObjectLiner().VelocityMagnitude();
  bullet6.ObjectLiner().Velocity()=newVelocity
                                   *bullet6.ObjectLiner().Velocity()
                                   /bullet6.ObjectLiner().VelocityMagnitude();
  bullet7.ObjectLiner().Velocity()=newVelocity
                                   *bullet7.ObjectLiner().Velocity()
                                   /bullet7.ObjectLiner().VelocityMagnitude();
  bullet8.ObjectLiner().Velocity()=newVelocity
                                   *bullet8.ObjectLiner().Velocity()
                                   /bullet8.ObjectLiner().VelocityMagnitude();
  bullet9.ObjectLiner().Velocity()=newVelocity
                                   *bullet9.ObjectLiner().Velocity()
                                   /bullet9.ObjectLiner().VelocityMagnitude();
  bullet10.ObjectLiner().Velocity()=newVelocity
                                    *bullet10.ObjectLiner().Velocity()
                                    /bullet10.ObjectLiner().VelocityMagnitude();
  bullet11.ObjectLiner().Velocity()=newVelocity
                                    *bullet11.ObjectLiner().Velocity()
                                    /bullet11.ObjectLiner().VelocityMagnitude();
  bullet12.ObjectLiner().Velocity()=newVelocity
                                    *bullet12.ObjectLiner().Velocity()
                                    /bullet12.ObjectLiner().VelocityMagnitude();
  bullet13.ObjectLiner().Velocity()=newVelocity
                                    *bullet13.ObjectLiner().Velocity()
                                    /bullet13.ObjectLiner().VelocityMagnitude();
  bullet14.ObjectLiner().Velocity()=newVelocity
                                    *bullet14.ObjectLiner().Velocity()
                                    /bullet14.ObjectLiner().VelocityMagnitude();
  bullet15.ObjectLiner().Velocity()=newVelocity
                                    *bullet15.ObjectLiner().Velocity()
                                    /bullet15.ObjectLiner().VelocityMagnitude();
  bullet16.ObjectLiner().Velocity()=newVelocity
                                    *bullet16.ObjectLiner().Velocity()
                                    /bullet16.ObjectLiner().VelocityMagnitude();
 }

inline void ShipBulletGroup::ResetVelocityLimits(const double newVelocityLimit)
 {bullet1.ObjectLiner().MaxVelocityMagnitude()=
  bullet1.ObjectLiner().MaxAccelerationMagnitude()=
  bullet2.ObjectLiner().MaxVelocityMagnitude()=
  bullet2.ObjectLiner().MaxAccelerationMagnitude()=
  bullet3.ObjectLiner().MaxVelocityMagnitude()=
  bullet3.ObjectLiner().MaxAccelerationMagnitude()=
  bullet4.ObjectLiner().MaxVelocityMagnitude()=
  bullet4.ObjectLiner().MaxAccelerationMagnitude()=
  bullet5.ObjectLiner().MaxVelocityMagnitude()=
  bullet5.ObjectLiner().MaxAccelerationMagnitude()=
  bullet6.ObjectLiner().MaxVelocityMagnitude()=
  bullet6.ObjectLiner().MaxAccelerationMagnitude()=
  bullet7.ObjectLiner().MaxVelocityMagnitude()=
  bullet7.ObjectLiner().MaxAccelerationMagnitude()=
  bullet8.ObjectLiner().MaxVelocityMagnitude()=
  bullet8.ObjectLiner().MaxAccelerationMagnitude()=
  bullet9.ObjectLiner().MaxVelocityMagnitude()=
  bullet9.ObjectLiner().MaxAccelerationMagnitude()=
  bullet10.ObjectLiner().MaxVelocityMagnitude()=
  bullet10.ObjectLiner().MaxAccelerationMagnitude()=
  bullet11.ObjectLiner().MaxVelocityMagnitude()=
  bullet11.ObjectLiner().MaxAccelerationMagnitude()=
  bullet12.ObjectLiner().MaxVelocityMagnitude()=
  bullet12.ObjectLiner().MaxAccelerationMagnitude()=
  bullet13.ObjectLiner().MaxVelocityMagnitude()=
  bullet13.ObjectLiner().MaxAccelerationMagnitude()=
  bullet14.ObjectLiner().MaxVelocityMagnitude()=
  bullet14.ObjectLiner().MaxAccelerationMagnitude()=
  bullet15.ObjectLiner().MaxVelocityMagnitude()=
  bullet15.ObjectLiner().MaxAccelerationMagnitude()=
  bullet16.ObjectLiner().MaxVelocityMagnitude()=
  bullet16.ObjectLiner().MaxAccelerationMagnitude()=newVelocityLimit;
 }

inline void ShipBulletGroup::ResetBulletDuration(const int newDuration)
 {bullet1.frameTimer.framesTillAlarm=
  bullet2.frameTimer.framesTillAlarm=
  bullet3.frameTimer.framesTillAlarm=
  bullet4.frameTimer.framesTillAlarm=
  bullet5.frameTimer.framesTillAlarm=
  bullet6.frameTimer.framesTillAlarm=
  bullet7.frameTimer.framesTillAlarm=
  bullet8.frameTimer.framesTillAlarm=
  bullet9.frameTimer.framesTillAlarm=
  bullet10.frameTimer.framesTillAlarm=
  bullet11.frameTimer.framesTillAlarm=
  bullet12.frameTimer.framesTillAlarm=
  bullet13.frameTimer.framesTillAlarm=
  bullet14.frameTimer.framesTillAlarm=
  bullet15.frameTimer.framesTillAlarm=
  bullet16.frameTimer.framesTillAlarm=newDuration;
}

inline void ShipBulletGroup::AdjustFramesPerSec(const double frameRatio)
 {reloadTimer.framesTillAlarm=double(reloadTimer.framesTillAlarm)/frameRatio+.5;
  bullet1.ObjectLiner().Velocity()=bullet1.ObjectLiner().Velocity()*frameRatio;
  bullet1.ObjectLiner().Acceleration()=bullet1.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet2.ObjectLiner().Velocity()=bullet2.ObjectLiner().Velocity()*frameRatio;
  bullet2.ObjectLiner().Acceleration()=bullet2.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet3.ObjectLiner().Velocity()=bullet3.ObjectLiner().Velocity()*frameRatio;
  bullet3.ObjectLiner().Acceleration()=bullet3.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet4.ObjectLiner().Velocity()=bullet4.ObjectLiner().Velocity()*frameRatio;
  bullet4.ObjectLiner().Acceleration()=bullet4.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet5.ObjectLiner().Velocity()=bullet5.ObjectLiner().Velocity()*frameRatio;
  bullet5.ObjectLiner().Acceleration()=bullet5.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet6.ObjectLiner().Velocity()=bullet6.ObjectLiner().Velocity()*frameRatio;
  bullet6.ObjectLiner().Acceleration()=bullet6.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet7.ObjectLiner().Velocity()=bullet7.ObjectLiner().Velocity()*frameRatio;
  bullet7.ObjectLiner().Acceleration()=bullet7.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet8.ObjectLiner().Velocity()=bullet8.ObjectLiner().Velocity()*frameRatio;
  bullet8.ObjectLiner().Acceleration()=bullet8.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet9.ObjectLiner().Velocity()=bullet9.ObjectLiner().Velocity()*frameRatio;
  bullet9.ObjectLiner().Acceleration()=bullet9.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet10.ObjectLiner().Velocity()=bullet10.ObjectLiner().Velocity()*frameRatio;
  bullet10.ObjectLiner().Acceleration()=bullet10.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet11.ObjectLiner().Velocity()=bullet11.ObjectLiner().Velocity()*frameRatio;
  bullet11.ObjectLiner().Acceleration()=bullet11.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet12.ObjectLiner().Velocity()=bullet12.ObjectLiner().Velocity()*frameRatio;
  bullet12.ObjectLiner().Acceleration()=bullet12.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet13.ObjectLiner().Velocity()=bullet13.ObjectLiner().Velocity()*frameRatio;
  bullet13.ObjectLiner().Acceleration()=bullet13.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet14.ObjectLiner().Velocity()=bullet14.ObjectLiner().Velocity()*frameRatio;
  bullet14.ObjectLiner().Acceleration()=bullet14.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet15.ObjectLiner().Velocity()=bullet15.ObjectLiner().Velocity()*frameRatio;
  bullet15.ObjectLiner().Acceleration()=bullet15.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet16.ObjectLiner().Velocity()=bullet16.ObjectLiner().Velocity()*frameRatio;
  bullet16.ObjectLiner().Acceleration()=bullet16.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  bullet1.frameTimer.framesTillAlarm=double(bullet1.frameTimer.framesTillAlarm)/frameRatio+.5;
  bullet2.frameTimer.framesTillAlarm=double(bullet2.frameTimer.framesTillAlarm)/frameRatio+.5;
  bullet3.frameTimer.framesTillAlarm=double(bullet3.frameTimer.framesTillAlarm)/frameRatio+.5;
  bullet4.frameTimer.framesTillAlarm=double(bullet4.frameTimer.framesTillAlarm)/frameRatio+.5;
  bullet5.frameTimer.framesTillAlarm=double(bullet5.frameTimer.framesTillAlarm)/frameRatio+.5;
  bullet6.frameTimer.framesTillAlarm=double(bullet6.frameTimer.framesTillAlarm)/frameRatio+.5;
  bullet7.frameTimer.framesTillAlarm=double(bullet7.frameTimer.framesTillAlarm)/frameRatio+.5;
  bullet8.frameTimer.framesTillAlarm=double(bullet8.frameTimer.framesTillAlarm)/frameRatio+.5;
  bullet9.frameTimer.framesTillAlarm=double(bullet9.frameTimer.framesTillAlarm)/frameRatio+.5;
  bullet10.frameTimer.framesTillAlarm=double(bullet10.frameTimer.framesTillAlarm)/frameRatio+.5;
  bullet11.frameTimer.framesTillAlarm=double(bullet11.frameTimer.framesTillAlarm)/frameRatio+.5;
  bullet12.frameTimer.framesTillAlarm=double(bullet12.frameTimer.framesTillAlarm)/frameRatio+.5;
  bullet13.frameTimer.framesTillAlarm=double(bullet13.frameTimer.framesTillAlarm)/frameRatio+.5;
  bullet14.frameTimer.framesTillAlarm=double(bullet14.frameTimer.framesTillAlarm)/frameRatio+.5;
  bullet15.frameTimer.framesTillAlarm=double(bullet15.frameTimer.framesTillAlarm)/frameRatio+.5;
  bullet16.frameTimer.framesTillAlarm=double(bullet16.frameTimer.framesTillAlarm)/frameRatio+.5;
  explosion1.frameDelay.framesTillAlarm=double(explosion1.frameDelay.framesTillAlarm)/frameRatio+.5;
  explosion2.frameDelay.framesTillAlarm=double(explosion2.frameDelay.framesTillAlarm)/frameRatio+.5;
  explosion3.frameDelay.framesTillAlarm=double(explosion3.frameDelay.framesTillAlarm)/frameRatio+.5;
  explosion4.frameDelay.framesTillAlarm=double(explosion4.frameDelay.framesTillAlarm)/frameRatio+.5;
  explosion5.frameDelay.framesTillAlarm=double(explosion5.frameDelay.framesTillAlarm)/frameRatio+.5;
  explosion6.frameDelay.framesTillAlarm=double(explosion6.frameDelay.framesTillAlarm)/frameRatio+.5;
  explosion7.frameDelay.framesTillAlarm=double(explosion7.frameDelay.framesTillAlarm)/frameRatio+.5;
  explosion8.frameDelay.framesTillAlarm=double(explosion8.frameDelay.framesTillAlarm)/frameRatio+.5;
  explosion9.frameDelay.framesTillAlarm=double(explosion9.frameDelay.framesTillAlarm)/frameRatio+.5;
  explosion10.frameDelay.framesTillAlarm=double(explosion10.frameDelay.framesTillAlarm)/frameRatio+.5;
  explosion11.frameDelay.framesTillAlarm=double(explosion11.frameDelay.framesTillAlarm)/frameRatio+.5;
  explosion12.frameDelay.framesTillAlarm=double(explosion12.frameDelay.framesTillAlarm)/frameRatio+.5;
  explosion13.frameDelay.framesTillAlarm=double(explosion13.frameDelay.framesTillAlarm)/frameRatio+.5;
  explosion14.frameDelay.framesTillAlarm=double(explosion14.frameDelay.framesTillAlarm)/frameRatio+.5;
  explosion15.frameDelay.framesTillAlarm=double(explosion15.frameDelay.framesTillAlarm)/frameRatio+.5;
  explosion16.frameDelay.framesTillAlarm=double(explosion16.frameDelay.framesTillAlarm)/frameRatio+.5;
 }



#endif
