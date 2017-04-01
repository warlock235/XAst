#ifndef _EXPLOSIONGRAPHIC_H
#define _EXPLOSIONGRAPHIC_H

#include<X11/Xlib.h>
#include<new>
#include"../../gamePlay/stage.H"
#include"../../utilities/pixmaps/composite/compositePixmap.H"
#include"../../bitmaps/explosionEdge.xbm"
#include"../../bitmaps/explosionMiddle.xbm"
#include"../../bitmaps/explosionCenter.xbm"

class ExplosionGraphic
 {public:
    static const int numFrames;

    CompositePixmap* const frames;
    GC gc[5];

    ExplosionGraphic();
    ~ExplosionGraphic();

  private:

    Pixmap clipMask[3];

    static XColor hottest,
                  hotter,
                  hot;
 };

extern ExplosionGraphic explosionGraphic;

const int ExplosionGraphic::numFrames=5;

XColor ExplosionGraphic::hottest={0,
                                  65535,//255
                                  65535,//255
                                  65535,//255
                                  DoRed|DoGreen|DoBlue},
       ExplosionGraphic::hotter={0,
                                 65535,//255
                                 65535,//255
                                 0,
                                 DoRed|DoGreen|DoBlue},
       ExplosionGraphic::hot={0,
                              65535,//255
                              42405,//165
                              0,
                              DoRed|DoGreen|DoBlue};
inline ExplosionGraphic::ExplosionGraphic(): frames((CompositePixmap*)new char[sizeof(CompositePixmap)*numFrames])
 {(new(&frames[0]) CompositePixmap(stage.display,stage.window,
                                   explosionEdge_width,explosionEdge_height))
      ->AddBitmapData(explosionCenter_bits,
                      explosionCenter_width,explosionCenter_height,
                      hottest);
  (new(&frames[1]) CompositePixmap(stage.display,stage.window,
                                   explosionEdge_width,explosionEdge_height))
      ->AddBitmapData(explosionMiddle_bits,
                      explosionMiddle_width,explosionMiddle_height,
                      hotter)
       .AddBitmapData(explosionCenter_bits,
                      explosionCenter_width,explosionCenter_height,
                      hottest);
  (new(&frames[2]) CompositePixmap(stage.display,stage.window,
                                   explosionEdge_width,explosionEdge_height))
      ->AddBitmapData(explosionEdge_bits,
                      explosionEdge_width,explosionEdge_height,
                      hot)
       .AddBitmapData(explosionMiddle_bits,
                      explosionMiddle_width,explosionMiddle_height,
                      hotter)
       .AddBitmapData(explosionCenter_bits,
                      explosionCenter_width,explosionCenter_height,
                      hottest);
  (new(&frames[3]) CompositePixmap(stage.display,stage.window,
                                  explosionEdge_width,explosionEdge_height))
      ->AddBitmapData(explosionEdge_bits,
                      explosionEdge_width,explosionEdge_height,
                      hot)
       .AddBitmapData(explosionMiddle_bits,
                      explosionMiddle_width,explosionMiddle_height,
                      hotter)
       .AddBitmapData(explosionCenter_bits,
                      explosionCenter_width,explosionCenter_height,
                      hottest);
  (new(&frames[4]) CompositePixmap(stage.display,stage.window,
                                  explosionEdge_width,explosionEdge_height))
      ->AddBitmapData(explosionMiddle_bits,
                      explosionMiddle_width,explosionMiddle_height,
                      hot)
       .AddBitmapData(explosionCenter_bits,
                      explosionCenter_width,explosionCenter_height,
                      hotter);
  clipMask[0]=XCreateBitmapFromData(stage.display,stage.window,
                                    (const char * const)explosionCenter_bits,
                                    explosionCenter_width,explosionCenter_height);
  clipMask[1]=XCreateBitmapFromData(stage.display,stage.window,
                                    (const char * const)explosionMiddle_bits,
                                    explosionMiddle_width,explosionMiddle_height);
  clipMask[2]=XCreateBitmapFromData(stage.display,stage.window,
                                    (const char * const)explosionEdge_bits,
                                    explosionEdge_width,explosionEdge_height);
  gc[0]=XCreateGC(stage.display,stage.window,NULL,0);
  XSetGraphicsExposures(stage.display,gc[0],FALSE);
  XSetClipMask(stage.display,gc[0],clipMask[0]);
  gc[1]=XCreateGC(stage.display,stage.window,NULL,0);
  XSetGraphicsExposures(stage.display,gc[1],FALSE);
  XSetClipMask(stage.display,gc[1],clipMask[1]);
  gc[2]=XCreateGC(stage.display,stage.window,NULL,0);
  XSetGraphicsExposures(stage.display,gc[2],FALSE);
  XSetClipMask(stage.display,gc[2],clipMask[2]);
  gc[3]=XCreateGC(stage.display,stage.window,NULL,0);
  XSetGraphicsExposures(stage.display,gc[3],FALSE);
  XSetClipMask(stage.display,gc[3],clipMask[2]);
  gc[4]=XCreateGC(stage.display,stage.window,NULL,0);
  XSetGraphicsExposures(stage.display,gc[4],FALSE);
  XSetClipMask(stage.display,gc[4],clipMask[1]);
 }

inline ExplosionGraphic::~ExplosionGraphic()
 {for(int i=5;i--;)
    XFreeGC(stage.display,gc[i]);
  for(int i=3;i--;)
    XFreePixmap(stage.display,clipMask[i]);
  for(int i=numFrames;i--;)
    frames[i].~CompositePixmap();
  delete [] (char*)frames;
 }

#endif
