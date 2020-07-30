#ifndef QWIDGETSERIALTXIBP2_H
#define QWIDGETSERIALTXIBP2_H

#include "qwidgetserialtx.h"

class QWidgetSerialTxIBP2 : public QWidgetSerialTx
{
    Q_OBJECT
public:
    explicit QWidgetSerialTxIBP2(int cycle, const QString &portName,
                             int *source, int sLen, QWidget *parent = nullptr, int pkgLen = 5);
    void sendPkg();
    char *packageData() override;

};

#endif // QWIDGETSERIALTXIBP2_H
