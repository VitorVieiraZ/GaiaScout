import QtQuick
import QtQuick.Controls

Rectangle {
  id: root
  visible: false
  color: __style.secondaryColor
  anchors.fill: parent

  signal settingsClosed

  Rectangle {
    id: contentContainer
    anchors.fill: parent

    color: __style.secondaryColor

    Rectangle {
      id: header
      width: parent.width
      height: 60
      color: __style.secondaryColor

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
          onClicked: root.settingsClosed()
        }
      }

      Text {
        text: "Settings"
        font.pixelSize: 18
        color: __style.mainColor
        anchors.centerIn: parent
      }
    }

    Flickable {
      id: scrollView
      anchors {
        top: header.bottom
        left: parent.left
        right: parent.right
        bottom: saveButton.top
        leftMargin: 16
        rightMargin: 16
      }
      contentWidth: width
      contentHeight: settingsColumn.height
      clip: true
      boundsBehavior: Flickable.StopAtBounds

      ScrollBar.vertical: ScrollBar {
        active: scrollView.contentHeight > scrollView.height
        visible: false
      }

      Column {
        id: settingsColumn
        width: parent.width
        spacing: 32

        Rectangle {
          width: parent.width
          height: generalColumn.height + 32
          border.color: __style.mainColor
          border.width: 1
          radius: 8
          color: "transparent"

          Column {
            id: generalColumn
            width: parent.width - 32
            anchors.centerIn: parent
            spacing: 8

            Text {
              text: "General"
              font.pixelSize: 20
              color: __style.mainColor
              font.bold: true
            }
            SettingsItem {
              text: "Project Settings"
              onClicked: console.log("Project Settings clicked")
            }
          }
        }

        Rectangle {
          width: parent.width
          height: captureColumn.height + 32
          border.color: __style.mainColor
          border.width: 1
          radius: 8
          color: "transparent"

          Column {
            id: captureColumn
            width: parent.width - 32
            anchors.centerIn: parent
            spacing: 8

            Text {
              text: "Capture"
              font.pixelSize: 20
              color: __style.mainColor
              font.bold: true
            }
            SettingsItem {
              text: "Camera Configuration"
              onClicked: console.log("Camera Configuration clicked")
            }
          }
        }

        // Let's get back to that later
        // Rectangle {
        //   width: parent.width
        //   height: mapColumn.height + 32
        //   border.color: __style.mainColor
        //   border.width: 1
        //   radius: 8
        //   color: "transparent"

        //   Column {
        //     id: mapColumn
        //     width: parent.width - 32
        //     anchors.centerIn: parent
        //     spacing: 8

        //     Text {
        //       text: "Map"
        //       font.pixelSize: 20
        //       color: __style.mainColor
        //       font.bold: true
        //     }
        //     SettingsItem {
        //       text: "Map Settings"
        //       onClicked: console.log("Map Settings clicked")
        //     }
        //   }
        // }
        Rectangle {
          width: parent.width
          height: localDataColumn.height + 32
          border.color: __style.mainColor
          border.width: 1
          radius: 8
          color: "transparent"

          Column {
            id: localDataColumn
            width: parent.width - 32
            anchors.centerIn: parent
            spacing: 8

            Text {
              text: "Local Data"
              font.pixelSize: 20
              color: __style.mainColor
              font.bold: true
            }
            SettingsItem {
              text: "Export"
              onClicked: {
                var filePath = __projectController.exportProject()
                __shareUtils.shareFile(filePath)
              }
            }
          }
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
        onClicked: root.settingsClosed()
      }
    }
  }
}
