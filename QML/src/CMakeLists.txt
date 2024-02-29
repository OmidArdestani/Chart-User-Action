cmake_minimum_required(VERSION 3.16)
project(UserChartAction LANGUAGES CXX)


find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui Qml Quick)
qt_standard_project_setup()

qt_add_executable(UserChartAction
    main.cpp
)

set_target_properties(UserChartAction PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(UserChartAction PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

set(resources_resource_files
    "qml/LineSeries.qml"
    "qml/PointerTool.qml"
    "qml/Main.qml"
)


qt6_add_resources(UserChartAction "UserChartAction"
    PREFIX
        "/"
    FILES
        ${resources_resource_files}
)

install(TARGETS UserChartAction
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
