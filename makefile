CXX=g++
CXXFLAGS=-I/opt/X11/include -O0 -g
LDFLAGS=-L/opt/X11/lib
all: XAsteroids AutoRepeatOn

XAsteroids: rotatorDisplayData.o compositePixmap.o XAsteroids.o
	${CXX} ${CXXFLAGS} XAsteroids.o rotatorDisplayData.o compositePixmap.o ${LDFLAGS} -lXm -lXt -lX11 -oXAsteroids

rotatorDisplayData.o: rotatorDisplayData.H rotatorDisplayData.C
	${CXX} ${CXXFLAGS}  -c rotatorDisplayData.C

compositePixmap.o: compositePixmap.H compositePixmap.C
	${CXX} ${CXXFLAGS}  -c compositePixmap.C

XAsteroids.o: ENEMYDecor.xbm ROCKDecor1.xbm ROCKDecor2.xbm ROCKDecor3.xbm XAsteroids.C box.H bullet.H compositePixmap.H enemyBulletDecor.xbm enemyBulletGroup.H enemyDecor.xbm enemyGroup.H explosion.H explosionCenter.xbm explosionEdge.xbm explosionGraphic.H explosionMiddle.xbm frameList.H frameTimer.H intersection2d.H liner.H linkedArray.H movableObject.H options.H playingField.H rockGroup.H rotator.H rotatorDisplayData.H score.H starDestroyerIcon.xbm NCC1701DIcon.xbm NCC1701AIcon.xbm shipBulletDecor.xbm shipBulletGroup.H starDestroyerDecor.xbm NCC1701DDecorBottom.xbm NCC1701DDecorTop.xbm NCC1701ADecor.xbm shipGroup.H button.H shipYard.H spawner.H stage.H starDestroyerThrustCenter.xbm starDestroyerThrustEdge.xbm starDestroyerThrustMiddle.xbm NCC1701DThrustDecor.xbm NCC1701AThrustDecor.xbm vector2d.H
	${CXX} ${CXXFLAGS}  -c XAsteroids.C

AutoRepeatOn: AutoRepeatOn.C
	${CXX} ${CXXFLAGS}  ${LDFLAGS} -lX11 AutoRepeatOn.C -oAutoRepeatOn

clean:
	\rm -rf XAsteroids AutoRepeatOn *.o *.bak *.CKP
