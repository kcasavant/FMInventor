cmake_minimum_required(VERSION 3.8.2)
project(FMInventor)

find_package(Qt5 COMPONENTS Core Quick Qml Multimedia REQUIRED)
find_package(ALSA REQUIRED)

qt5_add_binary_resources(FMAnalysisData FMAnalysisData.qrc)
set(Source main.cpp SineGenerator.cpp PreviewController.cpp SineSource.cpp)
qt5_wrap_cpp(Source PreviewController.h SineSource.h)

add_executable(FMInventor ${Source})
target_link_libraries(FMInventor Qt5::Core Qt5::Qml Qt5::Quick Qt5::Multimedia ALSA::ALSA)

add_executable(testaudiooutput testaudiooutput.cpp)
target_link_libraries(testaudiooutput Qt5::Core Qt5::Multimedia)
