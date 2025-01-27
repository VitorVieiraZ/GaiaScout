#include <QDebug>
#include <QGeoPositionInfoSource>
#include <QGuiApplication>
#include <QPermission>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QScreen>
#include <QWindow>

#include "appstyle.h"
#include "cameracontroller.h"
#include "mapcontroller.h"
#include "projectcontroller.h"
#include "shareutils.h"
// #include "androidutils.h"

int main ( int argc, char *argv[] ) {
  QGuiApplication app ( argc, argv );

  // Request location permissions
  QLocationPermission locationPermission;
  locationPermission.setAccuracy ( QLocationPermission::Precise );
  locationPermission.setAvailability ( QLocationPermission::WhenInUse );

  app.requestPermission ( locationPermission, [] ( const QPermission &permission ) {
    if ( permission.status () == Qt::PermissionStatus::Granted ) {
      qDebug () << "Location permission granted";
    } else if ( permission.status () == Qt::PermissionStatus::Denied ) {
      qDebug () << "Location permission denied";
    } else {
      qDebug () << "Location permission undetermined";
    }
  } );

  QQmlApplicationEngine engine;

  AppStyle *style = new AppStyle ( &engine, 1 );
  engine.rootContext ()->setContextProperty ( "__style", style );

  MapController *mapController = new MapController ( &engine );
  engine.rootContext ()->setContextProperty ( "__mapController", mapController );

  CameraController *cameraController = new CameraController ( &engine );
  engine.rootContext ()->setContextProperty ( "__cameraController", cameraController );

  ProjectController *projectController = new ProjectController ( &engine );
  engine.rootContext ()->setContextProperty ( "__projectController", projectController );

  // AndroidUtils *androidUtils = new AndroidUtils(&engine);
  // engine.rootContext()->setContextProperty("__androidUtils", androidUtils);

  // IosUtils *iosUtils = new IosUtils(&engine);
  // engine.rootContext()->setContextProperty("__iosUtils", iosUtils);

  ShareUtils *shareUtils = new ShareUtils ( &engine );
  engine.rootContext ()->setContextProperty ( "__shareUtils", shareUtils );

  qmlRegisterType<CameraController> ( "fieldWork", 1, 0, "CameraController" );

#ifdef MOBILE_OS
  engine.rootContext ()->setContextProperty ( "__appwindowvisibility", QWindow::Maximized );
  engine.rootContext ()->setContextProperty ( "__appwindowwidth", QVariant ( 0 ) );
  engine.rootContext ()->setContextProperty ( "__appwindowheight", QVariant ( 0 ) );
#else
  engine.rootContext ()->setContextProperty ( "__appwindowvisibility", QWindow::Windowed );
  engine.rootContext ()->setContextProperty ( "__appwindowwidth", 640 );
  engine.rootContext ()->setContextProperty ( "__appwindowheight", 1136 );
#endif

  // Set safe area values
  engine.rootContext()->setContextProperty("safeAreaTop", style->safeAreaTop());
  engine.rootContext()->setContextProperty("safeAreaBottom", style->safeAreaBottom());
  engine.rootContext()->setContextProperty("safeAreaLeft", style->safeAreaLeft());
  engine.rootContext()->setContextProperty("safeAreaRight", style->safeAreaRight());

  const QUrl url ( u"qrc:/tcc_vitor_def/app/qml/main.qml"_qs );
  QObject::connect (
      &engine,
      &QQmlApplicationEngine::objectCreated,
      &app,
      [url] ( QObject *obj, const QUrl &objUrl ) {
        if ( !obj && url == objUrl )
          QCoreApplication::exit ( -1 );
      },
      Qt::QueuedConnection );
  engine.load ( url );

  return app.exec ();
}
