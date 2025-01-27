cmake_minimum_required(VERSION 3.16)
project(tcc_vitor_def VERSION 0.1 LANGUAGES CXX)

# Basic CMake settings
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform detection and definitions
if(IOS OR ANDROID)
    add_compile_definitions(MOBILE_OS)
else()
    add_compile_definitions(DESKTOP_OS)
endif()

# Find required Qt packages
find_package(Qt6 6.2 REQUIRED COMPONENTS
    Quick
    Location
    Positioning
    Multimedia
    Sensors
)

# Source files
set(CPP_SOURCES
    app/cpp/main.cpp
    app/cpp/appstyle.h
    app/cpp/mapcontroller.h
    app/cpp/mapcontroller.cpp
    app/cpp/cameracontroller.h
    app/cpp/cameracontroller.cpp
    app/cpp/projectcontroller.h
    app/cpp/projectcontroller.cpp
    app/cpp/shareutils.h
    app/cpp/shareutils.cpp
)

# QML files
set(QML_FILES
    app/qml/main.qml
    app/qml/Toolbar.qml
    app/qml/ToolbarButton.qml
    app/qml/MapView.qml
    app/qml/Crosshair.qml
    app/qml/CameraView.qml
    app/qml/Form.qml
    app/qml/FormField.qml
    app/qml/Settings.qml
    app/qml/SettingsItem.qml
    app/qml/Projects.qml
    app/qml/ProjectItem.qml
    app/qml/Marker.qml
    app/qml/FeatureDetailsDialog.qml
    app/qml/PhotoPreview.qml
    app/qml/CreateProject.qml
)

# Platform-specific source files
if(IOS)
    set(PLATFORM_SOURCES
        app/ios/ShareUtils.mm
        app/ios/CameraHelper.mm
    )
endif()

# Android specific configuration
if(ANDROID)
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/app/android")
    set(ANDROID_JAVA_SOURCE_DIR "${ANDROID_PACKAGE_SOURCE_DIR}/src")

    # Create the directory structure if it doesn't exist
    file(MAKE_DIRECTORY "${ANDROID_JAVA_SOURCE_DIR}/br/co/gaiascout")

    # Set Android specific files
    set(PLATFORM_SOURCES
        ${ANDROID_JAVA_SOURCE_DIR}/br/co/gaiascout/ShareUtils.java
        ${ANDROID_JAVA_SOURCE_DIR}/br/co/gaiascout/CameraController.java
        ${ANDROID_JAVA_SOURCE_DIR}/br/co/gaiascout/MainActivity.java
    )

    # Configure Android dependencies
    set(ANDROID_EXTRA_LIBS)
    set(ANDROID_DEPENDENCIES
        "implementation 'androidx.appcompat:appcompat:1.6.1'"
        "implementation 'androidx.core:core:1.12.0'"
        "implementation 'com.google.android.material:material:1.11.0'"
    )

    # Create build.gradle if it doesn't exist
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/app/android/build.gradle.in"
        "${ANDROID_PACKAGE_SOURCE_DIR}/build.gradle"
        @ONLY
    )
endif()

# Main executable
qt_add_executable(apptcc_vitor_def
    ${CPP_SOURCES}
    ${PLATFORM_SOURCES}
    app/images/images.qrc
)

# QML module
qt_add_qml_module(apptcc_vitor_def
    URI tcc_vitor_def
    VERSION 1.0
    QML_FILES ${QML_FILES}
)

# Link libraries
target_link_libraries(apptcc_vitor_def
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Location
    PRIVATE Qt6::Positioning
    PRIVATE Qt6::PositioningQuick
    PRIVATE Qt6::Multimedia
    PRIVATE Qt6::Sensors
)

# Platform-specific settings
if(IOS)
    set_target_properties(apptcc_vitor_def PROPERTIES
        QT_IOS_CAMERA_USAGE_DESCRIPTION
            "This app needs to access your camera to capture photos."
        QT_IOS_PHOTO_LIBRARY_USAGE_DESCRIPTION
            "This app needs to access your photo library to select and upload pictures."
        QT_IOS_PHOTO_LIBRARY_ADD_USAGE_DESCRIPTION
            "This app needs to save images to your photo library."
        QT_IOS_LOCATION_WHEN_IN_USE_USAGE_DESCRIPTION
            "This app needs your location while in use to show your position on the map."
        MACOSX_BUNDLE_INFO_PLIST
            "${CMAKE_CURRENT_SOURCE_DIR}/app/ios/Info.plist"
    )
endif()

if(ANDROID)
    set_target_properties(apptcc_vitor_def PROPERTIES
        QT_ANDROID_PACKAGE_SOURCE_DIR "${ANDROID_PACKAGE_SOURCE_DIR}"
        QT_ANDROID_EXTRA_LIBS "${ANDROID_EXTRA_LIBS}"
        QT_ANDROID_EXTRA_DEPENDENCIES "${ANDROID_DEPENDENCIES}"
    )
endif()
