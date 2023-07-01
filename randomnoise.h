#pragma once

#include <QObject>

#include "randomnoiseelement.h"
#include "trackselector.h"


class TrackDownloader;
class CategoriesDownloader;

class RandomNoise : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString randomNoise READ randomNoise WRITE randomNoise NOTIFY randomNoiseChanged)
    Q_PROPERTY(QString status READ status WRITE status NOTIFY statusChanged)

public:
    RandomNoise();

    Q_INVOKABLE void openSpotify();

    void randomNoise(QString);
    QString randomNoise() const { return m_position < m_randomNoises.size() ? m_randomNoises[m_position].genre : ""; }

    void status(QString data);
    QString status() const { return m_status; }

signals:
    void statusChanged();
    void randomNoiseChanged();
    void trackAuthorChanged();
    void trackTitleChanged();

private:
    bool fetchTrackList();

private:
    std::vector<RandomNoiseElement> m_randomNoises;
    TrackSelector m_trackSelector;
    uint32_t m_position;
    uint32_t m_trackPosition;
    QString m_status;
    TrackDownloader* m_tracks;
    CategoriesDownloader* m_categories;
};
