#include "GeoportailLink.h"

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>

GeoportailLink::GeoportailLink() {
    qDebug() << "contr";

    request = *new QNetworkRequest(QUrl("http://url"));
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");
    _qnam = new QNetworkAccessManager(this);
    QObject::connect(_qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(Managerfinished(QNetworkReply*)));
}

GeoportailLink::~GeoportailLink()
{
    delete _qnam;
}

void GeoportailLink::requestGeo(QString req) {
    qDebug() << "start";

    request.setUrl(QUrl("https://wxs.ign.fr/" + APIkey + "/geoportail/wfs?" + req));
    _qnam->get(request);
}

void GeoportailLink::Managerfinished(QNetworkReply* reply) {
    emit finished(reply);
}
