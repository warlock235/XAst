class Rock;
#include<stdlib.h>
#include<math.h>
#include<X11/Xlib.h>
#include"../../utilities/vector2d.H"
#include"../../utilities/pixmaps/rotated/rotatorDisplayData.H"
#include"../../utilities/pixmaps/rotated/rotator.H"
#include"spawner.H"
#include"../movableObject.H"
#include"../../utilities/intersection2d.H"
#include"../../gamePlay/stage.H"
#include"../ships/shipGroup.H"

#ifdef _CORP_LOGO_
#include"../../bitmaps/ROCKDecor1.xbm"
#include"../../bitmaps/ROCKDecor2.xbm"
#include"../../bitmaps/ROCKDecor3.xbm"
#else
#include"../../bitmaps/eightball.xbm"
#include"../../bitmaps/peace.xbm"
#include"../../bitmaps/yinyang.xbm"
#endif

#ifndef _ROCKGROUP_H
#define _ROCKGROUP_H

class Rock: public MovableObject
 {public:
    Rock(const int s, const double scale);
    void SetRock(const Vector2d& velocity,
                  MaskedRotVectorData* const, const double angularVelocity,
                  const int score);
    virtual Rotator& ObjectRotator();
    virtual void MissScript(Intersector&, const double createTime,
                                          const double existTime);
    virtual void HitScript(Intersector&, const double createTime,
                                         const double existTime,
                                         const Vector2d& intersectPoint);
    virtual void AlterMinVelocity(const double newMinVelocity);
    virtual void AlterMaxVelocity(const double newMaxVelocity)=0;
    virtual void AlterMaxAngularVelocity(const double newAngularVelocity);
    virtual void AlterVelocityLimits(const double newVelLimit);
    virtual void AlterFramesPerSec(const double frameRatio);
    virtual void AlterScore(const double scoreFactor);

  protected:
    Rotator rotator;
    int score;
 };

class SpawningRock: public Rock
 {public:
    SpawningRock(const int score, const double scale, const int numSpawn);
    virtual void HitScript(Intersector&, const double createTime,
                                         const double existTime,
                                         const Vector2d& intersectPoint);
    virtual void AlterMinVelocity(const double newMinVelocity);
    virtual void AlterMaxVelocity(const double newMaxVelocity)=0;
    virtual void AlterMaxAngularVelocity(const double newAngularVelocity);
    virtual void AlterVelocityLimits(const double newVelLimit);
    virtual void AlterFramesPerSec(const double frameRatio);
    virtual void AlterScore(const double scoreFactor);

  protected:
    Spawner spawner;
 };

class RockGroup;
class ROCK: public SpawningRock
 {friend class RockGroup;
  public:
    ROCK();
    virtual void AlterMaxVelocity(const double newMaxVelocity);

    static const double scale;
    static double minVelocity,
                  maxVelocity,
                  maxAngularVelocity;
    static int score;
 };

class ROck: public SpawningRock
 {friend class RockGroup;
  public:
    ROck();
    virtual void AlterMaxVelocity(const double newMaxVelocity);

   static const double scale;

   static int score;
 };

class rock: public Rock
 {friend class RockGroup;
  public:
    rock();
    virtual void AlterMaxVelocity(const double newMaxVelocity);

    static const double scale;

    static int score;
 };

class RockGroup
 {public:
    typedef int Boolean;
    enum {off, on};

    ROCK ROCKs[16];
    ROck ROcks[32];
    rock rocks[128];

    RockGroup();
    ~RockGroup();

    inline void NewROCKs();

    inline void ResetMinVelocity(const double newMinVelocity);
    inline void ResetMaxVelocity(const double newMaxVelocity);
    inline void ResetMaxAngularVelocity(const double newAngularVelocity);
    inline void AdjustFramesPerSec(const double frameRatio);
    inline void ResetVelocityLimits(const double newVelLimit);
    inline void ResetScore(const double scoreFactor);

    static int initialROCKs,
               ROCKsPerLevel;
    static const int maxROCKs;

    static Boolean opaqueRocks;

    static XColor RockColor;

  private:
    void SetVectorData(const Vector2d* const RockVecs, const int numvecs,
                       const int graphicIndex);

    static const Vector2d RockVectors1[8],
                          RockVectors2[8],
                          RockVectors3[11];

    static const unsigned char* const ROCKDecor_bits[3];
    static const int ROCKDecor_width[3],
                     ROCKDecor_height[3];

    MaskedRotVectorData* ROCKGraphic[3],
                       * ROckGraphic[3],
                       * rockGraphic[3];
 };

extern RockGroup rockGroup;

#include"../../gamePlay/playingField.H"

inline Rock::Rock(const int s, const double scale): rotator(PlayingField::maxLinearVelocity/(4*scale)),
                                                    score(s)
 {
 }

inline void Rock::SetRock(const Vector2d& velocity,
                          MaskedRotVectorData* const graphic,
                          const double angularVelocity,
                          const int s)
 {rotator.SetRotator(graphic,
                     angularVelocity);
  SetMovableObject(Vector2d(),2*rotator.Radius(),2*rotator.Radius(),
		               velocity,PlayingField::maxLinearVelocity,Vector2d());
  score=s;
 }

Rotator& Rock::ObjectRotator()
 {return rotator;
 }

void Rock::MissScript(Intersector& intersector, const double createTime,
                             const double existTime)
 {rotator.UpdateAngle(existTime);
  if (PlayingField::universalGravitationalConst)
    ObjectLiner().UpdateVelocity(existTime);
  if (rockGroup.opaqueRocks)
   {int destX=CurrentBox().WrapMovingBox(PlayingField::playArea,
                                         ObjectLiner().Velocity())
                          .NorthWestCorner().x+.5,
        destY=CurrentBox().NorthWestCorner().y+.5;
    GC& gc=rotator.GetMaskGCAtTime(0);
    XSetClipOrigin(stage.display,gc,destX,destY);
    XCopyArea(stage.display,
              rotator.GetPixAtTime(0),
              playingField.pixmap,
              gc,
              0,0,
              rotator.PixWidth(),
              rotator.PixHeight(),
              destX,destY);
   }
  else
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

void Rock::HitScript(Intersector& intersector, const double createTime,
                             const double existTime,
                             const Vector2d& intersectPoint)
 {intersector.RemoveSelfPermeable(this);
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

void Rock::AlterMinVelocity(const double newMinVelocity)
 {if (ObjectLiner().VelocityMagnitude()<newMinVelocity)
    ObjectLiner().Velocity()=newMinVelocity*ObjectLiner().Velocity()/ObjectLiner().VelocityMagnitude();
 }

void Rock::AlterMaxAngularVelocity(const double newMaxAngularVelocity)
 {if (fabs(ObjectRotator().AngularVelocity())>newMaxAngularVelocity)
    ObjectRotator().AngularVelocity()=ObjectRotator().AngularVelocity()<0 ? -newMaxAngularVelocity
                                                                          :  newMaxAngularVelocity;
 }

void Rock::AlterVelocityLimits(const double newVelLimit)
 {ObjectLiner().MaxVelocityMagnitude()=
  ObjectLiner().MaxAccelerationMagnitude()=newVelLimit;
  ObjectRotator().UpdateMaxLinearVelocity(PlayingField::maxLinearVelocity);
 }

void Rock::AlterFramesPerSec(const double frameRatio)
 {ObjectLiner().Velocity()=ObjectLiner().Velocity()*frameRatio;
  ObjectLiner().Acceleration()=ObjectLiner().Acceleration()*frameRatio*frameRatio;
  ObjectRotator().AngularVelocity()=ObjectRotator().AngularVelocity()*frameRatio;
 }

void Rock::AlterScore(const double scoreFactor)
 {if (!(score*=scoreFactor))
    score=1;
 }

inline SpawningRock::SpawningRock(const int score,
                                     const double scale,
                                     const int numSpawn): Rock(score,scale),
                                                          spawner(numSpawn)
 {
 }

void SpawningRock::HitScript(Intersector& intersector, const double createTime,
                             const double existTime,
                             const Vector2d& intersectPoint)
 {intersector.RemoveSelfPermeable(this);
  {for (int i=0; i<spawner.GetNumSpawn(); ++i)
     intersector.AddSelfPermeable(spawner.GetSpawnWithInheritance(*this,
                                                                  existTime,i),
                                  createTime+existTime);
  }
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

void SpawningRock::AlterMinVelocity(const double newMinVelocity)
 {if (ObjectLiner().VelocityMagnitude()<newMinVelocity)
    ObjectLiner().Velocity()=newMinVelocity*ObjectLiner().Velocity()/ObjectLiner().VelocityMagnitude();
  for (int i=0;i<spawner.GetNumSpawn();++i)
    spawner[i]->AlterMinVelocity(newMinVelocity);
 }

void SpawningRock::AlterMaxAngularVelocity(const double newMaxAngularVelocity)
 {if (fabs(ObjectRotator().AngularVelocity())>newMaxAngularVelocity)
    ObjectRotator().AngularVelocity()=ObjectRotator().AngularVelocity()<0 ? -newMaxAngularVelocity
                                                                          :  newMaxAngularVelocity;
  for (int i=0;i<spawner.GetNumSpawn();++i)
    spawner[i]->AlterMaxAngularVelocity(newMaxAngularVelocity);
 }

void SpawningRock::AlterVelocityLimits(const double newVelLimit)
 {ObjectLiner().MaxVelocityMagnitude()=
  ObjectLiner().MaxAccelerationMagnitude()=newVelLimit;
  ObjectRotator().UpdateMaxLinearVelocity(PlayingField::maxLinearVelocity);
  for (int i=0;i<spawner.GetNumSpawn();++i)
    spawner[i]->AlterVelocityLimits(newVelLimit);
 }

void SpawningRock::AlterFramesPerSec(const double frameRatio)
 {ObjectLiner().Velocity()=ObjectLiner().Velocity()*frameRatio;
  ObjectLiner().Acceleration()=ObjectLiner().Acceleration()*frameRatio*frameRatio;
  ObjectRotator().AngularVelocity()=ObjectRotator().AngularVelocity()*frameRatio;
  for (int i=0;i<spawner.GetNumSpawn();++i)
    spawner[i]->AlterFramesPerSec(frameRatio);
 }

void SpawningRock::AlterScore(const double scoreFactor)
 {if (!(score*=scoreFactor))
    score=1;
  for (int i=0;i<spawner.GetNumSpawn();++i)
    spawner[i]->AlterScore(scoreFactor);
 }

int ROCK::score=10;

const double ROCK::scale=40;

double ROCK::minVelocity=.07*PlayingField::maxLinearVelocity,
       ROCK::maxVelocity=.13*PlayingField::maxLinearVelocity,
       ROCK::maxAngularVelocity=PlayingField::maxLinearVelocity/(4*ROCK::scale);

inline ROCK::ROCK(): SpawningRock(score,scale,2)
 {
 }

void ROCK::AlterMaxVelocity(const double newMaxVelocity)
 {if (ObjectLiner().VelocityMagnitude()>newMaxVelocity)
    ObjectLiner().Velocity()=newMaxVelocity*ObjectLiner().Velocity()/ObjectLiner().VelocityMagnitude();
  for (int i=0;i<spawner.GetNumSpawn();++i)
    spawner[i]->AlterMaxVelocity(newMaxVelocity);
 }

int ROck::score=20;

const double ROck::scale=sqrt(ROCK::scale*ROCK::scale/2);

inline ROck::ROck(): SpawningRock(score,scale,4)
 {
 }

void ROck::AlterMaxVelocity(const double newMaxVelocity)
 {if (ObjectLiner().VelocityMagnitude()>2*newMaxVelocity)
    ObjectLiner().Velocity()=2*newMaxVelocity*ObjectLiner().Velocity()/ObjectLiner().VelocityMagnitude();
  for (int i=0;i<spawner.GetNumSpawn();++i)
    spawner[i]->AlterMaxVelocity(newMaxVelocity);
 }

int rock::score=50;

const double rock::scale=sqrt(ROck::scale*ROck::scale/4);

inline rock::rock(): Rock(score,scale)
 {
 }

void rock::AlterMaxVelocity(const double newMaxVelocity)
 {if (ObjectLiner().VelocityMagnitude()>4*newMaxVelocity)
    ObjectLiner().Velocity()=4*newMaxVelocity*ObjectLiner().Velocity()/ObjectLiner().VelocityMagnitude();
 }

int RockGroup::initialROCKs=4,
    RockGroup::ROCKsPerLevel=2;

const int RockGroup::maxROCKs=16;

RockGroup::Boolean RockGroup::opaqueRocks=RockGroup::on;

const Vector2d RockGroup::RockVectors1[8]={Vector2d(-1,-28)/32,
                                           Vector2d(16,-15)/32,
                                           Vector2d(28,-14)/32,
                                           Vector2d(25,20)/32,
                                           Vector2d(8,12)/32,
                                           Vector2d(-8,30)/32,
                                           Vector2d(-30,11)/32,
                                           Vector2d(-22,-23)/32},
               RockGroup::RockVectors2[8]={Vector2d(0,-32)/32,
                                           Vector2d(29,-13)/32,
                                           Vector2d(31,6)/32,
                                           Vector2d(17,27)/32,
                                           Vector2d(2,21)/32,
                                           Vector2d(-22,23)/32,
                                           Vector2d(-31,-4)/32,
                                           Vector2d(-21,-24)/32},
               RockGroup::RockVectors3[11]={Vector2d(-6,-37)/40,
                                            Vector2d(4,-34)/40,
                                            Vector2d(12,-23)/40,
                                            Vector2d(39,-8)/40,
                                            Vector2d(39,2)/40,
                                            Vector2d(31,26)/40,
                                            Vector2d(5,34)/40,
                                            Vector2d(-18,30)/40,
                                            Vector2d(-39,6)/40,
                                            Vector2d(-39,-6)/40,
                                            Vector2d(-28,-29)/40};

#ifdef _CORP_LOGO_
const unsigned char* const RockGroup::ROCKDecor_bits[3]={ROCKDecor1_bits,ROCKDecor2_bits,ROCKDecor3_bits};
const int RockGroup::ROCKDecor_width[3]={ROCKDecor1_width,ROCKDecor2_width,ROCKDecor3_width},
          RockGroup::ROCKDecor_height[3]={ROCKDecor1_height,ROCKDecor2_height,ROCKDecor3_height};
#else
const unsigned char* const RockGroup::ROCKDecor_bits[3]={eightball_bits,peace_bits,yinyang_bits};
const int RockGroup::ROCKDecor_width[3]={eightball_width,peace_width,yinyang_width},
          RockGroup::ROCKDecor_height[3]={eightball_height,peace_height,yinyang_height};
#endif

XColor RockGroup::RockColor={0,
                             56026,//218
                             42405,//165
                             8224,//32
                             DoRed|DoGreen|DoBlue};

inline void RockGroup::SetVectorData(const Vector2d* const RockVecs, const int numvecs,
                                 const int graphicIndex)
 {Vector2d* scaledROCK=new Vector2d[numvecs],
          * scaledROck=new Vector2d[numvecs],
          * scaledrock=new Vector2d[numvecs];
  for(int i=0;i<numvecs;++i)
   {scaledROCK[i]=RockVecs[i]*ROCK::scale;
    scaledROck[i]=RockVecs[i]*ROck::scale;
    scaledrock[i]=RockVecs[i]*rock::scale;
   }
  ROCKGraphic[graphicIndex]=new MaskedRotVectorData(stage.display,stage.window,RockColor,
                                                    scaledROCK,numvecs,
                                                    ROCKDecor_bits[graphicIndex],
                                                    ROCKDecor_width[graphicIndex],
                                                    ROCKDecor_height[graphicIndex]);
  ROckGraphic[graphicIndex]=new MaskedRotVectorData(stage.display,stage.window,RockColor,
                                                    scaledROck,numvecs);
  rockGraphic[graphicIndex]=new MaskedRotVectorData(stage.display,stage.window,RockColor,
                                                    scaledrock,numvecs);
  delete [] scaledrock;
  delete [] scaledROck;
  delete [] scaledROCK;
 }

inline RockGroup::RockGroup()
 {SetVectorData(RockVectors1,sizeof(RockVectors1)/sizeof(Vector2d),0);
  SetVectorData(RockVectors2,sizeof(RockVectors2)/sizeof(Vector2d),1);
  SetVectorData(RockVectors3,sizeof(RockVectors3)/sizeof(Vector2d),2);
 }


inline RockGroup::~RockGroup()
 {for(int i=0;i<3;++i)
   {delete rockGraphic[i];
    delete ROckGraphic[i];
    delete ROCKGraphic[i];
   }
 }

inline void RockGroup::NewROCKs()
 {int numROCKs=ROCKsPerLevel*(playingField.level-1)+initialROCKs;
  if (numROCKs>maxROCKs)
    numROCKs=maxROCKs;
  for(int i=0;i<numROCKs;++i)
   {double ROCKAngularVelocity=2*ROCK::maxAngularVelocity*gary_rand::rand_16()/RAND_MAX_16
                               -ROCK::maxAngularVelocity,
    ROCKVelocityMagnitude=ROCK::maxVelocity*gary_rand::rand_16()/RAND_MAX_16;
    if (ROCKVelocityMagnitude<ROCK::minVelocity)
      ROCKVelocityMagnitude=ROCK::minVelocity;
    Vector2d ROCKVelocity(gary_rand::rand_16()-RAND_MAX_16/2,gary_rand::rand_16()-RAND_MAX_16/2);
    ROCKVelocity*=ROCKVelocityMagnitude/ROCKVelocity.Magnitude();
    double ROckMaxAngularVelocity=2*ROCKAngularVelocity,
           ROckMaxVelocityMagnitude=2*ROCKVelocityMagnitude;
    for(int j=0,
            ROckIndex=i*sizeof(ROcks)*sizeof(ROCK)/(sizeof(ROck)*sizeof(ROCKs));
            j<sizeof(ROcks)*sizeof(ROCK)/(sizeof(ROck)*sizeof(ROCKs));
            ++ROckIndex,++j)
     {double ROckAngularVelocity,
             ROckAVSum=0,
             ROckVelocityMagnitude;
      Vector2d ROckVelocity(gary_rand::rand_16()-RAND_MAX_16/2,gary_rand::rand_16()-RAND_MAX_16/2),
               ROckVMSum;
      if (j!=sizeof(ROcks)*sizeof(ROCK)/(sizeof(ROck)*sizeof(ROCKs)))
       {ROckAngularVelocity=2*ROckMaxAngularVelocity*gary_rand::rand_16()/RAND_MAX_16
                            -ROckMaxAngularVelocity;
        ROckAVSum+=ROckAngularVelocity;
        ROckVelocityMagnitude=ROckMaxVelocityMagnitude*gary_rand::rand_16()/RAND_MAX_16;
        if (ROckVelocityMagnitude<ROCK::minVelocity)
          ROckVelocityMagnitude=ROCK::minVelocity;
        ROckVelocity*=ROckVelocityMagnitude/ROckVelocity.Magnitude();
        ROckVMSum+=ROckVelocity;
       }
      else
       {ROckAngularVelocity=ROCKAngularVelocity
                            +.2*ROCKAngularVelocity*gary_rand::rand_16()/RAND_MAX_16-.1*ROCKAngularVelocity
                            -ROckAVSum;
        Vector2d randomVec(gary_rand::rand_16()-RAND_MAX_16/2,gary_rand::rand_16()-RAND_MAX_16/2);
        ROckVelocity=ROCKVelocity
                     +.1*ROCKVelocityMagnitude*gary_rand::rand_16()*randomVec/(randomVec.Magnitude()*RAND_MAX_16)
                     -ROckVMSum;
        if ((ROckVelocityMagnitude=ROckVelocity.Magnitude())<ROCK::minVelocity)
          ROckVelocity*=ROCK::minVelocity/ROckVelocityMagnitude;
       }
      double rockMaxAngularVelocity=4*ROckAngularVelocity,
             rockMaxVelocityMagnitude=2*ROckVelocityMagnitude;
      for(int k=0,
              rockIndex=ROckIndex*sizeof(rocks)*sizeof(ROck)/(sizeof(rock)*sizeof(ROcks));
          k<sizeof(rocks)*sizeof(ROck)/(sizeof(rock)*sizeof(ROcks));
          ++rockIndex,++k)
       {double rockAngularVelocity,
               rockAVSum=0,
               rockVelocityMagnitude;
        Vector2d rockVelocity(gary_rand::rand_16()-RAND_MAX_16/2,gary_rand::rand_16()-RAND_MAX_16/2),
                 rockVMSum;
        if (k!=sizeof(rocks)*sizeof(ROck)/(sizeof(rock)*sizeof(ROcks)))
         {rockAngularVelocity=2*rockMaxAngularVelocity*gary_rand::rand_16()/RAND_MAX_16
                              -rockMaxAngularVelocity;
          rockAVSum+=rockAngularVelocity;
          rockVelocityMagnitude=rockMaxVelocityMagnitude*gary_rand::rand_16()/RAND_MAX_16;
          if (rockVelocityMagnitude<ROCK::minVelocity)
            rockVelocityMagnitude=ROCK::minVelocity;
          rockVelocity*=rockVelocityMagnitude/rockVelocity.Magnitude();
          rockVMSum+=rockVelocity;
         }
        else
         {rockAngularVelocity=ROckAngularVelocity
                              +.2*ROckAngularVelocity*gary_rand::rand_16()/RAND_MAX_16-.1*ROckAngularVelocity
                              -rockAVSum;
          Vector2d randomVec(gary_rand::rand_16()-RAND_MAX_16/2,gary_rand::rand_16()-RAND_MAX_16/2);
          rockVelocity=ROckVelocity
                       +.1*ROckVelocityMagnitude*gary_rand::rand_16()*randomVec/(randomVec.Magnitude()*RAND_MAX_16)
                       -rockVMSum;
          if ((rockVelocityMagnitude=rockVelocity.Magnitude())<ROCK::minVelocity)
            rockVelocity*=ROCK::minVelocity/rockVelocityMagnitude;
         }
        rocks[rockIndex].SetRock(rockVelocity,
                                 rockGraphic[3*gary_rand::rand_16()/(RAND_MAX_16+1)],
                                 rockAngularVelocity,
	                               rock::score);
        ROcks[ROckIndex].spawner[k]=&rocks[rockIndex];
       }
      ROcks[ROckIndex].SetRock(ROckVelocity,
                               ROckGraphic[3*gary_rand::rand_16()/(RAND_MAX_16+1)],
                               ROckAngularVelocity,
	                             ROck::score);
      ROCKs[i].spawner[j]=&ROcks[ROckIndex];
     }
    ROCKs[i].SetRock(ROCKVelocity,
                     ROCKGraphic[3*gary_rand::rand_16()/(RAND_MAX_16+1)],
                     ROCKAngularVelocity,
	                   ROCK::score);
   }
  double ROCKPosWidth=PlayingField::playArea.Width()-2*ROCK::scale,
         ROCKPosHeight=PlayingField::playArea.Height()-2*ROCK::scale;
  for(int i=0;i<numROCKs;++i)
    {do
       ROCKs[i].CurrentBox().MoveBox((2*gary_rand::rand_16()/(RAND_MAX_16+1)
                                     ? Vector2d(ROCKPosWidth*(2*gary_rand::rand_16()/(RAND_MAX_16+1))+ROCK::scale,
                                                ROCKPosHeight*gary_rand::rand_16()/(RAND_MAX_16+1)+ROCK::scale)
                                     : Vector2d(ROCKPosWidth*gary_rand::rand_16()/(RAND_MAX_16+1)+ROCK::scale,
                                                ROCKPosHeight*(2*gary_rand::rand_16()/(RAND_MAX_16+1))+ROCK::scale))
                                     +PlayingField::playArea.NorthWestCorner()
                                     -ROCKs[i].CurrentBox().Center());
     while(!shipGroup.hyper.hyperspacing&&Intersect(ROCKs[i].CurrentBox(),shipGroup.ship->CurrentBox()));
     playingField.selfPermeableList.SetCurrentAtHole().GetData()=&ROCKs[i];
     playingField.selfPermeableList.SetCurrentAtHead().AddPrior();
     XCopyArea(stage.display,
               ROCKs[i].ObjectRotator().GetPixAtTime(0),
               playingField.pixmap,
               playingField.gc,
               0,0,
               ROCKs[i].ObjectRotator().PixWidth(),
               ROCKs[i].ObjectRotator().PixHeight(),
               ROCKs[i].CurrentBox().NorthWestCorner().x+.5,
               ROCKs[i].CurrentBox().NorthWestCorner().y+.5);
    }
 }

void RockGroup::ResetMinVelocity(const double newMinVelocity)
 {playingField.selfPermeableList.SetCurrentAtHead();
  for (int i=0;i<playingField.selfPermeableList.GetNumItems();++i)
   {((Rock*)playingField.selfPermeableList.GetData())->AlterMinVelocity(newMinVelocity);
    playingField.selfPermeableList.Next();
   }
 }

void RockGroup::ResetMaxVelocity(const double newMaxVelocity)
 {playingField.selfPermeableList.SetCurrentAtHead();
  for (int i=0;i<playingField.selfPermeableList.GetNumItems();++i)
   {((Rock*)playingField.selfPermeableList.GetData())->AlterMaxVelocity(newMaxVelocity);
    playingField.selfPermeableList.Next();
   }
 }

void RockGroup::ResetMaxAngularVelocity(const double newMaxAngularVelocity)
 {playingField.selfPermeableList.SetCurrentAtHead();
  for (int i=0;i<playingField.selfPermeableList.GetNumItems();++i)
   {((Rock*)playingField.selfPermeableList.GetData())->AlterMaxAngularVelocity(newMaxAngularVelocity);
    playingField.selfPermeableList.Next();
   }
 }

void RockGroup::ResetVelocityLimits(const double newVelLimit)
 {playingField.selfPermeableList.SetCurrentAtHead();
  for (int i=0;i<playingField.selfPermeableList.GetNumItems();++i)
   {((Rock*)playingField.selfPermeableList.GetData())->AlterVelocityLimits(newVelLimit);
    playingField.selfPermeableList.Next();
   }
 }

void RockGroup::AdjustFramesPerSec(const double frameRatio)
 {playingField.selfPermeableList.SetCurrentAtHead();
  for (int i=0;i<playingField.selfPermeableList.GetNumItems();++i)
   {((Rock*)playingField.selfPermeableList.GetData())->AlterFramesPerSec(frameRatio);
    playingField.selfPermeableList.Next();
   }
 }

void RockGroup::ResetScore(const double scoreFactor)
 {playingField.selfPermeableList.SetCurrentAtHead();
  for (int i=0;i<playingField.selfPermeableList.GetNumItems();++i)
   {((Rock*)playingField.selfPermeableList.GetData())->AlterScore(scoreFactor);
    playingField.selfPermeableList.Next();
   }
 }

#endif
