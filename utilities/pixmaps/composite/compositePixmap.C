#include<math.h>
#include"compositePixmap.H"


CompositePixmap::CompositePixmap(Display* const disp,
                               Drawable& drawable,
                               const int maxW,
                               const int maxH): display(disp),
                                                width(maxW),
                                                height(maxH)
 {int screen=DefaultScreen(display),
      background=BlackPixel(display,screen);
  GC gc=XCreateGC(display,drawable,0,NULL);
  XSetForeground(display,gc,background);
  pixmap=XCreatePixmap(display,drawable,width,height,DefaultDepth(display,screen));
  XFillRectangle(display,pixmap,gc,0,0,width,height);
  XFreeGC(display,gc);
 }

CompositePixmap::~CompositePixmap()
 {XFreePixmap(display,pixmap);
 }

CompositePixmap& CompositePixmap::AddBitmapData(const unsigned char* bitmap,
                                                const int w,
                                                const int h,
                                                XColor& color)
 {int screen=DefaultScreen(display),
      foreground=XAllocColor(display,DefaultColormap(display,screen),&color)
                 ? color.pixel
                 : WhitePixel(display,screen);
  GC gc=XCreateGC(display,pixmap,0,NULL);
  XSetForeground(display,gc,foreground);
  {int lineFill=8-w%8,
       bitNum=0;
   for(int j=0;j<h;++j)
    {for(int i=0;i<w;++i)
      {if (bitmap[bitNum/8]>>bitNum%8&0x01)
         XDrawPoint(display,pixmap,gc,(2*i-w+width)/2,(2*j-h+height)/2);
       ++bitNum;
      }
     bitNum+=lineFill;
    }
  }
  XFreeGC(display,gc);
  return *this;
 }
