#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<sstream>
#include<string>
#include "QThread"
#include "QBuffer"

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_udpSocket = new QUdpSocket(this);
    m_udpSocket->bind(QHostAddress::AnyIPv4,5800,QUdpSocket::ShareAddress);
    m_udpSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption,0);
    m_udpSocket->joinMulticastGroup(QHostAddress("224.0.0.1"));
    connect(m_udpSocket,&QUdpSocket::readyRead,this,&MainWindow::get_udp_data);

    m_udpSocket2 = new QUdpSocket(this);

    m_udpSocket3 = new QUdpSocket(this);
    m_udpSocket3->bind(QHostAddress::AnyIPv4, 2574,QUdpSocket::ShareAddress);
    m_udpSocket3->setSocketOption(QAbstractSocket::MulticastLoopbackOption,0);
    m_udpSocket3->joinMulticastGroup(QHostAddress("232.1.123.1"));
    connect(m_udpSocket3,&QUdpSocket::readyRead,this,&MainWindow::get_udp_radardata);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(send_Heart_beat()));
    timer->start(1000);

    QTimer *device_timer = new QTimer(this);
    connect(device_timer, SIGNAL(timeout()), this, SLOT(cant_find_device()));
    device_timer->start(1000);

    QImage pi(700,700,QImage::Format_Mono);
    pi.fill(0);
    ui->label_20->setPixmap(QPixmap::fromImage(pi));
    ui->label_136->setStyleSheet("QLabel{background-color:rgb(255,0,0);}");

    radar_img = cv::Mat(250, 500, CV_8UC1, cv::Scalar(0));

    ui->label_149->setStyleSheet("QLabel{background-color:rgb(255,255,0);}");
    ui->label_150->setStyleSheet("QLabel{background-color:rgb(255,255,0);}");
    ui->label_151->setStyleSheet("QLabel{background-color:rgb(255,255,0);}");
    ui->label_152->setStyleSheet("QLabel{background-color:rgb(255,255,0);}");
    ui->label_153->setStyleSheet("QLabel{background-color:rgb(255,255,0);}");
    ui->label_154->setStyleSheet("QLabel{background-color:rgb(255,255,0);}");
    ui->label_155->setStyleSheet("QLabel{background-color:rgb(255,255,0);}");
    ui->label_156->setStyleSheet("QLabel{background-color:rgb(255,255,0);}");
    ui->label_157->setStyleSheet("QLabel{background-color:rgb(255,255,0);}");
    ui->label_158->setStyleSheet("QLabel{background-color:rgb(255,255,0);}");
    ui->label_121->setStyleSheet("QLabel{background-color:rgb(255,255,0);}");
}
MainWindow::~MainWindow()
{
    m_udpSocket3->leaveMulticastGroup(ncip);
    delete ui;
}


void MainWindow::send_Heart_beat()
{
    //读取对方发送的内容
    //    const Heartbeat_t hb = MakeHeartBeat();
    QByteArray text = QByteArray::fromHex("000028005261646172000000");
    m_udpSocket2->writeDatagram(text,ncip,2575);
    //        cout<<"****"<<endl;
}

void MainWindow::get_udp_data ()
{
    //    qDebug()<<"get_udp_data";
    //读取对方发送的内容
    QByteArray datagram;
    datagram.resize(m_udpSocket->pendingDatagramSize());
    QHostAddress cliAddr;//对方地址
    quint16 port;//对方端口号
    m_udpSocket->readDatagram(datagram.data(), datagram.size(),&cliAddr,&port);
    MESSAGE_TYPE_T *msgid =(uint32_t*)datagram.data();
    switch (*msgid) {
    case msg_id::UNIT_INFO_MESSAGE_ID:
       UNIT_INFO_MESSAGE_ID_Precess(datagram);
        break;
    case msg_id::SERVICE_INFO_MESSAGE_ID:
        SERVICE_INFO_MESSAGE_ID_Precess(datagram);
        break;
    case msg_id::NOTHING:
        //        cout<<"NOTHING"<<endl;
        NOTHING_Precess(datagram);
        break;
    default:
        printf("Unknown id:  0x%08x", *msgid);
        cout<<endl;
        break;
    }
    //    UnitInfo_t *msg=(UnitInfo_t*)datagram.data();
    //    printf("0x%08x", aa);
}

void MainWindow::get_udp_radardata ()
{
    //读取对方发送的内容
    QByteArray datagram;
    datagram.resize(m_udpSocket3->pendingDatagramSize());
    QHostAddress cliAddr;//对方地址
    quint16 port;//对方端口号
    m_udpSocket3->readDatagram(datagram.data(), datagram.size(),&cliAddr,&port);
    MESSAGE_TYPE_T *msgid =(uint32_t*)datagram.data();

    if(*msgid==msg_id::SPOKE_DATA) {
        SPOKE_DATA_Precess(datagram);
        SPOKE_DATA_img_Precess(datagram);
    }
    else if(*msgid==msg_id::TARGET_STATUS){
        TARGET_STATUS_Precess(datagram);
    }
    else if(*msgid==msg_id::ATTRIBUTES)
    {
        ATTRIBUTES_Precess(datagram);
    }
    else if(*msgid==msg_id::FEATURES)
    {
        fea = (Features_t*)datagram.data();
    }
    else if(*msgid==msg_id::STATUS){
        STATUS_Precess(datagram);
    }
    else if(*msgid==msg_id::ALARM_LIST){
        AlarmList = (AlarmList_t*)datagram.data();
        QString qstr = "Alarm: ";
        ui->label_147->setText(qstr+QString::number(AlarmList->Count));
    }
    else{
        printf("Unknown id:  0x%08x", *msgid);
        cout<<endl;
    }
    //    UnitInfo_t *msg=(UnitInfo_t*)datagram.data();
    //    printf("0x%08x", aa);
}
double MainWindow::get_Range(uint8_t Range_inde)
{
    double tem;
    switch (Range_inde) {
    case 1:
        tem=0.0625;
        break;
    case 2:
        tem=0.125;
        break;
    case 3:
        tem=0.25;
        break;
    case 4:
        tem=0.375;
        break;
    case 5:
        tem=0.5;
        break;
    case 6:
        tem=0.75;
        break;
    case 7:
        tem=1.0;
        break;
    case 8:
        tem=1.5;
        break;
    case 9:
        tem=2.0;
        break;
    case 10:
        tem=3.0;
        break;
    case 11:
        tem=4.0;
        break;
    case 12:
        tem=6.0;
        break;
    case 13:
        tem=8;
        break;
    case 14:
        tem=12;
        break;
    case 15:
        tem=16;
        break;
    case 16:
        tem=24;
        break;
    default:
        tem=0.03125;
        break;
    }
    return tem;
}
QString MainWindow::get_QUANTUM_INTERFERENCE_REJECTION_MODE(QUANTUM_INTERFERENCE_REJECTION_MODE_T mode)
{
    QString tem;
    switch (mode) {
    case QUANTUM_INTERFERENCE_REJECTION_MODE_OFF:
        tem="OFF";
        break;
    case QUANTUM_INTERFERENCE_REJECTION_MODE_1:
        tem="MODE_1";
        break;
    case QUANTUM_INTERFERENCE_REJECTION_MODE_2:
        tem="MODE_2";
        break;
    case QUANTUM_INTERFERENCE_REJECTION_MODE_3:
        tem="MODE_3";
        break;
    case QUANTUM_INTERFERENCE_REJECTION_MODE_4:
        tem="MODE_4";
        break;
    case QUANTUM_INTERFERENCE_REJECTION_MODE_5:
        tem="MODE_5";
        break;
    default:
        tem="Null";
        break;
    }
    return tem;
}
QString MainWindow::get_QUANTUM_TX_FREQ(QUANTUM_TX_FREQ_T mode)
{
    QString tem;
    switch (mode) {
    case QUANTUM_TX_FREQ_NOMINAL:
        tem="TX_FREQ_NOMINAL";
        break;
    case QUANTUM_TX_FREQ_LOW:
        tem="TX_FREQ_LOW";
        break;
    case QUANTUM_TX_FREQ_HIGH:
        tem="TX_FREQ_HIGH";
        break;
    default:
        break;
    }
    return tem;
}
QString MainWindow::get_QUANTUM_MODE(QUANTUM_COLOUR_GAIN_MODE_T mode)
{
    QString tem;
    switch (mode) {
    case QUANTUM_COLOUR_GAIN_MODE_MANUAL:
        tem="MANUAL";
        break;
    case QUANTUM_COLOUR_GAIN_MODE_AUTO:
        tem="AUTO";
        break;
    default:
        break;
    }
    return tem;
}
QString MainWindow::get_QuantumMainBangSuppression(QuantumMainBangSuppression_t mode)
{
    QString tem;
    switch (mode) {
    case cQuantumMainBangSuppressionOff:
        tem="Off";
        break;
    case cQuantumMainBangSuppressionOn:
        tem="On";
        break;
    default:
        tem="Null";
        break;
    }
    return tem;
}
QString MainWindow::get_QuantumSeaClutterCurve(QuantumSeaClutterCurve_t mode)
{
    QString tem;
    switch (mode) {
    case cQuantumSeaCurve_R4:
        tem="Min";
        break;
    case cQuantumSeaCurve_R5_5:
        tem="Max";
        break;
    default:
        tem="Null";
        break;
    }
    return tem;
}
QString MainWindow::get_QUANTUM_TARGET_EXPANSION_MODE(QUANTUM_RAIN_MODE_T mode)
{
    QString tem;
    switch (mode) {
    case QUANTUM_TARGET_EXPANSION_MODE_OFF:
        tem="OFF";
        break;
    case QUANTUM_TARGET_EXPANSION_MODE_ON:
        tem="ON";
        break;
    default:
        tem="Null";
        break;
    }
    return tem;
}
QString MainWindow::get_QUANTUM_PRESET_MODE(QUANTUM_PRESET_MODE_T mode)
{
    QString tem;
    switch (mode) {
    case cPresetModeHarbour:
        tem="Harbour";
        break;
    case cPresetModeCoastal:
        tem="Coastal";
        break;
    case cPresetModeOffshore:
        tem="Offshore";
        break;
    case cPresetModeWeather:
        tem="Weather";
        break;
    default:
        tem="Null";
        break;
    }
    return tem;
}
QString MainWindow::get_radarnode(QUANTUM_MODE_T flag)
{
    QString tem;
    switch (flag) {
    case QUANTUM_MODE_TRANSMITTING:
        tem ="TRANSMITTING";
        break;
    case QUANTUM_MODE_POWER_DOWN:
        tem ="POWER_DOWN";
        break;
    case QUANTUM_MODE_TIMED_TX:
        tem ="TIMED_TX";
        break;
    case QUANTUM_MODE_SLEEP:
        tem ="SLEEP";
        break;
    case QUANTUM_MODE_STALLED:
        tem ="STALLED";
        break;
    case QUANTUM_MODE_SELFTEST_FAILED:
        tem ="SELFTEST_FAILED";
        break;
    case QUANTUM_MODE_STANDBY:
        tem ="STANDBY";
        break;
    default:
        tem ="Null";
        break;
    }
    return tem;
}
QString MainWindow::getstring(const uint8_t* data, std::size_t size)
{
    QString tmp;
    for(size_t i=0;i<size;i++) tmp+=QString::number(data[i])+" ";
    return tmp;
}
QString MainWindow::getstring(const uint32_t* data, std::size_t size)
{
    QString tmp;
    for(size_t i=0;i<size;i++) tmp+=QString::number(data[i])+" ";
    return tmp;
}
QString MainWindow::bool2qstring(bool v)
{
    QString result = "False";
    if(v) result="True";
    return result;
}
QImage  MainWindow::cvMatToQImage( const cv::Mat &inMat )
{
    switch ( inMat.type() )
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_ARGB32 );

        return image;
    }

        // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_RGB888 );

        return image.rgbSwapped();
    }

        // 8-bit, 1 channel
    case CV_8UC1:
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Grayscale8 );//Format_Alpha8 and Format_Grayscale8 were added in Qt 5.5
#else//这里还有一种写法，最后给出
        static QVector<QRgb>  sColorTable;

        // only create our color table the first time
        if ( sColorTable.isEmpty() )
        {
            sColorTable.resize( 256 );

            for ( int i = 0; i < 256; ++i )
            {
                sColorTable[i] = qRgb( i, i, i );
            }
        }

        QImage image( inMat.data,
                      inMat.cols, inMat.rows,
                      static_cast<int>(inMat.step),
                      QImage::Format_Indexed8 );

        image.setColorTable( sColorTable );
#endif

        return image;
    }

    default:
        qWarning() << "CVS::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}
QPixmap MainWindow::cvMatToQPixmap( const cv::Mat &inMat )
{
    return QPixmap::fromImage( cvMatToQImage( inMat ) );
}
QString MainWindow::get_msg_id(QByteArray datagram)
{
    QString strHex;
    QDataStream in(&datagram, QIODevice::ReadOnly);//因为其属性为只读，所以是输入
    for(int i=0;i<4;i++)
    {
        qint8 outChar = 0;
        in>>outChar;
        QString str = QString("%1").arg(outChar&0xFF,2,16,QLatin1Char('0'));
        strHex += str;
    }
    return strHex;
}
QHostAddress MainWindow::hexip_qhaip(uint32_t iphexdata)
{
    uint8_t ip_buff[4];
    for(size_t i=0;i<4;i++)
    {
        ip_buff[0]=iphexdata>>8;
        ip_buff[1]=iphexdata>>16;
        ip_buff[2]=iphexdata>>24;
        ip_buff[3]=iphexdata>>32;
    }
    QHostAddress qhaip = QHostAddress(QString::number(ip_buff[2])+"."+QString::number(ip_buff[1])+"."+
            QString::number(ip_buff[0])+"."+QString::number(ip_buff[3]));
    return qhaip;
}
Heartbeat_t MainWindow::MakeHeartBeat() {
    Heartbeat_t heartbeat;
    heartbeat.MessageCode = msg_id::HEARTBEAT;
    sprintf(heartbeat.HeartbeatText, "Radar");
    //    TestRLE();
    return heartbeat;
}
void MainWindow::TestRLE() {
    uint8_t data[] = {0x00, 0x0F, 0xAA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                      0xFF, 0xCC, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x03, 0x5C, 0x0A};
    //    uint8_t data[25] = {0};

    QByteArray array;
    int len_data = sizeof(data); // 4*4 = 16 (一个float占4个字节)
    array.resize(len_data);
    memcpy(array.data(), &data, len_data);

    uint8_t  outdata[array.size()];
    memcpy(&outdata, array.data(), array.size());

    std::vector<uint8_t> data_vector = array2vector(outdata,array.size());
    auto encode = RLE_Encoding(data_vector);
    auto decode = RLE_Decoding(encode);
    printf("RLE size : %d", RLE_DecodeSize(encode));
    for (auto d : encode) printf("%02x ", d);
    printf("\n");
    for (auto d : decode) printf("%02x ", d);
    printf("\n");
}
std::vector<uint8_t> MainWindow::RLE_Decoding(const std::vector<uint8_t> data) {
    std::vector<uint8_t> decode(RLE_DecodeSize(data));
    int i     = 0;
    int index = 0;
    while (i < data.size()) {
        if (data[i] == 0x5C) {
            memset(decode.data() + index, data[i + 2], data[i + 1]);
            index += data[i + 1];
            i += 3;
        } else {
            if (data[i] == 0x5B) {
                decode[index] = 0x5C;
                ++index;
            } else {
                decode[index] = data[i];
                ++index;
            }
            ++i;
        }
    }
    return std::move(decode);
}
std::size_t MainWindow::RLE_DecodeSize(const std::vector<uint8_t> data) {
    std::size_t len = 0;
    int32_t     i = 0;
    while (i < data.size()) {
        if (data[i] == 0x5C) {
            len += data[i + 1];
            i += 3;
        } else {
            ++len;
            ++i;
        }
    }
    return len;
}
std::vector<uint8_t> MainWindow::array2vector(const uint8_t* data, std::size_t size)
{
    std::vector<uint8_t> tmp(data, data + size);
    return tmp;
}
std::vector<uint8_t> MainWindow::RLE_Encoding(const std::vector<uint8_t> data) {
    std::vector<uint8_t> encode(data);
    std::size_t data_size = data.size();
    if (data_size == 1) return encode;
    uint8_t last = data[0]; // last data
    uint8_t curr = 0;       // current data
    int32_t rlen = 1;       // run length
    int32_t alen = 0;       // all length
    for (int32_t i = 1; i <data_size; ++i) {
        curr = data[i];
        if (curr == last) {
            ++rlen;
        } else {
            if (rlen == 1) {
                if (last == 0x5C) {
                    encode[alen++] = 0x5B;
                } else {
                    encode[alen++] = last;
                }
            } else if (rlen < 4) {
                for (int i = 0; i < rlen; ++i) encode[alen++] = last;
                rlen = 1;
            } else {
                encode[alen++] = 0x5C;
                encode[alen++] = rlen;
                encode[alen++] = last;
                rlen = 1;
            }
            last = curr;
        }
    }
    if (rlen == 1) {
        encode[alen++] = last;
    } else {
        encode[alen++] = 0x5C;
        encode[alen++] = rlen;
        encode[alen++] = last;
    }
    return std::move(
                std::vector<uint8_t>(encode.cbegin(), encode.cbegin() + alen));
}
void MainWindow::on_pushButton_5_clicked()
{
    SetGainValue_t SetGainValue;
    SetGainValue.m_MessageCode=msg_id::SET_GAIN_VALUE;
    SetGainValue.m_Channel=RangeInfo_Channel;
    SetGainValue.m_Value=ui->lineEdit_110->text().toUInt();
    m_udpSocket2->writeDatagram((char*)&SetGainValue,sizeof(SetGainValue),ncip,2575);
}
void MainWindow::on_pushButton_8_clicked()
{
    SetColourGainValue_t SetColourGainValue;
    SetColourGainValue.m_MessageCode=msg_id::SET_COLOUR_GAIN_VALUE;
    SetColourGainValue.m_Channel=RangeInfo_Channel;
    SetColourGainValue.m_Value=ui->lineEdit_112->text().toUInt();
    m_udpSocket2->writeDatagram((char*)&SetColourGainValue,sizeof(SetColourGainValue),ncip,2575);
}
void MainWindow::on_pushButton_10_clicked()
{
    SetSeaValue_t SetSeaValue;
    SetSeaValue.m_MessageCode=msg_id::SET_SEA_VALUE;
    SetSeaValue.m_Channel=RangeInfo_Channel;
    SetSeaValue.m_Value=ui->lineEdit_114->text().toUInt();
    m_udpSocket2->writeDatagram((char*)&SetSeaValue,sizeof(SetSeaValue),ncip,2575);
}
void MainWindow::on_pushButton_12_clicked()
{
    SetRainValue_t SetRainValue;
    SetRainValue.m_MessageCode=msg_id::SET_RAIN_VALUE;
    SetRainValue.m_Channel=RangeInfo_Channel;
    SetRainValue.m_Value=ui->lineEdit_116->text().toUInt();
    m_udpSocket2->writeDatagram((char*)&SetRainValue,sizeof(SetRainValue),ncip,2575);
}
void MainWindow::cant_find_device()
{
    if(timer_flag>5)
        ui->label_136->setStyleSheet("QLabel{background-color:rgb(255,0,0);}");
    timer_flag++;
}
void MainWindow::on_closebutton_clicked()
{
    m_udpSocket->leaveMulticastGroup(QHostAddress("224.0.0.1"));
    m_udpSocket3->leaveMulticastGroup(QHostAddress("232.1.123.1"));
    this->close();
}
void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    SetRadarMode_t RadarMode;
    RadarMode.m_MessageCode=msg_id::SET_RADAR_MODE;
    QByteArray text;
    switch (ui->comboBox->currentIndex()) {
    case 1:
        RadarMode.m_RadarMode =QUANTUM_MODE_TRANSMITTING;
        cout<<"set radar mode:QUANTUM_MODE_TRANSMITTING"<<endl;
        break;
    case 2:
        RadarMode.m_RadarMode =QUANTUM_MODE_POWER_DOWN;
        cout<<"set radar mode:QUANTUM_MODE_POWER_DOWN"<<endl;
        break;
    case 3:
        RadarMode.m_RadarMode =QUANTUM_MODE_TIMED_TX;
        cout<<"set radar mode:QUANTUM_MODE_TIMED_TX"<<endl;
        break;
    case 4:
        RadarMode.m_RadarMode =QUANTUM_MODE_SLEEP;
        cout<<"set radar mode:QUANTUM_MODE_SLEEP"<<endl;
        break;
    case 5:
        RadarMode.m_RadarMode =QUANTUM_MODE_STALLED;
        cout<<"set radar mode:QUANTUM_MODE_STALLED"<<endl;
        break;
    case 6:
        RadarMode.m_RadarMode =QUANTUM_MODE_SELFTEST_FAILED;
        cout<<"set radar mode:QUANTUM_MODE_SELFTEST_FAILED"<<endl;
        break;
    default:
        RadarMode.m_RadarMode =QUANTUM_MODE_STANDBY;
        cout<<"set radar mode:QUANTUM_MODE_STANDBY"<<endl;
        break;
    }
    m_udpSocket2->writeDatagram((char*)&RadarMode,sizeof(RadarMode),ncip,2575);
}
void MainWindow::on_comboBox_4_currentIndexChanged(const QString &arg1)
{
    SetRange_t SetRange;
    SetRange.m_MessageCode=msg_id::SET_RANGE;
    switch (ui->comboBox_4->currentIndex()) {
    case 1:
        SetRange.m_RangeIndex =Range_1_16;
        break;
    case 2:
        SetRange.m_RangeIndex =Range_1_8;
        break;
    case 3:
        SetRange.m_RangeIndex =Range_1_4;
        break;
    case 4:
        SetRange.m_RangeIndex =Range_3_8;
        break;
    case 5:
        SetRange.m_RangeIndex =Range_1_2;
        break;
    case 6:
        SetRange.m_RangeIndex =Range_3_4;
        break;
    case 7:
        SetRange.m_RangeIndex =Range_1;
        break;
    case 8:
        SetRange.m_RangeIndex =Range_3_2;
        break;
    case 9:
        SetRange.m_RangeIndex =Range_2;
        break;
    case 10:
        SetRange.m_RangeIndex =Range_3;
        break;
    case 11:
        SetRange.m_RangeIndex =Range_4;
        break;
    case 12:
        SetRange.m_RangeIndex =Range_6;
        break;
    case 13:
        SetRange.m_RangeIndex =Range_8;
        break;
    case 14:
        SetRange.m_RangeIndex =Range_12;
        break;
    case 15:
        SetRange.m_RangeIndex =Range_16;
        break;
    case 16:
        SetRange.m_RangeIndex =Range_24;
        break;
    default:
        SetRange.m_RangeIndex =Range_1_32;
        break;
    }
    SetRange.m_Channel=0;
    m_udpSocket2->writeDatagram((char*)&SetRange,sizeof(SetRange),ncip,2575);
    SetRange.m_Channel=1;
    m_udpSocket2->writeDatagram((char*)&SetRange,sizeof(SetRange),ncip,2575);
}
void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    SetTxFrequency_t SetTxFrequency;
    SetTxFrequency.MessageCode=msg_id::SET_TX_FREQ;
    switch (ui->comboBox_2->currentIndex()) {
    case 1:
        SetTxFrequency.Mode =QUANTUM_TX_FREQ_LOW;
        break;
    case 2:
        SetTxFrequency.Mode =QUANTUM_TX_FREQ_HIGH;
        break;
    default:
        SetTxFrequency.Mode =QUANTUM_TX_FREQ_NOMINAL;
        break;
    }
    m_udpSocket2->writeDatagram((char*)&SetTxFrequency,sizeof(SetTxFrequency),ncip,2575);
}
void MainWindow::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    SetInterferenceRejection_t SetInterferenceRejection;
    SetInterferenceRejection.m_MessageCode=msg_id::SET_INTERFERENCE_REJECTION;
    switch (ui->comboBox_3->currentIndex()) {
    case 1:
        SetInterferenceRejection.m_Mode =QUANTUM_INTERFERENCE_REJECTION_MODE_1;
        cout<<"set radar mode:QUANTUM_INTERFERENCE_REJECTION_MODE_1"<<endl;
        break;
    case 2:
        SetInterferenceRejection.m_Mode =QUANTUM_INTERFERENCE_REJECTION_MODE_2;
        cout<<"set radar mode:QUANTUM_INTERFERENCE_REJECTION_MODE_2"<<endl;
        break;
    case 3:
        SetInterferenceRejection.m_Mode =QUANTUM_INTERFERENCE_REJECTION_MODE_3;
        cout<<"set radar mode:QUANTUM_INTERFERENCE_REJECTION_MODE_3"<<endl;
        break;
    case 4:
        SetInterferenceRejection.m_Mode =QUANTUM_INTERFERENCE_REJECTION_MODE_4;
        cout<<"set radar mode:QUANTUM_INTERFERENCE_REJECTION_MODE_4"<<endl;
        break;
    case 5:
        SetInterferenceRejection.m_Mode =QUANTUM_INTERFERENCE_REJECTION_MODE_5;
        cout<<"set radar mode:QUANTUM_INTERFERENCE_REJECTION_MODE_5"<<endl;
        break;
    default:
        SetInterferenceRejection.m_Mode =QUANTUM_INTERFERENCE_REJECTION_MODE_OFF;
        cout<<"set radar mode:QUANTUM_INTERFERENCE_REJECTION_MODE_OFF"<<endl;
        break;
    }
    m_udpSocket2->writeDatagram((char*)&SetInterferenceRejection,sizeof(SetInterferenceRejection),ncip,2575);

}
void MainWindow::on_comboBox_5_currentIndexChanged(const QString &arg1)
{
    SetGainMode_t SetGainMode;
    SetGainMode.m_MessageCode=msg_id::SET_GAIN_MODE;
    switch (ui->comboBox_5->currentIndex()) {
    case 1:
        SetGainMode.m_Mode =QUANTUM_GAIN_MODE_AUTO;
        break;
    default:
        SetGainMode.m_Mode =QUANTUM_GAIN_MODE_MANUAL;
        break;
    }
    SetGainMode.m_Channel=0;
    m_udpSocket2->writeDatagram((char*)&SetGainMode,sizeof(SetGainMode),ncip,2575);
    SetGainMode.m_Channel=1;
    m_udpSocket2->writeDatagram((char*)&SetGainMode,sizeof(SetGainMode),ncip,2575);
}
void MainWindow::on_comboBox_6_currentIndexChanged(const QString &arg1)
{
    SetColourGainMode_t SetColourGainMode;
    SetColourGainMode.m_MessageCode=msg_id::SET_COLOUR_GAIN_MODE;
    switch (ui->comboBox_6->currentIndex()) {
    case 1:
        SetColourGainMode.m_Mode =QUANTUM_COLOUR_GAIN_MODE_AUTO;
        break;
    default:
        SetColourGainMode.m_Mode =QUANTUM_COLOUR_GAIN_MODE_MANUAL;
        break;
    }
    SetColourGainMode.m_Channel=0;
    m_udpSocket2->writeDatagram((char*)&SetColourGainMode,sizeof(SetColourGainMode),ncip,2575);
    SetColourGainMode.m_Channel=1;
    m_udpSocket2->writeDatagram((char*)&SetColourGainMode,sizeof(SetColourGainMode),ncip,2575);
}
void MainWindow::on_comboBox_7_currentIndexChanged(const QString &arg1)
{
    SetSeaMode_t SetSeaMode;
    SetSeaMode.m_MessageCode=msg_id::SET_SEA_MODE;
    switch (ui->comboBox_7->currentIndex())
    {
    case 1:
        SetSeaMode.m_Mode =QUANTUM_SEA_MODE_AUTO;
        break;
    default:
        SetSeaMode.m_Mode =QUANTUM_SEA_MODE_MANUAL;
        break;
    }
    SetSeaMode.m_Channel=0;
    m_udpSocket2->writeDatagram((char*)&SetSeaMode,sizeof(SetSeaMode),ncip,2575);
    SetSeaMode.m_Channel=1;
    m_udpSocket2->writeDatagram((char*)&SetSeaMode,sizeof(SetSeaMode),ncip,2575);
}
void MainWindow::on_comboBox_8_currentIndexChanged(const QString &arg1)
{
    SetRainMode_t SetRainMode;
    SetRainMode.m_MessageCode=msg_id::SET_RAIN_MODE;
    switch (ui->comboBox_8->currentIndex()) {
    case 1:
        SetRainMode.m_Mode =QUANTUM_RAIN_MODE_MANUAL;
        break;
    default:
        SetRainMode.m_Mode =QUANTUM_RAIN_MODE_OFF;
        break;
    }
    SetRainMode.m_Channel=0;
    m_udpSocket2->writeDatagram((char*)&SetRainMode,sizeof(SetRainMode),ncip,2575);
    SetRainMode.m_Channel=1;
    m_udpSocket2->writeDatagram((char*)&SetRainMode,sizeof(SetRainMode),ncip,2575);
}
void MainWindow::on_comboBox_9_currentIndexChanged(const QString &arg1)
{
    SetTargetExpansion TargetExpansion;
    TargetExpansion.m_MessageCode=msg_id::SET_TARGET_EXPANSION;
    switch (ui->comboBox_9->currentIndex()) {
    case 1:
        TargetExpansion.m_Mode =QUANTUM_TARGET_EXPANSION_MODE_ON;
        break;
    default:
        TargetExpansion.m_Mode =QUANTUM_TARGET_EXPANSION_MODE_OFF;
        break;
    }
    TargetExpansion.m_Channel=0;
    m_udpSocket2->writeDatagram((char*)&TargetExpansion,sizeof(TargetExpansion),ncip,2575);
    TargetExpansion.m_Channel=1;
    m_udpSocket2->writeDatagram((char*)&TargetExpansion,sizeof(TargetExpansion),ncip,2575);
}
void MainWindow::on_comboBox_10_currentIndexChanged(const QString &arg1)
{
    SetClutterCurve_t SetClutterCurve;
    SetClutterCurve.m_MessageCode=msg_id::SET_SEA_CLUTTER_CURVE;
    switch (ui->comboBox_10->currentIndex()) {
    case 1:
        SetClutterCurve.m_SeaClutterCurve =1;
        break;
    default:
        SetClutterCurve.m_SeaClutterCurve =0;
        break;
    }
    SetClutterCurve.m_Channel=0;
    m_udpSocket2->writeDatagram((char*)&SetClutterCurve,sizeof(SetClutterCurve),ncip,2575);
    SetClutterCurve.m_Channel=1;
    m_udpSocket2->writeDatagram((char*)&SetClutterCurve,sizeof(SetClutterCurve),ncip,2575);
}
void MainWindow::on_comboBox_11_currentIndexChanged(const QString &arg1)
{
    SetPresetMode_t SetPresetMode;
    SetPresetMode.MessageCode=msg_id::SET_PRESET_MODE;
    switch (ui->comboBox_11->currentIndex()) {
    case 1:
        SetPresetMode.Mode =1;
        break;
    case 2:
        SetPresetMode.Mode =2;
        break;
    case 3:
        SetPresetMode.Mode =3;
        break;
    default:
        SetPresetMode.Mode =0;
        break;
    }
    SetPresetMode.Channel=0;
    m_udpSocket2->writeDatagram((char*)&SetPresetMode,sizeof(SetPresetMode),ncip,2575);
    SetPresetMode.Channel=1;
    m_udpSocket2->writeDatagram((char*)&SetPresetMode,sizeof(SetPresetMode),ncip,2575);
}

void MainWindow::on_pushButton_clicked()
{
    QDir dir;
    if (!dir.exists(dir_str))
    {
        bool res = dir.mkpath(dir_str);
        qDebug() << "新建目录是否成功" << res;
    }
    QImage savepm1= cvMatToQImage(radar_img);
    QImage savepm2= cvMatToQImage(radar_img_final);
    QImage savepm3= cvMatToQImage(radarcolorimg);
    QDateTime time = QDateTime::currentDateTime();  //获取当前时间
    int timeT = time.toTime_t();   //将当前时间转为时间戳

    QString file_name1 ="Picture/"+QString::number(timeT)+"_linepolar.png";
    QString file_name2 ="Picture/"+QString::number(timeT)+"_radarimg.png";
    QString file_name3 ="Picture/"+QString::number(timeT)+"_radarcolorimg.png";
    savepm1.save(file_name1);
    savepm2.save(file_name2);
    savepm3.save(file_name3);
}

cv::Mat MainWindow::range_interval(cv::Mat img)
{
    cv::Point img_center(img.cols/2, img.rows/2);
    int font_shift = 25;
    double pixlesize = radar_range*1852/350;
    if(250/pixlesize<350) cv::circle(img,img_center,250/pixlesize,CV_RGB(0,255,0));
    if(500/pixlesize<350) cv::circle(img,img_center,500/pixlesize,CV_RGB(0,255,0));
    if(1000/pixlesize<350) cv::circle(img,img_center,1000/pixlesize,CV_RGB(0,255,0));
    cv::putText(img,"250m ",cv::Point(img_center.x-250/pixlesize-font_shift,img_center.y),cv::FONT_HERSHEY_SIMPLEX,0.3,cv::Scalar(0,0,255));
    cv::putText(img,"500m ",cv::Point(img_center.x-500/pixlesize-font_shift,img_center.y),cv::FONT_HERSHEY_SIMPLEX,0.3,cv::Scalar(0,0,255));
    cv::putText(img,"1000m ",cv::Point(img_center.x-1000/pixlesize-font_shift,img_center.y),cv::FONT_HERSHEY_SIMPLEX,0.3,cv::Scalar(0,0,255));

    return img;
}
void MainWindow::UNIT_INFO_MESSAGE_ID_Precess(QByteArray datagram)
{
    UnitInfo_msg=(UnitInfo_t*)datagram.data();
    ui->lineEdit->setText(QString::number(UnitInfo_msg->UnitType));
    ui->lineEdit_2->setText(QString::number(UnitInfo_msg->NodeID));
    ui->lineEdit_3->setText(QString::number(UnitInfo_msg->SoftwareVersion));
    ui->lineEdit_4->setText(hexip_qhaip(UnitInfo_msg->IPAddress).toString());
    ui->lineEdit_5->setText(QString(QLatin1String(UnitInfo_msg->Name)));
    ui->lineEdit_6->setText(QString::number(UnitInfo_msg->DataLength));
    ui->lineEdit_7->setText(QString::number(UnitInfo_msg->MFDOptions));
    if(timer_flag<5) ui->label_136->setStyleSheet("QLabel{background-color:rgb(0,255,0);}");
    timer_flag=0;
}

void MainWindow::SERVICE_INFO_MESSAGE_ID_Precess(QByteArray datagram)
{
    ServiceInfo_msg=(ServiceInfo_t*)datagram.data();
    if(ServiceInfo_msg->Data.nControlPort==2575) ncip = hexip_qhaip(ServiceInfo_msg->Data.nControlIPAddress);
    if(ServiceInfo_msg->Data.nDataPort==2574) ndip = hexip_qhaip(ServiceInfo_msg->Data.nDataIPAddress);
    ui->lineEdit_8->setText(QString::number(ServiceInfo_msg->Header.nNodeID));
    ui->lineEdit_9->setText(QString::number(ServiceInfo_msg->Header.nServiceID));
    ui->lineEdit_10->setText(QString::number(ServiceInfo_msg->Header.OriginalTransportType));
    ui->lineEdit_11->setText(QString::number(ServiceInfo_msg->Header.nTimeout));
    ui->lineEdit_12->setText(QString::number(ServiceInfo_msg->Header.nInstance));
    ui->lineEdit_13->setText(QString::number(ServiceInfo_msg->Header.nDataLength));
    ui->lineEdit_15->setText(ndip.toString());
    ui->lineEdit_16->setText(QString::number(ndip_port));
    ui->lineEdit_17->setText(ncip.toString());
    ui->lineEdit_14->setText(QString::number(ncip_port));
    //        qDebug()<<ncip<<ndip;
    if(timer_flag<5)
        ui->label_136->setStyleSheet("QLabel{background-color:rgb(0,255,0);}");
    timer_flag=0;
}

void MainWindow::NOTHING_Precess(QByteArray datagram)
{
    if(timer_flag<5)
        ui->label_136->setStyleSheet("QLabel{background-color:rgb(0,255,0);}");
    timer_flag=0;
}

void MainWindow::SPOKE_DATA_Precess(QByteArray datagram)
{
    SpokeData=(SpokeData_t*)datagram.data();
    ui->lineEdit_52->setText(QString::number(SpokeData->Spoke.SpokeHeader.PktHdr.SequenceNumber));
    ui->lineEdit_125->setText(QString::number(SpokeData->Spoke.SpokeHeader.PktHdr.CompressionFormat));
    ui->lineEdit_126->setText(QString::number(SpokeData->Spoke.SpokeHeader.PktHdr.SpokesInPacket));
    ui->lineEdit_127->setText(QString::number(SpokeData->Spoke.SpokeHeader.DataHdr.SamplesPerSpoke));
    ui->lineEdit_128->setText(QString::number(SpokeData->Spoke.SpokeHeader.DataHdr.SpokesPerScan));
    ui->lineEdit_129->setText(QString::number(SpokeData->Spoke.SpokeHeader.DataHdr.BitsPerSample));
    ui->lineEdit_130->setText(QString::number(SpokeData->Spoke.SpokeHeader.DataHdr.Channel));
    ui->lineEdit_131->setText(QString::number(SpokeData->Spoke.SpokeHeader.DataHdr.InstrumentedRange));
    ui->lineEdit_132->setText(QString::number(SpokeData->Spoke.SpokeHeader.DataHdr.Bearing));
}
void MainWindow::SPOKE_DATA_img_Precess(QByteArray datagram)
{
    uint8_t out_data[datagram.size()-20];
    std::vector<uint8_t> data_vector;
    cv::Rect rect;
    SpokeData=(SpokeData_t*)datagram.data();
    memcpy(&out_data, datagram.data()+20, datagram.size()-20);
    data_vector = array2vector(out_data,datagram.size()-20);
    data_vector = RLE_Decoding(data_vector);
    if(global_radar_resolution!=data_vector.size()){
        radar_img = cv::Mat(250, 500, CV_8UC1, cv::Scalar(0));
        global_radar_resolution=data_vector.size();
    }
    memcpy(     radar_img.ptr<uint8_t>() + SpokeData->Spoke.SpokeHeader.DataHdr.Bearing * 500,
                data_vector.data(),
                data_vector.size());
    rect=cv::Rect(0,0,data_vector.size(),250);
    tmp = radar_img(rect);
    cv::resize(tmp, tmp, cv::Size(700, 700));
    cv::linearPolar(tmp, radar_img_final, cv::Point(350, 350), 348,
                    CV_WARP_FILL_OUTLIERS | CV_INTER_LINEAR | CV_WARP_INVERSE_MAP);
    cv::applyColorMap(radar_img_final,radarcolorimg,cv::COLORMAP_JET);

    pm= cvMatToQImage(range_interval(radarcolorimg));
    pm = pm.scaled(ui->label_20->width(), ui->label_20->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_20->setPixmap(QPixmap::fromImage(pm));
    ui->label_20->show();
}

void MainWindow::TARGET_STATUS_Precess(QByteArray datagram)
{
    targetstatus = (MarpaTargetStatus_t*)datagram.data();
    ui->lineEdit_18->setText(QString::number(targetstatus->m_TargetData.m_ID));
    ui->lineEdit_19->setText(QString::number(targetstatus->m_TargetData.m_TargetType));
    ui->lineEdit_20->setText(bool2qstring(targetstatus->m_TargetData.m_AutoAcquisition));
    ui->lineEdit_21->setText(bool2qstring(targetstatus->m_TargetData.m_Valid));
    ui->lineEdit_22->setText(QString::number(targetstatus->m_TargetData.m_Distance));
    ui->lineEdit_23->setText(QString::number(targetstatus->m_TargetData.m_Bearing));
    ui->lineEdit_24->setText(QString::number(targetstatus->m_TargetData.m_TrueBearing));
    ui->lineEdit_25->setText(QString::number(targetstatus->m_TargetData.m_Speed));
    ui->lineEdit_26->setText(QString::number(targetstatus->m_TargetData.m_Course));
    ui->lineEdit_27->setText(QString::number(targetstatus->m_TargetData.m_TargetSpeed));
    ui->lineEdit_28->setText(QString::number(targetstatus->m_TargetData.m_TargetCourse));
    ui->lineEdit_29->setText(QString::number(targetstatus->m_TargetData.m_ClosestPointOfApproach));
    ui->lineEdit_30->setText(QString::number(targetstatus->m_TargetData.m_TimeToClosestApproach));
    ui->lineEdit_31->setText(QString::number(targetstatus->m_TargetData.m_HeadingAtUpdate));
    ui->lineEdit_32->setText(bool2qstring(targetstatus->m_TargetData.m_TargetGoingTowardsClosestPoint));
    ui->lineEdit_33->setText(bool2qstring(targetstatus->m_TargetData.m_TargetDataValid));
    ui->lineEdit_34->setText(bool2qstring(targetstatus->m_TargetData.m_DangerAlarmActive));
}

void MainWindow::ATTRIBUTES_Precess(QByteArray datagram)
{
    Attributes = (Attributes_t*)datagram.data();
    ui->lineEdit_35->setText( getstring(Attributes->m_Attributes.SerialNumber,cQuantumSerialNumberSize));
    ui->lineEdit_36->setText( hexip_qhaip(Attributes->m_Attributes.IpAddress).toString());
    ui->lineEdit_37->setText( getstring(Attributes->m_Attributes.MacAddress,cMacAddressSize));
    ui->lineEdit_38->setText( QString::number(Attributes->m_Attributes.SoftwareVersionMajor));
    ui->lineEdit_39->setText( QString::number(Attributes->m_Attributes.SoftwareVersionMinor));
    ui->lineEdit_40->setText( QString::number(Attributes->m_Attributes.UpdMgrVersionMajor));
    ui->lineEdit_41->setText( QString::number(Attributes->m_Attributes.UpdMgrVersionMinor));
    ui->lineEdit_42->setText( QString::number(Attributes->m_Attributes.BootVersionMajor));
    ui->lineEdit_43->setText( QString::number(Attributes->m_Attributes.BootVersionMinor));
    ui->lineEdit_44->setText( QString::number(Attributes->m_Attributes.FpgaVersionMajor));
    ui->lineEdit_45->setText( QString::number(Attributes->m_Attributes.FpgaVersionMinor));
    ui->lineEdit_53->setText( QString::number(Attributes->m_Attributes.PsuAppVersionMajor));
    ui->lineEdit_54->setText( QString::number(Attributes->m_Attributes.PsuAppVersionMinor));
    ui->lineEdit_46->setText( QString::number(Attributes->m_Attributes.PsuUpdMgrVersionMajor));
    ui->lineEdit_47->setText( QString::number(Attributes->m_Attributes.PsuUpdMgrVersionMinor));

    ui->lineEdit_48->setText( QString::number(Attributes->m_Attributes.PsuBootVersionMajor));
    ui->lineEdit_49->setText( QString::number(Attributes->m_Attributes.PsuBootVersionMinor));
    ui->lineEdit_50->setText( QString::number(Attributes->m_Attributes.WiFiVersionMajor));
    ui->lineEdit_51->setText( QString::number(Attributes->m_Attributes.WiFiVersionMinor));
    ui->lineEdit_55->setText( QString::number(Attributes->m_Attributes.CurrentSignalStrength));
    ui->lineEdit_56->setText( QString::number(Attributes->m_Attributes.StatusCode));
    ui->lineEdit_57->setText( QString::number(Attributes->m_Attributes.PowerDownCode));
    ui->lineEdit_58->setText( QString::number(Attributes->m_Attributes.RotationState));
    ui->lineEdit_59->setText( QString::number(Attributes->m_Attributes.TransmitState));
    ui->lineEdit_60->setText( QString::number(Attributes->m_Attributes.AzimuthZeroOffset));
    ui->lineEdit_61->setText( QString::number(Attributes->m_Attributes.CpuTemp_degCx10));
    ui->lineEdit_62->setText( QString::number(Attributes->m_Attributes.CpuFree));
    ui->lineEdit_63->setText( QString::number(Attributes->m_Attributes.ProdTestBits));
    ui->lineEdit_64->setText( bool2qstring(Attributes->m_Attributes.PriJitter));
    ui->lineEdit_65->setText( getstring(Attributes->m_Attributes.DiagnosticsData,9));
}

void MainWindow::STATUS_Precess(QByteArray datagram)
{
    Status = (Status_t*)datagram.data();
    ui->lineEdit_66->setText(get_radarnode(Status->m_Status.RadarMode));
    ui->label_116->setText(get_radarnode(Status->m_Status.RadarMode));
    ui->lineEdit_67->setText(QString::number(Status->m_Status.Spare));
    ui->lineEdit_68->setText(QString::number(Status->m_Status.StandbyTimeRemainingMins));
    ui->lineEdit_69->setText(QString::number(Status->m_Status.StandbyTimeRemainingSecs));
    ui->lineEdit_70->setText(QString::number(Status->m_Status.StandbyTime_Mins));
    ui->lineEdit_71->setText(QString::number(Status->m_Status.TransmitCount_Scans));
    ui->lineEdit_72->setText(get_QUANTUM_TX_FREQ(Status->m_Status.TxFreq));
    ui->label_117->setText(get_QUANTUM_TX_FREQ(Status->m_Status.TxFreq));
    ui->lineEdit_73->setText(bool2qstring(Status->m_Status.DualRangeMode));
    ui->lineEdit_74->setText(QString::number(Status->m_Status.ScannerSpeed));
    ui->lineEdit_75->setText(QString::number(Status->m_Status.BearingAlignment));
    ui->lineEdit_76->setText(QString::number(Status->m_Status.GuardZoneSensitivity));
    ui->lineEdit_77->setText(get_QUANTUM_INTERFERENCE_REJECTION_MODE(Status->m_Status.InterferenceRejectionMode));
    ui->label_118->setText(get_QUANTUM_INTERFERENCE_REJECTION_MODE(Status->m_Status.InterferenceRejectionMode));
    ui->lineEdit_78->setText(bool2qstring(Status->m_Status.StcEnable));
    ui->lineEdit_79->setText(bool2qstring(Status->m_Status.FtcEnable));

    ui->lineEdit_87->setText(QString::number(get_Range(Status->m_Status.RangeInfo[0].RangeIndex)));//+" n mile");
    radar_range = get_Range(Status->m_Status.RangeInfo[0].RangeIndex);
    ui->lineEdit_88->setText( get_QUANTUM_PRESET_MODE(Status->m_Status.RangeInfo[0].PresetMode));
    ui->lineEdit_89->setText(get_QUANTUM_TARGET_EXPANSION_MODE(Status->m_Status.RangeInfo[0].TargetExpansionMode));
    ui->lineEdit_90->setText(get_QuantumSeaClutterCurve(Status->m_Status.RangeInfo[0].SeaCurve));
    ui->lineEdit_91->setText(QString::number(Status->m_Status.RangeInfo[0].ZeroRange));
    ui->lineEdit_92->setText(QString::number(Status->m_Status.RangeInfo[0].STCKnee));
    ui->lineEdit_93->setText(get_QuantumMainBangSuppression(Status->m_Status.RangeInfo[0].MainBangSuppression));
    QUANTUM_PRESET_DATA = Status->m_Status.RangeInfo[0].PresetData;
    ui->lineEdit_94->setText(get_QUANTUM_MODE(QUANTUM_PRESET_DATA->GainMode));
    ui->lineEdit_95->setText(QString::number(QUANTUM_PRESET_DATA->GainValue));
    ui->lineEdit_96->setText(get_QUANTUM_MODE(QUANTUM_PRESET_DATA->ColourGainMode));
    ui->lineEdit_97->setText(QString::number(QUANTUM_PRESET_DATA->ColourGainValue));
    ui->lineEdit_98->setText(get_QUANTUM_MODE(QUANTUM_PRESET_DATA->SeaClutterMode));
    ui->lineEdit_99->setText(QString::number(QUANTUM_PRESET_DATA->SeaClutterValue));
    ui->lineEdit_100->setText(get_QUANTUM_MODE(QUANTUM_PRESET_DATA->RainClutterMode));
    ui->lineEdit_101->setText(QString::number(QUANTUM_PRESET_DATA->RainClutterValue));

    ui->lineEdit_120->setText(QString::number(get_Range(Status->m_Status.RangeInfo[1].RangeIndex))+" n mile");
    ui->label_119->setText(QString::number(get_Range(Status->m_Status.RangeInfo[1].RangeIndex)));//+" n mile");
    ui->lineEdit_122->setText(get_QUANTUM_PRESET_MODE(Status->m_Status.RangeInfo[1].PresetMode));
    ui->label_135->setText(get_QUANTUM_PRESET_MODE(Status->m_Status.RangeInfo[1].PresetMode));
    ui->lineEdit_119->setText(get_QUANTUM_TARGET_EXPANSION_MODE(Status->m_Status.RangeInfo[1].TargetExpansionMode));
    ui->label_120->setText(get_QUANTUM_TARGET_EXPANSION_MODE(Status->m_Status.RangeInfo[1].TargetExpansionMode));
    ui->lineEdit_124->setText(get_QuantumSeaClutterCurve(Status->m_Status.RangeInfo[1].SeaCurve));
    ui->label_125->setText(get_QuantumSeaClutterCurve(Status->m_Status.RangeInfo[1].SeaCurve));
    ui->lineEdit_121->setText(QString::number(Status->m_Status.RangeInfo[1].ZeroRange));
    ui->lineEdit_118->setText(QString::number(Status->m_Status.RangeInfo[1].STCKnee));
    ui->lineEdit_123->setText(get_QuantumMainBangSuppression(Status->m_Status.RangeInfo[1].MainBangSuppression));

    QUANTUM_PRESET_DATA = Status->m_Status.RangeInfo[1].PresetData;
    ui->lineEdit_104->setText(get_QUANTUM_MODE(QUANTUM_PRESET_DATA->GainMode));
    ui->label_159->setText(get_QUANTUM_MODE(QUANTUM_PRESET_DATA->GainMode));
    ui->lineEdit_107->setText(QString::number(QUANTUM_PRESET_DATA->GainValue));
    ui->lineEdit_111->setText(QString::number(QUANTUM_PRESET_DATA->GainValue));
    ui->lineEdit_106->setText(get_QUANTUM_MODE(QUANTUM_PRESET_DATA->ColourGainMode));
    ui->label_122->setText(get_QUANTUM_MODE(QUANTUM_PRESET_DATA->ColourGainMode));
    ui->lineEdit_102->setText(QString::number(QUANTUM_PRESET_DATA->ColourGainValue));
    ui->lineEdit_113->setText(QString::number(QUANTUM_PRESET_DATA->ColourGainValue));
    ui->lineEdit_105->setText(get_QUANTUM_MODE(QUANTUM_PRESET_DATA->SeaClutterMode));
    ui->label_123->setText(get_QUANTUM_MODE(QUANTUM_PRESET_DATA->SeaClutterMode));
    ui->lineEdit_108->setText(QString::number(QUANTUM_PRESET_DATA->SeaClutterValue));
    ui->lineEdit_115->setText(QString::number(QUANTUM_PRESET_DATA->SeaClutterValue));
    ui->lineEdit_103->setText(get_QUANTUM_MODE(QUANTUM_PRESET_DATA->RainClutterMode));
    ui->label_124->setText(get_QUANTUM_MODE(QUANTUM_PRESET_DATA->RainClutterMode));
    ui->lineEdit_109->setText(QString::number(QUANTUM_PRESET_DATA->RainClutterValue));
    ui->lineEdit_117->setText(QString::number(QUANTUM_PRESET_DATA->RainClutterValue));
    ui->lineEdit_80->setText(getstring(Status->m_Status.CustomRanges,QUANTUM_MAX_RANGES));

    //        ui->lineEdit_81->setText(QString::number(Status->m_Status.GuardZone));
    //        ui->lineEdit_82->setText(QString::number(Status->m_Status.BlankSector));
    //        ui->lineEdit_83->setText(QString::number(Status->m_Status.AutoAcquireZone));
}
