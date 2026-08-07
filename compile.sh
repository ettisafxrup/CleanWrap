echo "Compiling CleanWrap..."
echo "Processing icon..."
windres assets/icon.rc -O coff -o icon.o

echo "Linking..."
g++ -O2 -std=c++20 -Wall -Wextra -Iinclude main.cpp src/*.cpp icon.o -o CleanWrap.exe -mwindows -static-libgcc -static-libstdc++
rm icon.o

mkdir -p release
echo "Done."