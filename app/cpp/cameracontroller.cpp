// cameracontroller.cpp
#include "cameracontroller.h"
#include "mapcontroller.h"
#ifdef Q_OS_ANDROID
#include <QtCore/private/qandroidextras_p.h>
#include <QCoreApplication>
#include <QJniObject>
#include <QJniEnvironment>
#endif

CameraController::CameraController(QObject* parent)
    : QObject(parent) {
}

CameraController::~CameraController() {
}

QJsonObject CameraController::gatherSensorData() const {
    QJsonObject sensorData;
    MapController* mapController = qobject_cast<MapController*>(parent());
    if (mapController) {
        sensorData["latitude"] = mapController->center().latitude();
        sensorData["longitude"] = mapController->center().longitude();
        sensorData["direction"] = mapController->direction();
        sensorData["acceleration"] = mapController->acceleration();
    }
    return sensorData;
}

void CameraController::openNativeCamera() {
#ifdef Q_OS_ANDROID
    // Call the Java method to open the native camera
    auto activity = QJniObject(QNativeInterface::QAndroidApplication::context());
    if (activity.isValid()) {
        QJniObject::callStaticMethod<void>(
            "br/co/gaiascout/CameraController",
            "openNativeCamera",
            "(Landroid/content/Context;)V",
            activity.object<jobject>()
            );
    }
#endif
#ifdef Q_OS_IOS
    // Call the iOS-specific function
    openNativeCameraIOS(this);
#endif
}

#ifdef Q_OS_ANDROID
void CameraController::handleActivityResult(int requestCode, int resultCode, const QJniObject& data) {
    jint RESULT_OK = QJniObject::getStaticField<jint>("android/app/Activity", "RESULT_OK");

    if (requestCode == 1 && resultCode == RESULT_OK) {
        QJsonObject metadata = gatherSensorData();
        QJniObject RESULT_STRING = QJniObject::fromString("__RESULT__");
        QJniObject pathJNI = data.callObjectMethod(
            "getStringExtra",
            "(Ljava/lang/String;)Ljava/lang/String;",
            RESULT_STRING.object<jstring>()
            );

        if (pathJNI.isValid()) {
            QString filePath = pathJNI.toString();
            emit photoSaved(filePath, metadata);
        } else {
            emit error("Failed to get photo path");
        }
    } else {
        emit error("Camera operation canceled or failed.");
    }
}
#endif
