import QtQuick
import QtQuick.Controls

Dialog {
  id: newProjectDialog

  title: "Create New Project"
  modal: true
  anchors.centerIn: parent
  width: parent.width * 0.8

  background: Rectangle {
    color: __style.secondaryColor
    radius: 10

    border {
      width: 2
      color: __style.mainColor
    }
  }

  header: Label {
    text: newProjectDialog.title
    color: __style.mainColor
    font.bold: true
    padding: 10
  }

  contentItem: Column {
    spacing: 10
    width: parent.width

    TextField {
      id: projectName
      placeholderText: "Project Name"
      width: parent.width
      color: __style.mainColor
      placeholderTextColor: __style.mainColor

      background: Rectangle {
        color: __style.polarColor
        radius: 5
        border {
          width: 1
          color: __style.mainColor
        }
      }
    }

    TextField {
      id: projectDescription
      placeholderText: "Description"
      width: parent.width
      color: __style.mainColor
      placeholderTextColor: __style.mainColor

      background: Rectangle {
        color: __style.polarColor
        radius: 5
        border {
          width: 1
          color: __style.mainColor
        }
      }
    }

    Row {
      spacing: 10
      anchors.horizontalCenter: parent.horizontalCenter

      // OK Button
      Button {
        text: "OK"
        contentItem: Text {
          text: parent.text
          color: __style.mainColor
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
          color: __style.secondaryColor
          radius: 5
          border {
            width: 1
            color: __style.mainColor
          }
        }

        onClicked: {
          if (projectName.text.length > 0) {
            __projectController.createProject(projectName.text,
                                              projectDescription.text)
            refreshProjects()
            newProjectDialog.close()
          }
        }
      }

      Button {
        text: "Cancel"
        contentItem: Text {
          text: parent.text
          color: __style.mainColor
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
          color: __style.secondaryColor
          radius: 5
          border {
            width: 1
            color: __style.mainColor
          }
        }

        onClicked: {
          newProjectDialog.close()
        }
      }
    }
  }
}
