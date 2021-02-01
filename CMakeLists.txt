cmake_minimum_required(VERSION 3.13)
project(LeNet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-pthread -llapack -lblas -lcblas -lgfortran -llapack")

find_package(OpenCV REQUIRED )
find_package(FLTK REQUIRED )


add_executable(LeNet main.cpp Loader/Loader.cpp Loader/Loader.h Loader/ILoader.h Object.h File/LabelDataType.h File/LabelDataType.cpp Processor/IProcessor.h Processor/DummyProcessor.cpp Processor/DummyProcessor.h Folder/LabelPathType.h Folder/LabelPathType.cpp LeNet.h)
target_link_libraries(LeNet libdlib.a ${OpenCV_LIBS})
target_link_libraries(LeNet ${FLTK_LIBRARIES})

