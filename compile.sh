clear
if [[ $1 == "-re" ]]
then
    echo "------------RE-BUILD"------------
    rm -rf ./lib/
    rm -rf ./build/
    rm -f ./arcade
    if [ ! -d "./build/" ]
    then
        mkdir ./build/ && cd ./build/
        cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    else
        cd ./build/
        cmake --build . --target clean
    fi
    cmake --build .
    cd ..
    echo "------------END------------"

elif [[ $1 == "-d" ]]
then
    echo ""------------VALGRIND"------------"
    cd ./build/
    cmake .. -DCMAKE_BUILD_TYPE=Debug
    cmake --build .
    cd ..
    echo "------------END------------"

elif [[ $1 == "-c" ]]
then
    echo "------------CLEAR------------"
    rm -rf ./lib/
    rm -rf ./build/
    rm -f ./arcade
    echo "------------END------------"

else
    echo "------------BUILD------------"
    if [ ! -d "./build/" ]
    then
        mkdir ./build/ && cd ./build/
        cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    else
        cd ./build/
        cmake --build . --target clean
    fi
    cmake --build .
    cd ..
    echo "------------END------------"
fi
