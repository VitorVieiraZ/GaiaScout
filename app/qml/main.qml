import QtQuick
import QtQuick.Controls
import fieldWork 1.0

Window {
  id: mainAppWindow

  visible: true
  width: __appwindowwidth
  height: __appwindowheight
  visibility: __appwindowvisibility

  title: "GaiaScout"

  Rectangle {
    id: background
    anchors.fill: parent
    color: __style.secondaryColor
  }

  Item {
    id: stateManager
    state: "map" // Default state

    function setStateProperties(mapVisible, toolbarVisible, recordingVisible, crosshairVisible, cameraVisible, gpsLabelVisible) {
      mapView.visible = mapVisible
      mainToolbar.visible = toolbarVisible
      recordingToolbar.visible = recordingVisible
      crosshair.visible = crosshairVisible
      cameraView.visible = cameraVisible
      gpsLabel.visible = gpsLabelVisible
    }

    states: [
      State {
        name: "map"
        StateChangeScript {
          script: stateManager.setStateProperties(true, true, false, false,
                                                  false, true)
        }
      },
      State {
        name: "recording"
        StateChangeScript {
          script: stateManager.setStateProperties(true, false, true, true,
                                                  false, true)
        }
      },
      State {
        name: "projects"
        StateChangeScript {
          script: stateManager.setStateProperties(false, true, false, false,
                                                  false, false)
        }
      },
      State {
        name: "settings"
        StateChangeScript {
          script: stateManager.setStateProperties(false, false, false, false,
                                                  false, false)
        }
      },
      State {
        name: "camera"
        StateChangeScript {
          script: {
            stateManager.setStateProperties(false, false, false, false,
                                            true, false)
            __cameraController.openNativeCamera()
          }
        }
      }
    ]
  }

  MapView {
    id: mapView
    anchors {
      top: parent.top
      left: parent.left
      right: parent.right
      bottom: mainToolbar.top
    }

    Crosshair {
      id: crosshair
    }
  }

  CameraView {
    id: cameraView
    visible: false
    anchors {
      top: parent.top
      topMargin: __style.safeAreaTop
      bottom: parent.bottom
      bottomMargin: __style.safeAreaBottom
      left: parent.left
      right: parent.right
    }
  }

  Rectangle {
    id: gpsLabel
    width: childrenRect.width + __style.margin20
    height: 30
    color: __style.secondaryColor
    radius: 15
    anchors {
      bottom: mainToolbar.top
      bottomMargin: 20
      horizontalCenter: parent.horizontalCenter
    }

    Row {
      anchors.centerIn: parent
      spacing: 5

      Image {
        source: __style.gpsIcon
        width: 20
        height: 20
        anchors.verticalCenter: parent.verticalCenter
      }

      Text {
        id: gpsText
        text: "Lat: 0.000000, Lon: 0.000000"
        color: __style.mainColor
        font.pixelSize: 14
        anchors.verticalCenter: parent.verticalCenter
      }
    }

    MouseArea {
      anchors.fill: parent
      onClicked: {
        __mapController.centerOnGpsLocation()
      }
    }

    Connections {
      target: __mapController
      function onGpsPositionChanged(position) {
        gpsText.text = "Lat: " + position.latitude.toFixed(
              6) + ", Lon: " + position.longitude.toFixed(6)
      }
    }
  }

  Toolbar {
    id: mainToolbar
    anchors {
      bottom: parent.bottom
      bottomMargin: __style.safeAreaBottom
      left: parent.left
      right: parent.right
    }
    height: 60

    model: ObjectModel {
      ToolbarButton {
        text: "Add"
        iconSource: __style.addIcon
        onClicked: {
          stateManager.state = "recording"
        }
      }

      ToolbarButton {
        text: "Projects"
        iconSource: __style.projectsFolderIcon
        onClicked: {
          stateManager.state = "projects"
          projectsPage.visible = true
        }
      }

      ToolbarButton {
        text: "Settings"
        iconSource: __style.settingsIcon
        onClicked: {
          stateManager.state = "settings"
          settingsPage.visible = true
        }
      }
    }
  }

  Toolbar {
    id: recordingToolbar
    anchors {
      bottom: parent.bottom
      bottomMargin: __style.safeAreaBottom
      left: parent.left
      right: parent.right
    }
    height: 60
    visible: false

    model: ObjectModel {
      ToolbarButton {
        text: "Add Point"
        iconSource: __style.plusIcon
        onClicked: {
          form.visible = true
        }
      }

      ToolbarButton {
        text: "Photo"
        iconSource: __style.cameraIcon
        onClicked: {
          stateManager.state = "camera"
        }
      }

      ToolbarButton {
        text: "Cancel"
        iconSource: __style.cancelIcon
        onClicked: stateManager.state = "map"
      }
    }
  }

  Form {
    id: form
    visible: false
    anchors.fill: parent
  }

  Projects {
    id: projectsPage

    anchors {
      fill: parent
      topMargin: __style.safeAreaTop
      bottomMargin: __style.safeAreaBottom
    }
    visible: false
  }

  Settings {
    id: settingsPage

    anchors {
      fill: parent
      topMargin: __style.safeAreaTop
      bottomMargin: __style.safeAreaBottom
    }

    visible: false
    onSettingsClosed: {
      stateManager.state = "map"
      settingsPage.visible = false
    }
  }

  Connections {
    target: __cameraController
    function onPhotoSaved(filePath) {
      // Get the crosshair's center coordinates
      var crosshairCenter = crosshair.mapToItem(mapView, crosshair.width / 2,
                                                crosshair.height / 2)
      var crosshairCoordinate = mapView.map.toCoordinate(Qt.point(
                                                           crosshairCenter.x,
                                                           crosshairCenter.y))

      // Prepare feature properties
      var properties = {
        "id": (__projectController.getCurrentProjectFeatures(
                 ).length + 1).toString(),
        "description": "Photo Point",
        "photo": filePath,
        "date": new Date().toLocaleString(Qt.locale(), "yyyy-MM-dd hh:mm:ss"),
        "location": crosshairCoordinate.latitude.toFixed(
                      6) + ", " + crosshairCoordinate.longitude.toFixed(6)
      }

      // Add the feature to the current project
      if (__projectController.addFeatureToCurrentProject(crosshairCoordinate,
                                                         properties)) {
        console.log("Point added successfully!")
      } else {
        console.log("Failed to add point.")
      }

      // Return to map state
      stateManager.state = "map"
    }

    function onPhotoSelected() {
      // This signal is emitted on iOS after the photo is selected
      stateManager.state = "map"
    }
  }
}
