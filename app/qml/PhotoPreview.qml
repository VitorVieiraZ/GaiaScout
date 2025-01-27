import QtQuick
import QtQuick.Controls

Drawer {
  id: root

  property alias photoUrl: imagePreview.source

  parent: Overlay.overlay
  visible: false
  height: ApplicationWindow.window?.height ?? 0
  width: ApplicationWindow.window?.width ?? 0
  closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

  background: Rectangle {
    color: Qt.alpha(__style.secondaryColor, 0.9)
  }

  contentItem: Item {
    anchors.fill: parent

    BusyIndicator {
      anchors.centerIn: parent
      visible: imagePreview.status === Image.Loading
    }

    MouseArea {
      anchors.fill: parent
      onClicked: function (mouse) {
        mouse.accepted = true
      }
    }

    Item {
      id: photoFrame

      width: Math.min(imagePreview.width, parent.width)
      height: Math.min(imagePreview.height, parent.height)

      y: parent.height / 2 - height / 2
      x: parent.width / 2 - width / 2

      Image {
        id: imagePreview

        height: root.height / 2

        clip: true
        focus: true
        asynchronous: true
        autoTransform: true
        fillMode: Image.PreserveAspectFit

        // Pinch-to-zoom functionality
        PinchArea {
          anchors.fill: parent
          pinch.target: imagePreview
          pinch.minimumRotation: -180
          pinch.maximumRotation: 180
          pinch.minimumScale: 0.5
          pinch.maximumScale: 10
        }
      }
    }

    // Close button at the bottom
    Rectangle {
      id: closeButton

      width: 50
      height: 50
      radius: width / 2
      color: __style.secondaryColor
      anchors {
        horizontalCenter: parent.horizontalCenter
        bottom: parent.bottom
        bottomMargin: __style.safeAreaBottom + __style.spacing20
      }

      Image {
        source: __style.cancelIcon
        width: 24
        height: 24
        anchors.centerIn: parent
      }

      MouseArea {
        anchors.fill: parent
        onClicked: {
          root.close() // Close the popup
        }
      }
    }
  }
}
