#!/bin/bash
mkdir bin
mkdir bin/linux

cp Assets/* bin/linux

g++ -o bin/linux/ld42 Src/AssetLoader.cpp Src/AudioSystem.cpp Src/Game.cpp Src/HudRenderer.cpp Src/Input.cpp Src/Level.cpp Src/Main.cpp Src/NPC.cpp Src/Physics.cpp Src/Pickup.cpp Src/Player.cpp Src/Portal.cpp Src/RayCastRender.cpp Src/Renderer.cpp Src/SoundClip.cpp -std=c++1z -Ideps/all/glm -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

chmod +x bin/linux/ld42