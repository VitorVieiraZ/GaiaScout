#include "projectcontroller.h"

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

ProjectController::ProjectController ( QObject *parent ) : QObject ( parent ) {
  // Ensure the projects directory exists
  QString projectsDir =
      QStandardPaths::writableLocation ( QStandardPaths::AppDataLocation ) + "/fieldwork/projects";
  QDir dir;
  if ( !dir.mkpath ( projectsDir ) ) {
    qDebug () << "Failed to create projects directory:" << projectsDir;
  } else {
    qDebug () << "Projects directory created or already exists:" << projectsDir;
  }
}

bool ProjectController::createProject ( const QString &name, const QString &description ) {
  qDebug () << "Creating new project with name:" << name << "and description:" << description;

  // Generate a unique project ID
  QString projectId = QDateTime::currentDateTime ().toString ( "yyyyMMdd_hhmmss" );
  qDebug () << "Generated project ID:" << projectId;

  // Create the project JSON object
  QJsonObject project;
  project["type"] = "FeatureCollection";
  project["features"] = QJsonArray ();

  // Add project metadata
  QJsonObject properties;
  properties["name"] = name;
  properties["description"] = description;
  properties["created"] = QDateTime::currentDateTime ().toString ( Qt::ISODate );
  properties["modified"] = QDateTime::currentDateTime ().toString ( Qt::ISODate );
  properties["featuresCount"] = 0;  // Default features count
  properties["id"] = projectId;     // Include the project ID
  project["properties"] = properties;

  // Save project to file
  QString filePath = getProjectPath ( projectId );
  QFile file ( filePath );
  if ( !file.open ( QIODevice::WriteOnly ) ) {
    qDebug () << "Failed to open file for writing:" << filePath;
    qDebug () << "Error:" << file.errorString ();
    return false;
  }

  QJsonDocument doc ( project );
  file.write ( doc.toJson () );
  file.close ();

  qDebug () << "Project saved successfully:" << filePath;

  emit projectListChanged ();
  return openProject ( projectId );
}

bool ProjectController::openProject ( const QString &projectId ) {
  qDebug () << "Attempting to open project with ID:" << projectId;

  closeCurrentProject ();  // Close the previous project

  m_currentProjectData = loadProject ( projectId );
  if ( m_currentProjectData.isEmpty () ) {
    qDebug () << "Failed to load project data for ID:" << projectId;
    return false;
  }

  m_currentProjectId = projectId;
  m_currentProjectName = m_currentProjectData["properties"].toObject ()["name"].toString ();

  qDebug () << "Project opened successfully. Current project ID:" << m_currentProjectId
            << "Name:" << m_currentProjectName;

  emit currentProjectChanged ();
  emit featuresChanged ();
  return true;
}

bool ProjectController::closeCurrentProject () {
  if ( !m_currentProjectId.isEmpty () ) {
    qDebug () << "Closing current project. Project ID:" << m_currentProjectId;

    saveCurrentProject ();
    m_currentProjectId.clear ();
    m_currentProjectName.clear ();
    m_currentProjectData = QJsonObject ();

    qDebug () << "Project closed successfully.";

    emit currentProjectChanged ();
    return true;
  }
  qDebug () << "No project to close.";
  return false;
}

QJsonArray ProjectController::listProjects () {
  qDebug () << "Listing all projects.";

  QJsonArray projects;
  QString projectsDir =
      QStandardPaths::writableLocation ( QStandardPaths::AppDataLocation ) + "/fieldwork/projects";
  QDir dir ( projectsDir );
  QStringList filters;
  filters << "*.geojson";

  for ( const QString &file : dir.entryList ( filters, QDir::Files ) ) {
    QString projectId = file.split ( '.' ).first ();
    QJsonObject project = loadProject ( projectId );
    if ( !project.isEmpty () ) {
      QJsonObject properties = project["properties"].toObject ();
      properties["id"] = projectId;  // Ensure the ID is included
      projects.append ( properties );
      qDebug () << "Found project:" << properties["name"].toString () << "ID:" << projectId;
    }
  }

  qDebug () << "Total projects found:" << projects.size ();
  return projects;
}

bool ProjectController::addFeatureToCurrentProject(const QGeoCoordinate &coord,
                                                   const QJsonObject &properties) {
    if (m_currentProjectId.isEmpty()) {
        qDebug() << "Cannot add feature. No project is currently open.";
        return false;
    }

    qDebug() << "Adding new feature to current project. Coordinates:"
             << "Latitude:" << coord.latitude() << "Longitude:" << coord.longitude();

    QJsonObject feature;
    feature["type"] = "Feature";

    QJsonObject geometry;
    geometry["type"] = "Point";
    QJsonArray coordinates;
    coordinates.append(coord.longitude());
    coordinates.append(coord.latitude());
    geometry["coordinates"] = coordinates;

    feature["geometry"] = geometry;
    feature["properties"] = properties;

    QJsonArray features = m_currentProjectData["features"].toArray();
    features.append(feature);
    m_currentProjectData["features"] = features;

    // Update modified timestamp
    QJsonObject projectProps = m_currentProjectData["properties"].toObject();
    projectProps["modified"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    m_currentProjectData["properties"] = projectProps;

    if (saveCurrentProject()) {
        qDebug() << "Feature added successfully.";
        emit featuresChanged();
        return true;
    }

    qDebug() << "Failed to save feature.";
    return false;
}

QJsonArray ProjectController::getCurrentProjectFeatures () {
  qDebug () << "Retrieving features for current project. Project ID:" << m_currentProjectId;

  QJsonArray features = m_currentProjectData["features"].toArray ();
  qDebug () << "Total features found:" << features.size ();
  return features;
}

QString ProjectController::getProjectPath ( const QString &projectId ) const {
  QString projectsDir =
      QStandardPaths::writableLocation ( QStandardPaths::AppDataLocation ) + "/fieldwork/projects";
  QString filePath = projectsDir + "/" + projectId + ".geojson";
  qDebug () << "Generated project path for ID" << projectId << ":" << filePath;
  return filePath;
}

bool ProjectController::saveCurrentProject () {
  if ( m_currentProjectId.isEmpty () ) {
    qDebug () << "Cannot save project. No project is currently open.";
    return false;
  }

  QFile file ( getProjectPath ( m_currentProjectId ) );
  if ( !file.open ( QIODevice::WriteOnly ) ) {
    qDebug () << "Failed to open file for writing:" << file.fileName ();
    qDebug () << "Error:" << file.errorString ();
    return false;
  }

  QJsonDocument doc ( m_currentProjectData );
  file.write ( doc.toJson () );
  file.close ();

  qDebug () << "Project saved successfully:" << m_currentProjectId;
  return true;
}

QJsonObject ProjectController::loadProject ( const QString &projectId ) {
  QFile file ( getProjectPath ( projectId ) );
  if ( !file.open ( QIODevice::ReadOnly ) ) {
    qDebug () << "Failed to open file for reading:" << file.fileName ();
    qDebug () << "Error:" << file.errorString ();
    return QJsonObject ();
  }

  QJsonDocument doc = QJsonDocument::fromJson ( file.readAll () );
  file.close ();

  if ( doc.isNull () ) {
    qDebug () << "Failed to parse JSON data for project ID:" << projectId;
    return QJsonObject ();
  }

  qDebug () << "Project loaded successfully:" << projectId;
  return doc.object ();
}

bool ProjectController::deleteProject ( const QString &projectId ) {
  QFile file ( getProjectPath ( projectId ) );
  if ( file.remove () ) {
    emit projectListChanged ();
    return true;
  }
  return false;
}

QString ProjectController::exportProject () {
  if ( m_currentProjectId.isEmpty () ) {
    qDebug () << "Cannot export project. No project is currently open.";
    return "";
  }

  // Get the project data as JSON
  QJsonDocument doc ( m_currentProjectData );
  QString jsonString = doc.toJson ( QJsonDocument::Indented );

  // Save the JSON to a temporary file
  QString tempDir = QStandardPaths::writableLocation ( QStandardPaths::TempLocation );
  QString filePath = tempDir + "/" + m_currentProjectId + ".json";

  QFile file ( filePath );
  if ( !file.open ( QIODevice::WriteOnly ) ) {
    qDebug () << "Failed to open file for writing:" << filePath;
    qDebug () << "Error:" << file.errorString ();
    return "";
  }

  file.write ( jsonString.toUtf8 () );
  file.close ();

  qDebug () << "Project exported successfully to:" << filePath;
  return filePath;
}
