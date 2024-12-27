cmake_minimum_required(VERSION 3.16)

project(Instrument_cluster VERSION 0.1 LANGUAGES CXX)

set(PRJ_NAME Instrument_cluster)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(Qt6 6.5 REQUIRED COMPONENTS Quick SerialBus SerialPort)
find_package(Qt6 REQUIRED COMPONENTS Quick SerialBus SerialPort)
find_package(CommonAPI REQUIRED)
find_package(CommonAPI-SomeIP REQUIRED)
find_package(vsomeip3 REQUIRED)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appInstrument_cluster
    main.cpp
    vcan.cpp
    vcan.h
)

qt_add_qml_module(appInstrument_cluster
    URI Instrument_cluster
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES vcanworker.h vcanworker.cpp
)




set_target_properties(appInstrument_cluster PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appInstrument_cluster PRIVATE
    # /home/ahsan/Documents/Automotive-Software-Engineering-Project/Digital_Cockpit/IPC_Serivce/middleware/src-gen
    # vsomeip3 CommonAPI CommonAPI-SomeIP
    ${CMAKE_CURRENT_SOURCE_DIR}/../middleware/src-gen
    ${CommonAPI_INCLUDE_DIRS}
    ${CommonAPI-SomeIP_INCLUDE_DIRS}
    ${VSOMEIP_INCLUDE_DIRS}
    # ${CMAKE_SOURCE_DIR}/../IPC_Service/middleware/src-gen

    # /home/ahsan/capicxx-core-runtime/include
    /usr/local/include/CommonAPI-3.2/
    /usr/local/include/vsomeip
    # /home/ahsan/commonapi-someip/vsomeip/interface
)

target_link_libraries(appInstrument_cluster
    PRIVATE
    Qt6::Quick
    Qt6::SerialBus
    Qt6::SerialPort
    CommonAPI
    CommonAPI-SomeIP
    vsomeip3
)

include(GNUInstallDirs)
install(TARGETS appInstrument_cluster
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)



# MESA: error: ZINK: failed to choose pdev
# libEGL warning: egl: failed to create dri2 screen
# 19:12:37: /home/ahsan/Documents/Automotive-Software-Engineering-Project/Digital_Cockpit/QT/Instrument_cluster/build/Desktop_Qt_6_8_0-Debug/appInstrument_cluster crashed.
