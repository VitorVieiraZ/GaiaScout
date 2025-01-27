#ifndef PROJECTCONTROLLER_H
#define PROJECTCONTROLLER_H

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QGeoCoordinate>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QStandardPaths>

class ProjectController : public QObject {
  Q_OBJECT
  Q_PROPERTY ( QString currentProjectId READ currentProjectId NOTIFY currentProjectChanged )
  Q_PROPERTY ( QString currentProjectName READ currentProjectName NOTIFY currentProjectChanged )

public:
  explicit ProjectController ( QObject *parent = nullptr );

  QString currentProjectId () const {
    return m_currentProjectId;
  }
  QString currentProjectName () const {
    return m_currentProjectName;
  }

  Q_INVOKABLE bool createProject ( const QString &name, const QString &description );
  Q_INVOKABLE bool openProject ( const QString &projectId );
  Q_INVOKABLE bool closeCurrentProject ();
  Q_INVOKABLE QJsonArray listProjects ();
  Q_INVOKABLE bool addFeatureToCurrentProject ( const QGeoCoordinate &coord,
                                                const QJsonObject &properties );
  Q_INVOKABLE QJsonArray getCurrentProjectFeatures ();
  Q_INVOKABLE bool deleteProject ( const QString &projectId );
  Q_INVOKABLE QString exportProject ();

signals:
  void currentProjectChanged ();
  void projectListChanged ();
  void featuresChanged ();

private:
  QString m_currentProjectId;
  QString m_currentProjectName;
  QString getProjectPath ( const QString &projectId ) const;
  bool saveCurrentProject ();
  QJsonObject loadProject ( const QString &projectId );
  QJsonObject m_currentProjectData;
};

#endif  // PROJECTCONTROLLER_H
