#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#include<X11/Xlib.h>
#include"../../utilities/vector2d.H"
#include"../../utilities/box.H"
#include"../../utilities/frames/frameList.H"
#include"../../utilities/frames/frameTimer.H"
#include"../movableObject.H"
#include"../../utilities/intersection2d.H"
#include"../explosions/explosionGraphic.H"

class Explosion: public MovableObject
 {public:
    inline Explosion();

    virtual void MissScript(Intersector&, const double createTime,
			                                    const double existTime);
    FrameList frameList;
    FrameTimer frameTimer,
               frameDelay;

  protected:
    inline void DisplayFrame();

 };

#include"../../gamePlay/playingField.H"

inline Explosion::Explosion(): frameList(explosionGraphic.frames,
                                         ExplosionGraphic::numFrames,
                                         ExplosionGraphic::numFrames),
		                           frameTimer(ExplosionGraphic::numFrames),
                               frameDelay(1)
 {SetMovableObject(Vector2d(),frameList.PixWidth(),frameList.PixHeight(),
		               Vector2d(),PlayingField::maxLinearVelocity,Vector2d());
 }

inline void Explosion::DisplayFrame()
 {int destX=CurrentBox().WrapMovingBox(PlayingField::playArea,
                                       ObjectLiner().Velocity())
                        .NorthWestCorner().x+.5,
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

void Explosion::MissScript(Intersector& intersector, const double createTime,
                                                     const double existTime)
 {if (frameDelay.TimerAlarm()||frameList.GetFirstFrameNumber()==frameList.GetFrameNumber())
   {frameDelay.Reset();
    if (frameTimer.TimerAlarm())
      intersector.RemovePermeable(this);
    else
     {frameList.UpdateFrameNumber();
      DisplayFrame();
     }
   }
  else
    DisplayFrame();
 }

#endif
