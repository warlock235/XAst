#ifndef _SHIPYARD_H
#define _SHIPYARD_H

#include<X11/Xlib.h>

class ShipYard
 {public:
    ShipYard(Display* const d, Drawable& drawable,
             const unsigned char* const shipBitmap, const int shipBitmapWidth, const int shipBitmapHeight,
             XColor& shipColor,
             const int yardWidth, const int yardHeight,
             XColor& yardBackground);
    ~ShipYard();
    ShipYard& AddShip();
    ShipYard& RemoveShip();
    const int NumShips() const;
    const Pixmap& GetYard() const;
    ShipYard& ClearYard();
    ShipYard& AlterIcon(const unsigned char* const shipBitmap,
                        const int shipBitmapWidth, const int shipBitmapHeight,
                        XColor& shipColor);

  private:
    ShipYard(const ShipYard&);
    ShipYard& operator=(const ShipYard&);

    int shipWidth,
        shipHeight,
        shipColor,
        numShips,
        maxVisibleShips,
        yardWidth,
        yardHeight,
        yardColor,
        rowStartOffset,
        rowEndOffset,
        colStartOffset,
        lastShipInRowOffset,
        shipRow,
        shipCol;

    GC gc;

    Pixmap yard,
           ship,
           shipErase;

    Display* const display;
 };

inline ShipYard::ShipYard(Display* const d, Drawable& drawable,
                          const unsigned char* const shipBits,
                          const int shipBitsWidth, const int shipBitsHeight,
                          XColor& shipForeground,
    		                  const int yWidth, const int yHeight,
                          XColor& yardBackground): shipWidth(shipBitsWidth),
                                                   shipHeight(shipBitsHeight),
                                                   numShips(0),
                                                   maxVisibleShips(((yHeight-10)/shipBitsHeight)*((yWidth-10)/shipBitsWidth)),
                                                   yardWidth(yWidth),
                                                   yardHeight(yHeight),
                                                   rowStartOffset((yWidth-10)%shipBitsWidth/2+5),
                                                   rowEndOffset(rowStartOffset+shipBitsWidth*((yWidth-10)/shipBitsWidth)),
                                                   colStartOffset((yHeight-10)%shipBitsHeight/2+5),
                                                   lastShipInRowOffset(rowEndOffset-shipBitsWidth),
                                                   shipRow(rowStartOffset-shipBitsWidth),
                                                   shipCol(colStartOffset),
                                                   display(d)
 {int screen=DefaultScreen(display);
  yardColor=XAllocColor(display,DefaultColormap(display,screen),&yardBackground)
           ? yardBackground.pixel
           : WhitePixel(display,screen);
  gc=XCreateGC(display,drawable,0,NULL);
  yard=XCreatePixmap(display,drawable,yWidth,yHeight,DefaultDepth(display,screen));
  XSetForeground(display,gc,yardColor);
  XFillRectangle(display,yard,gc,0,0,yWidth,yHeight);
  shipErase=XCreatePixmap(display,yard,shipBitsWidth,shipBitsHeight,DefaultDepth(display,screen));
  XFillRectangle(display,shipErase,gc,0,0,shipBitsWidth,shipBitsHeight);
  shipColor=XAllocColor(display,DefaultColormap(display,screen),&shipForeground)
           ? shipForeground.pixel
           : WhitePixel(display,screen);
  ship=XCreatePixmapFromBitmapData(display,yard,(char*)shipBits,shipBitsWidth,shipBitsHeight,
                                   shipColor,yardColor,DefaultDepth(display,screen));
  XSetForeground(display,gc,shipColor);
  XSetBackground(display,gc,yardColor);
  XSetGraphicsExposures(display,gc,FALSE);
 }

inline ShipYard::~ShipYard()
 {XFreePixmap(display,ship);
  XFreePixmap(display,shipErase);
  XFreePixmap(display,yard);
  XFreeGC(display,gc);
 }

inline ShipYard& ShipYard::AddShip()
 {if (++numShips<=maxVisibleShips)
   {shipRow+=shipWidth;
    if (shipRow>=rowEndOffset)
     {shipRow=rowStartOffset;
      shipCol+=shipHeight;
     }
    XCopyArea(display,ship,yard,gc,
              0,0,shipWidth,shipHeight,
              shipRow,
              shipCol);
   }
  return *this;
 }

inline ShipYard& ShipYard::RemoveShip()
 {if (numShips&&numShips--<=maxVisibleShips)
   {XCopyArea(display,shipErase,yard,gc,
              0,0,shipWidth,shipHeight,
              shipRow,
              shipCol);
    shipRow-=shipWidth;
    if (shipRow<rowStartOffset)
     {shipRow=lastShipInRowOffset;
      shipCol-=shipHeight;
     }
   }
  return *this;
 }

inline const int ShipYard::NumShips() const
 {return numShips;
 }

inline const Pixmap& ShipYard::GetYard() const
 {return yard;
 }

inline ShipYard& ShipYard::ClearYard()
 {XSetForeground(display,gc,yardColor);
  XFillRectangle(display,yard,gc,0,0,yardWidth,yardHeight);
  XSetForeground(display,gc,shipColor);
  shipRow=rowStartOffset-shipWidth;
  shipCol=colStartOffset;
  numShips=0;
  return *this;
 }

inline ShipYard& ShipYard::AlterIcon(const unsigned char* const shipBits,
                                     const int shipBitsWidth, const int shipBitsHeight,
                                     XColor& shipForeground)
 {shipWidth=shipBitsWidth;
  shipHeight=shipBitsHeight;
  maxVisibleShips=((yardHeight-10)/shipBitsHeight)*((yardWidth-10)/shipBitsWidth);
  rowStartOffset=(yardWidth-10)%shipBitsWidth/2+5;
  rowEndOffset=rowStartOffset+shipBitsWidth*((yardWidth-10)/shipBitsWidth);
  colStartOffset=(yardHeight-10)%shipBitsHeight/2+5;
  lastShipInRowOffset=rowEndOffset-shipBitsWidth;
  int screen=DefaultScreen(display);
  shipColor=XAllocColor(display,DefaultColormap(display,screen),&shipForeground)
            ? shipForeground.pixel
            : WhitePixel(display,screen);
  XFreePixmap(display,ship);
  XFreePixmap(display,shipErase);
  shipErase=XCreatePixmap(display,yard,shipBitsWidth,shipBitsHeight,DefaultDepth(display,screen));
  XSetForeground(display,gc,yardColor);
  XFillRectangle(display,shipErase,gc,0,0,shipBitsWidth,shipBitsHeight);
  XSetForeground(display,gc,shipColor);
  ship=XCreatePixmapFromBitmapData(display,yard,(char*)shipBits,shipBitsWidth,shipBitsHeight,
                                   shipColor,yardColor,DefaultDepth(display,screen));
  int numShipsSave=numShips;
  ClearYard();
  for (int i=0;i<numShipsSave;++i)
    AddShip();
  return *this;
 }


#endif
