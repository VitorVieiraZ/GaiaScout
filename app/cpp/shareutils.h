#ifndef SHAREUTILS_H
#define SHAREUTILS_H

#include <QObject>
#include <QString>

class ShareUtils : public QObject {
  Q_OBJECT
public:
  explicit ShareUtils ( QObject *parent = nullptr );
  Q_INVOKABLE void shareFile ( const QString &filePath );
};

// Declare the iOS-specific function
#ifdef Q_OS_IOS
void shareFileIOS ( const QString &filePath );
#endif

#endif
