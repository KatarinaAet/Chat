#include <QString>
#include <QtTest>
#include "../SpoChat/clientlist.h"
#include "../SpoChat/udpclient.h"
#include "../SpoChat/udpserver.h"
#include "../SpoChat/clienttag.h"

class SpoChatTestTest : public QObject
{
    Q_OBJECT

public:
    SpoChatTestTest();
    ClientTag *_clientTag, *_clientTag2;
    ClientList _list;

private Q_SLOTS:
    void clientTag_InitializeList();
    void clientList_printClient();
    void clientList_refreshList();
};

SpoChatTestTest::SpoChatTestTest()
{

}

void SpoChatTestTest::clientTag_InitializeList()
{
    _clientTag = new ClientTag(this);
    _clientTag->setName("Ekaterina");
    _clientTag->setIp("192.168.0.163");
    _clientTag->setPort(45000);
    _clientTag->setUuid("0");
    _clientTag->setTime(QTime::currentTime().toString());
    _clientTag2 = new ClientTag(this);
    _clientTag2->setName("Ekaterina2");
    _clientTag2->setIp("192.168.0.164");
    _clientTag2->setPort(45000);
    _clientTag2->setUuid("1");
    _clientTag2->setTime(QTime::currentTime().toString());
    QCOMPARE(QString(_clientTag->getIp()), QString("192.168.0.163"));
    QCOMPARE(QString(_clientTag->getName()), QString("Ekaterina"));
    QCOMPARE(QString(_clientTag->getPort()), QString(45000));
    QCOMPARE(QString(_clientTag->getUuid()), QString("0"));
    QCOMPARE(QString(_clientTag2->getIp()), QString("192.168.0.164"));
    QCOMPARE(QString(_clientTag2->getName()), QString("Ekaterina2"));
    QCOMPARE(QString(_clientTag2->getPort()), QString(45000));
    QCOMPARE(QString(_clientTag2->getUuid()), QString("1"));
    QString _time1 = QTime::currentTime().toString();
    _clientTag->setTime(_time1);
    QCOMPARE(_clientTag->getTime(), QString(QTime::currentTime().toString()));
    QCOMPARE(QString(_clientTag->printInfo()), QString("192.168.0.163 Ekaterina 45000 " + _time1));
    QVERIFY2(true, "Failure");
}

void SpoChatTestTest::clientList_printClient()
{

    clientTag_InitializeList();
    QString _time1 = QTime::currentTime().toString();
    _list.slotNewClientTag(_clientTag);
    QCOMPARE(QStringList(_list.printClientList()), QStringList("192.168.0.163 Ekaterina 45000 " + _time1));

    QVERIFY2(true, "Failure");

}

void SpoChatTestTest::clientList_refreshList()
{
    QString _time1 = QTime::currentTime().toString();
    clientTag_InitializeList();
    QTest::qSleep(5*1000);
    QString _time2 = QTime::currentTime().toString();
    _clientTag2->setTime(_time2);
    _list.slotNewClientTag(_clientTag2);
    QStringList expectedRes = {"192.168.0.163 Ekaterina 45000 " + _time1, "192.168.0.164 Ekaterina2 45000 "+ _time2};
    QCOMPARE(QStringList(_list.printClientList()), expectedRes);
    QTest::qSleep(5*1000);
    _list.refreshList();
    QCOMPARE(QStringList(_list.printClientList()), QStringList("192.168.0.164 Ekaterina2 45000 " + _time2));
    QVERIFY2(true, "Failure");

}


QTEST_APPLESS_MAIN(SpoChatTestTest)

#include "tst_spochattesttest.moc"
