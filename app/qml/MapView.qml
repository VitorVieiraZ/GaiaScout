import QtQuick
import QtQuick.Window
import QtLocation
import QtPositioning

Item {
  id: root

  Plugin {
    id: mapPlugin
    name: "osm"

    PluginParameter {
      name: "osm.mapping.providersrepository.disabled"
      value: "true"
    }
    PluginParameter {
      name: "osm.mapping.provider"
      value: "thunderforest"
    }
    PluginParameter {
      name: "osm.mapping.custom.host"
      value: "https://tile.thunderforest.com/atlas/{z}/{x}/{y}.png?apikey=1a23c44cb946496697f52b9f29d818d5"
    }

    PluginParameter {
      name: "osm.mapping.providersrepository.disabled"
      value: "true"
    }
    PluginParameter {
      name: "osm.mapping.providersrepository.address"
      value: "http://maps-redirect.qt.io/osm/5.6/"
    }
  }

  ListModel {
    id: featuresModel
  }

  property alias map: map

  FeatureDetailsDialog {
    id: featureDetailsDialog
  }

  Map {
    id: map
    anchors.fill: parent
    plugin: mapPlugin
    center: __mapController.center
    zoomLevel: __mapController.zoomLevel
    property geoCoordinate startCentroid

    PinchHandler {
      id: pinch
      target: null
      onActiveChanged: if (active) {
                         map.startCentroid = map.toCoordinate(
                               pinch.centroid.position, false)
                       }
      onScaleChanged: delta => {
                        map.zoomLevel += Math.log2(delta)
                        map.alignCoordinateToPoint(map.startCentroid,
                                                   pinch.centroid.position)
                      }
      onRotationChanged: delta => {
                           map.bearing -= delta
                           map.alignCoordinateToPoint(map.startCentroid,
                                                      pinch.centroid.position)
                         }
      grabPermissions: PointerHandler.TakeOverForbidden
    }

    WheelHandler {
      acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName
                       === "wayland" ? PointerDevice.Mouse
                                       | PointerDevice.TouchPad : PointerDevice.Mouse
      rotationScale: 1 / 120
      property: "zoomLevel"
    }

    DragHandler {
      target: null
      onTranslationChanged: delta => map.pan(-delta.x, -delta.y)
    }

    MapItemView {
      id: featuresView
      model: featuresModel

      delegate: MapQuickItem {
        coordinate: QtPositioning.coordinate(model.lat, model.lon)
        anchorPoint.x: sourceItem.width / 2
        anchorPoint.y: sourceItem.height

        sourceItem: Image {
          source: __style.pointIcon
          width: 24
          height: 24

          MouseArea {
            anchors.fill: parent
            onClicked: {
              featureDetailsDialog.properties = model.properties
              featureDetailsDialog.open()
            }
          }
        }
      }
    }

    MapQuickItem {
      id: gpsMarker
      coordinate: QtPositioning.coordinate(0, 0)
      anchorPoint.x: sourceItem.width / 2
      anchorPoint.y: sourceItem.height / 2

      sourceItem: Item {
        width: Math.max(image.width, text.width)
        height: image.height + text.height

        Image {
          id: image
          source: __style.gpsDirection
          width: 24
          height: 24
          rotation: __mapController.direction
          anchors.horizontalCenter: parent.horizontalCenter
        }
      }
    }
  }

  Connections {
    target: __projectController
    function onFeaturesChanged() {
      refreshFeatures()
    }

    function onCurrentProjectChanged() {
      refreshFeatures()
    }
  }

  Connections {
    target: __mapController
    function onGpsPositionChanged(position) {
      gpsMarker.coordinate = position
    }
  }

  Connections {
    target: __mapController
    function onDirectionChanged() {
      map.update()
    }
  }

  //Component.onCompleted: refreshFeatures()
  Component.onCompleted: {

    refreshFeatures()
  }

  // Function to refresh features
  function refreshFeatures() {
    featuresModel.clear()
    var features = __projectController.getCurrentProjectFeatures()
    for (var i = 0; i < features.length; i++) {
      var feature = features[i]
      var coords = feature.geometry.coordinates
      featuresModel.append({
                             "lon": coords[0],
                             "lat": coords[1],
                             "properties": feature.properties
                           })
    }
    console.log("Refreshed features. Total features:", featuresModel.count)
  }
}
