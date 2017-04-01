#ifndef _FRAMETIMER_H
#define _FRAMETIMER_H


class FrameTimer
 {typedef int Boolean;
  enum {off, on};
  public:     
    FrameTimer(const int framesTillAlarm);
    Boolean TimerAlarm();
    FrameTimer& Reset();

    int framesTillAlarm;

  private: 
    int currentFrame;  
 };

inline FrameTimer::FrameTimer(const int alarmTime): framesTillAlarm(alarmTime),
                                                    currentFrame(0)     
 { 
 }

inline FrameTimer::Boolean FrameTimer::TimerAlarm()
 {if (currentFrame++>=framesTillAlarm)
    return on;
  else
    return off;
 }

inline FrameTimer& FrameTimer::Reset()
 {currentFrame=0;
  return *this;
 }

#endif
