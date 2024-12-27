#ifndef VCANWORKER_H
#define VCANWORKER_H

#include <QObject>
#include <vsomeip.hpp>
#include "vcan.h"

class VCanWorker : public QObject
{
    Q_OBJECT
    public:
        explicit VCanWorker(vcan *vc_instance, QObject *parent = nullptr);
        // VCanWorker();
        ~VCanWorker();

    public slots:
        void run();
    
    signals:
        void finished(); // Signal to indicate completion
        void error(const QString &errorString); // Signal for error

    private:
        // std::shared_ptr<vsomeip::application> _app;
        vcan *m_vcan;
};

#endif // VCANWORKER_H
