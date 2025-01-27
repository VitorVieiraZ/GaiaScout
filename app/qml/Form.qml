import QtQuick
import QtQuick.Controls
import fieldWork 1.0

Rectangle {
  id: root

  width: parent.width
  height: parent.height
  color: __style.secondaryColor

  Rectangle {
    id: header
    width: parent.width
    height: 60
    color: "transparent"

    Image {
      id: backButton
      source: __style.backIcon
      width: 24
      height: 24
      anchors {
        left: parent.left
        leftMargin: 16
        verticalCenter: parent.verticalCenter
      }

      MouseArea {
        anchors.fill: parent
        onClicked: root.visible = false
      }
    }

    Text {
      text: "Feature Data Entry"
      font.pixelSize: 18
      color: __style.mainColor
      anchors.centerIn: parent
    }
  }

  Flickable {
    anchors {
      top: header.bottom
      left: parent.left
      right: parent.right
      bottom: saveButton.top
      margins: 16
    }
    contentHeight: formColumn.height
    clip: true

    Column {
      id: formColumn
      width: parent.width
      spacing: 16

      FormField {
        id: featureIdField
        width: parent.width
        label: "Feature ID"
        placeholder: "Auto-generated"
        fieldType: "text"
        value: (__projectController.getCurrentProjectFeatures(
                  ).length + 1).toString()
        enabled: false
      }

      FormField {
        id: descriptionField
        width: parent.width
        label: "Description"
        placeholder: "Enter description"
        fieldType: "text"
        value: ""
      }

      FormField {
        id: photoField
        width: parent.width
        label: "Photo"
        placeholder: "Add a photo"
        fieldType: "photo"
        icon: __style.cameraIcon
        value: ""
        onIconClicked: {
          stateManager.state = "camera"
        }
      }

      FormField {
        id: dateField
        width: parent.width
        label: "Date"
        placeholder: "Auto-generated"
        fieldType: "text"
        value: new Date().toLocaleString(Qt.locale(), "yyyy-MM-dd hh:mm:ss")
        enabled: false
      }

      // Location (auto-generated)
      FormField {
        id: locationField
        width: parent.width
        label: "Location"
        placeholder: "Auto-generated"
        fieldType: "text"
        value: __mapController.center.latitude.toFixed(
                 6) + ", " + __mapController.center.longitude.toFixed(6)
        enabled: false
      }
    }
  }

  Rectangle {
    id: saveButton
    width: parent.width - 32
    height: 50
    radius: 8
    color: __style.secondaryColor
    border.color: __style.mainColor
    border.width: 1
    anchors {
      bottom: parent.bottom
      bottomMargin: 16
      horizontalCenter: parent.horizontalCenter
    }

    Text {
      text: "Save"
      color: __style.mainColor
      font.pixelSize: 16
      anchors.centerIn: parent
    }

    MouseArea {
      anchors.fill: parent
      onClicked: {
        var crosshairCenter = crosshair.mapToItem(mapView, crosshair.width / 2,
                                                  crosshair.height / 2)
        var crosshairCoordinate = mapView.map.toCoordinate(Qt.point(
                                                             crosshairCenter.x,
                                                             crosshairCenter.y))

        var properties = {
          "id": featureIdField.value,
          "description": descriptionField.value,
          "photo": photoField.value,
          "date": dateField.value,
          "location": locationField.value
        }

        if (__projectController.addFeatureToCurrentProject(crosshairCoordinate,
                                                           properties)) {
          console.log("Point added successfully!")
          root.visible = false
          stateManager.state = "map"
        } else {
          console.log("Failed to add point.")
        }
      }
    }
  }

  Connections {
    target: __cameraController
    function onPhotoSaved(filePath) {
      photoField.value = filePath
    }
  }
}
