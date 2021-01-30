cmake_minimum_required(VERSION 3.17)
project(LeNet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -pthread)

find_package(OpenCV REQUIRED )

add_executable(LeNet main.cpp Loader/Loader.cpp Loader/Loader.h Loader/ILoader.h Object.h File/LabelDataType.h File/LabelDataType.cpp Processor/IProcessor.h Processor/DummyProcessor.cpp Processor/DummyProcessor.h Folder/LabelPathType.h Folder/LabelPathType.cpp)
target_link_libraries(LeNet libdlib.a ${OpenCV_LIBS})
