all:
	g++ -Isrc/include/SDL2 -Lsrc/lib -o spaceshooter main.cpp Bullet.cpp Bullet.h Button.cpp Button.h Character.cpp Character.h Collision.cpp Collision.h Common.cpp Common.h Enemy.cpp Enemy.h EnemyWave.cpp EnemyWave.h ObjectHandler.cpp ObjectHandler.h Spaceship.cpp Spaceship.h Support.cpp Support.h TextObject.cpp TextObject.h Texture.cpp Texture.h -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer