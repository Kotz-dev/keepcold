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

find_package(magic_enum CONFIG REQUIRED)

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
        src/widgets/ItemCard.cpp
        include/widgets/ItemCard.h
        include/memory/Memory.h
        src/app/keepcold/windowItem/windowitem.cpp
        include/app/keepcold/windowItem/windowitem.h
        src/app/keepcold/windowItem/windowitem.ui
        src/app/keepcold/windowConfig/windowconfig.cpp
        include/app/keepcold/windowConfig/windowconfig.h
        src/app/keepcold/windowConfig/windowconfig.ui
        src/item/Item.cpp
        include/item/Item.h
        src/item/logins.cpp
        include/item/logins.h
        src/item/Note.cpp
        include/item/Note.h
        src/item/key.cpp
        include/item/key.h
        src/item/recuperacao.cpp
        include/item/recuperacao.h
        src/item/cartao.cpp
        include/item/cartao.h
        src/item/identidade.cpp
        include/item/identidade.h
        src/item/wifi.cpp
        include/item/wifi.h
        src/item/arquivo.cpp
        include/item/arquivo.h
        src/item/itens.cpp
        src/item/itens.h
        src/io/json_.cpp
        src/io/json_.h

)
target_include_directories(keepcold PRIVATE include)
set_target_properties(keepcold PROPERTIES AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/src/app/keepcold/mainwindow;${CMAKE_SOURCE_DIR}/src/app/keepcold/windowConfig;${CMAKE_SOURCE_DIR}/src/app/keepcold/windowItem")

if(DEFINED ENV{QT_WIDGETS_TOOLKIT_DIR} AND EXISTS "$ENV{QT_WIDGETS_TOOLKIT_DIR}")
    set(QT_WIDGETS_TOOLKIT_DIR "$ENV{QT_WIDGETS_TOOLKIT_DIR}")
elseif(EXISTS "${CMAKE_SOURCE_DIR}/../qt-widgets-toolkit")
    set(QT_WIDGETS_TOOLKIT_DIR "${CMAKE_SOURCE_DIR}/../qt-widgets-toolkit")
else()
    set(QT_WIDGETS_TOOLKIT_DIR "$ENV{USERPROFILE}/Documents/GitHub/qt-widgets-toolkit")
endif()
add_subdirectory("${QT_WIDGETS_TOOLKIT_DIR}" qt-widgets-toolkit)

target_link_libraries(keepcold
        Qt::Core
        Qt::Gui
        Qt::Widgets
        QtWidgetStoolkit
        magic_enum::magic_enum
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
    if (VCPKG_TOOLCHAIN)
        # vcpkg's Qt port lays out the triplet root two levels above Qt6_DIR
        # (.../installed/<triplet>/share/Qt6), with a further "debug/" split
        # for debug binaries and plugins nested under "<root>/Qt6/plugins".
        get_filename_component(QT_TRIPLET_ROOT "${Qt6_DIR}/../.." ABSOLUTE)
        if (DEBUG_SUFFIX)
            set(QT_TRIPLET_ROOT "${QT_TRIPLET_ROOT}/debug")
        endif ()
        set(QT_PLUGINS_DIR "${QT_TRIPLET_ROOT}/Qt6/plugins")
    else ()
        get_filename_component(QT_INSTALL_PATH "${Qt6_DIR}/../../.." ABSOLUTE)
        set(QT_PLUGINS_DIR "${QT_INSTALL_PATH}/plugins")
    endif ()
    if (EXISTS "${QT_PLUGINS_DIR}")
        # Point Qt straight at the plugin tree via qt.conf instead of copying
        # individual plugin DLLs: Qt's default runtime search only checks
        # "<exe_dir>/platforms/", not "<exe_dir>/plugins/platforms/", so a
        # hand-copied plugin would never actually be found without this.
        file(GENERATE OUTPUT "$<TARGET_FILE_DIR:${PROJECT_NAME}>/qt.conf" CONTENT
"[Paths]
Plugins = ${QT_PLUGINS_DIR}
")
    endif ()
    if (NOT VCPKG_TOOLCHAIN)
        # Under vcpkg, Qt6Core/Gui/Widgets are already deployed next to the
        # executable by vcpkg's own applocal.ps1 post-build step.
        foreach (QT_LIB Core Gui Widgets)
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
        endforeach (QT_LIB)
    endif ()
endif ()