#include"explosion.H"

#ifndef _BULLET_H
#define _BULLET_H

#include"vector2d.H"
#include"box.H"
#include"rotator.H"
#include"frameList.H"
#include"frameTimer.H"
#include<X11/Xlib.h>
#include"movableObject.H"
#include"intersection2d.H"

class BulletExplosion;
class Bullet: public MovableObject
 {friend class BulletExplosion;
  public:
    inline Bullet(Rotator* const,
                  const int numFrames,
                  BulletExplosion* const);
    virtual Rotator& ObjectRotator();
    virtual void MissScript(Intersector&, const double createTime,
                                          const double existTime);
    virtual void HitScript(Intersector&, const double createTime,
                                         const double existTime,
                                         const Vector2d& intersectPoint)=0;

    FrameTimer frameTimer;

  protected:
    typedef int Boolean;
    enum {off, on};
    Rotator* rotator;
    Boolean inactive;
    BulletExplosion* explosion;
 };

class BulletExplosion: public Explosion
 {public:
    inline BulletExplosion(Bullet* const);

    virtual void MissScript(Intersector& intersector, const double createTime,
                    	                                const double existTime);
  private:
    Bullet* bullet;

    inline void DisplayFrame();
 };

#include "playingField.H"

inline Bullet::Bullet(Rotator* const rot,
                       const int numFrames,
                       BulletExplosion* const exp): MovableObject(Vector2d(),
                                                                  2*rot->Radius(),
                                                                  2*rot->Radius(),
         	                                                        Vector2d(),
								                                                  PlayingField::maxLinearVelocity,
                                                                  Vector2d()),
                                                    rotator(rot),
                                                    frameTimer(numFrames),
                                                    inactive(on),
                                                    explosion(exp)
 {
 }

Rotator& Bullet::ObjectRotator()
 {return *rotator;
 }

void Bullet::MissScript(Intersector& intersector, const double createTime,
                                                  const double existTime)
 {if (frameTimer.TimerAlarm())
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

inline BulletExplosion::BulletExplosion(Bullet* const b): bullet(b)
 {
 }

inline void BulletExplosion::DisplayFrame()
 {int destX=CurrentBox().NorthWestCorner().x+.5,
      destY=CurrentBox().NorthWestCorner().y+.5;
  GC& gc=explosionGraphic.gc[frameList.GetFrameNumber()];
  XSetClipOrigin(stage.display,gc,destX,destY);
  XCopyArea(stage.display,
            frameList.GetFrame(),
            playingField.pixmap,
            gc,
            0,0,
            frameList.PixWidth(),
            frameList.PixHeight(),
	    destX,destY);
 }

void BulletExplosion::MissScript(Intersector& intersector, const double createTime,
                   	                                   const double existTime)
 {if (frameDelay.TimerAlarm()||frameList.GetFirstFrameNumber()==frameList.GetFrameNumber())
   {frameDelay.Reset();
    if (frameTimer.TimerAlarm())
     {intersector.RemovePermeable(this);
      bullet->inactive=Bullet::on;
     }
    else
     {frameList.UpdateFrameNumber();
      DisplayFrame();
     }
   }
  else
    DisplayFrame();
 }

#endif
