/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef APPSTYLE_H
#define APPSTYLE_H

#include <QColor>
#include <QFont>
#include <QObject>
#include <QUrl>
#include <QScreen>
#include <QGuiApplication>

class AppStyle : public QObject {
  Q_OBJECT

  // Fonts
  Q_PROPERTY ( QFont h1 READ h1 CONSTANT )
  Q_PROPERTY ( QFont h2 READ h2 CONSTANT )
  Q_PROPERTY ( QFont h3 READ h3 CONSTANT )
  Q_PROPERTY ( QFont t1 READ t1 CONSTANT )
  Q_PROPERTY ( QFont t2 READ t2 CONSTANT )
  Q_PROPERTY ( QFont t3 READ t3 CONSTANT )
  Q_PROPERTY ( QFont t4 READ t4 CONSTANT )
  Q_PROPERTY ( QFont t5 READ t5 CONSTANT )
  Q_PROPERTY ( QFont p1 READ p1 CONSTANT )
  Q_PROPERTY ( QFont p2 READ p2 CONSTANT )
  Q_PROPERTY ( QFont p3 READ p3 CONSTANT )
  Q_PROPERTY ( QFont p4 READ p4 CONSTANT )
  Q_PROPERTY ( QFont p5 READ p5 CONSTANT )
  Q_PROPERTY ( QFont p6 READ p6 CONSTANT )
  Q_PROPERTY ( QFont p7 READ p7 CONSTANT )
  Q_PROPERTY ( double fontLineHeight60 READ number60 CONSTANT )
  Q_PROPERTY ( double fontLineHeight48 READ number48 CONSTANT )
  Q_PROPERTY ( double fontLineHeight44 READ number44 CONSTANT )
  Q_PROPERTY ( double fontLineHeight36 READ number36 CONSTANT )
  Q_PROPERTY ( double fontLineHeight32 READ number32 CONSTANT )
  Q_PROPERTY ( double fontLineHeight30 READ number30 CONSTANT )
  Q_PROPERTY ( double fontLineHeight28 READ number28 CONSTANT )
  Q_PROPERTY ( double fontLineHeight26 READ number26 CONSTANT )
  Q_PROPERTY ( double fontLineHeight24 READ number24 CONSTANT )
  Q_PROPERTY ( double fontLineHeight22 READ number22 CONSTANT )

  // Colors - primary palette
  Q_PROPERTY ( QColor mainColor READ mainColor CONSTANT )
  Q_PROPERTY ( QColor secondaryColor READ secondaryColor CONSTANT )
  Q_PROPERTY ( QColor tertiaryColor READ tertiaryColor CONSTANT )
  Q_PROPERTY ( QColor nightColor READ nightColor CONSTANT )
  Q_PROPERTY ( QColor polarColor READ polarColor CONSTANT )
  Q_PROPERTY ( QColor transparentColor READ transparentColor CONSTANT )

  // Colors - secondary palette
  Q_PROPERTY ( QColor lightGreenColor READ lightGreenColor CONSTANT )
  Q_PROPERTY ( QColor mediumGreenColor READ mediumGreenColor CONSTANT )
  Q_PROPERTY ( QColor darkGreenColor READ darkGreenColor CONSTANT )
  Q_PROPERTY ( QColor greyColor READ greyColor CONSTANT )
  Q_PROPERTY ( QColor darkGreyColor READ darkGreyColor CONSTANT )
  Q_PROPERTY ( QColor mediumGreyColor READ mediumGreyColor CONSTANT )

  // Colors - additional colors
  Q_PROPERTY ( QColor sandColor READ sandColor CONSTANT )
  Q_PROPERTY ( QColor sunsetColor READ sunsetColor CONSTANT )
  Q_PROPERTY ( QColor sunColor READ sunColor CONSTANT )
  Q_PROPERTY ( QColor earthColor READ earthColor CONSTANT )
  Q_PROPERTY ( QColor roseColor READ roseColor CONSTANT )
  Q_PROPERTY ( QColor skyColor READ skyColor CONSTANT )
  Q_PROPERTY ( QColor grapeColor READ grapeColor CONSTANT )
  Q_PROPERTY ( QColor grapeTransparentColor READ grapeTransparentColor CONSTANT )
  Q_PROPERTY ( QColor deepOceanColor READ deepOceanColor CONSTANT )
  Q_PROPERTY ( QColor purpleColor READ purpleColor CONSTANT )
  Q_PROPERTY ( QColor fieldColor READ fieldColor CONSTANT )

  // Colors - sentiment colors
  Q_PROPERTY ( QColor positiveColor READ positiveColor CONSTANT )
  Q_PROPERTY ( QColor warningColor READ warningColor CONSTANT )
  Q_PROPERTY ( QColor negativeColor READ negativeColor CONSTANT )
  Q_PROPERTY ( QColor negativeLightColor READ negativeLightColor CONSTANT )
  Q_PROPERTY ( QColor negativeUltraLightColor READ negativeUltraLightColor CONSTANT )
  Q_PROPERTY ( QColor informativeColor READ informativeColor CONSTANT )

  // Colors - others
  Q_PROPERTY ( QColor shadowColor READ shadowColor CONSTANT )
  Q_PROPERTY ( QColor snappingColor READ snappingColor CONSTANT )

  // Icons
  Q_PROPERTY ( QUrl addIcon READ addIcon CONSTANT )
  Q_PROPERTY ( QUrl backIcon READ backIcon CONSTANT )
  Q_PROPERTY ( QUrl cameraIcon READ cameraIcon CONSTANT )
  Q_PROPERTY ( QUrl calendarIcon READ calendarIcon CONSTANT )
  Q_PROPERTY ( QUrl lightCameraIcon READ lightCameraIcon CONSTANT )
  Q_PROPERTY ( QUrl locationIcon READ locationIcon CONSTANT )
  Q_PROPERTY ( QUrl nextIcon READ nextIcon CONSTANT )
  Q_PROPERTY ( QUrl plusIcon READ plusIcon CONSTANT )
  Q_PROPERTY ( QUrl pointIcon READ pointIcon CONSTANT )
  Q_PROPERTY ( QUrl projectsFolderIcon READ projectsFolderIcon CONSTANT )
  Q_PROPERTY ( QUrl searchIcon READ searchIcon CONSTANT )
  Q_PROPERTY ( QUrl settingsIcon READ settingsIcon CONSTANT )
  Q_PROPERTY ( QUrl cancelIcon READ cancelIcon CONSTANT )
  Q_PROPERTY ( QUrl deleteIcon READ deleteIcon CONSTANT )
  Q_PROPERTY ( QUrl gpsIcon READ gpsIcon CONSTANT )
  Q_PROPERTY ( QUrl gpsDirection READ gpsDirection CONSTANT )

  // Imagess
  // Q_PROPERTY( QUrl loadingIndicatorImage READ loadingIndicatorImage CONSTANT )
  Q_PROPERTY ( QUrl crossImage READ crossImage CONSTANT )

  /*
   * Pixel sizes used across the app
   */

  // Icon sizes
  Q_PROPERTY ( double icon16 READ number16 CONSTANT )
  Q_PROPERTY ( double icon24 READ number24 CONSTANT )
  Q_PROPERTY ( double icon32 READ number32 CONSTANT )

  // Map items
  Q_PROPERTY ( double mapItemHeight READ number50 CONSTANT )
  Q_PROPERTY ( double mapButtonsMargin READ number20 CONSTANT )

  // Toolbar
  Q_PROPERTY ( double toolbarHeight READ toolbarHeight NOTIFY safeAreaBottomChanged )
  Q_PROPERTY ( double menuDrawerHeight READ number67 CONSTANT )

  // Safe area sizes - to not draw content over notch and system bars (used on mobile devices)
  Q_PROPERTY ( double safeAreaTop READ safeAreaTop WRITE setSafeAreaTop NOTIFY safeAreaTopChanged )
  Q_PROPERTY (
      double safeAreaRight READ safeAreaRight WRITE setSafeAreaRight NOTIFY safeAreaRightChanged )
  Q_PROPERTY ( double safeAreaBottom READ safeAreaBottom WRITE setSafeAreaBottom NOTIFY
                   safeAreaBottomChanged )
  Q_PROPERTY (
      double safeAreaLeft READ safeAreaLeft WRITE setSafeAreaLeft NOTIFY safeAreaLeftChanged )

  // Margins
  Q_PROPERTY ( double margin1 READ number1 CONSTANT )
  Q_PROPERTY ( double margin2 READ number2 CONSTANT )
  Q_PROPERTY ( double margin4 READ number4 CONSTANT )
  Q_PROPERTY ( double margin6 READ number6 CONSTANT )
  Q_PROPERTY ( double margin8 READ number8 CONSTANT )
  Q_PROPERTY ( double margin10 READ number10 CONSTANT )
  Q_PROPERTY ( double margin11 READ number11 CONSTANT )
  Q_PROPERTY ( double margin12 READ number12 CONSTANT )
  Q_PROPERTY ( double margin13 READ number13 CONSTANT )
  Q_PROPERTY ( double margin14 READ number14 CONSTANT )
  Q_PROPERTY ( double margin16 READ number16 CONSTANT )
  Q_PROPERTY ( double margin20 READ number20 CONSTANT )
  Q_PROPERTY ( double margin24 READ number24 CONSTANT )
  Q_PROPERTY ( double margin28 READ number28 CONSTANT )
  Q_PROPERTY ( double margin30 READ number30 CONSTANT )
  Q_PROPERTY ( double margin32 READ number32 CONSTANT )
  Q_PROPERTY ( double margin36 READ number36 CONSTANT )
  Q_PROPERTY ( double margin40 READ number40 CONSTANT )
  Q_PROPERTY ( double margin48 READ number48 CONSTANT )
  Q_PROPERTY ( double margin54 READ number54 CONSTANT )

  // Page
  Q_PROPERTY (
      double pageMargins READ number20 CONSTANT )  // distance between screen edge and components
  Q_PROPERTY ( double spacing2 READ number2 CONSTANT )
  Q_PROPERTY ( double spacing5 READ number5 CONSTANT )
  Q_PROPERTY ( double spacing10 READ number10 CONSTANT )
  Q_PROPERTY ( double spacing12 READ number12
                   CONSTANT )  // distance between page header, page content and page footer
  Q_PROPERTY ( double spacing20 READ number20 CONSTANT )
  Q_PROPERTY ( double spacing30 READ number30 CONSTANT )
  Q_PROPERTY ( double spacing40 READ number40 CONSTANT )
  Q_PROPERTY ( double maxPageWidth READ number720
                   CONSTANT )  // maximum page width (desktop, tablets, landscape)

  // Other
  Q_PROPERTY ( double row1 READ number1 CONSTANT )
  Q_PROPERTY ( double row4 READ number4 CONSTANT )
  Q_PROPERTY ( double row24 READ number24 CONSTANT )
  Q_PROPERTY ( double row36 READ number36 CONSTANT )
  Q_PROPERTY ( double row40 READ number40 CONSTANT )
  Q_PROPERTY ( double row45 READ number45 CONSTANT )
  Q_PROPERTY ( double row49 READ number49 CONSTANT )
  Q_PROPERTY ( double row50 READ number50 CONSTANT )
  Q_PROPERTY ( double row54 READ number54 CONSTANT )
  Q_PROPERTY ( double row60 READ number60 CONSTANT )
  Q_PROPERTY ( double row63 READ number63 CONSTANT )
  Q_PROPERTY ( double row67 READ number67 CONSTANT )
  Q_PROPERTY ( double row80 READ number80 CONSTANT )
  Q_PROPERTY ( double row114 READ number114 CONSTANT )
  Q_PROPERTY ( double row120 READ number120 CONSTANT )
  Q_PROPERTY ( double row160 READ number160 CONSTANT )
  Q_PROPERTY ( double radius2 READ number2 CONSTANT )
  Q_PROPERTY ( double radius6 READ number6 CONSTANT )
  Q_PROPERTY ( double radius8 READ number8 CONSTANT )
  Q_PROPERTY ( double radius12 READ number12 CONSTANT )
  Q_PROPERTY ( double radius16 READ number16 CONSTANT )
  Q_PROPERTY ( double radius20 READ number20 CONSTANT )
  Q_PROPERTY ( double radius30 READ number30 CONSTANT )
  Q_PROPERTY ( double radius40 READ number40 CONSTANT )
  Q_PROPERTY ( double width1 READ number1 CONSTANT )
  Q_PROPERTY ( double width2 READ number2 CONSTANT )
  Q_PROPERTY ( double scrollVelocityAndroid READ scrollVelocityAndroid
                   CONSTANT )  // [px/s] scrolling on Android devices is too slow by default

  // Breakpoint we use in some screens to differentiate mobile landscape
  Q_PROPERTY ( double heightBreakpointXS READ number400 CONSTANT )

public:
  explicit AppStyle(QObject* parent, qreal dp) : QObject(parent) {
      // Connect to screen orientation changes
      QScreen* primaryScreen = QGuiApplication::primaryScreen();
      if (primaryScreen) {
          connect(primaryScreen, &QScreen::orientationChanged, this, &AppStyle::updateSafeAreas);
      }

      updateSafeAreas();
  }

  ~AppStyle () = default;

  void updateSafeAreas() {
      qDebug() << "Starting updateSafeAreas method";

      QScreen* screen = QGuiApplication::primaryScreen();
      qDebug() << "Primary screen pointer:" << screen;

      if (!screen) {
          qDebug() << "Screen is null, returning early";
          return;
      }

#ifdef MOBILE_OS
        qDebug() << "Mobile OS detected";

        Qt::ScreenOrientation orientation = screen->orientation();
        qDebug() << "Screen orientation:" << orientation;

        bool isPortrait = (orientation == Qt::PortraitOrientation ||
                           orientation == Qt::InvertedPortraitOrientation);
        qDebug() << "Is portrait orientation:" << isPortrait;

        if (isPortrait) {
            qDebug() << "Setting portrait safe areas";
            setSafeAreaTop(30);
            qDebug() << "Set safe area top to 30";
            setSafeAreaBottom(15);
            qDebug() << "Set safe area bottom to 30";
            setSafeAreaLeft(0);
            qDebug() << "Set safe area left to 0";
            setSafeAreaRight(0);
            qDebug() << "Set safe area right to 0";
        } else {
            qDebug() << "Setting landscape safe areas";
            setSafeAreaTop(0);
            qDebug() << "Set safe area top to 0";
            setSafeAreaBottom(0);
            qDebug() << "Set safe area bottom to 0";
            setSafeAreaLeft(25);
            qDebug() << "Set safe area left to 15";
            setSafeAreaRight(25);
            qDebug() << "Set safe area right to 15";
        }
#else
        qDebug() << "Desktop OS detected";
        // Desktop: all safe areas are 0
        setSafeAreaTop(0);
        qDebug() << "Set safe area top to 0";
        setSafeAreaRight(0);
        qDebug() << "Set safe area right to 0";
        setSafeAreaBottom(0);
        qDebug() << "Set safe area bottom to 0";
        setSafeAreaLeft(0);
        qDebug() << "Set safe area left to 0";
#endif
        qDebug() << "Finished updateSafeAreas method";
    }

  QFont h1 () {
    return fontFactory ( 48, true );
  }
  QFont h2 () {
    return fontFactory ( 36, true );
  }
  QFont h3 () {
    return fontFactory ( 24, true );
  }

  QFont t1 () {
    return fontFactory ( 18, true );
  }
  QFont t2 () {
    return fontFactory ( 16, true );
  }
  QFont t3 () {
    return fontFactory ( 14, true );
  }
  QFont t4 () {
    return fontFactory ( 12, true );
  }
  QFont t5 () {
    return fontFactory ( 10, true );
  }

  QFont p1 () {
    return fontFactory ( 32, false );
  }
  QFont p2 () {
    return fontFactory ( 24, false );
  }
  QFont p3 () {
    return fontFactory ( 20, false );
  }
  QFont p4 () {
    return fontFactory ( 16, false );
  }
  QFont p5 () {
    return fontFactory ( 14, false );
  }
  QFont p6 () {
    return fontFactory ( 12, false );
  }
  QFont p7 () {
    return fontFactory ( 10, false );
  }

  QColor mainColor () {
    return QColor::fromString ( "#583827" );
  }
  QColor secondaryColor () {
    return QColor::fromString ( "#CE9A5F" );
  }
  QColor tertiaryColor () {
    return QColor::fromString ( "#F5D4A3" );
  }
  QColor nightColor () {
    return QColor::fromString ( "#12181F" );
  }
  QColor polarColor () {
    return QColor::fromString ( "#FFFFFF" );
  }
  QColor transparentColor () {
    return QColor::fromString ( "transparent" );
  }

  QColor lightGreenColor () {
    return QColor::fromString ( "#EFF5F3" );
  }
  QColor mediumGreenColor () {
    return QColor::fromString ( "#B7CDC4" );
  }
  QColor darkGreenColor () {
    return QColor::fromString ( "#6E9991" );
  }
  QColor greyColor () {
    return QColor::fromString ( "#E2E2E2" );
  }
  QColor darkGreyColor () {
    return QColor::fromString ( "#41464C" );
  }
  QColor mediumGreyColor () {
    return QColor::fromString ( "#A0A3A5" );
  }

  QColor sandColor () {
    return QColor::fromString ( "#FFF4E2" );
  }
  QColor sunsetColor () {
    return QColor::fromString ( "#FFB673" );
  }
  QColor sunColor () {
    return QColor::fromString ( "#F4CB46" );
  }
  QColor earthColor () {
    return QColor::fromString ( "#4D2A24" );
  }
  QColor roseColor () {
    return QColor::fromString ( "#FFBABC" );
  }
  QColor skyColor () {
    return QColor::fromString ( "#A6CBF4" );
  }
  QColor grapeColor () {
    return QColor::fromString ( "#5A2740" );
  }
  QColor grapeTransparentColor () {
    return QColor ( 0x5A, 0x27, 0x40, 102 );
  }
  QColor deepOceanColor () {
    return QColor::fromString ( "#1C324A" );
  }
  QColor purpleColor () {
    return QColor::fromString ( "#CCBDF5" );
  }
  QColor fieldColor () {
    return QColor::fromString ( "#9BD1A9" );
  }

  QColor positiveColor () {
    return QColor::fromString ( "#C0EBCF" );
  }
  QColor warningColor () {
    return QColor::fromString ( "#F7DDAF" );
  }
  QColor negativeColor () {
    return QColor::fromString ( "#F0C4BC" );
  }
  QColor negativeLightColor () {
    return QColor::fromString ( "#FFF0ED" );
  }
  QColor negativeUltraLightColor () {
    return QColor::fromString ( "#FEFAF9" );
  }
  QColor informativeColor () {
    return QColor::fromString ( "#BEDAF0" );
  }
  QColor snappingColor () {
    return QColor::fromString ( "#BD74FF" );
  }

  QColor shadowColor () {
    return QColor::fromString ( "#66777777" );
  }

  // ICONS
  QUrl addIcon () const {
    return QUrl ( "qrc:/Add.svg" );
  }
  QUrl backIcon () const {
    return QUrl ( "qrc:/Back.svg" );
  }
  QUrl cameraIcon () const {
    return QUrl ( "qrc:/Camera.svg" );
  }
  QUrl calendarIcon () const {
    return QUrl ( "qrc:/IconCalendar.svg" );
  }
  QUrl lightCameraIcon () const {
    return QUrl ( "qrc:/IconLightCamera.svg" );
  }
  QUrl locationIcon () const {
    return QUrl ( "qrc:/IconLocation.svg" );
  }
  QUrl nextIcon () const {
    return QUrl ( "qrc:/Next.svg" );
  }
  QUrl plusIcon () const {
    return QUrl ( "qrc:/Plus.svg" );
  }
  QUrl pointIcon () const {
    return QUrl ( "qrc:/Point.svg" );
  }
  QUrl projectsFolderIcon () const {
    return QUrl ( "qrc:/ProjectsFolder.svg" );
  }
  QUrl searchIcon () const {
    return QUrl ( "qrc:/Search.svg" );
  }
  QUrl settingsIcon () const {
    return QUrl ( "qrc:/Settings.svg" );
  }
  QUrl cancelIcon () const {
    return QUrl ( "qrc:/Cancel.svg" );
  }

  // IMAGES
  QUrl crossImage () const {
    return QUrl ( "qrc:/images/Cross.svg" );
  }

  QUrl deleteIcon () const {
    return QUrl ( "qrc:/Delete.svg" );  // Path to your delete icon
  }

  QUrl gpsIcon () const {
    return QUrl ( "qrc:/Gps.svg" );  // Path to your delete icon
  }

  QUrl gpsDirection () const {
    return QUrl ( "qrc:/GpsDirection.svg" );  // Path to your delete icon
  }

  double toolbarHeight () {
    if ( mSafeAreaBottom > 2 ) {
      return 54 * mDp;
    } else {
      return 58 * mDp;
    }
  }

  double safeAreaTop () const {
    return mSafeAreaTop;
  };
  double safeAreaRight () const {
    return mSafeAreaRight;
  };
  double safeAreaBottom () const {
    return mSafeAreaBottom;
  };
  double safeAreaLeft () const {
    return mSafeAreaLeft;
  };

  // Numbers from 1 to 150 and number 720
  double number1 () {
    return qMax<double> ( 1 * mDp, 1 );
  }  // make sure these sizes are visible if mDP < 1
  double number2 () {
    return qMax<double> ( 2 * mDp, 1 );
  }  // make sure these sizes are visible if mDP < 1
  double number3 () {
    return 3 * mDp;
  }
  double number4 () {
    return 4 * mDp;
  }
  double number5 () {
    return 5 * mDp;
  }
  double number6 () {
    return 6 * mDp;
  }
  double number7 () {
    return 7 * mDp;
  }
  double number8 () {
    return 8 * mDp;
  }
  double number9 () {
    return 9 * mDp;
  }
  double number10 () {
    return 10 * mDp;
  }
  double number11 () {
    return 11 * mDp;
  }
  double number12 () {
    return 12 * mDp;
  }
  double number13 () {
    return 13 * mDp;
  }
  double number14 () {
    return 14 * mDp;
  }
  double number15 () {
    return 15 * mDp;
  }
  double number16 () {
    return 16 * mDp;
  }
  double number17 () {
    return 17 * mDp;
  }
  double number18 () {
    return 18 * mDp;
  }
  double number19 () {
    return 19 * mDp;
  }
  double number20 () {
    return 20 * mDp;
  }
  double number21 () {
    return 21 * mDp;
  }
  double number22 () {
    return 22 * mDp;
  }
  double number23 () {
    return 23 * mDp;
  }
  double number24 () {
    return 24 * mDp;
  }
  double number25 () {
    return 25 * mDp;
  }
  double number26 () {
    return 26 * mDp;
  }
  double number27 () {
    return 27 * mDp;
  }
  double number28 () {
    return 28 * mDp;
  }
  double number29 () {
    return 29 * mDp;
  }
  double number30 () {
    return 30 * mDp;
  }
  double number31 () {
    return 31 * mDp;
  }
  double number32 () {
    return 32 * mDp;
  }
  double number33 () {
    return 33 * mDp;
  }
  double number34 () {
    return 34 * mDp;
  }
  double number35 () {
    return 35 * mDp;
  }
  double number36 () {
    return 36 * mDp;
  }
  double number37 () {
    return 37 * mDp;
  }
  double number38 () {
    return 38 * mDp;
  }
  double number39 () {
    return 39 * mDp;
  }
  double number40 () {
    return 40 * mDp;
  }
  double number41 () {
    return 41 * mDp;
  }
  double number42 () {
    return 42 * mDp;
  }
  double number43 () {
    return 43 * mDp;
  }
  double number44 () {
    return 44 * mDp;
  }
  double number45 () {
    return 45 * mDp;
  }
  double number46 () {
    return 46 * mDp;
  }
  double number47 () {
    return 47 * mDp;
  }
  double number48 () {
    return 48 * mDp;
  }
  double number49 () {
    return 49 * mDp;
  }
  double number50 () {
    return 50 * mDp;
  }
  double number51 () {
    return 51 * mDp;
  }
  double number52 () {
    return 52 * mDp;
  }
  double number53 () {
    return 53 * mDp;
  }
  double number54 () {
    return 54 * mDp;
  }
  double number55 () {
    return 55 * mDp;
  }
  double number56 () {
    return 56 * mDp;
  }
  double number57 () {
    return 57 * mDp;
  }
  double number58 () {
    return 58 * mDp;
  }
  double number59 () {
    return 59 * mDp;
  }
  double number60 () {
    return 60 * mDp;
  }
  double number61 () {
    return 61 * mDp;
  }
  double number62 () {
    return 62 * mDp;
  }
  double number63 () {
    return 63 * mDp;
  }
  double number64 () {
    return 64 * mDp;
  }
  double number65 () {
    return 65 * mDp;
  }
  double number66 () {
    return 66 * mDp;
  }
  double number67 () {
    return 67 * mDp;
  }
  double number68 () {
    return 68 * mDp;
  }
  double number69 () {
    return 69 * mDp;
  }
  double number70 () {
    return 70 * mDp;
  }
  double number71 () {
    return 71 * mDp;
  }
  double number72 () {
    return 72 * mDp;
  }
  double number73 () {
    return 73 * mDp;
  }
  double number74 () {
    return 74 * mDp;
  }
  double number75 () {
    return 75 * mDp;
  }
  double number76 () {
    return 76 * mDp;
  }
  double number77 () {
    return 77 * mDp;
  }
  double number78 () {
    return 78 * mDp;
  }
  double number79 () {
    return 79 * mDp;
  }
  double number80 () {
    return 80 * mDp;
  }
  double number81 () {
    return 81 * mDp;
  }
  double number82 () {
    return 82 * mDp;
  }
  double number83 () {
    return 83 * mDp;
  }
  double number84 () {
    return 84 * mDp;
  }
  double number85 () {
    return 85 * mDp;
  }
  double number86 () {
    return 86 * mDp;
  }
  double number87 () {
    return 87 * mDp;
  }
  double number88 () {
    return 88 * mDp;
  }
  double number89 () {
    return 89 * mDp;
  }
  double number90 () {
    return 90 * mDp;
  }
  double number91 () {
    return 91 * mDp;
  }
  double number92 () {
    return 92 * mDp;
  }
  double number93 () {
    return 93 * mDp;
  }
  double number94 () {
    return 94 * mDp;
  }
  double number95 () {
    return 95 * mDp;
  }
  double number96 () {
    return 96 * mDp;
  }
  double number97 () {
    return 97 * mDp;
  }
  double number98 () {
    return 98 * mDp;
  }
  double number99 () {
    return 99 * mDp;
  }
  double number100 () {
    return 100 * mDp;
  }
  double number101 () {
    return 101 * mDp;
  }
  double number102 () {
    return 102 * mDp;
  }
  double number103 () {
    return 103 * mDp;
  }
  double number104 () {
    return 104 * mDp;
  }
  double number105 () {
    return 105 * mDp;
  }
  double number106 () {
    return 106 * mDp;
  }
  double number107 () {
    return 107 * mDp;
  }
  double number108 () {
    return 108 * mDp;
  }
  double number109 () {
    return 109 * mDp;
  }
  double number110 () {
    return 110 * mDp;
  }
  double number111 () {
    return 111 * mDp;
  }
  double number112 () {
    return 112 * mDp;
  }
  double number113 () {
    return 113 * mDp;
  }
  double number114 () {
    return 114 * mDp;
  }
  double number115 () {
    return 115 * mDp;
  }
  double number116 () {
    return 116 * mDp;
  }
  double number117 () {
    return 117 * mDp;
  }
  double number118 () {
    return 118 * mDp;
  }
  double number119 () {
    return 119 * mDp;
  }
  double number120 () {
    return 120 * mDp;
  }
  double number121 () {
    return 121 * mDp;
  }
  double number122 () {
    return 122 * mDp;
  }
  double number123 () {
    return 123 * mDp;
  }
  double number124 () {
    return 124 * mDp;
  }
  double number125 () {
    return 125 * mDp;
  }
  double number126 () {
    return 126 * mDp;
  }
  double number127 () {
    return 127 * mDp;
  }
  double number128 () {
    return 128 * mDp;
  }
  double number129 () {
    return 129 * mDp;
  }
  double number130 () {
    return 130 * mDp;
  }
  double number131 () {
    return 131 * mDp;
  }
  double number132 () {
    return 132 * mDp;
  }
  double number133 () {
    return 133 * mDp;
  }
  double number134 () {
    return 134 * mDp;
  }
  double number135 () {
    return 135 * mDp;
  }
  double number136 () {
    return 136 * mDp;
  }
  double number137 () {
    return 137 * mDp;
  }
  double number138 () {
    return 138 * mDp;
  }
  double number139 () {
    return 139 * mDp;
  }
  double number140 () {
    return 140 * mDp;
  }
  double number141 () {
    return 141 * mDp;
  }
  double number142 () {
    return 142 * mDp;
  }
  double number143 () {
    return 143 * mDp;
  }
  double number144 () {
    return 144 * mDp;
  }
  double number145 () {
    return 145 * mDp;
  }
  double number146 () {
    return 146 * mDp;
  }
  double number147 () {
    return 147 * mDp;
  }
  double number148 () {
    return 148 * mDp;
  }
  double number149 () {
    return 149 * mDp;
  }
  double number150 () {
    return 150 * mDp;
  }
  double number160 () {
    return 160 * mDp;
  }
  double number250 () {
    return 250 * mDp;
  }
  double number400 () {
    return 400 * mDp;
  }
  double number720 () {
    return 720 * mDp;
  }

  double scrollVelocityAndroid () {
    return 10000;
  }

  void setSafeAreaTop ( double newSafeAreaTop ) {
    if ( qFuzzyCompare ( mSafeAreaTop, newSafeAreaTop ) )
      return;
    mSafeAreaTop = newSafeAreaTop;
    emit safeAreaTopChanged ( mSafeAreaTop );
  }

  void setSafeAreaRight ( double newSafeAreaRight ) {
    if ( qFuzzyCompare ( mSafeAreaRight, newSafeAreaRight ) )
      return;
    mSafeAreaRight = newSafeAreaRight;
    emit safeAreaRightChanged ( mSafeAreaRight );
  }

  void setSafeAreaBottom ( double newSafeAreaBottom ) {
    if ( qFuzzyCompare ( mSafeAreaBottom, newSafeAreaBottom ) )
      return;

    mSafeAreaBottom = newSafeAreaBottom;
    emit safeAreaBottomChanged ( mSafeAreaBottom );
  }

  void setSafeAreaLeft ( double newSafeAreaLeft ) {
    if ( qFuzzyCompare ( mSafeAreaLeft, newSafeAreaLeft ) )
      return;
    mSafeAreaLeft = newSafeAreaLeft;
    emit safeAreaLeftChanged ( mSafeAreaLeft );
  }

signals:
  void styleChanged ();

  void safeAreaTopChanged ( double safeAreaTop );
  void safeAreaRightChanged ( double safeAreaRight );
  void safeAreaBottomChanged ( double safeAreaBottom );
  void safeAreaLeftChanged ( double safeAreaLeft );

private:
  QFont fontFactory ( int pixelSize, bool bold ) {
    QFont f;
    f.setPixelSize ( pixelSize * mDp );

    if ( bold ) {
      f.setWeight ( QFont::DemiBold );
    }

    return f;
  }

  qreal mDp = 1;

  double mSafeAreaTop = 0;
  double mSafeAreaRight = 0;
  double mSafeAreaBottom = 0;
  double mSafeAreaLeft = 0;
};

#endif  // APPSTYLE_H
