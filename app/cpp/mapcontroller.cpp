#include "mapcontroller.h"

#include <QDebug>
#include <QGeoPositionInfo>
#include <QtMath>  // for math functions (optional)

MapController::MapController(QObject* parent)
    : QObject(parent),
    m_center(QGeoCoordinate(-23.5505, -46.6333)),
    m_zoomLevel(14.0),
    m_direction(0.0),
    m_acceleration(0.0),  // Initialize acceleration
    m_positionSource(nullptr),
    m_compass(nullptr),
    m_accelerometer(nullptr) {
    // 1) Initialize the default position source
    m_positionSource = QGeoPositionInfoSource::createDefaultSource(this);
    if (m_positionSource) {
        connect(m_positionSource,
                &QGeoPositionInfoSource::positionUpdated,
                this,
                &MapController::updatePosition);
        m_positionSource->setUpdateInterval(1000);  // e.g. 1 second
        m_positionSource->startUpdates();
    } else {
        qDebug() << "No position source available";
    }

    // 2) Initialize the compass
    m_compass = new QCompass(this);
    m_compass->start();
    if (!m_compass->isActive()) {
        qDebug() << "Compass not available on this platform/device.";
    } else {
        qDebug() << "Compass started successfully.";
        connect(m_compass, &QCompass::readingChanged, this, &MapController::handleCompassReadingChanged);
    }

    // 3) Initialize the accelerometer
    m_accelerometer = new QAccelerometer(this);
    m_accelerometer->start();
    if (!m_accelerometer->isActive()) {
        qDebug() << "Accelerometer not available on this platform/device.";
    } else {
        qDebug() << "Accelerometer started successfully.";
        connect(m_accelerometer, &QAccelerometer::readingChanged, this, &MapController::handleAccelerometerReadingChanged);
    }
}

MapController::~MapController() {
    if (m_accelerometer) {
        m_accelerometer->stop();
        delete m_accelerometer;
    }
}

QGeoCoordinate MapController::center() const {
    return m_center;
}

void MapController::setCenter(const QGeoCoordinate& center) {
    if (m_center != center) {
        m_center = center;
        emit centerChanged(m_center);
    }
}

double MapController::zoomLevel() const {
    return m_zoomLevel;
}

void MapController::setZoomLevel(double zoomLevel) {
    if (!qFuzzyCompare(m_zoomLevel, zoomLevel)) {
        m_zoomLevel = zoomLevel;
        emit zoomLevelChanged(m_zoomLevel);
    }
}

double MapController::direction() const {
    return m_direction;
}

void MapController::setDirection(double direction) {
    // Normalize direction to [0..360) if desired
    while (direction < 0)
        direction += 360.0;
    while (direction >= 360)
        direction -= 360.0;

    if (!qFuzzyCompare(m_direction, direction)) {
        m_direction = direction;
        emit directionChanged(m_direction);
    }
}

double MapController::acceleration() const {
    return m_acceleration;
}

void MapController::resetView() {
    setCenter(QGeoCoordinate(-23.5505, -46.6333));
    setZoomLevel(14.0);
}

void MapController::addPoint() {
    qDebug() << "Adding point at center: " << m_center;
    emit pointAdded(m_center);
}

void MapController::refreshMap() {
    emit centerChanged(m_center);  // Force the map to refresh
}

void MapController::centerOnGpsLocation() {
    if (m_gpsPosition.isValid()) {
        setCenter(m_gpsPosition);
        emit centerChanged(m_center);
    }
}

void MapController::updatePosition(const QGeoPositionInfo& info) {
    if (!info.isValid())
        return;

    // Update our stored GPS position
    m_gpsPosition = info.coordinate();

    // If the position info includes heading/direction, update direction
    if (info.hasAttribute(QGeoPositionInfo::Direction)) {
        double direction = info.attribute(QGeoPositionInfo::Direction);
        qDebug() << "GPS Direction Received:" << direction;
        setDirection(direction);
        emit gpsDirectionChanged(direction);
    } else {
        qDebug() << "No direction attribute in QGeoPositionInfo (GPS heading not provided)";
    }

    // Notify QML that the GPS position changed
    emit gpsPositionChanged(m_gpsPosition);
}

void MapController::handleCompassReadingChanged() {
    if (!m_compass || !m_compass->isActive())
        return;

    QCompassReading* reading = m_compass->reading();
    if (!reading)
        return;

    double azimuth = reading->azimuth();  // 0°=North, 90°=East, etc.
    setDirection(azimuth);
}

void MapController::handleAccelerometerReadingChanged() {
    if (!m_accelerometer || !m_accelerometer->isActive())
        return;

    QAccelerometerReading* reading = m_accelerometer->reading();
    if (!reading)
        return;

    // Calculate the magnitude of the acceleration vector
    double x = reading->x();
    double y = reading->y();
    double z = reading->z();
    m_acceleration = std::sqrt(x * x + y * y + z * z);

    emit accelerationChanged(m_acceleration);
}
