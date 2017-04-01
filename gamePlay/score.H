#ifndef _SCORE_H
#define _SCORE_H

#include<fstream>
#include<string.h>
#include<sys/types.h>
#include<pwd.h>
#include<unistd.h>

using namespace std;

class Score
 {typedef int Boolean;
  enum {off, on};

  friend ifstream& operator>>(ifstream&, char* const);
  friend ofstream& operator<<(ofstream&, char* const);

  public:
    Score();
    ~Score();
    int& CurrentScore();
    const char* const CurrentName() const;
    const int TopTenScore(const int i) const;
    const char* const TopTenName(const int i) const;
    const int NumScores() const;
    Score& UpdateTopTen();
    Score& Reset();

  private:
    void UpdateScoreArray();

    Boolean scoreUpdated;
    int currentScore,
        score[10],
        numScores;
    char currentName[9],
         name[10][9],
       * fileName;
 };

inline ifstream& operator>>(ifstream& f, char* const s)
 {int i=0;
  if (!f.eof())
   {char ch;
    while (!f.get(ch).eof()&&(ch=='\n'||ch=='\t'||ch==' '));
    if (!f.eof()&&ch!='\0')
     {s[i++]=ch;
      while (!f.get(ch).eof()&&ch!='\0'&&i<8)
        s[i++]=ch;
      while(ch!='\0'&&!f.get(ch).eof());
     }
   }
  s[i]='\0';
  return f;
 }

inline ofstream& operator<<(ofstream& f, char* const s)
 {int i=0;
  while(s[i])f.put(s[i++]);
  f.put(s[i]);
  return f;
 }

inline Score::Score(): currentScore(0),
                       numScores(0),
                       scoreUpdated(off)
 {passwd* userData=getpwuid(geteuid());
  strncpy(currentName,userData->pw_name,8)[8]='\0';
  char* cwd=getcwd(new char[3000],3000);
  int fnLen1=strlen("/Volumes/XAsteroids/XAst/hiScore.data"),
      fnLen2=strlen(userData->pw_dir)
             +strlen("/XAsteroids/hiScore.data"),
      fnLen3=strlen(cwd)
             +strlen("/XAsteroids/hiScore.data"),
      fnLen4=strlen(cwd)
             +strlen("/hiScore.data");
  fileName=new char[(fnLen1>(fnLen2=fnLen2>(fnLen3=fnLen3>fnLen4
                                                   ? fnLen3
                                                   : fnLen4)
                                    ? fnLen2
                                    : fnLen3)
                     ? fnLen1
		                 : fnLen2)+1];
  strcpy(fileName,"/Volumes/XAsteroids/XAst/hiScore.data");
  ifstream file(fileName,ios::in);
  if (!file)
   {file.open(strcat(strcpy(fileName,userData->pw_dir),
                          "/XAsteroids/hiScore.data"),
              ios::in);
    if (!file)
     {file.open(strcat(strcpy(fileName,cwd),
                            "/XAsteroids/hiScore.data"),
                ios::in);

      if (!file)
       {file.open(strcat(strcpy(fileName,cwd),
                              "/hiScore.data"),
                  ios::in);
        if (!file)
         {delete [] cwd;
          return;
         }
       }
     }
   }
  delete [] cwd;
  do
    file>>name[numScores]>>score[numScores];
  while(!file.eof()&&++numScores<sizeof(score)/sizeof(int));
 }

inline void Score::UpdateScoreArray()
 {if (numScores<sizeof(score)/sizeof(int))
   {name[numScores][0]='\0';
    score[numScores++]=-1;
   }
  for (int i=0;i<numScores;++i)
    if (currentScore>score[i])
     {for (int j=numScores<sizeof(score)/sizeof(int)
                 ? numScores
                 : sizeof(score)/sizeof(int)-1;j>i;--j)
       {strcpy(name[j],name[j-1]);
        score[j]=score[j-1];
       }
      strcpy(name[i],currentName);
      score[i]=currentScore;
      break;
     }
 }

inline Score& Score::UpdateTopTen()
 {if (!scoreUpdated)
   {ifstream ifile(fileName,ios::in);
    if (ifile)
     {numScores=0;
      do
        ifile>>name[numScores]>>score[numScores];
      while(!ifile.eof()&&++numScores<sizeof(score)/sizeof(int));
     }
    UpdateScoreArray();
    ofstream ofile(fileName,ios::out);
    for (int i=0;i<numScores;++i)
      ofile<<name[i]<<score[i];
    scoreUpdated=on;
   }
  return *this;
 }

inline Score::~Score()
 {UpdateTopTen();
  delete [] fileName;
 }

inline int& Score::CurrentScore()
 {return currentScore;
 }

inline const char* const Score::CurrentName() const
 {return currentName;
 }

inline const int Score::TopTenScore(const int i) const
 {return score[i];
 }

inline const char* const Score::TopTenName(const int i) const
 {return name[i];
 }

inline const int Score::NumScores() const
 {return numScores;
 }

inline Score& Score::Reset()
 {currentScore=0;
  scoreUpdated=off;
  return *this;
 }

#endif
