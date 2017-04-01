#ifndef _ENEMYGROUP_H
#define _ENEMYGROUP_H

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
#include"../explosions/explosion.H"
#include"../../gamePlay/stage.H"
#include"../../bitmaps/ENEMYDecor.xbm"
#include"../../bitmaps/enemyDecor.xbm"

class EnemyGroup;
class Enemy: public MovableObject
 {friend class EnemyGroup;
  public:

    Enemy(const Vector2d* const vectors, const int numVecs, XColor& color,
          const unsigned char* const decor, const int decorWidth, const int decorHeight,
          const int score);

    virtual Rotator& ObjectRotator();
    virtual void MissScript(Intersector&, const double createTime,
                                          const double existTime)=0;
    virtual void HitScript(Intersector&, const double createTime,
                                          const double existTime,
                                          const Vector2d& intersectPoint);
  protected:
    NonRotVectorData graphic;
    Rotator rotator;

  private:
    int score;
 };


class ENEMY: public Enemy
 {friend class EnemyGroup;
  public:
    ENEMY();
    virtual void MissScript(Intersector&, const double createTime,
                                          const double existTime);

    static double minVelocity,
                  maxVelocity;

    static int score;

    static XColor color;

  private:
    static const int shiftRate,
                     shiftSize;

    static const Vector2d vectors[10];
 };



class enemy: public Enemy
 {friend class EnemyGroup;
  public:
    enemy();
    virtual void MissScript(Intersector&, const double createTime,
                                          const double existTime);

    static double minVelocity,
                  maxVelocity;

    static int score;

    static XColor color;

  private:
    static const Vector2d vectors[8];
 };

class EnemyExplosion: public Explosion
 {public:
    virtual void MissScript(Intersector&, const double createTime,
                    	                 const double existTime);
 };


class EnemyGroup
 {friend class Enemy;
  friend class ENEMY;
  friend class enemy;
  public:

    typedef int Boolean;
    enum {off, on};
    Boolean enemyInactive;

    EnemyGroup();
    inline void NewEnemy(const int level);
    inline void Reset();
    inline void AdjustFramesPerSec(const double frameRatio);
    inline void ResetENEMYMinVelocity(const double newMinVelocity);
    inline void ResetENEMYMaxVelocity(const double newMaxVelocity);
    inline void ResetenemyMinVelocity(const double newMinVelocity);
    inline void ResetenemyMaxVelocity(const double newMaxVelocity);
    inline void ResetVelocityLimits(const double newVelLimit);
    inline void ResetScore(const double scoreFactor);

    static int minimumFrames;


  private:

    Boolean Overlap(const Box& overlapBox);

    static const int scoreThreshold,
                     scoreLevelIncrement,
                     ENEMYFrequency1,
                     ENEMYFrequency2;

    ENEMY ENEMy;
    enemy enemY;
    EnemyExplosion explosion;
    FrameTimer frameTimer;
 };

extern EnemyGroup enemyGroup;

#include"enemyBulletGroup.H"
#include"../../gamePlay/playingField.H"

inline Enemy::Enemy(const Vector2d* const vectors, const int numVecs, XColor& color,
                    const unsigned char* const decor, const int decorWidth, const int decorHeight,
                    const int s):
                             graphic(stage.display,stage.window,color,
                                     vectors,numVecs,
                                     decor,decorWidth,decorHeight),
                             rotator(&graphic,0,PlayingField::maxLinearVelocity),
                             score(s)
{SetMovableObject(Vector2d(),2*rotator.Radius(),2*rotator.Radius(),
                  Vector2d(),PlayingField::maxLinearVelocity,Vector2d());
 }

Rotator& Enemy::ObjectRotator()
 {return rotator;
 }

void Enemy::HitScript(Intersector& intersector, const double createTime,
                        const double existTime,
                        const Vector2d& intersectPoint)
 {intersector.RemoveNonPermeable(this);
  enemyGroup.explosion.CurrentBox().MoveBox(ObjectLiner()
                                            .Move(OldBox().Center(),
                                                  existTime)
				     -enemyGroup.explosion.CurrentBox().Center());
  enemyGroup.explosion.ObjectLiner().Velocity()=ObjectLiner().Velocity();
  enemyGroup.explosion.frameList.Reset();
  enemyGroup.explosion.frameTimer.Reset();
  intersector.AddPermeable(&enemyGroup.explosion,createTime+existTime);
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

int ENEMY::score=250;

const int ENEMY::shiftRate=RAND_MAX_16/20,
          ENEMY::shiftSize=1;

double ENEMY::minVelocity=.1*PlayingField::maxLinearVelocity,
       ENEMY::maxVelocity=.3*PlayingField::maxLinearVelocity;

const Vector2d ENEMY::vectors[10]={Vector2d(2,-5),
                                   Vector2d(5,-2),
                                   Vector2d(6,-2),
                                   Vector2d(15,1),
                                   Vector2d(3,4),
                                   Vector2d(-3,4),
                                   Vector2d(-15,1),
                                   Vector2d(-6,-2),
                                   Vector2d(-5,-2),
                                   Vector2d(-2,-5)};

XColor ENEMY::color={0,
                     39064,//152
                     64507,//251
                     39064,//152
                     DoRed|DoGreen|DoBlue};

inline ENEMY::ENEMY(): Enemy(vectors,sizeof(vectors)/sizeof(Vector2d),color,
                             ENEMYDecor_bits,ENEMYDecor_width,ENEMYDecor_height,
                             score)
 {
 }


void ENEMY::MissScript(Intersector& intersector, const double createTime,
                                          const double existTime)
 {playingField.framesSinceEnemy=0;
  if (enemyGroup.frameTimer.TimerAlarm()&&
      !Intersect(CurrentBox(),PlayingField::playArea))
   {intersector.RemoveNonPermeable(this);
    enemyGroup.enemyInactive=EnemyGroup::on;
   }
  else
   {enemyBulletGroup.Fire(intersector,createTime+existTime,*this);
    unsigned int random=gary_rand::rand_16();
    if (random<=shiftRate)
     {Vector2d velocity;
      if (random<<31)
        velocity=Vector2d(ObjectLiner().XVelocity(),
                          ObjectLiner().YVelocity()-shiftSize);
      else
        velocity=Vector2d(ObjectLiner().XVelocity(),
                          ObjectLiner().YVelocity()+shiftSize);
      ObjectLiner().Velocity()=ObjectLiner().VelocityMagnitude()
                               *velocity/velocity.Magnitude();
     }
    if (PlayingField::universalGravitationalConst)
      ObjectLiner().UpdateVelocity(existTime);
    XCopyArea(stage.display,
              rotator.GetPixAtTime(0),
              playingField.pixmap,
              playingField.gc,
              0,0,
              rotator.PixWidth(),
              rotator.PixHeight(),
              CurrentBox().WrapMovingBox(PlayingField::playArea,
                                         ObjectLiner().Velocity())
                          .NorthWestCorner().x+.5,
              CurrentBox().NorthWestCorner().y+.5);
   }
 }

int enemy::score=1000;

double enemy::minVelocity=.1*PlayingField::maxLinearVelocity,
       enemy::maxVelocity=.4*PlayingField::maxLinearVelocity;

const Vector2d enemy::vectors[8]={Vector2d(1,-3),
                                  Vector2d(3,-1),
                                  Vector2d(8,1),
                                  Vector2d(3,3),
                                  Vector2d(-3,3),
                                  Vector2d(-8,1),
                                  Vector2d(-3,-1),
                                  Vector2d(-1,-3)};

XColor enemy::color={0,
                     0,
                     65535,//255
                     0,
                     DoRed|DoGreen|DoBlue};

inline enemy::enemy(): Enemy(vectors,sizeof(vectors)/sizeof(Vector2d),color,
                             enemyDecor_bits,enemyDecor_width,enemyDecor_height,
                             score)
 {
 }

void enemy::MissScript(Intersector& intersector, const double createTime,
                                          const double existTime)
 {playingField.framesSinceEnemy=0;
  if (enemyGroup.frameTimer.TimerAlarm()&&
      !Intersect(CurrentBox(),PlayingField::playArea))
   {intersector.RemoveNonPermeable(this);
    enemyGroup.enemyInactive=EnemyGroup::on;
   }
  else
   {enemyBulletGroup.Fire(intersector,createTime+existTime,*this);
    if (!shipGroup.hyper.hyperspacing)
     {Vector2d TargetDeltaPos=shipGroup.ship->CurrentBox().Center()
                              -CurrentBox().Center();
      ObjectLiner().Velocity()=ObjectLiner().VelocityMagnitude()
                               *TargetDeltaPos/TargetDeltaPos.Magnitude();
     }
    if (PlayingField::universalGravitationalConst)
      ObjectLiner().UpdateVelocity(existTime);
    XCopyArea(stage.display,
              rotator.GetPixAtTime(0),
              playingField.pixmap,
              playingField.gc,
              0,0,
              rotator.PixWidth(),
              rotator.PixHeight(),
              CurrentBox().WrapMovingBox(PlayingField::playArea,
                                         ObjectLiner().Velocity())
                          .NorthWestCorner().x+.5,
              CurrentBox().NorthWestCorner().y+.5);
   }
 }

void EnemyExplosion::MissScript(Intersector& intersector, const double createTime,
                    	                 const double existTime)
 {if (frameDelay.TimerAlarm()||frameList.GetFirstFrameNumber()==frameList.GetFrameNumber())
   {frameDelay.Reset();
    if (frameTimer.TimerAlarm())
     {intersector.RemovePermeable(this);
      enemyGroup.enemyInactive=EnemyGroup::on;
     }
    else
     {frameList.UpdateFrameNumber();
      Explosion::DisplayFrame();
     }
   }
  else
      Explosion::DisplayFrame();
 }

int EnemyGroup::minimumFrames=25;

const int EnemyGroup::scoreThreshold=1800,
          EnemyGroup::scoreLevelIncrement=500,
          EnemyGroup::ENEMYFrequency1=RAND_MAX_16*70/100,
          EnemyGroup::ENEMYFrequency2=RAND_MAX_16-ENEMYFrequency1;

inline EnemyGroup::EnemyGroup(): enemyInactive(on),
                                   frameTimer(minimumFrames)
 {
 }

inline EnemyGroup::Boolean EnemyGroup::Overlap(const Box& overlapBox)
 {playingField.nonPermeableList.SetCurrentAtHead();
  {for (int i=0; i<playingField.nonPermeableList.GetNumItems(); ++i)
    {if (Intersect(playingField.nonPermeableList.GetData()->CurrentBox(),
                   overlapBox))
       return on;
     playingField.nonPermeableList.Next();
    }
  }
  playingField.selfPermeableList.SetCurrentAtHead();
  {for (int i=0; i<playingField.selfPermeableList.GetNumItems(); ++i)
    {if (Intersect(playingField.selfPermeableList.GetData()->CurrentBox(),
                   overlapBox))
       return on;
     playingField.selfPermeableList.Next();
    }
  }
  return off;
 }

inline void EnemyGroup::NewEnemy(const int level)
 {if (gary_rand::rand_16()<(score.CurrentScore()<scoreThreshold+scoreLevelIncrement*(level>7 ? 6 : level-1)
             ? ENEMYFrequency1
             : ENEMYFrequency2))
   {double velMagnitude=2*ENEMY::maxVelocity*gary_rand::rand_16()/RAND_MAX_16-ENEMY::maxVelocity;
   if (fabs(velMagnitude)<ENEMY::minVelocity)
       velMagnitude=velMagnitude<0 ? -ENEMY::minVelocity
	                           : ENEMY::minVelocity;
    if (Vector2d(ENEMy.ObjectLiner().Velocity()=Vector2d(velMagnitude)).x<0)
      ENEMy.CurrentBox().SetBox(Vector2d(PlayingField::playArea.EastSide()+ENEMy.rotator.Radius(),
                                         (PlayingField::playArea.Height()
                                          -2*ENEMy.rotator.Radius())*gary_rand::rand_16()/(RAND_MAX_16+1)
                                         +ENEMy.rotator.Radius()
                                         +PlayingField::playArea.NorthSide()),
			        ENEMy.rotator.Radius());
    else
      ENEMy.CurrentBox().SetBox(Vector2d(PlayingField::playArea.WestSide()-ENEMy.rotator.Radius(),
                                         (PlayingField::playArea.Height()
                                          -2*ENEMy.rotator.Radius())*gary_rand::rand_16()/(RAND_MAX_16+1)
                                         +ENEMy.rotator.Radius()
                                         +PlayingField::playArea.NorthSide()),
			        ENEMy.rotator.Radius());
    if (Overlap(ENEMy.CurrentBox()))
      return;
    playingField.nonPermeableList.SetCurrentAtHole().GetData()=&ENEMy;
   }
  else
   {double velMagnitude=2*enemY.maxVelocity*gary_rand::rand_16()/RAND_MAX_16-enemY.maxVelocity;
   if (fabs(velMagnitude)<enemy::minVelocity)
       velMagnitude=velMagnitude<0 ? -enemy::minVelocity
	                           : enemy::minVelocity;
    if (Vector2d(enemY.ObjectLiner().Velocity()=Vector2d(velMagnitude)).x<0)
      enemY.CurrentBox().SetBox(Vector2d(PlayingField::playArea.EastSide()+enemY.rotator.Radius(),
                                         (PlayingField::playArea.Height()
                                          -2*enemY.rotator.Radius())*gary_rand::rand_16()/(RAND_MAX_16+1)
                                         +enemY.rotator.Radius()
                                         +PlayingField::playArea.NorthSide()),
                                enemY.rotator.Radius());
      enemY.CurrentBox().SetBox(Vector2d(PlayingField::playArea.WestSide()-enemY.rotator.Radius(),
                                          (PlayingField::playArea.Height()
                                           -2*enemY.rotator.Radius())*gary_rand::rand_16()/(RAND_MAX_16+1)
                                          +enemY.rotator.Radius()
                                          +PlayingField::playArea.NorthSide()),
                                 enemY.rotator.Radius());
    if (Overlap(enemY.CurrentBox()))
      return;
    playingField.nonPermeableList.SetCurrentAtHole().GetData()=&enemY;
   }
  playingField.nonPermeableList.SetCurrentAtHead().AddPrior();
  enemyInactive=off;
 }

inline void EnemyGroup::Reset()
 {enemyInactive=on;
 }

inline void EnemyGroup::AdjustFramesPerSec(const double frameRatio)
 {ENEMy.ObjectLiner().Velocity()=ENEMy.ObjectLiner().Velocity()*frameRatio;
  ENEMy.ObjectLiner().Acceleration()=ENEMy.ObjectLiner().Acceleration()
                                     *frameRatio*frameRatio;
  enemY.ObjectLiner().Velocity()=enemY.ObjectLiner().Velocity()*frameRatio;
  enemY.ObjectLiner().Acceleration()=enemY.ObjectLiner().Acceleration()
                                     *frameRatio*frameRatio;
  explosion.ObjectLiner().Velocity()=explosion.ObjectLiner().Velocity()*frameRatio;
  explosion.ObjectLiner().Acceleration()=explosion.ObjectLiner().Acceleration()
                                         *frameRatio*frameRatio;
  explosion.frameDelay.framesTillAlarm=double(explosion.frameDelay.framesTillAlarm)/frameRatio+.5;
  frameTimer.framesTillAlarm=double(frameTimer.framesTillAlarm)/frameRatio+.5;
  minimumFrames=double(minimumFrames)/frameRatio+.5;
 }

inline void EnemyGroup::ResetENEMYMinVelocity(const double newMinVelocity)
 {if (ENEMy.ObjectLiner().VelocityMagnitude()<newMinVelocity)
    ENEMy.ObjectLiner().Velocity()=newMinVelocity
                                   *ENEMy.ObjectLiner().Velocity()
                                   /ENEMy.ObjectLiner().VelocityMagnitude();
  if (explosion.ObjectLiner().VelocityMagnitude()<newMinVelocity)
    explosion.ObjectLiner().Velocity()=newMinVelocity
                                       *explosion.ObjectLiner().Velocity()
                                       /explosion.ObjectLiner().VelocityMagnitude();
 }

inline void EnemyGroup::ResetENEMYMaxVelocity(const double newMaxVelocity)
 {if (ENEMy.ObjectLiner().VelocityMagnitude()>newMaxVelocity)
    ENEMy.ObjectLiner().Velocity()=newMaxVelocity
                                   *ENEMy.ObjectLiner().Velocity()
                                   /ENEMy.ObjectLiner().VelocityMagnitude();
  if (explosion.ObjectLiner().VelocityMagnitude()>newMaxVelocity)
    explosion.ObjectLiner().Velocity()=newMaxVelocity
                                       *explosion.ObjectLiner().Velocity()
                                       /explosion.ObjectLiner().VelocityMagnitude();
 }

inline void EnemyGroup::ResetenemyMinVelocity(const double newMinVelocity)
 {if (enemY.ObjectLiner().VelocityMagnitude()<newMinVelocity)
    enemY.ObjectLiner().Velocity()=newMinVelocity
                                   *enemY.ObjectLiner().Velocity()
                                   /enemY.ObjectLiner().VelocityMagnitude();
  if (explosion.ObjectLiner().VelocityMagnitude()<newMinVelocity)
    explosion.ObjectLiner().Velocity()=newMinVelocity
                                       *explosion.ObjectLiner().Velocity()
                                       /explosion.ObjectLiner().VelocityMagnitude();
 }

inline void EnemyGroup::ResetenemyMaxVelocity(const double newMaxVelocity)
 {if (enemY.ObjectLiner().VelocityMagnitude()>newMaxVelocity)
    enemY.ObjectLiner().Velocity()=newMaxVelocity
                                   *enemY.ObjectLiner().Velocity()
                                   /enemY.ObjectLiner().VelocityMagnitude();
  if (explosion.ObjectLiner().VelocityMagnitude()<newMaxVelocity)
    explosion.ObjectLiner().Velocity()=newMaxVelocity
                                       *explosion.ObjectLiner().Velocity()
                                       /explosion.ObjectLiner().VelocityMagnitude();
 }

inline void EnemyGroup::ResetVelocityLimits(const double newVelLimit)
 {ENEMy.ObjectLiner().MaxVelocityMagnitude()=
  ENEMy.ObjectLiner().MaxAccelerationMagnitude()=
  enemY.ObjectLiner().MaxVelocityMagnitude()=
  enemY.ObjectLiner().MaxAccelerationMagnitude()=
  explosion.ObjectLiner().MaxVelocityMagnitude()=newVelLimit;
 }


inline void EnemyGroup::ResetScore(const double scoreFactor)
 {if (!(ENEMy.Enemy::score*=scoreFactor))
    ENEMy.Enemy::score=1;
  if (!(enemY.Enemy::score*=scoreFactor))
    enemY.Enemy::score=1;
 }

#endif
