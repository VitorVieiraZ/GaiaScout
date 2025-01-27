import QtQuick
import QtLocation

MapQuickItem {
  id: marker

  property string name: ""
  property string street: ""

  sourceItem: Image {
    source: __style.pointIcon
    width: 24
    height: 24
  }

  anchorPoint.x: sourceItem.width / 2
  anchorPoint.y: sourceItem.height / 2

  MouseArea {
    anchors.fill: parent

    onClicked: {
      console.log("Marker clicked aat Latitude:", coordinate.latitude,
                  "Longitude:", coordinate.longitude)
    }
  }
}
