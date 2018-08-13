#!/bin/bash
mkdir bin
mkdir bin/macos
mkdir bin/macos/TempleOfHate.app
mkdir bin/macos/TempleOfHate.app/Contents
mkdir bin/macos/TempleOfHate.app/Contents/MacOS
mkdir bin/macos/TempleOfHate.app/Contents/Resources

cp Assets/* bin/macos/TemplateOfHate.app/Contents/Resources
cp deploy/mac/Info.plist bin/macos/TemplateOfHate.app/Contents
cp deploy/mac/TemplateOfHate.icns bin/macos/TemplateOfHate.app/Contents/Resources

g++ -o bin/macos/TemplateOfHate.app/Contents/MacOS/ld42 src/AssetLoader.cpp src/AudioSystem.cpp src/Game.cpp src/HudRenderer.cpp src/Input.cpp src/Level.cpp src/Main.cpp src/NPC.cpp src/Physics.cpp src/Pickup.cpp src/Player.cpp src/Portal.cpp src/RayCastRender.cpp src/Renderer.cpp src/SoundClip.cpp -std=c++1z -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf -Ideps/all/glm -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Frameworks/SDL2_mixer.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers 
