#ifndef _ROTATORDISPLAYDATA_H
#define _ROTATORDISPLAYDATA_H


#include<X11/Xlib.h>
#include"vector2d.H"
#include"box.H"
#include"compositePixmap.H"

class RotatorDisplayData
 {public:
    RotatorDisplayData(Display* const, const Vector2d* const, const int);
    RotatorDisplayData(Display* const, const Vector2d* const, const int, const double area);
    RotatorDisplayData(Display* const, const int);
    virtual ~RotatorDisplayData();
    virtual const Vector2d* const GetVecs(const double) const;
    virtual const int GetNumVecs() const; 
    virtual const Pixmap& GetPixmap(const double) const=0;
    virtual const int GetNumPix() const=0; 
    virtual GC& GetGC(const double) const;
    const Box& GetBox() const;
    const double GetRadius() const;
    const double GetArea() const;
    const int GetPixWidth() const;
    const int GetPixHeight() const;

  protected:
    Display* const display;
    Box box;
    double radius,
           area; 
    int sideSize;

  private:
    RotatorDisplayData& operator=(const RotatorDisplayData&);
 };

class NonRotVectorData: public RotatorDisplayData
 {public:
    NonRotVectorData(Display* const, Drawable&, XColor&,
                     const Vector2d* const, const int); 
    NonRotVectorData(Display* const, Drawable&, XColor&,
                     const Vector2d* const, const int, const double area); 
    NonRotVectorData(Display* const, Drawable&, XColor&,
                     const Vector2d* const, const int,  
                     const unsigned char* const, const int, const int);
    NonRotVectorData(Display* const, Drawable&, XColor&,
                     const Vector2d* const, const int, const double area, 
                     const unsigned char* const, const int, const int);
    NonRotVectorData(Display* const, Drawable&, XColor&,
                     const Vector2d* const, const int,  
                     const CompositePixmap&);
    NonRotVectorData(Display* const, Drawable&, XColor&,
                     const Vector2d* const, const int, const double area,  
                     const CompositePixmap&);
    virtual ~NonRotVectorData();                 
    virtual const Vector2d* const GetVecs(const double) const;
    virtual const int GetNumVecs() const; 
    virtual const Pixmap& GetPixmap(const double) const;
    virtual const int GetNumPix() const; 

  private:
    NonRotVectorData(const NonRotVectorData&);
    NonRotVectorData& operator=(const NonRotVectorData&);
    void NoDecorInit(Display* const, Drawable&, XColor&,
                     const Vector2d* const);
    void BitmapDecorInit(Display* const, Drawable&, XColor&,
                         const Vector2d* const,  
                         const unsigned char* const, const int, const int);
    void PixmapDecorInit(Display* const, Drawable&, XColor&,
                         const Vector2d* const,  
                         const CompositePixmap&);
    void BuildPixmap(Drawable&, const int,
                     const int, const int, GC& gc,
                     const Vector2d* const); 

    Vector2d* vectors;
    Pixmap pixmap;
    int numVecs;
 };

class RotVectorData: public RotatorDisplayData
 {public:
    RotVectorData(Display* const, Drawable&, XColor&,
                  const Vector2d* const, const int); 
    RotVectorData(Display* const, Drawable&, XColor&,
                  const Vector2d* const, const int, const double area); 
    RotVectorData(Display* const, Drawable&, XColor&,
                  const Vector2d* const, const int,  
                  const unsigned char* const, const int, const int);
    RotVectorData(Display* const, Drawable&, XColor&,
                  const Vector2d* const, const int, const double area,  
                  const unsigned char* const, const int, const int);
    RotVectorData(Display* const, Drawable&, XColor&,
                  const Vector2d* const, const int,  
                  const CompositePixmap&);
    RotVectorData(Display* const, Drawable&, XColor&,
                  const Vector2d* const, const int, const double area, 
                  const CompositePixmap&);
    virtual ~RotVectorData();                 
    virtual const Vector2d* const GetVecs(const double) const;
    virtual const int GetNumVecs() const; 
    virtual const Pixmap& GetPixmap(const double) const;
    virtual const int GetNumPix() const; 

  private:
    RotVectorData(const RotVectorData&);
    RotVectorData& operator=(const RotVectorData&);
    void NoDecorInit(Display* const, Drawable&, XColor&,
                     const Vector2d* const);
    void BitmapDecorInit(Display* const, Drawable&, XColor&,
                         const Vector2d* const,  
                         const unsigned char* const, const int, const int);
    void PixmapDecorInit(Display* const, Drawable&, XColor&,
                         const Vector2d* const,  
                         const CompositePixmap&);
    void RotateVecs(Drawable&, const int,
                    const int, const int, GC&, 
                    const Vector2d* const);

    Vector2d** rotatedVecs;
    Pixmap* rotatedPix;
    double incAngle;
    int numPix,
        numVecs;
  };

class MaskedRotVectorData: public RotatorDisplayData
 {public:
    MaskedRotVectorData(Display* const, Drawable&, XColor&,
                  const Vector2d* const, const int); 
    MaskedRotVectorData(Display* const, Drawable&, XColor&,
                  const Vector2d* const, const int, const double area); 
    MaskedRotVectorData(Display* const, Drawable&, XColor&,
                  const Vector2d* const, const int,  
                  const unsigned char* const, const int, const int);
    MaskedRotVectorData(Display* const, Drawable&, XColor&,
                  const Vector2d* const, const int, const double area, 
                  const unsigned char* const, const int, const int);
    MaskedRotVectorData(Display* const, Drawable&, XColor&,
                  const Vector2d* const, const int,  
                  const CompositePixmap&);
    MaskedRotVectorData(Display* const, Drawable&, XColor&,
                  const Vector2d* const, const int, const double area,  
                  const CompositePixmap&);
    virtual ~MaskedRotVectorData();                 
    virtual const Vector2d* const GetVecs(const double) const;
    virtual const int GetNumVecs() const; 
    virtual const Pixmap& GetPixmap(const double) const;
    virtual const int GetNumPix() const; 
    virtual GC& GetGC(const double) const;

  private:
    MaskedRotVectorData(const MaskedRotVectorData&);
    MaskedRotVectorData& operator=(const MaskedRotVectorData&);
    void NoDecorInit(Display* const, Drawable&, XColor&,
                     const Vector2d* const);
    void BitmapDecorInit(Display* const, Drawable&, XColor&,
                         const Vector2d* const,  
                         const unsigned char* const, const int, const int);
    void PixmapDecorInit(Display* const, Drawable&, XColor&,
                         const Vector2d* const,  
                         const CompositePixmap&);
    void RotateVecs(Drawable&, const int,
                    const int, const int, GC&, 
                    const Vector2d* const);

    Vector2d** rotatedVecs;
    Pixmap* rotatedPix,
          * clipMasks; 
    GC* maskGC;
    double incAngle;
    int numPix,
        numVecs;
  };

class RotPixmapData: public RotatorDisplayData
 {public:
    RotPixmapData(Display* const, Drawable&, XColor&,
                  const unsigned char* const, const int, const int);
    RotPixmapData(Display* const, Drawable&, const CompositePixmap&);
    virtual ~RotPixmapData();                 
    virtual const Pixmap& GetPixmap(const double) const;
    virtual const int GetNumPix() const; 

  private:
    RotPixmapData(const RotVectorData&);
    RotPixmapData& operator=(const RotPixmapData&);
    void CreatePix(Drawable&, const int, const int, GC&);

    Pixmap* rotatedPix;
    double incAngle;
    int numPix;
  };

class MaskedRotPixmapData: public RotatorDisplayData
 {public:
    MaskedRotPixmapData(Display* const, Drawable&, XColor&,
                         const unsigned char* const, const int, const int);
    MaskedRotPixmapData(Display* const, Drawable&, const CompositePixmap&);
    virtual ~MaskedRotPixmapData();                 
    virtual const Pixmap& GetPixmap(const double) const;
    virtual const int GetNumPix() const; 
    virtual GC& GetGC(const double) const;

  private:
    MaskedRotPixmapData(const RotVectorData&);
    MaskedRotPixmapData& operator=(const MaskedRotPixmapData&);
    void CreatePix(Drawable&, const int, const int, GC&, GC&);

    Pixmap* rotatedPix,
          * clipMasks; 
    GC* maskGC;
    double incAngle;
    int numPix;
  };

inline const Box& RotatorDisplayData::GetBox() const
 {return box;
 }

inline const double RotatorDisplayData::GetRadius() const
 {return radius;
 }

inline const double RotatorDisplayData::GetArea() const
 {return area;
 }

inline const int RotatorDisplayData::GetPixWidth() const
 {return sideSize;
 }

inline const int RotatorDisplayData::GetPixHeight() const
 {return sideSize;
 }


#endif
