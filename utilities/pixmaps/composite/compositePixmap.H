#ifndef _COMPOSITEPIXMAP_H
#define _COMPOSITEPIXMAP_H

#include<X11/Xlib.h>

class CompositePixmap
 {public:
   CompositePixmap(Display* const,
                   Drawable&,
                   const int maxWidth,
                   const int maxHeight);
   ~CompositePixmap();
   CompositePixmap& AddBitmapData(const unsigned char* bitmap,
                                  const int width,
                                  const int height,
                                  XColor&);
   const Pixmap& GetPixmap() const;
   const int GetPixWidth() const;
   const int GetPixHeight() const;

 private:
   CompositePixmap(const CompositePixmap&);
   CompositePixmap& operator=(const CompositePixmap&);
   Display* const display;
   Pixmap pixmap;
   int width,
       height;
 };

inline const Pixmap& CompositePixmap::GetPixmap() const
 {return pixmap;
 }

inline const int CompositePixmap::GetPixWidth() const
 {return width;
 }

inline const int CompositePixmap::GetPixHeight() const
 {return height;
 }

#endif
