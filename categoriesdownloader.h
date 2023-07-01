#pragma once

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <atomic>

#include "randomnoiseelement.h"


class CategoriesDownloader : public QObject
{
    Q_OBJECT

public:
    CategoriesDownloader(std::vector<RandomNoiseElement>& output);

    void download();

signals:
    void error(QString);
    void success();

private:
    void parse(QString reply);
    QString getRidOfHtmlSymbols(QString value);

private:
    QNetworkAccessManager* m_manager;
    QNetworkRequest m_request;
    std::vector<RandomNoiseElement>& m_output;
    std::atomic_bool m_isOngoing;
};
