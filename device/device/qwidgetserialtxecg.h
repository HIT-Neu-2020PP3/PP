#ifndef QWIDGETSERIALTXECG_H
#define QWIDGETSERIALTXECG_H

#include "qwidgetserialtx.h"

class QWidgetSerialTxEcg : public QWidgetSerialTx
{
    Q_OBJECT
public:
    explicit QWidgetSerialTxEcg(int cycle, const QString &portName,
                             int *source, int sLen, QWidget *parent = nullptr, int pkgLen = 10);
    void sendPkg() override;
    char *packageData() override;
};

#endif // QWIDGETSERIALTXECG_H
