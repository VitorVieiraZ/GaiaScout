#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QObject>
#include <QGeoCoordinate>
#include <QJsonObject>

#ifdef Q_OS_ANDROID
class QJniObject;
#endif

class CameraController : public QObject {
    Q_OBJECT

public:
    explicit CameraController(QObject* parent = nullptr);
    ~CameraController();
    Q_INVOKABLE void openNativeCamera();

#ifdef Q_OS_ANDROID
    void handleActivityResult(int requestCode, int resultCode, const QJniObject& data);
#endif

signals:
    void photoSaved(const QString& path, const QJsonObject& metadata);
    void error(const QString& message);
    void photoSelected();

private:
    QJsonObject gatherSensorData() const;
};

#ifdef Q_OS_IOS
void openNativeCameraIOS(CameraController* controller);
#endif

#endif // CAMERACONTROLLER_H
