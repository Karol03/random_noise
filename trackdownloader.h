#pragma once

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <atomic>

#include "randomnoiseelement.h"


class TrackDownloader : public QObject
{
    Q_OBJECT

public:
    TrackDownloader(std::vector<RandomTrackElement>& output,
                    QString& playlistLink,
                    QString reflink);

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
    std::vector<RandomTrackElement>& m_output;
    QString& m_playlistLink;
    std::atomic_bool m_isOngoing;
};
