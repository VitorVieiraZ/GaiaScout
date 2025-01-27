import QtQuick
import QtMultimedia
import fieldWork 1.0

Item {
  id: root

  CameraController {
    id: camera
    onPhotoSaved: {
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
                      6) + ", " + crosshairCoordinate.longitude.toFixed(6),
        "direction": metadata.direction || "N/A",
        "acceleration": metadata.acceleration || "N/A"
      }

      __projectController.addFeatureToCurrentProject(crosshairCoordinate,
                                                     properties)

      stateManager.state = "map"
    }

    onPhotoSelected: {
      stateManager.state = "map"
    }
  }

  // Rectangle {
  //   id: captureButton
  //   width: 70
  //   height: 70
  //   radius: width / 2
  //   color: "white"
  //   border.color: "black"
  //   border.width: 2
  //   anchors.horizontalCenter: parent.horizontalCenter
  //   anchors.bottom: parent.bottom
  //   anchors.bottomMargin: 20

  //   MouseArea {
  //     anchors.fill: parent
  //     onClicked: {
  //       camera.openNativeCamera() // Open native camera
  //     }
  //   }
  // }
}
