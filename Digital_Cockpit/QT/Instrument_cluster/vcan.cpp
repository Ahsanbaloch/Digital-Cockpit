#include "vcan.h"

// vcan::vcan() {}

vcan::vcan(QObject *parent): QObject(parent), _app(nullptr)
{
    // initializeSomeIpClient();
}


vcan::~vcan()
{
    if (_app)
    {
        _app->clear_all_handler();
        _app->stop();
    }
   /*  if (m_device)
    {
        m_device->disconnectDevice();
        delete m_device;
    } */
}


int vcan::framePayload() const
{
    // int speed = m_framePayload.toInt();
    // qDebug() << "Value in int" << speed ;
    if (m_speedBuffer.empty())
        return 0;
    //moving average filter
    int averageSpeed = std::accumulate(m_speedBuffer.begin(), m_speedBuffer.end(), 0) / m_speedBuffer.size();

    if (m_speedBuffer.back() < 5)
        return 0;
    return averageSpeed;
    // return std::accumulate(m_speedBuffer.begin(), m_speedBuffer.end(), 0) / m_speedBuffer.size();
}

// export VSOMEIP_CLIENT_CONFIGURATION= /home/ahsan/commonapi-someip/vsomeip/config/vsomeip_client.json


void vcan::clearSpeedBuffer()
{
    m_speedBuffer.clear();
}

//vsomeip
void vcan::initializeSomeIpClient()
{
    try
    {
        _app = vsomeip::runtime::get()->create_application("CANClient", "/home/ahsan/commonapi-someip/vsomeip/config/vsomeip_client.json");

        if (!_app || !_app->init())
            throw std::runtime_error("SOME/IP initialization failed");

        _app->register_state_handler(
            [this](vsomeip::state_type_e state)
            {
                if (state == vsomeip::state_type_e::ST_REGISTERED)
                    this->onServiceRegistered();
            }
        );

        _app->register_message_handler(
            0x1234, 0x5678, 33000,
            [this](const std::shared_ptr<vsomeip::message>& msg) {
                onCANDataReceived(msg);
            }
        );

        _app->register_availability_handler(0x1234, 0x5678,
            [this](vsomeip::service_t service, vsomeip::instance_t instance, bool is_available)
            {
                qDebug() << "Service" << service << "instance" << instance << "is" << (is_available ? "available" : "not available");
                if (is_available)
                    this->requestService();
            });
        _app->start();
    }
    catch(const std::exception& e)
    {
        qCritical() << "Exception in initializeSomeIpClient:" << e.what();
        throw;
    }
}

void vcan::onCANDataReceived(const std::shared_ptr<vsomeip::message>& msg) 
{
    auto payload = msg->get_payload();
    
    if (!payload) {
        qDebug() << "Received empty payload.";
        return;
    }

    const vsomeip::byte_t* data = payload->get_data();
    vsomeip::length_t data_length = payload->get_length();

    if (data_length < 4)
    {
        qDebug() << "Payload too small to contain CAN ID.";
        return;
    }

    //Extracing the can_id (first 4 bytes)
    uint32_t can_id = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];

    
    // qDebug() << "Received CAN Data from SOME/IP server:";
    
    //Extract the can Data (remaining bytes)
    QByteArray canData(reinterpret_cast<const char *>(data + 4), static_cast<int>(data_length - 4));
    qDebug() << "Received CAN Data from SOME/IP server:";
    qDebug() << "CAN ID:" << QString("0x%1").arg(can_id, 0, 16);
    qDebug() << "SOME/IP CAN Data:" << canData.toHex();

    int speed = 0;
    for (vsomeip::length_t i = 4; i < data_length; ++i) {
        speed = (speed << 8) | data[i];
    }
    // for (auto byte : *data)
    //     speed = (speed << 8) | byte;


    if (!m_speedBuffer.empty() && std::abs(speed - m_speedBuffer.back()))
        clearSpeedBuffer();
    
    m_speedBuffer.push_back(speed);
    
    if (m_speedBuffer.size() > BUFFER_SIZE)
        m_speedBuffer.pop_front();
    
    emit framePayloadChanged();
}

void vcan::onServiceRegistered() {
    try {
        _app->request_service(0x1234, 0x5678);
        
        std::set<vsomeip::eventgroup_t> groups;
        groups.insert(0x01); // Replace with your actual event group ID
        _app->request_event(0x1234, 0x5678, 33000, groups);
        
        qDebug() << "Service requested and event subscribed";
    } catch (const std::exception& e) {
        qCritical() << "Exception in onServiceRegistered:" << e.what();
    }
}

void vcan::requestService() {
   try {
        vsomeip::eventgroup_t event_group = 0x01; // Replace with your actual event group ID
        _app->subscribe(0x1234, 0x5678, event_group);
        qDebug() << "Subscribed to event group" << event_group;
    } catch (const std::exception& e) {
        qCritical() << "Exception in requestService:" << e.what();
    }
}

