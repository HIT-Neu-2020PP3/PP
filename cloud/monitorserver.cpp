#include "monitorserver.h"

MonitorServer::MonitorServer(int maxCon, quint16 port, QWidget *parent): MyTcpServer(maxCon, port)
{

}
