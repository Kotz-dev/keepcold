cmake_minimum_required(VERSION 4.2)
project(keepcold)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Test
        REQUIRED)

add_executable(keepcold
        src/app/main.cpp
        src/app/keepcold/mainwindow/mainwindow.cpp
        include/app/keepcold/mainwindow/mainwindow.h
        src/app/keepcold/mainwindow/mainwindow.ui
        src/styles/UIStyle.cpp
        include/styles/UIStyle.h
        src/styles/RichText.cpp
        include/styles/RichText.h
        src/io/FileManager.cpp
        include/io/FileManager.h
        resources/Resource.qrc
        src/core/third_party/zxcvbn/zxcvbn.c
        src/core/third_party/zxcvbn/zxcvbn.h
        src/core/PasswordStrength.cpp
        include/core/PasswordStrength.h
        src/styles/LinePassword.cpp
        include/styles/LinePassword.h
        src/widgets/WindowPage.cpp
        include/widgets/WindowPage.h
        include/memory/Memory.h
        src/app/keepcold/mainwindow/windowitem.cpp
        include/app/keepcold/mainwindow/windowitem.h
        src/app/keepcold/mainwindow/windowitem.ui
        src/app/keepcold/mainwindow/windowconfig.cpp
        include/app/keepcold/mainwindow/windowconfig.h
        src/app/keepcold/mainwindow/windowconfig.ui

)
target_include_directories(keepcold PRIVATE include)
set_target_properties(keepcold PROPERTIES AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/src/app/keepcold/mainwindow")

add_subdirectory("$ENV{USERPROFILE}/Documents/GitHub/qt-widgets-toolkit" qt-widgets-toolkit)

target_link_libraries(keepcold
        Qt::Core
        Qt::Gui
        Qt::Widgets
        QtWidgetStoolkit
)

target_include_directories(keepcold PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/third_party/zxcvbn
        ${CMAKE_CURRENT_BINARY_DIR}
)

# dict-generate.cpp has its own main() and only exists to turn the zxcvbn word
# lists into the dict-src.h that zxcvbn.c includes, so it's built as a
# separate host tool rather than linked into keepcold.
add_executable(dict_generate src/core/third_party/zxcvbn/dict-generate.cpp)

set(ZXCVBN_WORDLISTS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/third_party/zxcvbn/dict/words-eng_wiki.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/third_party/zxcvbn/dict/words-female.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/third_party/zxcvbn/dict/words-male.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/third_party/zxcvbn/dict/words-passwd.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/third_party/zxcvbn/dict/words-surname.txt
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/third_party/zxcvbn/dict/words-tv_film.txt
)
set(ZXCVBN_DICT_SRC ${CMAKE_CURRENT_BINARY_DIR}/dict-src.h)

add_custom_command(
        OUTPUT ${ZXCVBN_DICT_SRC}
        COMMAND dict_generate ${ZXCVBN_WORDLISTS} -o ${ZXCVBN_DICT_SRC}
        DEPENDS dict_generate ${ZXCVBN_WORDLISTS}
        COMMENT "Generating zxcvbn dictionary source (dict-src.h)"
)
add_custom_target(generate_zxcvbn_dict DEPENDS ${ZXCVBN_DICT_SRC})
add_dependencies(keepcold generate_zxcvbn_dict)

enable_testing()

add_executable(test_blur
        tests/test_widgets/test_blur.cpp
)
target_include_directories(test_blur PRIVATE include ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_blur PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Test
        QtWidgetStoolkit
)
add_test(NAME test_blur COMMAND test_blur)


if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    get_filename_component(QT_INSTALL_PATH "${Qt6_DIR}/../../.." ABSOLUTE)
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()