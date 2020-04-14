#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QTime>
#include <QDir>
#include "QHostAddress"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "details/details.h"
#include <sys/socket.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString get_msg_id(QByteArray datagram);

private slots:
    void get_udp_data ();
    void get_udp_radardata ();
    QHostAddress hexip_qhaip(uint32_t iphexdata);
    Heartbeat_t MakeHeartBeat();
    void send_Heart_beat();
    std::vector<uint8_t> RLE_Decoding(const std::vector<uint8_t> data);
    std::size_t RLE_DecodeSize(const std::vector<uint8_t> data);
    std::vector<uint8_t> RLE_Encoding(const std::vector<uint8_t> data);
    std::vector<uint8_t> array2vector(const uint8_t* data, std::size_t size);
    void TestRLE();
    QImage cvMatToQImage( const cv::Mat &inMat );
    QPixmap cvMatToQPixmap( const cv::Mat &inMat );
    QString bool2qstring(bool v);
    QString getstring(const uint8_t* data, std::size_t size);
    QString get_radarnode(QUANTUM_MODE_T flag);
    QString get_QUANTUM_PRESET_MODE(QUANTUM_PRESET_MODE_T mode);
    QString get_QUANTUM_TARGET_EXPANSION_MODE(QUANTUM_RAIN_MODE_T mode);
    QString get_QuantumSeaClutterCurve(QuantumSeaClutterCurve_t mode);
    QString get_QuantumMainBangSuppression(QuantumMainBangSuppression_t mode);
    QString get_QUANTUM_MODE(QUANTUM_COLOUR_GAIN_MODE_T mode);
    QString getstring(const uint32_t* data, std::size_t size);
    QString get_QUANTUM_TX_FREQ(QUANTUM_TX_FREQ_T mode);
    QString get_QUANTUM_INTERFERENCE_REJECTION_MODE(QUANTUM_INTERFERENCE_REJECTION_MODE_T mode);
    double get_Range(uint8_t Range_inde);
    void on_pushButton_5_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_12_clicked();
    void on_closebutton_clicked();
    void cant_find_device();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_4_currentIndexChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_comboBox_3_currentIndexChanged(const QString &arg1);

    void on_comboBox_5_currentIndexChanged(const QString &arg1);

    void on_comboBox_6_currentIndexChanged(const QString &arg1);

    void on_comboBox_7_currentIndexChanged(const QString &arg1);

    void on_comboBox_8_currentIndexChanged(const QString &arg1);

    void on_comboBox_9_currentIndexChanged(const QString &arg1);

    void on_comboBox_10_currentIndexChanged(const QString &arg1);

    void on_comboBox_11_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();
    cv::Mat range_interval(cv::Mat img);
    void UNIT_INFO_MESSAGE_ID_Precess(QByteArray datagram);
    void SERVICE_INFO_MESSAGE_ID_Precess(QByteArray datagram);
    void NOTHING_Precess(QByteArray datagram);
    void SPOKE_DATA_Precess(QByteArray datagram);
    void SPOKE_DATA_img_Precess(QByteArray datagram);
    void TARGET_STATUS_Precess(QByteArray datagram);
    void ATTRIBUTES_Precess(QByteArray datagram);
    void STATUS_Precess(QByteArray datagram);
private:
    Ui::MainWindow *ui;
    QUdpSocket *m_udpSocket;
    QUdpSocket *m_udpSocket2;
    QUdpSocket *m_udpSocket3;
    UnitInfo_t *UnitInfo_msg;
    ServiceInfo_t * ServiceInfo_msg;
    QHostAddress ncip=QHostAddress("192.168.2.155");
    uint16_t ncip_port=2575;
    QHostAddress ndip=QHostAddress("232.1.123.1");
    uint16_t ndip_port=2574;
    SpokeData_t *SpokeData;
    QThread * m_childThread;
    QImage pm;
    int indexx=0;
    MarpaTargetStatus_t *targetstatus;
    Attributes_t *Attributes;
    Features_t *fea;
    Status_t *Status;
    AlarmList_t *AlarmList;
    QUANTUM_RANGE_STATUS_T *RangeInfo;
    QUANTUM_PRESET_DATA_T *QUANTUM_PRESET_DATA;
    uint8_t RangeInfo_Channel=1;
    bool finddevice = false;
    int timer_flag = 0;
    int sock_fd;
    cv::Mat radar_img,radar_img_final,tmp,radarcolorimg;
    size_t global_radar_resolution=500;
    QString dir_str = "Picture/";
    double radar_range = 0.5;
};


#endif // MAINWINDOW_H
