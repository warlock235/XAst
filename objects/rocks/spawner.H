#ifndef _SPAWNER_H
#define _SPAWNER_H

class Spawner
 {public:
    inline Spawner(const int numObjs);
    inline Spawner(const Spawner&);
    inline ~Spawner();
    inline Spawner& operator=(const Spawner&);
    inline Rock*& operator[](const int spawnNum) const;
    inline Rock* GetSpawnWithInheritance(const Rock& parent,
                                  const double time,
                                  const int spawnNum);
    inline const int GetNumSpawn() const;

  private:
    int numSpawn;
    Rock** spawnList;
 };

#include"rockGroup.H"

inline Spawner::Spawner(const int numObjs): numSpawn(numObjs),
                                            spawnList(new Rock*[numSpawn])

 {for (int i=0;i<numSpawn;++i)
    spawnList[i]=NULL;
 }

inline Rock*& Spawner::operator[](const int spawnNum) const
 {return spawnList[spawnNum];
 }

inline const int Spawner::GetNumSpawn() const
 {return numSpawn;
 }

inline Spawner::Spawner(const Spawner& spawn): numSpawn(spawn.GetNumSpawn()),
                                               spawnList(new Rock*[numSpawn])
 {for (int i=0;i<numSpawn;++i)
    spawnList[i]=spawn[i];
 }

inline Spawner::~Spawner()
 {delete [] spawnList;
 }

inline Spawner& Spawner::operator=(const Spawner& spawn)
 {delete [] spawnList;
  numSpawn=spawn.GetNumSpawn();
  spawnList=new Rock*[numSpawn];
  for (int i=0;i<numSpawn;++i)
    spawnList[i]=spawn[i];
  return *this;
 }

inline Rock* Spawner::GetSpawnWithInheritance(const Rock& parent,
                                              const double time,
                                              const int spawnNum)
 {spawnList[spawnNum]->CurrentBox().MoveBox(parent.ObjectLiner()
                                                  .Move(parent.OldBox().Center(),time)
                                            -spawnList[spawnNum]->CurrentBox().Center());
  return spawnList[spawnNum];
 }


#endif
