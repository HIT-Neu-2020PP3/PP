#ifndef QWIDGETSERIALTXSPO2_H
#define QWIDGETSERIALTXSPO2_H

#include "qwidgetserialtx.h"

class QWidgetSerialTxSPO2 : public QWidgetSerialTx
{
    Q_OBJECT
public:
    explicit QWidgetSerialTxSPO2(int cycle, const QString &portName,
                             int *source, int sLen, QWidget *parent = nullptr, int pkgLen = 5);
    void sendPkg() override;
    char *packageData() override;

};

#endif // QWIDGETSERIALTXSPO2_H
