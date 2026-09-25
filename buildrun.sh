cmake -S . -B build

if [ $? -ne 0 ]; then
    echo "Problem running CMake!"
    exit 1
fi

cmake --build build

if [ $? -ne 0 ]; then
    echo "Problem building project!"
    exit 1
fi

./build/test/game

if [ $? -ne 0 ]; then
    echo "Problem running game!"
    exit 1
fi