#ifndef IDGENERATOR_H
#define IDGENERATOR_H
#include <QObject>
#include <QStringList>

class IdGenerator : public QObject
{
    Q_OBJECT
public:
    explicit IdGenerator(QObject *parent=0);
    ~IdGenerator(){}
    QString genId();
};

#endif // IDGENERATOR_H
