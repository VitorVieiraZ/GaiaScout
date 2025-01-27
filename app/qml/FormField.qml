import QtQuick

Item {
  id: root

  property string label: ""
  property string placeholder: ""
  property string icon: ""
  property string fieldType: "text"
  property var value

  signal iconClicked

  height: column.height

  Column {
    id: column
    width: parent.width
    spacing: 8

    Text {
      text: root.label
      font.pixelSize: 14
      color: __style.mainColor
    }

    Rectangle {
      width: parent.width
      height: 48
      radius: 8
      color: "white"
      border.width: 1
      border.color: "#E0E0E0"

      TextInput {
        id: textInput
        visible: fieldType === "text"
        anchors {
          left: parent.left
          right: parent.right
          verticalCenter: parent.verticalCenter
          margins: 16
        }
        text: root.value || ""
        font.pixelSize: 14
        color: __style.mainColor
        clip: true

        Text {
          text: root.placeholder
          color: "#A0A0A0"
          visible: !parent.text && !parent.activeFocus
          font: parent.font
        }
      }

      Image {
        visible: root.icon !== ""
        source: root.icon
        width: 24
        height: 24
        anchors {
          right: parent.right
          rightMargin: 16
          verticalCenter: parent.verticalCenter
        }

        MouseArea {
          anchors.fill: parent
          onClicked: root.iconClicked()
        }
      }
    }
  }
}
