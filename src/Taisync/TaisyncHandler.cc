/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "TaisyncHandler.h"
#include "SettingsManager.h"
#include "QGCApplication.h"
#include "VideoManager.h"


QGC_LOGGING_CATEGORY(TaisyncLog,     "TaisyncLog")
QGC_LOGGING_CATEGORY(TaisyncVerbose, "TaisyncVerbose")

//-----------------------------------------------------------------------------
TaisyncHandler::TaisyncHandler(QObject* parent)
    : QObject (parent)
{
}

//-----------------------------------------------------------------------------
TaisyncHandler::~TaisyncHandler()
{
    close();
}

//-----------------------------------------------------------------------------
void
TaisyncHandler::close()
{
    if(_tcpSocket) {
        qCDebug(TaisyncLog) << "Close Taisync TCP";
        _tcpSocket->close();
        _tcpSocket->deleteLater();
        _tcpSocket = nullptr;
    }
}

//-----------------------------------------------------------------------------
bool
TaisyncHandler::_start(uint16_t port, QHostAddress addr)
{
    close();
    _serverMode = addr == QHostAddress::AnyIPv4;
    if(_serverMode) {
        qCDebug(TaisyncLog) << "Listen for Taisync TCP on port" << port;
        _tcpServer = new QTcpServer(this);
        QObject::connect(_tcpServer, &QTcpServer::newConnection, this, &TaisyncHandler::_newConnection);
        _tcpServer->listen(QHostAddress::AnyIPv4, port);
    } else {
        _tcpSocket = new QTcpSocket();
        QObject::connect(_tcpSocket, &QIODevice::readyRead, this, &TaisyncHandler::_readBytes);
        qCDebug(TaisyncLog) << "Connecting to" << addr;
        _tcpSocket->connectToHost(addr, port);
        if (!_tcpSocket->waitForConnected(1000)) {
            close();
            return false;
        }
        emit connected();
    }
    return true;
}

//-----------------------------------------------------------------------------
void
TaisyncHandler::_newConnection()
{
    qCDebug(TaisyncLog) << "New Taisync TCP Connection";
    if(_tcpSocket) {
        _tcpSocket->close();
        _tcpSocket->deleteLater();
    }
    _tcpSocket = _tcpServer->nextPendingConnection();
    QObject::connect(_tcpSocket, &QIODevice::readyRead, this, &TaisyncHandler::_readBytes);
    emit connected();
}

//-----------------------------------------------------------------------------
void
TaisyncHandler::_socketDisconnected()
{
    qCDebug(TaisyncLog) << "Taisync Telemetry Connection Closed";
    if(_tcpSocket) {
        _tcpSocket->close();
        _tcpSocket->deleteLater();
        _tcpSocket = nullptr;
    }
}