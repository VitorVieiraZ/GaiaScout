import QtQuick
import QtQuick.Controls

Rectangle {
  id: root
  visible: false
  color: __style.secondaryColor
  height: parent.height

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
        onClicked: {
          root.visible = false
          stateManager.state = "map"
        }
      }
    }

    Text {
      text: "Projects"
      font.pixelSize: 24
      color: __style.mainColor
      anchors.centerIn: parent
    }
  }

  ListView {
    id: projectsList
    anchors {
      top: header.bottom
      left: parent.left
      right: parent.right
      bottom: parent.bottom
      margins: 16
    }
    spacing: 16
    clip: true

    model: ListModel {
      id: projectsModel
      Component.onCompleted: refreshProjects()
    }

    delegate: ProjectItem {
      width: projectsList.width
      title: model.name || "Unnamed Project"
      lastModified: model.modified || "Unknown"
      description: model.description || "No description"
      projectId: model.id || "unknown"

      onClicked: {
        if (__projectController.openProject(projectId)) {
          root.visible = false
          stateManager.state = "map"
        }
      }

      onDeleteClicked: {
        console.log("Delete clicked for project:", projectId)
        deleteConfirmationDialog.projectIdToDelete = projectId
        deleteConfirmationDialog.open()
      }
    }
  }

  Rectangle {
    id: addButton
    width: 56
    height: 56
    radius: width / 2
    color: __style.secondaryColor
    border.color: __style.mainColor
    border.width: 2

    anchors {
      right: parent.right
      bottom: parent.bottom
      margins: __style.margin24
    }

    Image {
      source: __style.plusIcon
      width: 24
      height: 24
      anchors.centerIn: parent
    }

    MouseArea {
      anchors.fill: parent
      onClicked: newProjectDialog.open()
    }
  }

  CreateProject {
    id: newProjectDialog
  }

  Dialog {
    id: deleteConfirmationDialog
    title: "Delete Project"
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel
    anchors.centerIn: parent
    width: parent.width * 0.8

    background: Rectangle {
      color: __style.secondaryColor
      radius: 10
    }

    property string projectIdToDelete: ""

    Text {
      text: "Are you sure you want to delete this project?"
      font.pixelSize: 16
      color: __style.polarColor
      anchors.centerIn: parent
    }

    onAccepted: {
      if (projectIdToDelete !== "") {
        __projectController.deleteProject(projectIdToDelete)
        refreshProjects()
        projectIdToDelete = ""
      }
    }
  }

  function refreshProjects() {
    projectsModel.clear()
    var projects = __projectController.listProjects()
    for (var i = 0; i < projects.length; i++) {
      projectsModel.append(projects[i])
    }
  }

  Connections {
    target: __projectController
    function onProjectListChanged() {
      refreshProjects()
    }
  }
}
