QT       += core gui serialport concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QCustomDevice/qcustomdevice.cpp \
    QCustomPlot/qcustomplot.cpp \
    QDevice/qinterferometer.cpp \
    QDevice/qprobdevice.cpp \
    QDevice/qpztdevice.cpp \
    QDevlink/qdevlink.cpp \
    QOscilloScope/qoscilloscope.cpp \
    QPlanner/qastar.cpp \
    QPlanner/qplanner.cpp \
    QVision/mvs_driver.cpp \
    QVision/qvision.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    QCustomDevice/qcustomdevice.h \
    QCustomPlot/qcustomplot.h \
    QDevice/qinterferometer.h \
    QDevice/qprobdevice.h \
    QDevice/qpztdevice.h \
    QDevlink/qdevlink.h \
    QOscilloScope/qoscilloscope.h \
    QPlanner/qastar.h \
    QPlanner/qplanner.h \
    QPlanner/qplanner_common.h \
    QVision/mvs_driver.h \
    QVision/qvision.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += \
    QCustomDevice \
    QCustomPlot \
    QDevice \
    QDevlink \
    QOscilloScope \
    QVision \
    QPlanner \
    D:\opencv\opencv\build_contrib\install\include\opencv2 \
    D:\opencv\opencv\build_contrib\install\include \
    $$quote(D:/Program Files (x86)/MVS/Development/Includes)

CONFIG(debug,debug|release){
LIBS += \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_core470d \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_highgui470d \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_xfeatures2d470d \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_flann470d \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_features2d470d \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_imgproc470d \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_photo470d \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_plot470d \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_imgcodecs470d \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_rgbd470d \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_stitching470d \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_video470d \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_calib3d470d \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_ccalib470d \
    -L$$quote(D:/Program Files (x86)/MVS/Development/Libraries/win64) -lMvCameraControl
}
CONFIG(release,debug|release){
LIBS += \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_core470 \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_highgui470 \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_xfeatures2d470 \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_flann470 \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_features2d470 \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_imgproc470 \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_photo470 \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_plot470 \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_imgcodecs470 \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_rgbd470 \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_stitching470 \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_video470 \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_calib3d470 \
    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_ccalib470 \
    -L$$quote(D:/Program Files (x86)/MVS/Development/Libraries/win64) -lMvCameraControl
}

#LIBS += \
#    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib \
#    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_core470d \
#    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_highgui470d \
#    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_xfeatures2d470d \
#    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_flann470d \
#    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_features2d470d \
#    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_imgproc470d \
#    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_photo470d \
#    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_plot470d \
#    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_imgcodecs470d \
#    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_rgbd470d \
#    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_stitching470d \
#    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_video470d \
#    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_calib3d470d \
#    -LD:\opencv\opencv\build_contrib\install\x64\vc17\lib -lopencv_ccalib470d \
#    -L$$quote(D:/Program Files (x86)/MVS/Development/Libraries/win64) -lMvCameraControl

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
