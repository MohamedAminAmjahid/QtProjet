QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcommanddialog.cpp \
    adddialog.cpp \
    addrecettedialog.cpp \
    commande.cpp \
    databasemanager.cpp \
    gerant.cpp \
    gestionadminform.cpp \
    gestionserveurform.cpp \
    listform.cpp \
    main.cpp \
    mainwindow.cpp \
    monthyeardialog.cpp \
    personne.cpp \
    produit.cpp \
    recette.cpp \
    searchproductdialog.cpp \
    searchserveranddaterecettedialog.cpp \
    serveur.cpp \
    updatecommanddialog.cpp \
    updatedialog.cpp \
    updaterecettedialog.cpp \
    updateserverdialog.cpp

HEADERS += \
    addcommanddialog.h \
    adddialog.h \
    addrecettedialog.h \
    commande.h \
    databasemanager.h \
    gerant.h \
    gestionadminform.h \
    gestionserveurform.h \
    listform.h \
    mainwindow.h \
    monthyeardialog.h \
    personne.h \
    produit.h \
    recette.h \
    searchproductdialog.h \
    searchserveranddaterecettedialog.h \
    serveur.h \
    updatecommanddialog.h \
    updatedialog.h \
    updaterecettedialog.h \
    updateserverdialog.h

FORMS += \
    addcommanddialog.ui \
    adddialog.ui \
    addrecettedialog.ui \
    gestionadminform.ui \
    gestionserveurform.ui \
    listform.ui \
    mainwindow.ui \
    monthyeardialog.ui \
    searchproductdialog.ui \
    searchserveranddaterecettedialog.ui \
    updatecommanddialog.ui \
    updatedialog.ui \
    updaterecettedialog.ui \
    updateserverdialog.ui
# Définition des fichiers de traduction --------------------------------------------------
TRANSLATIONS += Translations/gestionrestaurant_en_US.ts \
                Translations/gestionrestaurant_fr_FR.ts

# Génération des fichiers de traduction --------------------------------------------------
translate.target = translate
translate.depends = $$ALLSOURCES
translate.commands = lupdate $$TARGET.pro
QMAKE_EXTRA_TARGETS += translate

# Compilation des fichiers de traduction --------------------------------------------------
compile_translation.target = compile_translation
compile_translation.depends = $$TRANSLATIONS
compile_translation.commands = lrelease $$TARGET.pro
QMAKE_EXTRA_TARGETS += compile_translation

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
