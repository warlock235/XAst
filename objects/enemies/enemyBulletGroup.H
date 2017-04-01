#include<stdlib.h>
#include<X11/Xlib.h>
#include"../../utilities/vector2d.H"
#include"../../utilities/box.H"
#include"../../utilities/pixmaps/rotated/rotatorDisplayData.H"
#include"../../utilities/pixmaps/rotated/rotator.H"
#include"../../utilities/frames/frameList.H"
#include"../../utilities/frames/frameTimer.H"
#include"../movableObject.H"
#include"../../utilities/intersection2d.H"
#include"../bullet.H"
#include"enemyGroup.H"
#include"../../gamePlay/stage.H"
#include"../../bitmaps/enemyBulletDecor.xbm"

#ifndef _ENEMYBULLETGROUP_H
#define _ENEMYBULLETGROUP_H

class EnemyBulletGroup;
class EnemyBullet: public Bullet
 {friend class EnemyBulletGroup;
  public:
    EnemyBullet(BulletExplosion* const);
    virtual void HitScript(Intersector&, const double createTime,
                                         const double existTime,
                                         const Vector2d& intersectPoint);

    static double velocity;

    static int numFrames,
               score;

  private:
    void SetInterceptVector(Enemy& shooter,
                            const MovableObject& target);
    void Aim(Intersector& intersector,
             const double creationTime,
             Enemy& shooter);

 };

class EnemyBulletGroup
 {friend class EnemyBullet;
  public:
    EnemyBulletGroup();
    inline void Fire(Intersector& intersector,
                const double creationTime,
                Enemy& shooter);
    inline void Reset();
    inline void ResetVelocity(const double newVelocity);
    inline void ResetVelocityLimits(const double newVelocityLimit);
    inline void ResetBulletDuration(const int newDuration);
    inline void AdjustFramesPerSec(const double frameRatio);

    static int numBullets;

    static XColor color;

  private:
    static const Vector2d vectors[4];

    NonRotVectorData graphic;

    Rotator rotator;

    EnemyBullet bullet10,
                bullet9,
                bullet8,
                bullet7,
                bullet6,
                bullet5,
                bullet4,
                bullet3,
                bullet2,
                bullet1;

    BulletExplosion explosion10,
                    explosion9,
                    explosion8,
                    explosion7,
                    explosion6,
                    explosion5,
                    explosion4,
                    explosion3,
                    explosion2,
                    explosion1;

    FrameTimer reloadTimer;

    unsigned int clipsFired;
 };

extern EnemyBulletGroup enemyBulletGroup;

#include"../../gamePlay/playingField.H"

double EnemyBullet::velocity=.5*PlayingField::maxLinearVelocity;

int EnemyBullet::score=1,
    EnemyBullet::numFrames=34;

inline EnemyBullet::EnemyBullet(BulletExplosion* const explosion): Bullet(&enemyBulletGroup.rotator,
                                                                          numFrames,explosion)
 {
 }

void EnemyBullet::HitScript(Intersector& intersector, const double createTime,
                                                      const double existTime,
                                                      const Vector2d& intersectPoint)
 {intersector.RemoveNonPermeable(this);
  explosion->CurrentBox().MoveBox(intersectPoint
                                  -explosion->CurrentBox().Center());
  explosion->frameList.Reset();
  explosion->frameTimer.Reset();
  intersector.AddPermeable(explosion,createTime+existTime);
  if (playingField.lastHitFromAlly)
   {::score.CurrentScore()+=score;
    playingField.lastHitFromAlly=PlayingField::off;
   }
  else
    if (playingField.lastHitScore)
      playingField.lastHitScore=0;
    else
      playingField.lastHitScore=score;
 }

inline void EnemyBullet::SetInterceptVector(Enemy& shooter,
                                            const MovableObject& target)
 {if (target.CurrentBox().Center().x<
      shooter.CurrentBox().Center().x)
    CurrentBox().MoveBox(Vector2d(shooter.CurrentBox().Center().x
                                  -shooter.ObjectRotator().Radius()
                                  -rotator->Radius()-.5,
                                  shooter.CurrentBox().Center().y+1)
                         -CurrentBox().Center());
  else
    CurrentBox().MoveBox(Vector2d(shooter.CurrentBox().Center().x
                                  +shooter.ObjectRotator().Radius()
                                  +rotator->Radius()+.5,
                                  shooter.CurrentBox().Center().y+1)
                         -CurrentBox().Center());
  SetToIntercept(target,velocity);
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

inline void EnemyBullet::Aim(Intersector& intersector,
                             const double creationTime,
                             Enemy& shooter)
 {if (enemyBulletGroup.clipsFired<<8*sizeof(enemyBulletGroup.clipsFired)-4)
   {int bulletID=enemyBulletGroup.clipsFired%enemyBulletGroup.numBullets;
    if (playingField.selfPermeableList.GetNumItems()&&
        playingField.selfPermeableList.GetNumItems()>=bulletID)
     {playingField.selfPermeableList.SetCurrentAtHead();
      for (;bulletID--;)
        playingField.selfPermeableList.Next();
      SetInterceptVector(shooter,
                         *playingField.selfPermeableList.GetData());
     }
    else
     {int numROCKs=RockGroup::ROCKsPerLevel*(playingField.level-1)+RockGroup::initialROCKs;
      if (numROCKs>RockGroup::maxROCKs)
        numROCKs=RockGroup::maxROCKs;
      SetInterceptVector(shooter,
                         rockGroup.ROCKs[gary_rand::rand_16()*numROCKs/(RAND_MAX_16+1)]);
     }
   }
  else
    SetInterceptVector(shooter,*shipGroup.ship);
  inactive=off;
  intersector.AddNonPermeable(this,creationTime);
  ++enemyBulletGroup.clipsFired;
 }

int EnemyBulletGroup::numBullets=2;

const Vector2d EnemyBulletGroup::vectors[4]={Vector2d(0,-2),
                                             Vector2d(2,0),
                                             Vector2d(0,2),
                                             Vector2d(-2,0)};

XColor EnemyBulletGroup::color={0,
                                65535,//255
                                0,
                                0,
                                DoRed|DoGreen|DoBlue};

inline EnemyBulletGroup::EnemyBulletGroup(): graphic(stage.display,stage.window,color,
                                                     vectors,sizeof(vectors)/sizeof(Vector2d),
                                                     enemyBulletDecor_bits,
                                                     enemyBulletDecor_width,enemyBulletDecor_height),
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
                                             reloadTimer(2),
                                             clipsFired(0)
 {
 }

inline void EnemyBulletGroup::Fire(Intersector& intersector,
                                   const double creationTime,
                                   Enemy& shooter)
 {if (reloadTimer.TimerAlarm())
   {reloadTimer.Reset();
    switch (numBullets)
     {case 10: if (bullet10.inactive)
                {bullet10.Aim(intersector,creationTime,shooter);
                 break;
                }
      case  9: if (bullet9.inactive)
                {bullet9.Aim(intersector,creationTime,shooter);
                 break;
                }
      case  8: if (bullet8.inactive)
                {bullet8.Aim(intersector,creationTime,shooter);
                 break;
                }
      case  7: if (bullet7.inactive)
                {bullet7.Aim(intersector,creationTime,shooter);
                 break;
                }
      case  6: if (bullet6.inactive)
                {bullet6.Aim(intersector,creationTime,shooter);
                 break;
                }
      case  5: if (bullet5.inactive)
                {bullet5.Aim(intersector,creationTime,shooter);
                 break;
                }
      case  4: if (bullet4.inactive)
                {bullet4.Aim(intersector,creationTime,shooter);
                 break;
                }
      case  3: if (bullet3.inactive)
                {bullet3.Aim(intersector,creationTime,shooter);
                 break;
                }
      case  2: if (bullet2.inactive)
                {bullet2.Aim(intersector,creationTime,shooter);
                 break;
                }
      case  1: if (bullet1.inactive)
                {bullet1.Aim(intersector,creationTime,shooter);
                 break;
                }
      case  0: ;
     }
   }
 }

inline void EnemyBulletGroup::Reset()
 {bullet10.inactive=EnemyBullet::on;
  bullet9.inactive=EnemyBullet::on;
  bullet8.inactive=EnemyBullet::on;
  bullet7.inactive=EnemyBullet::on;
  bullet6.inactive=EnemyBullet::on;
  bullet5.inactive=EnemyBullet::on;
  bullet4.inactive=EnemyBullet::on;
  bullet3.inactive=EnemyBullet::on;
  bullet2.inactive=EnemyBullet::on;
  bullet1.inactive=EnemyBullet::on;
 }

inline void EnemyBulletGroup::ResetVelocity(const double newVelocity)
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
}

inline void EnemyBulletGroup::ResetVelocityLimits(const double newVelLimit)
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
  bullet10.ObjectLiner().MaxAccelerationMagnitude()=newVelLimit;
 }

inline void EnemyBulletGroup::ResetBulletDuration(const int newDuration)
 {bullet1.frameTimer.framesTillAlarm=
  bullet2.frameTimer.framesTillAlarm=
  bullet3.frameTimer.framesTillAlarm=
  bullet4.frameTimer.framesTillAlarm=
  bullet5.frameTimer.framesTillAlarm=
  bullet6.frameTimer.framesTillAlarm=
  bullet7.frameTimer.framesTillAlarm=
  bullet8.frameTimer.framesTillAlarm=
  bullet9.frameTimer.framesTillAlarm=
  bullet10.frameTimer.framesTillAlarm=newDuration;
}

inline void EnemyBulletGroup::AdjustFramesPerSec(const double frameRatio)
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
 }

#endif
