#-------------------------------------------------
#
# Project created by QtCreator 2020-03-06T14:10:53
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = radarreader
TEMPLATE = app

CONFIG += c++11
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
        details/uint_info.h \
    details/message_id.h \
    details/alarm_acknowledge.h \
    details/alarm_list.h \
    details/attributes.h \
    details/details.h \
    details/diagnostics_data_packet.h \
    details/features.h \
    details/heartbeat.h \
    details/marpa_clear_target.h \
    details/marpa_designate_target.h \
    details/marpa_setup_info.h \
    details/marpa_target_status.h \
    details/navigation_data.h \
    details/radar_mode.h \
    details/request_diagnostics_data.h \
    details/requset_self_test_results.h \
    details/self_test_results.h \
    details/service_info.h \
    details/set_bearing_alignment.h \
    details/set_colour_gain_mode.h \
    details/set_colour_gain_value.h \
    details/set_gain_mode.h \
    details/set_gain_value.h \
    details/set_guard_zone.h \
    details/set_guard_zone_enable.h \
    details/set_guard_zone_sensitivity.h \
    details/set_interface_rejection.h \
    details/set_preset_mode.h \
    details/set_radar_mode.h \
    details/set_rain_mode.h \
    details/set_rain_value.h \
    details/set_range.h \
    details/set_scanner_command.h \
    details/set_sea_clutter_curve.h \
    details/set_sea_mode.h \
    details/set_sea_value.h \
    details/set_target_expansion_mode.h \
    details/set_timed_tx_parameters.h \
    details/set_tx_frequency.h \
    details/spoke_data.h \
    details/status.h \
    details/wired_adaptor.h \
    details/rle.h

FORMS += \
        mainwindow.ui
INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2 \
                /usr/include/tbb

LIBS += /usr/lib/x86_64-linux-gnu/libopencv* -lz
LIBS += -L/usr/lib/x86_64-linux-gnu -lopencv_core -lopencv_highgui -lopencv_imgproc -lz
LIBS +=-ldl
LIBS +=/usr/lib/x86_64-linux-gnu/libtbb*
LIBS +=/usr/include/tbb/tbb*
