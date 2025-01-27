#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H

#include <QCompass>  // <- From Qt Sensors module
#include <QAccelerometer>  // Add this header
#include <QGeoCoordinate>
#include <QGeoPositionInfoSource>
#include <QObject>

class MapController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate center READ center WRITE setCenter NOTIFY centerChanged)
    Q_PROPERTY(double zoomLevel READ zoomLevel WRITE setZoomLevel NOTIFY zoomLevelChanged)
    Q_PROPERTY(double direction READ direction WRITE setDirection NOTIFY directionChanged)
    Q_PROPERTY(double acceleration READ acceleration NOTIFY accelerationChanged)  // Add this property

public:
    explicit MapController(QObject* parent = nullptr);
    ~MapController();

    QGeoCoordinate center() const;
    void setCenter(const QGeoCoordinate& center);

    double zoomLevel() const;
    void setZoomLevel(double zoomLevel);

    double direction() const;
    void setDirection(double direction);

    double acceleration() const;  // Add this method

    Q_INVOKABLE void resetView();
    Q_INVOKABLE void addPoint();
    Q_INVOKABLE void refreshMap();
    Q_INVOKABLE void centerOnGpsLocation();

signals:
    void centerChanged(const QGeoCoordinate& center);
    void zoomLevelChanged(double zoomLevel);
    void directionChanged(double direction);
    void accelerationChanged(double acceleration);  // Add this signal

    void pointAdded(const QGeoCoordinate& point);

    // GPS-specific signals
    void gpsPositionChanged(const QGeoCoordinate& position);
    void gpsDirectionChanged(double direction);

private slots:
    void updatePosition(const QGeoPositionInfo& info);
    void handleCompassReadingChanged();
    void handleAccelerometerReadingChanged();  // Add this slot

private:
    QGeoCoordinate m_center;
    double m_zoomLevel;
    double m_direction;
    double m_acceleration;  // Add this member

    QGeoCoordinate m_gpsPosition;
    QGeoPositionInfoSource* m_positionSource;

    // Compass for real-time orientation
    QCompass* m_compass;

    // Accelerometer for acceleration data
    QAccelerometer* m_accelerometer;  // Add this member
};

#endif  // MAPCONTROLLER_H
