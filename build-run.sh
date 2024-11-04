rm -r bin
rm compile_commands.json
/home/cristmor/programs/premake/premake5 gmake2
bear -- make -j32
./bin/Debug/LevelMaker
