// shareutils.cpp
#include "shareutils.h"
#ifdef Q_OS_ANDROID
#include <QtCore/private/qandroidextras_p.h>
#include <QCoreApplication>
#include <QJniObject>
#include <QJniEnvironment>
#endif
#ifdef Q_OS_IOS
#include "ShareUtils.h"
#endif

ShareUtils::ShareUtils(QObject* parent) : QObject(parent) {}

void ShareUtils::shareFile(const QString& filePath) {
#ifdef Q_OS_ANDROID
    // Call the Java method to share the file
    auto activity = QJniObject(QNativeInterface::QAndroidApplication::context());
    if (activity.isValid()) {
        QJniObject jFilePath = QJniObject::fromString(filePath);
        if (jFilePath.isValid()) {
            activity.callMethod<void>(
                "shareFile",
                "(Ljava/lang/String;)V",
                jFilePath.object<jstring>()
                );
        }
    }
#endif
#ifdef Q_OS_IOS
    // Call the iOS-specific function
    shareFileIOS(filePath);
#endif
}
