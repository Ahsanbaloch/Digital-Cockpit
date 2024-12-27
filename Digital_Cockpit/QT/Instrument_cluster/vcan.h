#ifndef VCAN_H
#define VCAN_H

#include <QObject>
#include <QCanBus>
#include <QDebug>

#include <deque>
#include <numeric>

#include <QCanBusFrame>
// #include <CommonAPI/CommonAPI.hpp>
// #include <v1/org/example/canservice/CANServiceSomeIPProxy.hpp>
#include <vsomeip.hpp>
#include <v1/org/example/canservice/CANServiceProxy.hpp>
// #include "../../../IPC_Service/middleware/src-gen/v1/org/example/canservice/CANServiceProxy.hpp"



class vcan : public QObject
{
        Q_OBJECT
        Q_PROPERTY(int framePayload READ framePayload NOTIFY framePayloadChanged)
    public:
        // vcan();
        explicit vcan(QObject *parent = nullptr);
        ~vcan();

        int framePayload() const;
        void initializeSomeIpClient();
        void onServiceRegistered();
        void requestService();

    signals:
        void framePayloadChanged();

    private slots:
        void clearSpeedBuffer();
    
    private:
        std::deque<int> m_speedBuffer;
        static const int BUFFER_SIZE = 5;
        std::shared_ptr<vsomeip::application> _app;
        void onCANDataReceived(const std::shared_ptr<vsomeip::message>& msg);

};

#endif // VCAN_H

