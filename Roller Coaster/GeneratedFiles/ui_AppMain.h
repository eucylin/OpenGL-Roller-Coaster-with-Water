/********************************************************************************
** Form generated from reading UI file 'AppMainp26324.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef APPMAINP26324_H
#define APPMAINP26324_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppMainClass
{
public:
    QAction *aExit;
    QAction *aLoadPath;
    QAction *aSavePath;
    QAction *aWorld;
    QAction *aTop;
    QAction *aTrain;
    QAction *aLinear;
    QAction *aCardinal;
    QAction *aCubic;
    QAction *aLine;
    QAction *aTrack;
    QAction *aRoad;
    QAction *actionBlood;
    QAction *actionCloudyLightRays;
    QAction *actionDarkStormy;
    QAction *actionFullMoon;
    QAction *actionSunSet;
    QAction *actionThickCloudsWater;
    QAction *actionTropicalSunnyDay;
    QAction *actionNONE;
    QAction *actionWood;
    QAction *actionDimple;
    QAction *actionKill;
    QAction *actionSWater;
    QAction *actionPhong;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupCamera;
    QComboBox *comboCamera;
    QGroupBox *groupCurve;
    QComboBox *comboCurve;
    QGroupBox *groupTrack;
    QComboBox *comboTrack;
    QGroupBox *groupPlay;
    QPushButton *bPlay;
    QGroupBox *groupCP;
    QPushButton *bAdd;
    QPushButton *bDelete;
    QGroupBox *groupBox;
    QPushButton *rcpxadd;
    QPushButton *rcpxsub;
    QGroupBox *groupBox_2;
    QPushButton *rcpzadd;
    QPushButton *rcpzsub;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QSlider *sSpeed;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuCamera;
    QMenu *menuCurve;
    QMenu *menuTrack;
    QMenu *menuVelocity;
    QMenu *menuSkybox;
    QMenu *menuShader;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *AppMainClass)
    {
        if (AppMainClass->objectName().isEmpty())
            AppMainClass->setObjectName(QStringLiteral("AppMainClass"));
        AppMainClass->resize(1032, 769);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AppMainClass->sizePolicy().hasHeightForWidth());
        AppMainClass->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        AppMainClass->setFont(font);
        AppMainClass->setLayoutDirection(Qt::LeftToRight);
        AppMainClass->setAutoFillBackground(true);
        AppMainClass->setStyleSheet(QStringLiteral(""));
        AppMainClass->setDockNestingEnabled(false);
        aExit = new QAction(AppMainClass);
        aExit->setObjectName(QStringLiteral("aExit"));
        aLoadPath = new QAction(AppMainClass);
        aLoadPath->setObjectName(QStringLiteral("aLoadPath"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/AppMain/Resources/Icons/openfile.ico"), QSize(), QIcon::Normal, QIcon::Off);
        aLoadPath->setIcon(icon);
        aLoadPath->setIconVisibleInMenu(true);
        aSavePath = new QAction(AppMainClass);
        aSavePath->setObjectName(QStringLiteral("aSavePath"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/AppMain/Resources/Icons/savefile.ico"), QSize(), QIcon::Normal, QIcon::Off);
        aSavePath->setIcon(icon1);
        aWorld = new QAction(AppMainClass);
        aWorld->setObjectName(QStringLiteral("aWorld"));
        aWorld->setCheckable(false);
        aWorld->setChecked(false);
        aTop = new QAction(AppMainClass);
        aTop->setObjectName(QStringLiteral("aTop"));
        aTop->setCheckable(true);
        aTrain = new QAction(AppMainClass);
        aTrain->setObjectName(QStringLiteral("aTrain"));
        aTrain->setCheckable(true);
        aLinear = new QAction(AppMainClass);
        aLinear->setObjectName(QStringLiteral("aLinear"));
        aLinear->setCheckable(false);
        aLinear->setChecked(false);
        aCardinal = new QAction(AppMainClass);
        aCardinal->setObjectName(QStringLiteral("aCardinal"));
        aCardinal->setCheckable(true);
        aCubic = new QAction(AppMainClass);
        aCubic->setObjectName(QStringLiteral("aCubic"));
        aCubic->setCheckable(true);
        aLine = new QAction(AppMainClass);
        aLine->setObjectName(QStringLiteral("aLine"));
        aLine->setCheckable(false);
        aLine->setChecked(false);
        aTrack = new QAction(AppMainClass);
        aTrack->setObjectName(QStringLiteral("aTrack"));
        aTrack->setCheckable(true);
        aRoad = new QAction(AppMainClass);
        aRoad->setObjectName(QStringLiteral("aRoad"));
        aRoad->setCheckable(true);
        actionBlood = new QAction(AppMainClass);
        actionBlood->setObjectName(QStringLiteral("actionBlood"));
        actionCloudyLightRays = new QAction(AppMainClass);
        actionCloudyLightRays->setObjectName(QStringLiteral("actionCloudyLightRays"));
        actionDarkStormy = new QAction(AppMainClass);
        actionDarkStormy->setObjectName(QStringLiteral("actionDarkStormy"));
        actionFullMoon = new QAction(AppMainClass);
        actionFullMoon->setObjectName(QStringLiteral("actionFullMoon"));
        actionSunSet = new QAction(AppMainClass);
        actionSunSet->setObjectName(QStringLiteral("actionSunSet"));
        actionThickCloudsWater = new QAction(AppMainClass);
        actionThickCloudsWater->setObjectName(QStringLiteral("actionThickCloudsWater"));
        actionTropicalSunnyDay = new QAction(AppMainClass);
        actionTropicalSunnyDay->setObjectName(QStringLiteral("actionTropicalSunnyDay"));
        actionNONE = new QAction(AppMainClass);
        actionNONE->setObjectName(QStringLiteral("actionNONE"));
        actionWood = new QAction(AppMainClass);
        actionWood->setObjectName(QStringLiteral("actionWood"));
        actionDimple = new QAction(AppMainClass);
        actionDimple->setObjectName(QStringLiteral("actionDimple"));
        actionKill = new QAction(AppMainClass);
        actionKill->setObjectName(QStringLiteral("actionKill"));
        actionSWater = new QAction(AppMainClass);
        actionSWater->setObjectName(QStringLiteral("actionSWater"));
        actionPhong = new QAction(AppMainClass);
        actionPhong->setObjectName(QStringLiteral("actionPhong"));
        centralWidget = new QWidget(AppMainClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        mainLayout = new QVBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        mainLayout->setSizeConstraint(QLayout::SetDefaultConstraint);

        verticalLayout->addLayout(mainLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        groupCamera = new QGroupBox(centralWidget);
        groupCamera->setObjectName(QStringLiteral("groupCamera"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupCamera->sizePolicy().hasHeightForWidth());
        groupCamera->setSizePolicy(sizePolicy2);
        groupCamera->setMinimumSize(QSize(120, 150));
        groupCamera->setMaximumSize(QSize(200, 150));
        QFont font1;
        font1.setFamily(QStringLiteral("Comic Sans MS"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        groupCamera->setFont(font1);
        groupCamera->setAutoFillBackground(false);
        groupCamera->setStyleSheet(QLatin1String("background-color: rgb(249, 249, 249);\n"
"border-radius: 5px;"));
        groupCamera->setAlignment(Qt::AlignCenter);
        comboCamera = new QComboBox(groupCamera);
        comboCamera->setObjectName(QStringLiteral("comboCamera"));
        comboCamera->setGeometry(QRect(10, 40, 96, 96));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboCamera->sizePolicy().hasHeightForWidth());
        comboCamera->setSizePolicy(sizePolicy3);
        QFont font2;
        font2.setFamily(QStringLiteral("Comic Sans MS"));
        font2.setPointSize(9);
        font2.setBold(true);
        font2.setWeight(75);
        comboCamera->setFont(font2);
        comboCamera->setStyleSheet(QLatin1String(" QComboBox {\n"
"	background-color: rgb(80, 80, 80);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QComboBox:on {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.499001, fy:0.000500999, stop:0 rgba(152, 152, 152, 217), stop:1 rgba(0, 0, 0, 232));\n"
"     padding-top: 3px;\n"
"     padding-left: 4px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"	image: url(:/AppMain/down_arrow.ico);\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"     border-left-color: rgb(240, 240, 240);\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"     selection-background-color: rgb(80, 80, 80);\n"
"}"));

        horizontalLayout->addWidget(groupCamera);

        groupCurve = new QGroupBox(centralWidget);
        groupCurve->setObjectName(QStringLiteral("groupCurve"));
        sizePolicy2.setHeightForWidth(groupCurve->sizePolicy().hasHeightForWidth());
        groupCurve->setSizePolicy(sizePolicy2);
        groupCurve->setMinimumSize(QSize(120, 150));
        groupCurve->setMaximumSize(QSize(200, 150));
        groupCurve->setFont(font1);
        groupCurve->setStyleSheet(QLatin1String("background-color: rgb(249, 249, 249);\n"
"border-radius: 5px;"));
        groupCurve->setAlignment(Qt::AlignCenter);
        comboCurve = new QComboBox(groupCurve);
        comboCurve->setObjectName(QStringLiteral("comboCurve"));
        comboCurve->setGeometry(QRect(10, 40, 96, 96));
        sizePolicy3.setHeightForWidth(comboCurve->sizePolicy().hasHeightForWidth());
        comboCurve->setSizePolicy(sizePolicy3);
        comboCurve->setFont(font2);
        comboCurve->setStyleSheet(QLatin1String(" QComboBox {\n"
"	background-color: rgb(80, 80, 80);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QComboBox:on {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.499001, fy:0.000500999, stop:0 rgba(152, 152, 152, 217), stop:1 rgba(0, 0, 0, 232));\n"
"     padding-top: 3px;\n"
"     padding-left: 4px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"	image: url(:/AppMain/down_arrow.ico);\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"     border-left-color: rgb(240, 240, 240);\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"     selection-background-color: rgb(80, 80, 80);\n"
"}"));

        horizontalLayout->addWidget(groupCurve);

        groupTrack = new QGroupBox(centralWidget);
        groupTrack->setObjectName(QStringLiteral("groupTrack"));
        sizePolicy2.setHeightForWidth(groupTrack->sizePolicy().hasHeightForWidth());
        groupTrack->setSizePolicy(sizePolicy2);
        groupTrack->setMinimumSize(QSize(120, 120));
        groupTrack->setMaximumSize(QSize(200, 150));
        groupTrack->setFont(font1);
        groupTrack->setStyleSheet(QLatin1String("background-color: rgb(249, 249, 249);\n"
"border-radius: 5px;"));
        groupTrack->setAlignment(Qt::AlignCenter);
        comboTrack = new QComboBox(groupTrack);
        comboTrack->setObjectName(QStringLiteral("comboTrack"));
        comboTrack->setGeometry(QRect(10, 40, 96, 96));
        sizePolicy3.setHeightForWidth(comboTrack->sizePolicy().hasHeightForWidth());
        comboTrack->setSizePolicy(sizePolicy3);
        comboTrack->setFont(font2);
        comboTrack->setStyleSheet(QLatin1String(" QComboBox {\n"
"	background-color: rgb(80, 80, 80);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QComboBox:on {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.499001, fy:0.000500999, stop:0 rgba(152, 152, 152, 217), stop:1 rgba(0, 0, 0, 232));\n"
"     padding-top: 3px;\n"
"     padding-left: 4px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"	image: url(:/AppMain/down_arrow.ico);\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"     border-left-color: rgb(240, 240, 240);\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"     selection-background-color: rgb(80, 80, 80);\n"
"}"));
        comboTrack->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        horizontalLayout->addWidget(groupTrack);

        groupPlay = new QGroupBox(centralWidget);
        groupPlay->setObjectName(QStringLiteral("groupPlay"));
        sizePolicy2.setHeightForWidth(groupPlay->sizePolicy().hasHeightForWidth());
        groupPlay->setSizePolicy(sizePolicy2);
        groupPlay->setMinimumSize(QSize(120, 150));
        groupPlay->setMaximumSize(QSize(200, 150));
        groupPlay->setFont(font1);
        groupPlay->setStyleSheet(QLatin1String("background-color: rgb(249, 249, 249);\n"
"border-radius: 5px;"));
        groupPlay->setAlignment(Qt::AlignCenter);
        bPlay = new QPushButton(groupPlay);
        bPlay->setObjectName(QStringLiteral("bPlay"));
        bPlay->setGeometry(QRect(10, 40, 96, 96));
        sizePolicy2.setHeightForWidth(bPlay->sizePolicy().hasHeightForWidth());
        bPlay->setSizePolicy(sizePolicy2);
        bPlay->setFont(font2);
        bPlay->setStyleSheet(QLatin1String(" QPushButton {\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"}"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/AppMain/mplay.png"), QSize(), QIcon::Normal, QIcon::Off);
        bPlay->setIcon(icon2);
        bPlay->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(groupPlay);

        groupCP = new QGroupBox(centralWidget);
        groupCP->setObjectName(QStringLiteral("groupCP"));
        sizePolicy2.setHeightForWidth(groupCP->sizePolicy().hasHeightForWidth());
        groupCP->setSizePolicy(sizePolicy2);
        groupCP->setMinimumSize(QSize(120, 150));
        groupCP->setMaximumSize(QSize(200, 150));
        groupCP->setFont(font1);
        groupCP->setMouseTracking(false);
        groupCP->setAutoFillBackground(false);
        groupCP->setStyleSheet(QLatin1String("background-color: rgb(249, 249, 249);\n"
"border-radius: 5px;"));
        groupCP->setAlignment(Qt::AlignCenter);
        groupCP->setFlat(false);
        groupCP->setCheckable(false);
        bAdd = new QPushButton(groupCP);
        bAdd->setObjectName(QStringLiteral("bAdd"));
        bAdd->setGeometry(QRect(10, 40, 100, 44));
        sizePolicy2.setHeightForWidth(bAdd->sizePolicy().hasHeightForWidth());
        bAdd->setSizePolicy(sizePolicy2);
        bAdd->setFont(font2);
        bAdd->setStyleSheet(QLatin1String(" QPushButton {\n"
"	background-color: rgb(80, 80, 80);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/AppMain/madd.png"), QSize(), QIcon::Normal, QIcon::Off);
        bAdd->setIcon(icon3);
        bAdd->setIconSize(QSize(14, 14));
        bDelete = new QPushButton(groupCP);
        bDelete->setObjectName(QStringLiteral("bDelete"));
        bDelete->setGeometry(QRect(10, 90, 100, 44));
        sizePolicy2.setHeightForWidth(bDelete->sizePolicy().hasHeightForWidth());
        bDelete->setSizePolicy(sizePolicy2);
        bDelete->setFont(font2);
        bDelete->setFocusPolicy(Qt::ClickFocus);
        bDelete->setStyleSheet(QLatin1String(" QPushButton {\n"
"	background-color: rgb(80, 80, 80);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/AppMain/mdelete.png"), QSize(), QIcon::Normal, QIcon::Off);
        bDelete->setIcon(icon4);
        bDelete->setIconSize(QSize(12, 12));

        horizontalLayout->addWidget(groupCP);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        groupBox->setMinimumSize(QSize(120, 150));
        groupBox->setMaximumSize(QSize(200, 150));
        QPalette palette;
        QBrush brush(QColor(249, 249, 249, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        groupBox->setPalette(palette);
        groupBox->setFont(font1);
        groupBox->setStyleSheet(QLatin1String("background-color: rgb(249, 249, 249);\n"
"border-radius: 5px;"));
        groupBox->setAlignment(Qt::AlignCenter);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        rcpxadd = new QPushButton(groupBox);
        rcpxadd->setObjectName(QStringLiteral("rcpxadd"));
        rcpxadd->setGeometry(QRect(10, 40, 100, 44));
        sizePolicy2.setHeightForWidth(rcpxadd->sizePolicy().hasHeightForWidth());
        rcpxadd->setSizePolicy(sizePolicy2);
        rcpxadd->setStyleSheet(QLatin1String("QPushButton {\n"
"	background-color: rgb(80, 80, 80);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        rcpxadd->setIcon(icon3);
        rcpxadd->setIconSize(QSize(14, 14));
        rcpxsub = new QPushButton(groupBox);
        rcpxsub->setObjectName(QStringLiteral("rcpxsub"));
        rcpxsub->setGeometry(QRect(10, 90, 100, 44));
        rcpxsub->setStyleSheet(QLatin1String("QPushButton {\n"
"	background-color: rgb(80, 80, 80);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        rcpxsub->setIcon(icon4);

        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(120, 150));
        groupBox_2->setMaximumSize(QSize(200, 150));
        groupBox_2->setFont(font1);
        groupBox_2->setStyleSheet(QLatin1String("background-color: rgb(249, 249, 249);\n"
"border-radius: 5px;"));
        rcpzadd = new QPushButton(groupBox_2);
        rcpzadd->setObjectName(QStringLiteral("rcpzadd"));
        rcpzadd->setGeometry(QRect(10, 40, 100, 44));
        sizePolicy2.setHeightForWidth(rcpzadd->sizePolicy().hasHeightForWidth());
        rcpzadd->setSizePolicy(sizePolicy2);
        rcpzadd->setStyleSheet(QLatin1String("QPushButton {\n"
"	background-color: rgb(80, 80, 80);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        rcpzadd->setIcon(icon3);
        rcpzsub = new QPushButton(groupBox_2);
        rcpzsub->setObjectName(QStringLiteral("rcpzsub"));
        rcpzsub->setGeometry(QRect(10, 90, 100, 44));
        rcpzsub->setStyleSheet(QLatin1String("QPushButton {\n"
"	background-color: rgb(80, 80, 80);\n"
"	color: rgb(240, 240, 240);\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"	background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(172, 172, 172, 255), stop:1 rgba(0, 0, 0, 203));\n"
"     padding-top: 10px;\n"
"     padding-left: 5px;\n"
"}"));
        rcpzsub->setIcon(icon4);

        horizontalLayout->addWidget(groupBox_2);

        horizontalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        sSpeed = new QSlider(centralWidget);
        sSpeed->setObjectName(QStringLiteral("sSpeed"));
        sSpeed->setMinimumSize(QSize(850, 0));
        sSpeed->setStyleSheet(QLatin1String("QSlider::groove:horizontal {\n"
"	background-color: #505050;\n"
"    height: 3px; \n"
"    margin: 2px 0;\n"
" }\n"
" QSlider::handle:horizontal {\n"
"	image: url(:/AppMain/slider_handle.png);\n"
"	width: 15px;\n"
"	margin: -5px 0;\n"
" }"));
        sSpeed->setSingleStep(1);
        sSpeed->setValue(50);
        sSpeed->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(sSpeed);

        horizontalSpacer_3 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        AppMainClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AppMainClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1032, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuCamera = new QMenu(menuBar);
        menuCamera->setObjectName(QStringLiteral("menuCamera"));
        menuCurve = new QMenu(menuBar);
        menuCurve->setObjectName(QStringLiteral("menuCurve"));
        menuTrack = new QMenu(menuBar);
        menuTrack->setObjectName(QStringLiteral("menuTrack"));
        menuVelocity = new QMenu(menuBar);
        menuVelocity->setObjectName(QStringLiteral("menuVelocity"));
        menuSkybox = new QMenu(menuBar);
        menuSkybox->setObjectName(QStringLiteral("menuSkybox"));
        menuShader = new QMenu(menuBar);
        menuShader->setObjectName(QStringLiteral("menuShader"));
        AppMainClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(AppMainClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        AppMainClass->setStatusBar(statusBar);
        mainToolBar = new QToolBar(AppMainClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        AppMainClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuCamera->menuAction());
        menuBar->addAction(menuTrack->menuAction());
        menuBar->addAction(menuCurve->menuAction());
        menuBar->addAction(menuVelocity->menuAction());
        menuBar->addAction(menuSkybox->menuAction());
        menuBar->addAction(menuShader->menuAction());
        menuFile->addAction(aLoadPath);
        menuFile->addAction(aSavePath);
        menuFile->addSeparator();
        menuFile->addAction(aExit);
        menuCamera->addAction(aWorld);
        menuCamera->addAction(aTop);
        menuCamera->addAction(aTrain);
        menuCurve->addAction(aLinear);
        menuCurve->addAction(aCardinal);
        menuCurve->addAction(aCubic);
        menuTrack->addAction(aLine);
        menuTrack->addAction(aTrack);
        menuTrack->addAction(aRoad);
        menuSkybox->addAction(actionBlood);
        menuSkybox->addAction(actionCloudyLightRays);
        menuSkybox->addAction(actionDarkStormy);
        menuSkybox->addAction(actionFullMoon);
        menuSkybox->addAction(actionSunSet);
        menuSkybox->addAction(actionThickCloudsWater);
        menuSkybox->addAction(actionTropicalSunnyDay);
        menuShader->addAction(actionNONE);
        menuShader->addAction(actionWood);
        menuShader->addAction(actionDimple);
        menuShader->addAction(actionKill);
        menuShader->addAction(actionSWater);
        menuShader->addAction(actionPhong);
        mainToolBar->addAction(aLoadPath);
        mainToolBar->addAction(aSavePath);

        retranslateUi(AppMainClass);

        QMetaObject::connectSlotsByName(AppMainClass);
    } // setupUi

    void retranslateUi(QMainWindow *AppMainClass)
    {
        AppMainClass->setWindowTitle(QApplication::translate("AppMainClass", "AppMain", 0));
        aExit->setText(QApplication::translate("AppMainClass", "Exit", 0));
        aLoadPath->setText(QApplication::translate("AppMainClass", "Load Path", 0));
        aSavePath->setText(QApplication::translate("AppMainClass", "Save Path", 0));
        aWorld->setText(QApplication::translate("AppMainClass", "World", 0));
        aTop->setText(QApplication::translate("AppMainClass", "Top", 0));
        aTrain->setText(QApplication::translate("AppMainClass", "Train", 0));
        aLinear->setText(QApplication::translate("AppMainClass", "Linear", 0));
        aCardinal->setText(QApplication::translate("AppMainClass", "Cardinal", 0));
        aCubic->setText(QApplication::translate("AppMainClass", "Cubic", 0));
        aLine->setText(QApplication::translate("AppMainClass", "Line", 0));
        aTrack->setText(QApplication::translate("AppMainClass", "Track", 0));
        aRoad->setText(QApplication::translate("AppMainClass", "Road", 0));
        actionBlood->setText(QApplication::translate("AppMainClass", "blood", 0));
        actionCloudyLightRays->setText(QApplication::translate("AppMainClass", "CloudyLightRays", 0));
        actionDarkStormy->setText(QApplication::translate("AppMainClass", "DarkStormy", 0));
        actionFullMoon->setText(QApplication::translate("AppMainClass", "FullMoon", 0));
        actionSunSet->setText(QApplication::translate("AppMainClass", "SunSet", 0));
        actionThickCloudsWater->setText(QApplication::translate("AppMainClass", "ThickCloudsWater", 0));
        actionTropicalSunnyDay->setText(QApplication::translate("AppMainClass", "TropicalSunnyDay", 0));
        actionNONE->setText(QApplication::translate("AppMainClass", "NONE", 0));
        actionWood->setText(QApplication::translate("AppMainClass", "wood", 0));
        actionDimple->setText(QApplication::translate("AppMainClass", "dimple", 0));
        actionKill->setText(QApplication::translate("AppMainClass", "kill", 0));
        actionSWater->setText(QApplication::translate("AppMainClass", "sWater", 0));
        actionPhong->setText(QApplication::translate("AppMainClass", "Phong", 0));
        groupCamera->setTitle(QApplication::translate("AppMainClass", "Camera", 0));
        comboCamera->clear();
        comboCamera->insertItems(0, QStringList()
         << QApplication::translate("AppMainClass", "World", 0)
         << QApplication::translate("AppMainClass", "Top", 0)
         << QApplication::translate("AppMainClass", "Train", 0)
        );
        groupCurve->setTitle(QApplication::translate("AppMainClass", "Curve", 0));
        comboCurve->clear();
        comboCurve->insertItems(0, QStringList()
         << QApplication::translate("AppMainClass", "Linear", 0)
         << QApplication::translate("AppMainClass", "Cardinal", 0)
         << QApplication::translate("AppMainClass", "Cubic", 0)
        );
        groupTrack->setTitle(QApplication::translate("AppMainClass", "Track", 0));
        comboTrack->clear();
        comboTrack->insertItems(0, QStringList()
         << QApplication::translate("AppMainClass", "Line", 0)
         << QApplication::translate("AppMainClass", "Track", 0)
         << QApplication::translate("AppMainClass", "Road", 0)
        );
        groupPlay->setTitle(QApplication::translate("AppMainClass", "Play", 0));
        bPlay->setText(QString());
        groupCP->setTitle(QApplication::translate("AppMainClass", "Ctrl Point", 0));
        bAdd->setText(QString());
        bDelete->setText(QString());
        groupBox->setTitle(QApplication::translate("AppMainClass", "Rotate CP X", 0));
        rcpxadd->setText(QString());
        rcpxsub->setText(QString());
        groupBox_2->setTitle(QApplication::translate("AppMainClass", "Rotate CP Z", 0));
        rcpzadd->setText(QString());
        rcpzsub->setText(QString());
        menuFile->setTitle(QApplication::translate("AppMainClass", "File", 0));
        menuCamera->setTitle(QApplication::translate("AppMainClass", "Camera", 0));
        menuCurve->setTitle(QApplication::translate("AppMainClass", "Curve", 0));
        menuTrack->setTitle(QApplication::translate("AppMainClass", "Track", 0));
        menuVelocity->setTitle(QApplication::translate("AppMainClass", "Velocity", 0));
        menuSkybox->setTitle(QApplication::translate("AppMainClass", "Skybox", 0));
        menuShader->setTitle(QApplication::translate("AppMainClass", "Shader", 0));
    } // retranslateUi

};

namespace Ui {
    class AppMainClass: public Ui_AppMainClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // APPMAINP26324_H
