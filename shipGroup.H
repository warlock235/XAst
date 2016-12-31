#include<stdlib.h>
#include<X11/Xlib.h>
#include"vector2d.H"
#include"box.H"
#include"compositePixmap.H"
#include"rotatorDisplayData.H"
#include"rotator.H"
#include"frameList.H"
#include"frameTimer.H"
#include"movableObject.H"
#include"intersection2d.H"
#include"explosion.H"
#include"shipBulletGroup.H"
#include"stage.H"
#include"options.H"

#ifdef _CORP_LOGO_
#include"starDestroyerDecor.xbm"
#else
#include"fortytwo.xbm"
#endif

#include"starDestroyerThrustEdge.xbm"
#include"starDestroyerThrustMiddle.xbm"
#include"starDestroyerThrustCenter.xbm"
#include"starDestroyerIcon.xbm"
#include"NCC1701DDecorBottom.xbm"
#include"NCC1701DDecorTop.xbm"
#include"NCC1701DThrustDecor.xbm"
#include"NCC1701DIcon.xbm"
#include"NCC1701ADecor.xbm"
#include"NCC1701AThrustDecor.xbm"
#include"NCC1701AIcon.xbm"

#ifndef _SHIPGROUP_H
#define _SHIPGROUP_H

class Ship: public MovableObject
 {public:
    typedef int Boolean;
    enum {off, on};

    Ship(const unsigned char* const icon,
         const int iconWidth, const int iconHeight,
         XColor& iconColor);
    virtual ~Ship();
    virtual Rotator& ObjectRotator()=0;
    virtual void MissScript(Intersector&, const double createTime,
                                          const double existTime);
    virtual void HitScript(Intersector&, const double createTime,
                                         const double existTime,
                                         const Vector2d& intersectPoint);

    const unsigned char* const icon;
    const int iconWidth,
              iconHeight;
    XColor iconColor;
    static double maxVelocity,
                  acceleration,
                  angularVelocity;
    Boolean dead;
 };

class StarDestroyer: public Ship
 {public:
    StarDestroyer();
    virtual Rotator& ObjectRotator();

  private:
    static const Vector2d vectors[5];
    static XColor color;
    RotVectorData graphic;
    Rotator rotator;
 };

class NextGenerationEnterprise: public Ship
 {public:
    NextGenerationEnterprise();
    virtual ~NextGenerationEnterprise();
    virtual Rotator& ObjectRotator();

  private:
    static const Vector2d vectors[34];
    static XColor bottomColor,
                  topColor;
    static const double area;
    RotVectorData* graphic;
    Rotator* rotator;
 };

class MovieEnterprise: public Ship
 {public:
    MovieEnterprise();
    virtual Rotator& ObjectRotator();

  private:
    static const Vector2d vectors[32];
    static XColor color;
    static const double area;
    RotVectorData graphic;
    Rotator rotator;
 };

class Thrust: public MovableObject
 {public:
    typedef int Boolean;
    enum {off, on};

    Thrust();
    virtual ~Thrust();
    virtual Rotator& ObjectRotator()=0;
    virtual void MissScript(Intersector&, const double createTime,
                                          const double existTime);
    Boolean thrusting;
 };

class StarDestroyerThrust: public Thrust
 {public:
    StarDestroyerThrust();
    virtual ~StarDestroyerThrust();
    virtual Rotator& ObjectRotator();

  private:
    static XColor edgeColor,
                  middleColor,
                  centerColor;
    RotPixmapData* graphic;
    Rotator* rotator;
 };

class NextGenerationEnterpriseThrust: public Thrust
 {public:
    NextGenerationEnterpriseThrust();
    virtual Rotator& ObjectRotator();

  private:
    static XColor color;
    RotPixmapData graphic;
    Rotator rotator;
 };

class MovieEnterpriseThrust: public Thrust
 {public:
    MovieEnterpriseThrust();
    virtual Rotator& ObjectRotator();
    virtual void MissScript(Intersector&, const double createTime,
                                          const double existTime);

  private:
    static XColor color;
    MaskedRotPixmapData graphic;
    Rotator rotator;
 };


class ShipGroup;
class Hyper: public MovableObject
 {friend class ShipGroup;
  friend class Options;
  public:
    typedef int Boolean;
    enum {off, on};

    Hyper();
    virtual void MissScript(Intersector&, const double createTime,
                                          const double existTime);

    Boolean hyperspacing;
    static double percentDestructRate;
    static int destructRate;

  private:
    int hyperCount;
 };


class ShipGroup
{friend class Options;
  public:
    StarDestroyer starDestroyer;
    StarDestroyerThrust starDestroyerThrust;
    NextGenerationEnterprise NCC1701D;
    NextGenerationEnterpriseThrust NCC1701DThrust;
    MovieEnterprise NCC1701A;
    MovieEnterpriseThrust NCC1701AThrust;

    Hyper hyper;
    Explosion explosion;

    static Ship* ship;
    static Thrust* thrust;

    static const int maxIconHeight,
                     maxIconWidth;

    inline void NewShip();
    inline void NewThrust();
    inline void NewHyper();
    inline void ResetAcceleration(const double newAcceleration);
    inline void ResetAngularVelocity(const double newAngularVelocity);
    inline void ResetAccelerationLimits(const double newMaxAcceleration);
    inline void ResetVelocityLimits(const double newMaxVelocity);
    inline void AdjustFramesPerSec(const double frameRatio);
 };

extern ShipGroup shipGroup;

#include"playingField.H"


double Ship::maxVelocity=.43*PlayingField::maxLinearVelocity,
       Ship::acceleration=1.425,
       Ship::angularVelocity=0.2;

inline Ship::Ship(const unsigned char* const i,
                  const int iWidth, const int iHeight,
                  XColor& iColor): icon(i),
                                   iconWidth(iWidth),
                                   iconHeight(iHeight),
                                   iconColor(iColor),
                                   dead(on)
 {if (!XAllocColor(stage.display,DefaultColormap(stage.display,
                                                 DefaultScreen(stage.display)),
                   &iconColor))
    iconColor.pixel=WhitePixel(stage.display,DefaultScreen(stage.display));
 }

Ship::~Ship()
 {
 }

void Ship::MissScript(Intersector& intersector,
                      const double createTime, const double existTime)
 {ObjectRotator().UpdateAngle(existTime);
  ObjectLiner().UpdateVelocity(existTime);
  shipBulletGroup.Fire(intersector,createTime+existTime);
  XCopyArea(stage.display,
            ObjectRotator().GetPixAtTime(0),
            playingField.pixmap,
            playingField.gc,
            0,0,
            ObjectRotator().PixWidth(),
            ObjectRotator().PixHeight(),
            CurrentBox().WrapMovingBox(PlayingField::playArea,
                                       ObjectLiner().Velocity())
                        .NorthWestCorner().x+.5,
            CurrentBox().NorthWestCorner().y+.5);
 }

void Ship::HitScript(Intersector& intersector,
                     const double createTime, const double existTime,
                     const Vector2d& intersectPoint)
 {intersector.RemoveNonPermeable(this);
  if (shipGroup.thrust->thrusting)
    intersector.RemovePermeable(shipGroup.thrust);
  shipGroup.hyper.hyperspacing=Hyper::on;
  dead=on;
  shipGroup.explosion.CurrentBox().MoveBox(ObjectLiner()
                                           .Move(OldBox().Center(),existTime)
		                          -shipGroup.explosion.CurrentBox().Center());
  ObjectLiner().UpdateVelocity(existTime);
  shipGroup.explosion.ObjectLiner().Velocity()=ObjectLiner().Velocity();
  shipGroup.explosion.frameList.Reset();
  shipGroup.explosion.frameTimer.Reset();
  intersector.AddPermeable(&shipGroup.explosion,createTime+existTime);
  if (playingField.lastHitScore)
   {score.CurrentScore()+=playingField.lastHitScore;
    playingField.lastHitScore=0;
   }
  else
    playingField.lastHitFromAlly=!playingField.lastHitFromAlly;
 }

const Vector2d StarDestroyer::vectors[5]={Vector2d(0,-19),
                                          Vector2d(8,11),
                                          Vector2d(4,7),
                                          Vector2d(-4,7),
                                          Vector2d(-8,11)};

XColor StarDestroyer::color={0,
                             44461,//173
                             55512,//216
                             59110,//230
                             DoRed|DoGreen|DoBlue};

inline StarDestroyer::StarDestroyer(): Ship(starDestroyerIcon_bits,
                                            starDestroyerIcon_width,
                                            starDestroyerIcon_height,
                                            color),
                                       graphic(stage.display,stage.window,color,
                                               vectors,sizeof(vectors)/sizeof(Vector2d),
#ifdef _CORP_LOGO_
                                               starDestroyerDecor_bits,
                                               starDestroyerDecor_width,starDestroyerDecor_height),
#else
                                               fortytwo_bits,
                                               fortytwo_width,fortytwo_height),
#endif
                                               rotator(&graphic,angularVelocity,PlayingField::maxLinearVelocity)
 {SetMovableObject(Vector2d(),2*rotator.Radius(),2*rotator.Radius(),
                   Vector2d(),maxVelocity,Vector2d());
 }

Rotator& StarDestroyer::ObjectRotator()
 {return rotator;
 }

const Vector2d NextGenerationEnterprise::vectors[34]={Vector2d(0,-10),
                                                      Vector2d(8,-8),
                                                      Vector2d(10,-6),
                                                      Vector2d(11,-2),
                                                      Vector2d(10,2),
                                                      Vector2d(8,4),
                                                      Vector2d(2,7),
                                                      Vector2d(3,8),
                                                      Vector2d(2,13),
                                                      Vector2d(4,15),
                                                      Vector2d(6,15),
                                                      Vector2d(6,8),
                                                      Vector2d(7,7),
                                                      Vector2d(8,8),
                                                      Vector2d(8,19),
                                                      Vector2d(6,19),
                                                      Vector2d(3,17),
                                                      Vector2d(0,17),
                                                      Vector2d(-3,17),
                                                      Vector2d(-6,19),
                                                      Vector2d(-8,19),
                                                      Vector2d(-8,8),
                                                      Vector2d(-7,7),
                                                      Vector2d(-6,8),
                                                      Vector2d(-6,15),
                                                      Vector2d(-4,15),
                                                      Vector2d(-2,13),
                                                      Vector2d(-3,8),
                                                      Vector2d(-2,7),
                                                      Vector2d(-8,4),
                                                      Vector2d(-10,2),
                                                      Vector2d(-11,-2),
                                                      Vector2d(-10,-6),
                                                      Vector2d(-8,-8)};

XColor NextGenerationEnterprise::bottomColor={0,
                                              61680,//240
                                              61680,//240
                                              61680,//240
                                              DoRed|DoGreen|DoBlue},
       NextGenerationEnterprise::topColor={0,
                                           49344,//192
                                           0,//0
                                           0,//0
                                           DoRed|DoGreen|DoBlue};

const double NextGenerationEnterprise::area=472;

inline NextGenerationEnterprise::NextGenerationEnterprise(): Ship(NCC1701DIcon_bits,
                                                                  NCC1701DIcon_width,
                                                                  NCC1701DIcon_height,
                                                                  bottomColor)
 {CompositePixmap NextGenerationEnterpriseCP(stage.display,stage.window,
                                             NCC1701DDecorBottom_width,
                                             NCC1701DDecorBottom_height);
  NextGenerationEnterpriseCP.AddBitmapData(NCC1701DDecorBottom_bits,
                                           NCC1701DDecorBottom_width,
                                           NCC1701DDecorBottom_height,
                                           bottomColor)
                            .AddBitmapData(NCC1701DDecorTop_bits,
                                           NCC1701DDecorTop_width,
                                           NCC1701DDecorTop_height,
                                           topColor);
  graphic=new RotVectorData(stage.display,stage.window,bottomColor,
                            vectors,sizeof(vectors)/sizeof(Vector2d),
                            area,
                            NextGenerationEnterpriseCP);
  rotator=new Rotator(graphic,angularVelocity,PlayingField::maxLinearVelocity);
  SetMovableObject(Vector2d(),2*rotator->Radius(),2*rotator->Radius(),
                   Vector2d(),maxVelocity,Vector2d());
 }

NextGenerationEnterprise::~NextGenerationEnterprise()
 {delete rotator;
  delete graphic;
 }

Rotator& NextGenerationEnterprise::ObjectRotator()
 {return *rotator;
 }

const Vector2d MovieEnterprise::vectors[32]={Vector2d(0,-16),
                                             Vector2d(6,-14),
                                             Vector2d(7,-13),
                                             Vector2d(9,-7),
                                             Vector2d(7,-1),
                                             Vector2d(6,0),
                                             Vector2d(2,2),
                                             Vector2d(2,6),
                                             Vector2d(7,11),
                                             Vector2d(7,4),
                                             Vector2d(8,4),
                                             Vector2d(8,27),
                                             Vector2d(7,26),
                                             Vector2d(7,13),
                                             Vector2d(2,7),
                                             Vector2d(1,14),
                                             Vector2d(0,15),
                                             Vector2d(-1,14),
                                             Vector2d(-2,7),
                                             Vector2d(-7,13),
                                             Vector2d(-7,26),
                                             Vector2d(-8,27),
                                             Vector2d(-8,4),
                                             Vector2d(-7,4),
                                             Vector2d(-7,11),
                                             Vector2d(-2,6),
                                             Vector2d(-2,2),
                                             Vector2d(-6,0),
                                             Vector2d(-7,-1),
                                             Vector2d(-9,-7),
                                             Vector2d(-7,-13),
                                             Vector2d(-6,-14)};

XColor MovieEnterprise::color={0,
                               61680,//240
                               61680,//240
                               61680,//240
                               DoRed|DoGreen|DoBlue};

const double MovieEnterprise::area=446;

inline MovieEnterprise::MovieEnterprise(): Ship(NCC1701AIcon_bits,
                                                NCC1701AIcon_width,
                                                NCC1701AIcon_height,
                                                color),
                                           graphic(stage.display,stage.window,color,
                                                   vectors,sizeof(vectors)/sizeof(Vector2d),
                                                   area,
                                                   NCC1701ADecor_bits,
                                                   NCC1701ADecor_width,NCC1701ADecor_height),
                                           rotator(&graphic,angularVelocity,PlayingField::maxLinearVelocity)
 {SetMovableObject(Vector2d(),2*rotator.Radius(),2*rotator.Radius(),
                   Vector2d(),maxVelocity,Vector2d());
 }

Rotator& MovieEnterprise::ObjectRotator()
 {return rotator;
 }

inline Thrust::Thrust(): thrusting(off)
 {
 }

Thrust::~Thrust()
 {
 }

void Thrust::MissScript(Intersector& intersector, const double createTime,
                        const double existTime)
 {shipGroup.NewThrust();
  XCopyArea(stage.display,
            ObjectRotator().GetPixAtTime(0),
            playingField.pixmap,
            playingField.gc,
            0,0,
            ObjectRotator().PixWidth(),
            ObjectRotator().PixHeight(),
            CurrentBox().WrapMovingBox(PlayingField::playArea,
                                       ObjectLiner().Velocity())
                        .NorthWestCorner().x+.5,
            CurrentBox().NorthWestCorner().y+.5);
 }

XColor StarDestroyerThrust::edgeColor={0,
                                       0,
                                       0,
                                       65535,//255
                                       DoRed|DoGreen|DoBlue},
       StarDestroyerThrust::middleColor={0,
                                         0,
                                         49087,//191
                                         65535,//255
                                         DoRed|DoGreen|DoBlue},
       StarDestroyerThrust::centerColor={0,
                                         61680,//240
                                         63736,//248
                                         65535,//255
                                         DoRed|DoGreen|DoBlue};

inline StarDestroyerThrust::StarDestroyerThrust()
 {CompositePixmap thrustCP(stage.display,stage.window,
                           starDestroyerThrustEdge_width,starDestroyerThrustEdge_height);
  thrustCP.AddBitmapData(starDestroyerThrustEdge_bits,
                         starDestroyerThrustEdge_width,starDestroyerThrustEdge_height,
                         edgeColor)
          .AddBitmapData(starDestroyerThrustMiddle_bits,
                         starDestroyerThrustMiddle_width,starDestroyerThrustMiddle_height,
                         middleColor)
          .AddBitmapData(starDestroyerThrustCenter_bits,
                         starDestroyerThrustCenter_width,starDestroyerThrustCenter_height,
                         centerColor);
  graphic=new RotPixmapData(stage.display,stage.window,thrustCP);
  rotator=new Rotator(graphic,Ship::angularVelocity,PlayingField::maxLinearVelocity);
  SetMovableObject(Vector2d(),2*rotator->Radius(),2*rotator->Radius(),
                   Vector2d(),Ship::maxVelocity,Vector2d());
 }

inline StarDestroyerThrust::~StarDestroyerThrust()
 {delete rotator;
  delete graphic;
 }

Rotator& StarDestroyerThrust::ObjectRotator()
 {return *rotator;
 }

XColor NextGenerationEnterpriseThrust::color={0,
                                              65535,//255
                                              0,
                                              0,
                                              DoRed|DoGreen|DoBlue};

inline NextGenerationEnterpriseThrust::NextGenerationEnterpriseThrust(): graphic(stage.display,stage.window,color,
                                                                                 NCC1701DThrustDecor_bits,
                                                                                 NCC1701DThrustDecor_width,
                                                                                 NCC1701DThrustDecor_height),
                                                                         rotator(&graphic,Ship::angularVelocity,
                                                                                 PlayingField::maxLinearVelocity)
 {SetMovableObject(Vector2d(),2*rotator.Radius(),2*rotator.Radius(),
                   Vector2d(),Ship::maxVelocity,Vector2d());
 }

Rotator& NextGenerationEnterpriseThrust::ObjectRotator()
 {return rotator;
 }

XColor MovieEnterpriseThrust::color={0,
                                     65535,//255
                                     0,
                                     0,
                                     DoRed|DoGreen|DoBlue};

inline MovieEnterpriseThrust::MovieEnterpriseThrust():
                       graphic(stage.display,stage.window,color,
                               NCC1701AThrustDecor_bits,
                               NCC1701AThrustDecor_width,NCC1701AThrustDecor_height),
                       rotator(&graphic,Ship::angularVelocity,PlayingField::maxLinearVelocity)
 {SetMovableObject(Vector2d(),2*rotator.Radius(),2*rotator.Radius(),
                   Vector2d(),Ship::maxVelocity,Vector2d());
 }

Rotator& MovieEnterpriseThrust::ObjectRotator()
 {return rotator;
 }

void MovieEnterpriseThrust::MissScript(Intersector& intersector, const double createTime,
                                       const double existTime)
 {shipGroup.NewThrust();
  int destX=CurrentBox().WrapMovingBox(PlayingField::playArea,
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

double Hyper::percentDestructRate=1.25;

int Hyper::destructRate=RAND_MAX_16*percentDestructRate/100;

inline Hyper::Hyper(): MovableObject(Vector2d(),
                                     3*shipGroup.ship->ObjectRotator().PixWidth(),
                                     3*shipGroup.ship->ObjectRotator().PixHeight(),
                                     Vector2d(),0,Vector2d()),
                       hyperspacing(on),
                       hyperCount(-destructRate)
 {
 }

void Hyper::MissScript(Intersector& intersector,
                       const double createTime, const double existTime)
 {playingField.nonPermeableList.SetCurrentAtHead();
  for (int i=0; i<playingField.nonPermeableList.GetNumItems(); ++i)
   {if (Intersect(playingField.nonPermeableList.GetData()->CurrentBox(),
                  CurrentBox()))
      return;
    playingField.nonPermeableList.Next();
   }
  playingField.selfPermeableList.SetCurrentAtHead();
  for (int i=0; i<playingField.selfPermeableList.GetNumItems(); ++i)
   {if (Intersect(playingField.selfPermeableList.GetData()->CurrentBox(),
                  CurrentBox()))
      return;
    playingField.selfPermeableList.Next();
   }
  intersector.RemovePermeable(this);
  if (gary_rand::rand_16()>(hyperCount+=destructRate))
   {shipGroup.ship->CurrentBox().MoveBox(CurrentBox().Center()
                                         -shipGroup.ship->CurrentBox().Center());
    shipGroup.ship->ObjectLiner().Velocity()=Vector2d();
    shipGroup.ship->ObjectLiner().Acceleration()=Vector2d();
    shipGroup.ship->ObjectRotator().AngularVelocity()=0;
    intersector.AddNonPermeable(shipGroup.ship,createTime+existTime);
    XCopyArea(stage.display,
	            shipGroup.ship->ObjectRotator().GetPixAtTime(0),
              playingField.pixmap,
              playingField.gc,
              0,0,
	            shipGroup.ship->ObjectRotator().PixWidth(),
	            shipGroup.ship->ObjectRotator().PixHeight(),
	            shipGroup.ship->CurrentBox().NorthWestCorner().x+.5,
	            shipGroup.ship->CurrentBox().NorthWestCorner().y+.5);
    shipGroup.thrust->thrusting=Thrust::off;
    shipGroup.hyper.hyperspacing=Hyper::off;
   }
  else
   {shipGroup.explosion.CurrentBox().MoveBox(CurrentBox().Center()
	                                    -shipGroup.explosion.CurrentBox().Center());
    shipGroup.explosion.ObjectLiner().Velocity()=Vector2d();
    intersector.AddPermeable(&shipGroup.explosion,createTime+existTime);
    shipGroup.explosion.frameList.Reset();
    int destX=shipGroup.explosion.CurrentBox().NorthWestCorner().x+.5,
        destY=shipGroup.explosion.CurrentBox().NorthWestCorner().y+.5;
    GC& gc=explosionGraphic.gc[0];
    XSetClipOrigin(stage.display,gc,destX,destY);
    XCopyArea(stage.display,
              shipGroup.explosion.frameList.GetFrame(),
              playingField.pixmap,
              gc,
              0,0,
              shipGroup.explosion.frameList.PixWidth(),
              shipGroup.explosion.frameList.PixHeight(),
	            destX,destY);
    shipGroup.explosion.frameList.UpdateFrameNumber();
    shipGroup.explosion.frameTimer.Reset().TimerAlarm();
   }
 }

#define max(a,b) (a>b?a:b)
const int ShipGroup::maxIconHeight=max(max(starDestroyerIcon_height,
                                           NCC1701DIcon_height),
                                       NCC1701AIcon_height),
          ShipGroup::maxIconWidth=max(max(starDestroyerIcon_width,
                                          NCC1701DIcon_width),
                                      NCC1701AIcon_width);
#undef max

Ship* ShipGroup::ship=&shipGroup.starDestroyer;

Thrust* ShipGroup::thrust=&shipGroup.starDestroyerThrust;

inline void ShipGroup::NewShip()
 {ship->ObjectRotator().Angle()=0;
  hyper.CurrentBox().MoveBox(PlayingField::playArea.Center()
                             -hyper.CurrentBox().Center());
  hyper.hyperCount=-Hyper::destructRate;
  hyper.hyperspacing=Hyper::on;
  ship->dead=Ship::off;
  shipBulletGroup.fireThisFrame=ShipBulletGroup::off;
  playingField.permeableList.SetCurrentAtHole().GetData()=&hyper;
  playingField.permeableList.SetCurrentAtHead().AddPrior();
 }

inline void ShipGroup::NewThrust()
 {thrust->CurrentBox().MoveBox(ship->CurrentBox().Center()-
                              thrust->CurrentBox().Center());
  thrust->ObjectLiner().Velocity()=ship->ObjectLiner().Velocity();
  Vector2d accelDirection(ship->ObjectRotator().GetVecsAtTime(0)[0]);
  thrust->ObjectLiner().Acceleration()=ship->ObjectLiner().Acceleration()
                                     =ship->acceleration*accelDirection/accelDirection.Magnitude();
  thrust->ObjectRotator().Angle()=ship->ObjectRotator().Angle();
  thrust->ObjectRotator().AngularVelocity()=ship->ObjectRotator().AngularVelocity();
 }

inline void ShipGroup::NewHyper()
 {hyper.CurrentBox().MoveBox(Vector2d((PlayingField::playArea.Width()
                                       -2*ship->ObjectRotator().Radius())*gary_rand::rand_16()/(RAND_MAX_16+1)
                                      +ship->ObjectRotator().Radius(),
                                      (PlayingField::playArea.Height()
                                       -2*ship->ObjectRotator().Radius())*gary_rand::rand_16()/(RAND_MAX_16+1)
                                      +ship->ObjectRotator().Radius())
			                       +PlayingField::playArea.NorthWestCorner()
                             -hyper.CurrentBox().Center());
  hyper.hyperspacing=Hyper::on;
  playingField.permeableList.SetCurrentAtHole().GetData()=&hyper;
  playingField.permeableList.SetCurrentAtHead().AddPrior();
 }

inline void ShipGroup::ResetAngularVelocity(const double newAngularVelocity)
 {starDestroyer.ObjectRotator().AngularVelocity()=
  starDestroyerThrust.ObjectRotator().AngularVelocity()=
  NCC1701A.ObjectRotator().AngularVelocity()=
  NCC1701AThrust.ObjectRotator().AngularVelocity()=
  NCC1701D.ObjectRotator().AngularVelocity()=
  NCC1701DThrust.ObjectRotator().AngularVelocity()=newAngularVelocity;
 }

inline void ShipGroup::ResetAccelerationLimits(const double newMaxAcceleration)
 {starDestroyer.ObjectLiner().MaxAccelerationMagnitude()=
  starDestroyerThrust.ObjectLiner().MaxAccelerationMagnitude()=
  NCC1701A.ObjectLiner().MaxAccelerationMagnitude()=
  NCC1701AThrust.ObjectLiner().MaxAccelerationMagnitude()=
  NCC1701D.ObjectLiner().MaxAccelerationMagnitude()=
  NCC1701DThrust.ObjectLiner().MaxAccelerationMagnitude()=newMaxAcceleration;
 }

inline void ShipGroup::ResetVelocityLimits(const double newMaxVelocity)
 {starDestroyer.ObjectLiner().MaxVelocityMagnitude()=
  starDestroyerThrust.ObjectLiner().MaxVelocityMagnitude()=
  NCC1701A.ObjectLiner().MaxVelocityMagnitude()=
  NCC1701AThrust.ObjectLiner().MaxVelocityMagnitude()=
  NCC1701D.ObjectLiner().MaxVelocityMagnitude()=
  NCC1701DThrust.ObjectLiner().MaxVelocityMagnitude()=
  explosion.ObjectLiner().MaxVelocityMagnitude()=newMaxVelocity;
  starDestroyer.ObjectRotator().UpdateMaxLinearVelocity(PlayingField::maxLinearVelocity);
  NCC1701A.ObjectRotator().UpdateMaxLinearVelocity(PlayingField::maxLinearVelocity);
  NCC1701D.ObjectRotator().UpdateMaxLinearVelocity(PlayingField::maxLinearVelocity);
 }

inline void ShipGroup::AdjustFramesPerSec(const double frameRatio)
 {ship->ObjectLiner().Velocity()=ship->ObjectLiner().Velocity()*frameRatio;
  ship->ObjectLiner().Acceleration()=ship->ObjectLiner().Acceleration()*frameRatio*frameRatio;
  ship->ObjectRotator().AngularVelocity()=ship->ObjectRotator().AngularVelocity()*frameRatio;
  thrust->ObjectLiner().Velocity()=ship->ObjectLiner().Velocity();
  thrust->ObjectLiner().Acceleration()=ship->ObjectLiner().Acceleration();
  thrust->ObjectRotator().AngularVelocity()=ship->ObjectRotator().AngularVelocity();
  explosion.ObjectLiner().Velocity()=explosion.ObjectLiner().Velocity()*frameRatio;
  explosion.ObjectLiner().Acceleration()=
  explosion.ObjectLiner().Acceleration()*frameRatio*frameRatio;
  explosion.frameDelay.framesTillAlarm=double(explosion.frameDelay.framesTillAlarm)/frameRatio+.5;
 }

#endif
