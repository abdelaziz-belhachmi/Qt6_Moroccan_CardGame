cmake_minimum_required(VERSION 3.16)

project(cardGame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Multimedia REQUIRED)

qt_standard_project_setup()

qt_add_executable(appcardGame
    main.cpp
)

qt_add_qml_module(appcardGame
    URI cardGame
    VERSION 1.0
    QML_FILES Main.qml


    RESOURCES
    assets/audios/lost.wav
    assets/audios/winner.wav
    assets/audios/shuffle.wav
    assets/audios/cardSound.wav
    assets/audios/liftcard.wav
    assets/audios/achivementsound.wav

    assets/images/stars/bluestar.png
    assets/images/stars/blackstar.png
    assets/images/stars/redstar.png
    assets/images/stars/goldstar.png
    assets/images/stars/silverstar.png
    assets/images/stars/bronzestar.png

    assets/images/pen1.png
    assets/images/enter.png

    assets/images/3.png
    assets/images/5.png
    assets/images/10.png

    assets/images/pause.png
    assets/images/winn.png
    assets/images/playagain.png
    assets/images/home.png
    assets/images/home2.png
    assets/images/newgame.png
    assets/images/resume.png

    assets/images/A/S.png
    assets/images/A/F.png
    assets/images/A/J.png
    assets/images/A/Z.png

    assets/images/B/S.png
    assets/images/B/F.png
    assets/images/B/J.png
    assets/images/B/Z.png


    assets/images/gameover.png
    assets/images/colorpick.png
    assets/images/arrow.png

    assets/images/B/home_image.png
    assets/images/A/home_image.png

    assets/images/A/back_1.png
    assets/images/A/back_2.png
    assets/images/A/back_4.png
    assets/images/A/back_6.png
    assets/images/A/back_8.png
    assets/images/A/back.png

    assets/images/B/back.png
    assets/images/B/back_1.png
    assets/images/B/back_2.png
    assets/images/B/back_4.png
    assets/images/B/back_6.png
    assets/images/B/back_8.png

    assets/images/A/1S.png
    assets/images/A/1Z.png
    assets/images/A/1J.png
    assets/images/A/1F.png

    assets/images/A/2S.png
    assets/images/A/2Z.png
    assets/images/A/2J.png
    assets/images/A/2F.png

    assets/images/A/3S.png
    assets/images/A/3Z.png
    assets/images/A/3J.png
    assets/images/A/3F.png

    assets/images/A/4S.png
    assets/images/A/4Z.png
    assets/images/A/4J.png
    assets/images/A/4F.png

    assets/images/A/5S.png
    assets/images/A/5Z.png
    assets/images/A/5J.png
    assets/images/A/5F.png

    assets/images/A/6S.png
    assets/images/A/6Z.png
    assets/images/A/6J.png
    assets/images/A/6F.png

    assets/images/A/7S.png
    assets/images/A/7Z.png
    assets/images/A/7J.png
    assets/images/A/7F.png

    assets/images/A/10S.png
    assets/images/A/10Z.png
    assets/images/A/10J.png
    assets/images/A/10F.png

    assets/images/A/11S.png
    assets/images/A/11Z.png
    assets/images/A/11J.png
    assets/images/A/11F.png

    assets/images/A/12S.png
    assets/images/A/12Z.png
    assets/images/A/12J.png
    assets/images/A/12F.png


    assets/images/B/1S.png
    assets/images/B/1Z.png
    assets/images/B/1J.png
    assets/images/B/1F.png

    assets/images/B/2S.png
    assets/images/B/2Z.png
    assets/images/B/2J.png
    assets/images/B/2F.png

    assets/images/B/3S.png
    assets/images/B/3Z.png
    assets/images/B/3J.png
    assets/images/B/3F.png

    assets/images/B/4S.png
    assets/images/B/4Z.png
    assets/images/B/4J.png
    assets/images/B/4F.png

    assets/images/B/5S.png
    assets/images/B/5Z.png
    assets/images/B/5J.png
    assets/images/B/5F.png

    assets/images/B/6S.png
    assets/images/B/6Z.png
    assets/images/B/6J.png
    assets/images/B/6F.png

    assets/images/B/7S.png
    assets/images/B/7Z.png
    assets/images/B/7J.png
    assets/images/B/7F.png

    assets/images/B/10S.png
    assets/images/B/10Z.png
    assets/images/B/10J.png
    assets/images/B/10F.png

    assets/images/B/11S.png
    assets/images/B/11Z.png
    assets/images/B/11J.png
    assets/images/B/11F.png

    assets/images/B/12S.png
    assets/images/B/12Z.png
    assets/images/B/12J.png
    assets/images/B/12F.png

    SOURCES controller.h controller.cpp
    SOURCES card.h card.cpp
    SOURCES deck.h deck.cpp
    SOURCES player.h player.cpp
    SOURCES table.h table.cpp

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appcardGame PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appcardGame
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appcardGame
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Multimedia
)

include(GNUInstallDirs)
install(TARGETS appcardGame
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
