#ifndef _FRAMELIST_H
#define _FRAMELIST_H

#include<X11/Xlib.h>
#include"../pixmaps/composite/compositePixmap.H"


class FrameList
 {public:
   FrameList(const CompositePixmap* const,
             const int numFrames,
             const int firstFrame=0);
   const Pixmap& GetFrame() const;
   const int PixWidth() const;
   const int PixHeight() const;
   const int GetNumFrames() const;
   const int GetFrameNumber() const;
   const int GetFirstFrameNumber() const;
   FrameList& UpdateFrameNumber();
   FrameList& Reset();
   FrameList& SetFrame(const int frameNum=0);
 private:
   const CompositePixmap* const frameData;
   const int numFrames,
             firstFrame;
   int currentFrame;
 };


inline FrameList::FrameList(const CompositePixmap* const fData,
                            const int nFrames,
			                      const int frame1): frameData(fData),
                                               numFrames(nFrames),
                                               firstFrame(frame1),
                                               currentFrame(frame1)
 {
 }

inline const Pixmap& FrameList::GetFrame() const
 {return frameData[currentFrame].GetPixmap();
 }

inline const int FrameList::PixWidth() const
 {return frameData->GetPixWidth();
 }

inline const int FrameList::PixHeight() const
 {return frameData->GetPixHeight();
 }

inline const int FrameList::GetNumFrames() const
 {return numFrames;
 }

inline const int FrameList::GetFrameNumber() const
 {return currentFrame;
 }

inline const int FrameList::GetFirstFrameNumber() const
 {return firstFrame;
 }

inline FrameList& FrameList::UpdateFrameNumber()
 {if (++currentFrame>=numFrames)
    currentFrame=0;
   return *this;
 }

inline FrameList& FrameList::Reset()
 {currentFrame=firstFrame;
  return *this;
 }

inline FrameList& FrameList::SetFrame(const int frameNum)
 {currentFrame=frameNum;
  return *this;
 }

#endif
