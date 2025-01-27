import QtQuick

Rectangle {
  id: root

  property var model: []
  property int selectedIndex: -1

  signal buttonClicked(int index)

  height: 60
  color: __style.secondaryColor

  anchors {
    left: parent.left
    right: parent.right
    bottom: parent.bottom
    bottomMargin: mainAppWindow.safeAreaBottom // Adjust for safe area
  }

  Row {
    anchors.fill: parent
    anchors.margins: 4
    spacing: (width - (model.count * buttonWidth)) / (model.count - 1)

    property int buttonWidth: 80

    Repeater {
      model: root.model

      delegate: ToolbarButton {
        height: parent.height - 8
        width: parent.buttonWidth

        iconSource: modelData.iconSource
        text: modelData.text
        selected: root.selectedIndex === index
        enabled: modelData.enabled !== undefined ? modelData.enabled : true

        onClicked: {
          root.selectedIndex = index
          root.buttonClicked(index)
        }
      }
    }
  }
}
