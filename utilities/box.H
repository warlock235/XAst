#ifndef _BOX_H
#define _BOX_H


#include"vector2d.H"


class Box
 {typedef int Boolean;
  enum {off, on};

  friend Boolean Intersect(const Box&, const Box&);
  public:
    Box();
    Box(const Vector2d&, const Vector2d&);
    Box(const double width, const double height, const Vector2d& center);
    Box(const Vector2d& center, const double radius);
    Box(const Box&, const Box&);
    Box(const Box&, const Box&, int&);
    Box& SetBox(const Vector2d&, const Vector2d&);
    Box& SetBox(const double width, const double height, const Vector2d& center);
    Box& SetBox(const Vector2d& center, const double radius);
    Box& SetBox(const Box&, const Box&); // Smallest Box that contains both input Boxes.
    Box& SetBox(const Box&, const Box&, int&); // Returns quadrant of the vector Box2.center-Box1.center
    Box& MoveBox(const Vector2d&);
    Box& WrapMovingBox(const Box& container, const Vector2d& velocity);
    const Vector2d& NorthWestCorner() const;
    const Vector2d& NorthEastCorner() const;
    const Vector2d& SouthEastCorner() const;
    const Vector2d& SouthWestCorner() const;
    const Vector2d& Center() const;
    const double& NorthSide() const;
    const double& EastSide() const;
    const double& SouthSide() const;
    const double& WestSide() const;
    const double& Width() const;
    const double& Height() const;

  private:
    void SetWidthHeightCenter();
    void SetBoxFromVector2d(const Vector2d&, const Vector2d&);
    void SetBoxFromWidthHeightCenter();
    int SetBoxFromBox(const Box&, const Box&);

    Vector2d northWestCorner,
             northEastCorner,
             southEastCorner,
             southWestCorner,
             center;
    double width,
          height;
 };

inline Box::Box(): northWestCorner(),
                   northEastCorner(),
                   southEastCorner(),
                   southWestCorner(),
                   center(),
                   width(0),
                   height(0) {}

inline void Box::SetWidthHeightCenter()
 {Vector2d temp(southEastCorner-northWestCorner);
  width=temp.x;
  height=temp.y;
  center=.5*temp;
 }

inline void Box::SetBoxFromVector2d(const Vector2d& v1, const Vector2d& v2)
 {if (v1.x<v2.x)
   {northWestCorner.x=v1.x;
    northEastCorner.x=v2.x;
    southEastCorner.x=v2.x;
    southWestCorner.x=v1.x;
   }
  else
   {northWestCorner.x=v2.x;
    northEastCorner.x=v1.x;
    southEastCorner.x=v1.x;
    southWestCorner.x=v2.x;
   };
  if (v1.y<v2.y)
   {northWestCorner.y=v1.y;
    northEastCorner.y=v2.y;
    southEastCorner.y=v2.y;
    southWestCorner.y=v1.y;
   }
  else
   {northWestCorner.y=v2.y;
    northEastCorner.y=v1.y;
    southEastCorner.y=v1.y;
    southWestCorner.y=v2.y;
   };
  SetWidthHeightCenter();
 }

inline void Box::SetBoxFromWidthHeightCenter()
 {double halfWidth=.5*width,
        halfHeight=.5*height;
  northWestCorner.x=center.x-halfWidth;
  northWestCorner.y=center.y-halfHeight;
  northEastCorner.x=center.x+halfWidth;
  northEastCorner.y=center.y-halfHeight;
  southEastCorner.x=center.x+halfWidth;
  southEastCorner.y=center.y+halfHeight;
  southWestCorner.x=center.x-halfWidth;
  southWestCorner.y=center.y+halfHeight;
 }

inline int Box::SetBoxFromBox(const Box& b1, const Box& b2)
 {int quadrant((b2.center-b1.center).Quadrant());
  switch (quadrant)
   {case 0: *this=b1;
            break;
    case 1: northWestCorner=b1.northWestCorner;
            northEastCorner.SetVector2d(b2.northEastCorner.x,
                                        b1.northEastCorner.y);
            southEastCorner=b2.southEastCorner;
            southWestCorner.SetVector2d(b1.southWestCorner.x,
                                        b2.southWestCorner.y);
            SetWidthHeightCenter();
            break;
    case 2: northWestCorner.SetVector2d(b2.northWestCorner.x,
                                        b1.northWestCorner.y);
            northEastCorner=b1.northEastCorner;
            southEastCorner.SetVector2d(b1.southEastCorner.x,
                                        b2.southEastCorner.y);
            southWestCorner=b2.southWestCorner;
            SetWidthHeightCenter();
            break;
    case 3: northWestCorner=b2.northWestCorner;
            northEastCorner.SetVector2d(b1.northEastCorner.x,
                                        b2.northEastCorner.y);
            southEastCorner=b1.southEastCorner;
            southWestCorner.SetVector2d(b2.southWestCorner.x,
                                        b1.southWestCorner.y);
            SetWidthHeightCenter();
            break;
    case 4: northWestCorner.SetVector2d(b1.northWestCorner.x,
                                        b2.northWestCorner.y);
            northEastCorner=b2.northEastCorner;
            southEastCorner.SetVector2d(b2.southEastCorner.x,
                                        b1.southEastCorner.y);
            southWestCorner=b1.southWestCorner;
            SetWidthHeightCenter();
            break;
   };
  return quadrant;
 }

inline Box::Box(const Vector2d& v1, const Vector2d& v2)
 {SetBoxFromVector2d(v1, v2);
 }

inline Box::Box(const double w, const double h, const Vector2d& c): width(w),
                                                                 height(h),
                                                                 center(c)
 {SetBoxFromWidthHeightCenter();
 }

inline Box::Box(const Vector2d& c, const double r): width(2*r),
                                              height(2*r),
                                              center(c)
 {SetBoxFromWidthHeightCenter();
 }

inline Box::Box(const Box& b1, const Box& b2)
 {SetBoxFromBox(b1, b2);
 }

inline Box::Box(const Box& b1, const Box& b2, int& quadrant)
 {quadrant=SetBoxFromBox(b1, b2);
 }

inline Box& Box::SetBox(const Vector2d& v1, const Vector2d& v2)
 {SetBoxFromVector2d(v1, v2);
  return *this;
 }

inline Box& Box::SetBox(const double w, const double h, const Vector2d& c)
 {width=w;
  height=h;
  center=c;
  SetBoxFromWidthHeightCenter();
  return *this;
 }

inline Box& Box::SetBox(const Vector2d& c, const double r)
 {width=2*r;
  height=2*r;
  center=c;
  SetBoxFromWidthHeightCenter();
  return *this;
 }

inline Box& Box::SetBox(const Box& b1, const Box& b2)
 {SetBoxFromBox(b1, b2);
  return *this;
 }

inline Box& Box::SetBox(const Box& b1, const Box& b2, int& quadrant)
 {quadrant=SetBoxFromBox(b1, b2);
  return *this;
 }

inline Box& Box::MoveBox(const Vector2d& deltaDist)
 {northWestCorner+=deltaDist;
  northEastCorner+=deltaDist;
  southEastCorner+=deltaDist;
  southWestCorner+=deltaDist;
  center+=deltaDist;
  return *this;
 }

inline const Vector2d& Box::NorthWestCorner() const
 {return northWestCorner;
 }

inline const Vector2d& Box::NorthEastCorner() const
 {return northEastCorner;
 }

inline const Vector2d& Box::SouthEastCorner() const
 {return southEastCorner;
 }

inline const Vector2d& Box::SouthWestCorner() const
 {return southWestCorner;
 }

inline const Vector2d& Box::Center() const
 {return center;
 }

inline const double& Box::NorthSide() const
 {return northWestCorner.y;
 }

inline const double& Box::EastSide() const
 {return northEastCorner.x;
 }

inline const double& Box::SouthSide() const
 {return southEastCorner.y;
 }

inline const double& Box::WestSide() const
 {return southWestCorner.x;
 }

inline Box& Box::WrapMovingBox(const Box& container, const Vector2d& velocity)
 {if (EastSide()<=container.WestSide()&&velocity.x<0)
   {northWestCorner.x+=container.EastSide();
    northEastCorner.x+=container.EastSide();
    southEastCorner.x+=container.EastSide();
    southWestCorner.x+=container.EastSide();
    center.x+=container.EastSide();
   }
  else
    if (WestSide()>=container.EastSide()&&velocity.x>0)
     {double westSideSave=WestSide();
      northWestCorner.x=fmod(westSideSave,container.EastSide());
      double offset=northWestCorner.x-westSideSave;
      northEastCorner.x+=offset;
      southEastCorner.x+=offset;
      southWestCorner.x+=offset;
      center.x+=offset;
     }
  if (SouthSide()<=container.NorthSide()&&velocity.y<0)
   {northWestCorner.y+=container.SouthSide();
    northEastCorner.y+=container.SouthSide();
    southEastCorner.y+=container.SouthSide();
    southWestCorner.y+=container.SouthSide();
    center.y+=container.SouthSide();
   }
  else
    if (NorthSide()>=container.SouthSide()&&velocity.y>0)
     {double northSideSave=NorthSide();
      northWestCorner.y=fmod(northSideSave,container.SouthSide());
      double offset=northWestCorner.y-northSideSave;
      northEastCorner.y+=offset;
      southEastCorner.y+=offset;
      southWestCorner.y+=offset;
      center.y+=offset;
     }
  return *this;
 }

inline const double& Box::Width() const
 {return width;
 }

inline const double& Box::Height() const
 {return height;
 }

inline Box::Boolean Intersect(const Box& b1, const Box& b2)
 {return (b1.width<=b2.width   ? b1.northWestCorner.x>=b2.northWestCorner.x&&
                                 b1.northWestCorner.x<=b2.southEastCorner.x||
                                 b1.southEastCorner.x>=b2.northWestCorner.x&&
                                 b1.southEastCorner.x<=b2.southEastCorner.x
                               : b2.northWestCorner.x>=b1.northWestCorner.x&&
                                 b2.northWestCorner.x<=b1.southEastCorner.x||
                                 b2.southEastCorner.x>=b1.northWestCorner.x&&
                                 b2.southEastCorner.x<=b1.southEastCorner.x)&&
         (b1.height<=b2.height ? b1.northWestCorner.y>=b2.northWestCorner.y&&
                                 b1.northWestCorner.y<=b2.southEastCorner.y||
                                 b1.southEastCorner.y>=b2.northWestCorner.y&&
                                 b1.southEastCorner.y<=b2.southEastCorner.y
                               : b2.northWestCorner.y>=b1.northWestCorner.y&&
                                 b2.northWestCorner.y<=b1.southEastCorner.y||
                                 b2.southEastCorner.y>=b1.northWestCorner.y&&
                                 b2.southEastCorner.y<=b1.southEastCorner.y);
 };




#endif
