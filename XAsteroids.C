#include<stdlib.h>
#include<iostream>
#include"stage.H"
#include"score.H"
#include"shipYard.H"
#include"explosionGraphic.H"
#include"shipGroup.H"
#include"shipBulletGroup.H"
#include"rockGroup.H"
#include"enemyGroup.H"
#include"enemyBulletGroup.H"
#include"playingField.H"
Stage stage;
Button button(stage.display,stage.window,
              "Options",stage.buttonInfo,
              stage.buttonFg,stage.buttonBg,
              stage.buttonX,stage.buttonY);
Score score;
ExplosionGraphic explosionGraphic;
ShipGroup shipGroup;
ShipYard shipYard(stage.display,stage.window,
		              shipGroup.ship->icon,
		              shipGroup.ship->iconWidth,shipGroup.ship->iconHeight,
                  shipGroup.ship->iconColor,
		              stage.shipYardWidth,stage.shipYardHeight,Stage::shipYardBg);
ShipBulletGroup shipBulletGroup;
RockGroup rockGroup;
EnemyGroup enemyGroup;
EnemyBulletGroup enemyBulletGroup;
PlayingField playingField;

int main (int argc, char *argv[])
 {cout<<"Your highest score this game was "<<playingField.PlayTheGame(argc>1 ? atoi(argv[1])
                                                                             : 1,
                                                                      argc, argv)<<'.'<<endl;
  return 0;
 }
