#include "vcanworker.h"

// VCanWorker::VCanWorker() {}

VCanWorker::VCanWorker(vcan *vc_instance, QObject *parent) : QObject(parent), m_vcan(vc_instance) {
}

VCanWorker::~VCanWorker() {
}

void VCanWorker::run() {
    try {
        m_vcan->initializeSomeIpClient();
        qDebug() << "VCAN Initialize Successfully";
        emit finished(); // Emit finished when done
    } catch (const std::exception &e) {
        emit error(e.what()); // Emit error if initialization fails
    }
}