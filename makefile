CXX=g++
CXXFLAGS=-I/usr/include/X11 -O3 -w
LDFLAGS=-L/usr/lib/X11
all: XAsteroids AutoRepeatOn

XAsteroids: rotatorDisplayData.o compositePixmap.o XAsteroids.o
	${CXX} ${CXXFLAGS} XAsteroids.o rotatorDisplayData.o compositePixmap.o ${LDFLAGS} -lXm -lXt -lX11 -oXAsteroids

rotatorDisplayData.o: utilities/pixmaps/rotated/rotatorDisplayData.H utilities/pixmaps/rotated/rotatorDisplayData.C
	${CXX} ${CXXFLAGS}  -c utilities/pixmaps/rotated/rotatorDisplayData.C

compositePixmap.o: utilities/pixmaps/composite/compositePixmap.H utilities/pixmaps/composite/compositePixmap.C
	${CXX} ${CXXFLAGS}  -c utilities/pixmaps/composite/compositePixmap.C

XAsteroids.o: bitmaps/ENEMYDecor.xbm bitmaps/ROCKDecor1.xbm bitmaps/ROCKDecor2.xbm bitmaps/ROCKDecor3.xbm XAsteroids.C utilities/box.H objects/bullet.H utilities/pixmaps/composite/compositePixmap.H bitmaps/enemyBulletDecor.xbm objects/enemies/enemyBulletGroup.H bitmaps/enemyDecor.xbm objects/enemies/enemyGroup.H objects/explosions/explosion.H bitmaps/explosionCenter.xbm bitmaps/explosionEdge.xbm objects/explosions/explosionGraphic.H bitmaps/explosionMiddle.xbm utilities/frames/frameList.H utilities/frames/frameTimer.H utilities/intersection2d.H utilities/liner.H utilities/linkedArray.H objects/movableObject.H gamePlay/options/options.H gamePlay/playingField.H objects/rocks/rockGroup.H utilities/pixmaps/rotated/rotator.H utilities/pixmaps/rotated/rotatorDisplayData.H gamePlay/score.H bitmaps/starDestroyerIcon.xbm bitmaps/NCC1701DIcon.xbm bitmaps/NCC1701AIcon.xbm bitmaps/shipBulletDecor.xbm objects/ships/shipBulletGroup.H bitmaps/starDestroyerDecor.xbm bitmaps/NCC1701DDecorBottom.xbm bitmaps/NCC1701DDecorTop.xbm bitmaps/NCC1701ADecor.xbm objects/ships/shipGroup.H gamePlay/options/button.H gamePlay/shipYard.H objects/rocks/spawner.H gamePlay/stage.H bitmaps/starDestroyerThrustCenter.xbm bitmaps/starDestroyerThrustEdge.xbm bitmaps/starDestroyerThrustMiddle.xbm bitmaps/NCC1701DThrustDecor.xbm bitmaps/NCC1701AThrustDecor.xbm utilities/vector2d.H
	${CXX} ${CXXFLAGS}  -c XAsteroids.C

AutoRepeatOn: AutoRepeatOn.C
	${CXX} ${CXXFLAGS} AutoRepeatOn.C ${LDFLAGS} -lX11 -o AutoRepeatOn

clean:
	\rm -rf XAsteroids AutoRepeatOn *.o *.u *.bak *.CKP
