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
    C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.1\include \
    D:\opencv\opencv\build_gpu_contrib\install\include\opencv2 \
    D:\opencv\opencv\build_gpu_contrib\install\include \
    $$quote(D:/Program Files (x86)/MVS/Development/Includes)

CONFIG(debug,debug|release){
LIBS += \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_aruco470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_barcode470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_bgsegm470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_bioinspired470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_calib3d470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_ccalib470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_core470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudaarithm470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudabgsegm470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudacodec470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudafeatures2d470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudafilters470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudaimgproc470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudalegacy470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudaobjdetect470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudaoptflow470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudastereo470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudawarping470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudev470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_datasets470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_dnn470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_dnn_objdetect470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_dnn_superres470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_dpm470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_face470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_features2d470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_flann470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_fuzzy470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_gapi470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_hdf470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_hfs470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_highgui470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_imgcodecs470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_imgproc470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_img_hash470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_intensity_transform470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_line_descriptor470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_mcc470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_ml470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_objdetect470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_optflow470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_phase_unwrapping470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_photo470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_plot470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_quality470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_rapid470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_reg470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_rgbd470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_saliency470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_shape470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_stereo470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_stitching470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_structured_light470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_superres470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_surface_matching470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_text470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_tracking470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_video470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_videoio470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_videostab470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_wechat_qrcode470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_xfeatures2d470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_ximgproc470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_xobjdetect470d \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_xphoto470d \
    -L$$quote(D:/Program Files (x86)/MVS/Development/Libraries/win64) -lMvCameraControl
}
CONFIG(release,debug|release){
LIBS += \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_aruco470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_barcode470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_bgsegm470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_bioinspired470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_calib3d470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_ccalib470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_core470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudaarithm470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudabgsegm470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudacodec470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudafeatures2d470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudafilters470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudaimgproc470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudalegacy470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudaobjdetect470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudaoptflow470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudastereo470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudawarping470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_cudev470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_datasets470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_dnn470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_dnn_objdetect470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_dnn_superres470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_dpm470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_face470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_features2d470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_flann470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_fuzzy470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_gapi470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_hdf470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_hfs470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_highgui470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_imgcodecs470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_imgproc470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_img_hash470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_intensity_transform470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_line_descriptor470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_mcc470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_ml470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_objdetect470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_optflow470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_phase_unwrapping470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_photo470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_plot470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_quality470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_rapid470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_reg470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_rgbd470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_saliency470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_shape470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_stereo470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_stitching470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_structured_light470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_superres470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_surface_matching470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_text470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_tracking470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_video470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_videoio470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_videostab470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_wechat_qrcode470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_xfeatures2d470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_ximgproc470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_xobjdetect470 \
    -LD:\opencv\opencv\build_gpu_contrib\install\x64\vc17\lib -lopencv_xphoto470 \
    -L$$quote(D:/Program Files (x86)/MVS/Development/Libraries/win64) -lMvCameraControl
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
