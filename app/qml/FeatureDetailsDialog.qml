import QtQuick
import QtQuick.Controls

Dialog {
  id: featureDetailsDialog
  title: "Feature Details"

  modal: true
  anchors.centerIn: parent
  width: parent.width * 0.9
  height: parent.height * 0.8

  header: Rectangle {
    color: "transparent"
    height: 40
    Text {
      text: featureDetailsDialog.title
      color: __style.mainColor
      font.pixelSize: 18
      anchors.centerIn: parent
    }
  }

  background: Rectangle {
    color: __style.secondaryColor
    radius: 12
    border.color: __style.mainColor
    border.width: 2
  }

  property var properties: ({})

  Column {
    spacing: 16
    width: parent.width
    anchors.centerIn: parent

    Rectangle {
      width: parent.width
      height: 40
      color: __style.secondaryColor
      radius: 8

      Text {
        text: "Feature ID: " + (featureDetailsDialog.properties.id || "N/A")
        font.pixelSize: 18
        color: __style.mainColor
        anchors.centerIn: parent
      }
    }

    Rectangle {
      width: parent.width
      height: 60
      color: __style.secondaryColor
      radius: 8
      border.color: __style.mainColor
      border.width: 1

      Text {
        text: "Description: " + (featureDetailsDialog.properties.description
                                 || "N/A")
        font.pixelSize: 16
        color: __style.mainColor
        anchors {
          left: parent.left
          leftMargin: 16
          verticalCenter: parent.verticalCenter
        }
      }
    }

    Rectangle {
      width: parent.width
      height: 40
      color: __style.secondaryColor
      radius: 8
      border.color: __style.mainColor
      border.width: 1

      Text {
        text: "Date: " + (featureDetailsDialog.properties.date || "N/A")
        font.pixelSize: 16
        color: __style.mainColor
        anchors {
          left: parent.left
          leftMargin: 16
          verticalCenter: parent.verticalCenter
        }
      }
    }

    Rectangle {
      width: parent.width
      height: 40
      color: __style.secondaryColor
      radius: 8
      border.color: __style.mainColor
      border.width: 1

      Text {
        text: "Location: " + (featureDetailsDialog.properties.location || "N/A")
        font.pixelSize: 16
        color: __style.mainColor
        anchors {
          left: parent.left
          leftMargin: 16
          verticalCenter: parent.verticalCenter
        }
      }
    }

    Rectangle {
      width: parent.width
      height: 200
      color: __style.secondaryColor
      radius: 8
      border.color: __style.mainColor
      border.width: 1

      Image {
        visible: featureDetailsDialog.properties.photo !== ""
        source: featureDetailsDialog.properties.photo ? "file://"
                                                        + featureDetailsDialog.properties.photo : ""
        width: parent.width - 32
        height: parent.height - 32
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
      }

      Text {
        visible: !featureDetailsDialog.properties.photo
        text: "No Image Available"
        font.pixelSize: 16
        color: __style.mainColor
        anchors.centerIn: parent
      }
    }

    Button {
      anchors.horizontalCenter: parent.horizontalCenter
      width: 120
      height: 40
      text: "Ok"

      background: Rectangle {
        color: __style.tertiaryColor
        radius: 8
      }

      contentItem: Text {
        text: parent.text
        color: __style.mainColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 16
      }

      onClicked: featureDetailsDialog.close()
    }
  }
}
