#include<iostream>
#include<math.h>
#include"rotatorDisplayData.H"
#include<X11/Xutil.h>
#include<X11/Intrinsic.h>

using namespace std;

RotatorDisplayData::RotatorDisplayData(Display* const disp,
                                       const Vector2d* const vecs,
                                       const int numVecs): display(disp),
                                                           radius(0),
                                                           area(0)

 {double r=vecs[0].MagnitudeSquared();
  for(int i=0;i<numVecs;++i)
   {if (r>radius)
      radius=r;
    int j=i+1==numVecs ? 0
                       : i+1;
    double s=vecs[j].MagnitudeSquared(),
           t=(vecs[i]-vecs[j]).MagnitudeSquared(),
           temp=r-s+t;
    area+=sqrt(4*r*t-temp*temp);
    r=s;
   }
  area*=.25;
  radius=sqrt(radius);
  sideSize=2*radius+1.5;
  box.SetBox(0,radius);
 }

RotatorDisplayData::RotatorDisplayData(Display* const disp,
                                       const Vector2d* const vecs, const int numVecs,
				                               const double a): display(disp),
                                                        radius(0),
                                                        area(a)
 {for (int i=0;i<numVecs;++i)
   {double r=vecs[i].MagnitudeSquared();
    if (r>radius)
      radius=r;
   }
  radius=sqrt(radius);
  sideSize=2*radius+1.5;
  box.SetBox(0,radius);
 }

RotatorDisplayData::RotatorDisplayData(Display* const disp,
                                       const int sideSz): display(disp),
                                                          radius((sideSz-1)/2.0),
                                                          area(0),
                                                          sideSize(sideSz)
 {
 }

RotatorDisplayData::~RotatorDisplayData()
 {
 }

const Vector2d* const RotatorDisplayData::GetVecs(const double angle) const
 {cout<<endl<<"Reference made to nonexistent RotatorDislayData::GetVecs vitual function.  Execution terminated."<<endl;
  abort();
  return NULL;
 }

const int RotatorDisplayData::GetNumVecs() const
 {return 0;
 }

GC& RotatorDisplayData::GetGC(const double angle) const
 {cout<<endl<<"Reference made to nonexistent RotatorDislayData::GetGC virtual function.  Execution terminated."<<endl;
  abort();
  return *(GC*)NULL;
 }

NonRotVectorData::NonRotVectorData(Display* const disp, Drawable& drawable,
                                   XColor& color,
                                   const Vector2d* const vecs, const int nVecs): RotatorDisplayData(disp,vecs,nVecs),
                                                                                 numVecs(nVecs)
 {NoDecorInit(disp,drawable,color,vecs);
 }

NonRotVectorData::NonRotVectorData(Display* const disp, Drawable& drawable,
                                   XColor& color,
                                   const Vector2d* const vecs, const int nVecs,
                                   const double area):
                                        RotatorDisplayData(disp,vecs,nVecs,area),
                                        numVecs(nVecs)
 {NoDecorInit(disp,drawable,color,vecs);
 }


void NonRotVectorData::NoDecorInit(Display* const disp, Drawable& drawable,
                                   XColor& color,
				   const Vector2d* const vecs)
 {int screen=DefaultScreen(display),
      foreground=XAllocColor(display,DefaultColormap(display,screen),&color)
                 ? color.pixel
                 : WhitePixel(display,screen),
      background=BlackPixel(display,screen);
  GC gc=XCreateGC(display,drawable,0,NULL);
  BuildPixmap(drawable,screen,foreground,background,gc,vecs);
  XFreeGC(display,gc);
 }

NonRotVectorData::NonRotVectorData(Display* const disp, Drawable& drawable,
                                   XColor& color,
                                   const Vector2d* const vecs, const int nVecs,
                                   const unsigned char* const bitmap,
                                   const int width , const int height): RotatorDisplayData(disp,vecs,nVecs),
                                                                        numVecs(nVecs)
 {BitmapDecorInit(disp,drawable,color,vecs,bitmap,width,height);
 }


NonRotVectorData::NonRotVectorData(Display* const disp, Drawable& drawable,
                                   XColor& color,
                                   const Vector2d* const vecs, const int nVecs,
                                   const double area,
                                   const unsigned char* const bitmap,
                                   const int width , const int height): RotatorDisplayData(disp,vecs,nVecs,area),
                                                                        numVecs(nVecs)
 {BitmapDecorInit(disp,drawable,color,vecs,bitmap,width,height);
 }

void NonRotVectorData::BitmapDecorInit(Display* const disp, Drawable& drawable,
                                       XColor& color,
                                       const Vector2d* const vecs,
                                       const unsigned char* const bitmap, const int width, const int height)
 {int screen=DefaultScreen(display),
      foreground=XAllocColor(display,DefaultColormap(display,screen),&color)
                 ? color.pixel
                 : WhitePixel(display,screen),
      background=BlackPixel(display,screen);
  GC gc=XCreateGC(display,drawable,0,NULL);
  BuildPixmap(drawable,screen,foreground,background,gc,vecs);
  Pixmap bitPixmap=XCreateBitmapFromData(display,drawable,
                                         (const char * const)bitmap,width,height);
  XSetGraphicsExposures(display,gc,FALSE);
  XCopyPlane(display,bitPixmap,pixmap,gc,
             0,0,width,height,
             (sideSize-width)/2,(sideSize-height)/2,
             1);
  XFreePixmap(display,bitPixmap);
  XFreeGC(display,gc);
 }

NonRotVectorData::NonRotVectorData(Display* const disp, Drawable& drawable,
                                   XColor& color,
                                   const Vector2d* const vecs, const int nVecs,
			                             const CompositePixmap& compositePixmap): RotatorDisplayData(disp,vecs,nVecs),
                                                                            numVecs(nVecs)
 {PixmapDecorInit(disp,drawable,color,vecs,compositePixmap);
 }

NonRotVectorData::NonRotVectorData(Display* const disp, Drawable& drawable,
                                   XColor& color,
                                   const Vector2d* const vecs, const int nVecs,
                                   const double area,
			                             const CompositePixmap& compositePixmap): RotatorDisplayData(disp,vecs,nVecs,area),
                                                                            numVecs(nVecs)
 {PixmapDecorInit(disp,drawable,color,vecs,compositePixmap);
 }

void NonRotVectorData::PixmapDecorInit(Display* const disp, Drawable& drawable,
                                       XColor& color,
                                       const Vector2d* const vecs,
                                       const CompositePixmap& compositePixmap)
 {int screen=DefaultScreen(display),
      foreground=XAllocColor(display,DefaultColormap(display,screen),&color)
                 ? color.pixel
                 : WhitePixel(display,screen),
      background=BlackPixel(display,screen);
  GC gc=XCreateGC(display,drawable,0,NULL);
  BuildPixmap(drawable,screen,foreground,background,gc,vecs);
  XSetGraphicsExposures(display,gc,FALSE);
  XCopyArea(display,compositePixmap.GetPixmap(),pixmap,gc,
            0,0,compositePixmap.GetPixWidth(),compositePixmap.GetPixHeight(),
            (sideSize-compositePixmap.GetPixWidth())/2,
            (sideSize-compositePixmap.GetPixHeight())/2);
  XFreeGC(display,gc);
 }

void NonRotVectorData::BuildPixmap(Drawable& drawable, const int screen,
				                           const int foreground, const int background, GC& gc,
                                   const Vector2d* const vecs)
 {vectors=new Vector2d[numVecs];
  XSetLineAttributes(display,gc,1,LineSolid,CapButt,JoinMiter);
  XSetBackground(display,gc,background);
  XPoint* points=new XPoint[numVecs+1];
  pixmap=XCreatePixmap(display,drawable,sideSize,sideSize,DefaultDepth(display,screen));
  XSetForeground(display,gc,background);
  XFillRectangle(display,pixmap,gc,0,0,sideSize,sideSize);
  for(int i=0;i<numVecs;++i)
   {vectors[i]=vecs[i];
    points[i].x=vectors[i].x+radius+.5;
    points[i].y=vectors[i].y+radius+.5;
   }
  points[numVecs]=points[0];
  XSetForeground(display,gc,foreground);
  XDrawLines(display,pixmap,gc,points,numVecs+1,CoordModeOrigin);
  delete [] points;
 }

NonRotVectorData::~NonRotVectorData()
 {XFreePixmap(display,pixmap);
  delete [] vectors;
 }

const Vector2d* const NonRotVectorData::GetVecs(const double angle) const
 {return vectors;
 }

const int NonRotVectorData::GetNumVecs() const
 {return numVecs;
 }

const Pixmap& NonRotVectorData::GetPixmap(const double angle) const
 {return pixmap;
 }

const int NonRotVectorData::GetNumPix() const
 {return 1;
 }

RotVectorData::RotVectorData(Display* const disp, Drawable& drawable,
                             XColor& color,
                             const Vector2d* const vecs, const int nVecs): RotatorDisplayData(disp,vecs,nVecs),
                                                                           numVecs(nVecs)
 {NoDecorInit(disp,drawable,color,vecs);
 }


RotVectorData::RotVectorData(Display* const disp, Drawable& drawable,
                             XColor& color,
                             const Vector2d* const vecs, const int nVecs,
                             const double area): RotatorDisplayData(disp,vecs,nVecs,area),
                                                 numVecs(nVecs)
 {NoDecorInit(disp,drawable,color,vecs);
 }

void RotVectorData::NoDecorInit(Display* const disp, Drawable& drawable,
                                XColor& color,
                                const Vector2d* const vecs)
 {int screen=DefaultScreen(display),
      foreground=XAllocColor(display,DefaultColormap(display,screen),&color)
                 ? color.pixel
                 : WhitePixel(display,screen),
      background=BlackPixel(display,screen);
  GC gc=XCreateGC(display,drawable,0,NULL);
  RotateVecs(drawable,screen,foreground,background,gc,vecs);
  XFreeGC(display,gc);
 }

RotVectorData::RotVectorData(Display* const disp, Drawable& drawable,
                             XColor& color,
                             const Vector2d* const vecs, const int nVecs,
                             const unsigned char* const bitmap,
                             const int width , const int height): RotatorDisplayData(disp,vecs,nVecs),
                                                                  numVecs(nVecs)
 {BitmapDecorInit(disp,drawable,color,vecs,bitmap,width,height);
 }

RotVectorData::RotVectorData(Display* const disp, Drawable& drawable,
                             XColor& color,
                             const Vector2d* const vecs, const int nVecs,
                             const double area,
                             const unsigned char* const bitmap,
                             const int width , const int height): RotatorDisplayData(disp,vecs,nVecs,area),
                                                                  numVecs(nVecs)
 {BitmapDecorInit(disp,drawable,color,vecs,bitmap,width,height);
 }

void RotVectorData::BitmapDecorInit(Display* const disp, Drawable& drawable,
                                    XColor& color,
                                    const Vector2d* const vecs,
                                    const unsigned char* const bitmap, const int width, const int height)
 {int screen=DefaultScreen(display),
      foreground=XAllocColor(display,DefaultColormap(display,screen),&color)
                 ? color.pixel
                 : WhitePixel(display,screen),
      background=BlackPixel(display,screen);
  GC gc=XCreateGC(display,drawable,0,NULL);
  RotateVecs(drawable,screen,foreground,background,gc,vecs);
  int lineFill=8-width%8,
      bitNum=0;
  for(int j=0;j<height;++j)
   {for(int i=0;i<width;++i)
     {if (bitmap[bitNum/8]>>bitNum%8&0x01)
        for(int k=0;k<numPix;++k)
         {double x=i-.5*(width-1),
                 y=j-.5*(height-1),
          angle=k*incAngle;
          int xRot=x*cos(angle)-y*sin(angle)+radius+.5,
              yRot=y*cos(angle)+x*sin(angle)+radius+.5;
          XDrawPoint(display,rotatedPix[k],gc,xRot,yRot);
         }
      ++bitNum;
     }
    bitNum+=lineFill;
   }
  XFreeGC(display,gc);
 }

RotVectorData::RotVectorData(Display* const disp, Drawable& drawable,
                             XColor& color,
                             const Vector2d* const vecs, const int nVecs,
			                       const CompositePixmap& compositePixmap): RotatorDisplayData(disp,vecs,nVecs),
                                                                      numVecs(nVecs)
 {PixmapDecorInit(disp,drawable,color,vecs,compositePixmap);
 }

RotVectorData::RotVectorData(Display* const disp, Drawable& drawable,
                             XColor& color,
                             const Vector2d* const vecs, const int nVecs,
                             const double area,
			                       const CompositePixmap& compositePixmap): RotatorDisplayData(disp,vecs,nVecs,area),
                                                                      numVecs(nVecs)
 {PixmapDecorInit(disp,drawable,color,vecs,compositePixmap);
 }

void RotVectorData::PixmapDecorInit(Display* const disp, Drawable& drawable,
                                    XColor& color,
                                    const Vector2d* const vecs,
                                    const CompositePixmap& compositePixmap)
 {int screen=DefaultScreen(display),
      foreground=XAllocColor(display,DefaultColormap(display,screen),&color)
                 ? color.pixel
                 : WhitePixel(display,screen),
      background=BlackPixel(display,screen);
  GC gc=XCreateGC(display,drawable,0,NULL);
  RotateVecs(drawable,screen,foreground,background,gc,vecs);
  XImage* compositeImage=XGetImage(display,compositePixmap.GetPixmap(),
                                   0,0,compositePixmap.GetPixWidth(),compositePixmap.GetPixHeight(),
                                   AllPlanes,ZPixmap);
  for(int j=0;j<compositePixmap.GetPixHeight();++j)
    for(int i=0;i<compositePixmap.GetPixWidth();++i)
     {int pixel=XGetPixel(compositeImage,i,j);
      if (pixel!=background)
        for(int k=0;k<numPix;++k)
         {double x=i-.5*(compositePixmap.GetPixWidth()-1),
                 y=j-.5*(compositePixmap.GetPixHeight()-1),
	        angle=k*incAngle;
          int xRot=x*cos(angle)-y*sin(angle)+radius+.5,
              yRot=y*cos(angle)+x*sin(angle)+radius+.5;
          XSetForeground(display,gc,pixel);
          XDrawPoint(display,rotatedPix[k],gc,xRot,yRot);
	       }
     }
  XDestroyImage(compositeImage);
  XFreeGC(display,gc);
 }

void RotVectorData::RotateVecs(Drawable& drawable, const int screen,
                               const int foreground, const int background, GC& gc,
                               const Vector2d* const vecs)
 {numPix=6.28318530717958*radius+.5;
  incAngle=6.28318530717958/numPix;
  rotatedVecs=new Vector2d*[numPix];
  rotatedPix=new Pixmap[numPix];
  XSetLineAttributes(display,gc,1,LineSolid,CapButt,JoinMiter);
  XSetBackground(display,gc,background);
  XPoint* points=new XPoint[numVecs+1];
  for(int i=0;i<numPix;++i)
   {rotatedVecs[i]=new Vector2d[numVecs];
    rotatedPix[i]=XCreatePixmap(display,drawable,sideSize,sideSize,DefaultDepth(display,screen));
    XSetForeground(display,gc,background);
    XFillRectangle(display,rotatedPix[i],gc,0,0,sideSize,sideSize);
    double angle=i*incAngle;
    for(int j=0;j<numVecs;++j)
     {rotatedVecs[i][j]=vecs[j].Rotate(angle);
      points[j].x=rotatedVecs[i][j].x+radius+.5;
      points[j].y=rotatedVecs[i][j].y+radius+.5;
     }
    points[numVecs]=points[0];
    XSetForeground(display,gc,foreground);
    XDrawLines(display,rotatedPix[i],gc,points,numVecs+1,CoordModeOrigin);
   }
  delete [] points;
 }

RotVectorData::~RotVectorData()
 {for(int i=numPix;i--;)
   {XFreePixmap(display,rotatedPix[i]);
    delete [] rotatedVecs[i];
   }
  delete [] rotatedPix;
  delete [] rotatedVecs;
 }

const Vector2d* const RotVectorData::GetVecs(const double angle) const
 {return rotatedVecs[int((fmod(angle,6.28318530717958)+6.28318530717958)
                         /incAngle+.5)%numPix];
 }

const int RotVectorData::GetNumVecs() const
 {return numVecs;
 }

const Pixmap& RotVectorData::GetPixmap(const double angle) const
 {return rotatedPix[int((fmod(angle,6.28318530717958)+6.28318530717958)
                        /incAngle+.5)%numPix];
 }

const int RotVectorData::GetNumPix() const
 {return numPix;
 }

MaskedRotVectorData::MaskedRotVectorData(Display* const disp, Drawable& drawable,
                                         XColor& color,
                                         const Vector2d* const vecs, const int nVecs): RotatorDisplayData(disp,vecs,nVecs),
                                                                                       numVecs(nVecs)
 {NoDecorInit(disp,drawable,color,vecs);
 }

MaskedRotVectorData::MaskedRotVectorData(Display* const disp, Drawable& drawable,
                                         XColor& color,
                                         const Vector2d* const vecs, const int nVecs,
                                         const double area): RotatorDisplayData(disp,vecs,nVecs,area),
                                                             numVecs(nVecs)
 {NoDecorInit(disp,drawable,color,vecs);
 }

void MaskedRotVectorData::NoDecorInit(Display* const disp, Drawable& drawable,
                                      XColor& color,
                                      const Vector2d* const vecs)
 {int screen=DefaultScreen(display),
      foreground=XAllocColor(display,DefaultColormap(display,screen),&color)
                 ? color.pixel
                 : WhitePixel(display,screen),
      background=BlackPixel(display,screen);
  GC gc=XCreateGC(display,drawable,0,NULL);
  RotateVecs(drawable,screen,foreground,background,gc,vecs);
  XFreeGC(display,gc);
 }

MaskedRotVectorData::MaskedRotVectorData(Display* const disp, Drawable& drawable,
                                         XColor& color,
                                         const Vector2d* const vecs, const int nVecs,
			                                   const unsigned char* const bitmap,
                                         const int width , const int height): RotatorDisplayData(disp,vecs,nVecs),
                                                                              numVecs(nVecs)
 {BitmapDecorInit(disp,drawable,color,vecs,bitmap,width,height);
 }

MaskedRotVectorData::MaskedRotVectorData(Display* const disp, Drawable& drawable,
                                         XColor& color,
                                         const Vector2d* const vecs, const int nVecs,
                                         const double area,
			                                   const unsigned char* const bitmap,
                                         const int width , const int height): RotatorDisplayData(disp,vecs,nVecs,area),
                                                                              numVecs(nVecs)
 {BitmapDecorInit(disp,drawable,color,vecs,bitmap,width,height);
 }

void MaskedRotVectorData::BitmapDecorInit(Display* const disp, Drawable& drawable,
                                          XColor& color,
                                          const Vector2d* const vecs,
	                                        const unsigned char* const bitmap, const int width, const int height)
 {int screen=DefaultScreen(display),
      foreground=XAllocColor(display,DefaultColormap(display,screen),&color)
                 ? color.pixel
                 : WhitePixel(display,screen),
      background=BlackPixel(display,screen);
  GC gc=XCreateGC(display,drawable,0,NULL);
  RotateVecs(drawable,screen,foreground,background,gc,vecs);
  int lineFill=8-width%8,
       bitNum=0;
  for(int j=0;j<height;++j)
   {for(int i=0;i<width;++i)
      {if (bitmap[bitNum/8]>>bitNum%8&0x01)
         for(int k=0;k<numPix;++k)
          {double x=i-.5*(width-1),
                  y=j-.5*(height-1),
	                angle=k*incAngle;
           int xRot=x*cos(angle)-y*sin(angle)+radius+.5,
               yRot=y*cos(angle)+x*sin(angle)+radius+.5;
           XDrawPoint(display,rotatedPix[k],gc,xRot,yRot);
	        }
       ++bitNum;
      }
     bitNum+=lineFill;
    }
  XFreeGC(display,gc);
 }

MaskedRotVectorData::MaskedRotVectorData(Display* const disp, Drawable& drawable,
                                         XColor& color,
                                         const Vector2d* const vecs, const int nVecs,
			                                   const CompositePixmap& compositePixmap): RotatorDisplayData(disp,vecs,nVecs),
                                                                                  numVecs(nVecs)
 {PixmapDecorInit(disp,drawable,color,vecs,compositePixmap);
 }

MaskedRotVectorData::MaskedRotVectorData(Display* const disp, Drawable& drawable,
                                         XColor& color,
                                         const Vector2d* const vecs, const int nVecs,
                                         const double area,
			                                   const CompositePixmap& compositePixmap): RotatorDisplayData(disp,vecs,nVecs,area),
                                                                                  numVecs(nVecs)
 {PixmapDecorInit(disp,drawable,color,vecs,compositePixmap);
 }

void MaskedRotVectorData::PixmapDecorInit(Display* const disp, Drawable& drawable,
                                          XColor& color,
                                          const Vector2d* const vecs,
                                          const CompositePixmap& compositePixmap)
 {int screen=DefaultScreen(display),
      foreground=XAllocColor(display,DefaultColormap(display,screen),&color)
                 ? color.pixel
                 : WhitePixel(display,screen),
      background=BlackPixel(display,screen);
  GC gc=XCreateGC(display,drawable,0,NULL);
  RotateVecs(drawable,screen,foreground,background,gc,vecs);
  XImage* compositeImage=XGetImage(display,compositePixmap.GetPixmap(),
                                   0,0,compositePixmap.GetPixWidth(),compositePixmap.GetPixHeight(),
                                   AllPlanes,ZPixmap);
  for(int j=0;j<compositePixmap.GetPixHeight();++j)
    for(int i=0;i<compositePixmap.GetPixWidth();++i)
     {int pixel=XGetPixel(compositeImage,i,j);
      if (pixel!=background)
        for(int k=0;k<numPix;++k)
         {double x=i-.5*(compositePixmap.GetPixWidth()-1),
                 y=j-.5*(compositePixmap.GetPixHeight()-1),
                 angle=k*incAngle;
          int xRot=x*cos(angle)-y*sin(angle)+radius+.5,
              yRot=y*cos(angle)+x*sin(angle)+radius+.5;
          XSetForeground(display,gc,pixel);
          XDrawPoint(display,rotatedPix[k],gc,xRot,yRot);
	       }
     }
  XDestroyImage(compositeImage);
  XFreeGC(display,gc);
 }

void MaskedRotVectorData::RotateVecs(Drawable& drawable, const int screen,
                               const int foreground, const int background, GC& gc,
                               const Vector2d* const vecs)
 {numPix=6.28318530717958*radius+.5;
  incAngle=6.28318530717958/numPix;
  rotatedVecs=new Vector2d*[numPix];
  rotatedPix=new Pixmap[numPix];
  clipMasks=new Pixmap[numPix];
  maskGC=new GC[numPix];
  XSetLineAttributes(display,gc,1,LineSolid,CapButt,JoinMiter);
  XSetBackground(display,gc,background);
  XPoint* points=new XPoint[numVecs+1];
  for(int i=0;i<numPix;++i)
   {rotatedVecs[i]=new Vector2d[numVecs];
    rotatedPix[i]=XCreatePixmap(display,drawable,sideSize,sideSize,DefaultDepth(display,screen));
    XSetForeground(display,gc,background);
    XFillRectangle(display,rotatedPix[i],gc,0,0,sideSize,sideSize);
    clipMasks[i]=XCreatePixmap(display,drawable,sideSize,sideSize,1);
    GC clipGC=XCreateGC(display,clipMasks[i],NULL,0);
    XSetBackground(display,clipGC,BlackPixel(display,screen));
    XSetLineAttributes(display,clipGC,1,LineSolid,CapButt,JoinMiter);
    XSetForeground(display,clipGC,BlackPixel(display,screen));
    XFillRectangle(display,clipMasks[i],clipGC,0,0,sideSize,sideSize);
    maskGC[i]=XCreateGC(display,drawable,NULL,0);
    XSetForeground(display,maskGC[i],foreground);
    XSetBackground(display,maskGC[i],background);
    XSetGraphicsExposures(display,maskGC[i],FALSE);
    double angle=i*incAngle;
    for(int j=0;j<numVecs;++j)
     {rotatedVecs[i][j]=vecs[j].Rotate(angle);
      points[j].x=rotatedVecs[i][j].x+radius+.5;
      points[j].y=rotatedVecs[i][j].y+radius+.5;
     }
    points[numVecs]=points[0];
    XSetForeground(display,gc,foreground);
    XDrawLines(display,rotatedPix[i],gc,points,numVecs+1,CoordModeOrigin);
    XSetForeground(display,clipGC,WhitePixel(display,screen));
    XDrawLines(display,clipMasks[i],clipGC,points,numVecs+1,CoordModeOrigin);
    XFillPolygon(display,clipMasks[i],clipGC,points,numVecs+1,Nonconvex,CoordModeOrigin);
    XSetClipMask(display,maskGC[i],clipMasks[i]);
    XFreeGC(display,clipGC);
   }
  delete [] points;
 }

MaskedRotVectorData::~MaskedRotVectorData()
 {for(int i=numPix;i--;)
   {XFreeGC(display,maskGC[i]);
    XFreePixmap(display,clipMasks[i]);
    XFreePixmap(display,rotatedPix[i]);
    delete [] rotatedVecs[i];
   }
  delete [] maskGC;
  delete [] clipMasks;
  delete [] rotatedPix;
  delete [] rotatedVecs;
 }

const Vector2d* const MaskedRotVectorData::GetVecs(const double angle) const
 {return rotatedVecs[int((fmod(angle,6.28318530717958)+6.28318530717958)
                         /incAngle+.5)%numPix];
 }

const int MaskedRotVectorData::GetNumVecs() const
 {return numVecs;
 }

const Pixmap& MaskedRotVectorData::GetPixmap(const double angle) const
 {return rotatedPix[int((fmod(angle,6.28318530717958)+6.28318530717958)
                        /incAngle+.5)%numPix];
 }

const int MaskedRotVectorData::GetNumPix() const
 {return numPix;
 }

GC& MaskedRotVectorData::GetGC(const double angle) const
 {return maskGC[int((fmod(angle,6.28318530717958)+6.28318530717958)
                /incAngle+.5)%numPix];
 }

RotPixmapData::RotPixmapData(Display* const disp, Drawable& drawable,
                             XColor& color,
			     const unsigned char* const bitmap, const int width , const int height):
                                  RotatorDisplayData(disp,width>height ? width
                                                                       : height)
 {int screen=DefaultScreen(display),
      foreground=XAllocColor(display,DefaultColormap(display,screen),&color)
                 ? color.pixel
                 : WhitePixel(display,screen),
      background=BlackPixel(display,screen);
  GC gc=XCreateGC(display,drawable,0,NULL);
  CreatePix(drawable,screen,background,gc);
  XSetForeground(display,gc,foreground);
  int lineFill=8-width%8,
      bitNum=0;
   for(int j=0;j<height;++j)
    {for(int i=0;i<width;++i)
      {if (bitmap[bitNum/8]>>bitNum%8&0x01)
         for(int k=0;k<numPix;++k)
          {double x=i-.5*(width-1),
                  y=j-.5*(height-1),
	         angle=k*incAngle;
           int xRot=x*cos(angle)-y*sin(angle)+radius+.5,
               yRot=y*cos(angle)+x*sin(angle)+radius+.5;
           XDrawPoint(display,rotatedPix[k],gc,xRot,yRot);
	        }
       ++bitNum;
      }
     bitNum+=lineFill;
    }
  XFreeGC(display,gc);
 }


RotPixmapData::RotPixmapData(Display* const disp, Drawable& drawable,
			                       const CompositePixmap& compositePixmap): RotatorDisplayData(disp,
                                                                                         compositePixmap.GetPixWidth()>compositePixmap.GetPixHeight()
                                                                                          ? compositePixmap.GetPixWidth()
                                                                                          : compositePixmap.GetPixHeight())
 {int screen=DefaultScreen(display),
      background=BlackPixel(display,screen);
  GC gc=XCreateGC(display,drawable,0,NULL);
  CreatePix(drawable,screen,background,gc);
  XImage* compositeImage=XGetImage(display,compositePixmap.GetPixmap(),
                                    0,0,compositePixmap.GetPixWidth(),compositePixmap.GetPixHeight(),
                                    AllPlanes,ZPixmap);
   for(int j=0;j<compositePixmap.GetPixHeight();++j)
     for(int i=0;i<compositePixmap.GetPixWidth();++i)
      {int pixel=XGetPixel(compositeImage,i,j);
       if (pixel!=background)
         for(int k=0;k<numPix;++k)
          {double x=i-.5*(compositePixmap.GetPixWidth()-1),
                  y=j-.5*(compositePixmap.GetPixHeight()-1),
	         angle=k*incAngle;
           int xRot=x*cos(angle)-y*sin(angle)+radius+.5,
               yRot=y*cos(angle)+x*sin(angle)+radius+.5;
           XSetForeground(display,gc,pixel);
           XDrawPoint(display,rotatedPix[k],gc,xRot,yRot);
	        }
      }
  XDestroyImage(compositeImage);
  XFreeGC(display,gc);
 }

void RotPixmapData::CreatePix(Drawable& drawable, const int screen, const int background, GC& gc)
 {numPix=6.28318530717958*radius+.5;
  incAngle=6.28318530717958/numPix;
  rotatedPix=new Pixmap[numPix];
  XSetBackground(display,gc,background);
  XSetForeground(display,gc,background);
  for(int i=0;i<numPix;++i)
   {rotatedPix[i]=XCreatePixmap(display,drawable,sideSize,sideSize,DefaultDepth(display,screen));
    XFillRectangle(display,rotatedPix[i],gc,0,0,sideSize,sideSize);
   }
 }

RotPixmapData::~RotPixmapData()
 {for(int i=numPix;i--;)
    XFreePixmap(display,rotatedPix[i]);
  delete [] rotatedPix;
 }

const Pixmap& RotPixmapData::GetPixmap(const double angle) const
 {return rotatedPix[int((fmod(angle,6.28318530717958)+6.28318530717958)
                        /incAngle+.5)%numPix];
 }

const int RotPixmapData::GetNumPix() const
 {return numPix;
 }

MaskedRotPixmapData::MaskedRotPixmapData(Display* const disp, Drawable& drawable,
                                         XColor& color,
			                                   const unsigned char* const bitmap,
                                         const int width , const int height): RotatorDisplayData(disp,width>height
                                                                               ? width
                                                                               : height)
 {int screen=DefaultScreen(display),
      foreground=XAllocColor(display,DefaultColormap(display,screen),&color)
                 ? color.pixel
                 : WhitePixel(display,screen),
      background=BlackPixel(display,screen);
  GC gcPixmap,
     gcBitmap;
  CreatePix(drawable,screen,background,gcPixmap,gcBitmap);
  XSetForeground(display,gcPixmap,foreground);
  int lineFill=8-width%8,
       bitNum=0;
   for(int j=0;j<height;++j)
    {for(int i=0;i<width;++i)
      {if (bitmap[bitNum/8]>>bitNum%8&0x01)
         for(int k=0;k<numPix;++k)
          {double x=i-.5*(width-1),
                 y=j-.5*(height-1),
	         angle=k*incAngle;
           int xRot=x*cos(angle)-y*sin(angle)+radius+.5,
               yRot=y*cos(angle)+x*sin(angle)+radius+.5;
           XDrawPoint(display,rotatedPix[k],gcPixmap,xRot,yRot);
           XDrawPoint(display,clipMasks[k],gcBitmap,xRot,yRot);
	        }
       ++bitNum;
      }
     bitNum+=lineFill;
    }
  XFreeGC(display,gcBitmap);
  XFreeGC(display,gcPixmap);
  for(int i=0;i<numPix;++i)
    XSetClipMask(display,maskGC[i],clipMasks[i]);
 }


MaskedRotPixmapData::MaskedRotPixmapData(Display* const disp, Drawable& drawable,
			                                   const CompositePixmap& compositePixmap): RotatorDisplayData(disp,
                                                                                  compositePixmap.GetPixWidth()>compositePixmap.GetPixHeight()
                                                                                   ? compositePixmap.GetPixWidth()
                                                                                   : compositePixmap.GetPixHeight())
 {int screen=DefaultScreen(display),
      background=BlackPixel(display,screen);
  GC gcPixmap,
     gcBitmap;
  CreatePix(drawable,screen,background,gcPixmap,gcBitmap);
  XImage* compositeImage=XGetImage(display,compositePixmap.GetPixmap(),
                                    0,0,compositePixmap.GetPixWidth(),compositePixmap.GetPixHeight(),
                                    AllPlanes,ZPixmap);
  for(int j=0;j<compositePixmap.GetPixHeight();++j)
    for(int i=0;i<compositePixmap.GetPixWidth();++i)
     {int pixel=XGetPixel(compositeImage,i,j);
      if (pixel!=background)
        for(int k=0;k<numPix;++k)
         {double x=i-.5*(compositePixmap.GetPixWidth()-1),
                 y=j-.5*(compositePixmap.GetPixHeight()-1),
	               angle=k*incAngle;
          int xRot=x*cos(angle)-y*sin(angle)+radius+.5,
              yRot=y*cos(angle)+x*sin(angle)+radius+.5;
          XSetForeground(display,gcPixmap,pixel);
          XDrawPoint(display,rotatedPix[k],gcPixmap,xRot,yRot);
          XDrawPoint(display,clipMasks[k],gcBitmap,xRot,yRot);
	       }
     }
  XDestroyImage(compositeImage);
  XFreeGC(display,gcBitmap);
  XFreeGC(display,gcPixmap);
  for(int i=0;i<numPix;++i)
    XSetClipMask(display,maskGC[i],clipMasks[i]);
 }

void MaskedRotPixmapData::CreatePix(Drawable& drawable, const int screen,
                                    const int background,
                                    GC& gcPixmap, GC& gcBitmap)
 {numPix=6.28318530717958*radius+.5;
  incAngle=6.28318530717958/numPix;
  rotatedPix=new Pixmap[numPix];
  clipMasks=new Pixmap[numPix];
  maskGC=new GC[numPix];
  gcPixmap=XCreateGC(display,drawable,0,NULL);
  XSetBackground(display,gcPixmap,background);
  XSetForeground(display,gcPixmap,background);
  rotatedPix[0]=XCreatePixmap(display,drawable,sideSize,sideSize,DefaultDepth(display,screen));
  XFillRectangle(display,rotatedPix[0],gcPixmap,0,0,sideSize,sideSize);
  clipMasks[0]=XCreatePixmap(display,drawable,sideSize,sideSize,1);
  gcBitmap=XCreateGC(display,clipMasks[0],NULL,0);
  XSetBackground(display,gcBitmap,background);
  XSetForeground(display,gcBitmap,background);
  XFillRectangle(display,clipMasks[0],gcBitmap,0,0,sideSize,sideSize);
  maskGC[0]=XCreateGC(display,drawable,NULL,0);
  XSetForeground(display,maskGC[0],background);
  XSetBackground(display,maskGC[0],background);
  XSetGraphicsExposures(display,maskGC[0],FALSE);
  for(int i=1;i<numPix;++i)
   {rotatedPix[i]=XCreatePixmap(display,drawable,sideSize,sideSize,DefaultDepth(display,screen));
    XFillRectangle(display,rotatedPix[i],gcPixmap,0,0,sideSize,sideSize);
    clipMasks[i]=XCreatePixmap(display,drawable,sideSize,sideSize,1);
    XFillRectangle(display,clipMasks[i],gcBitmap,0,0,sideSize,sideSize);
    maskGC[i]=XCreateGC(display,drawable,NULL,0);
    XSetForeground(display,maskGC[i],background);
    XSetBackground(display,maskGC[i],background);
    XSetGraphicsExposures(display,maskGC[i],FALSE);
   }
  XSetForeground(display,gcBitmap,WhitePixel(display,screen));
  XSetLineAttributes(display,gcBitmap,1,LineSolid,CapButt,JoinMiter);
 }

MaskedRotPixmapData::~MaskedRotPixmapData()
 {for(int i=numPix;i--;)
   {XFreeGC(display,maskGC[i]);
    XFreePixmap(display,clipMasks[i]);
    XFreePixmap(display,rotatedPix[i]);
   }
  delete [] maskGC;
  delete [] clipMasks;
  delete [] rotatedPix;
 }

const Pixmap& MaskedRotPixmapData::GetPixmap(const double angle) const
 {return rotatedPix[int((fmod(angle,6.28318530717958)+6.28318530717958)
                        /incAngle+.5)%numPix];
 }

const int MaskedRotPixmapData::GetNumPix() const
 {return numPix;
 }


GC& MaskedRotPixmapData::GetGC(const double angle) const
 {return maskGC[int((fmod(angle,6.28318530717958)+6.28318530717958)
                /incAngle+.5)%numPix];
 }
