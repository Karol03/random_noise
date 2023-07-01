#include "randomnoise.h"

#include <QRandomGenerator>
#include <QDesktopServices>
#include <QUrl>

#include "trackdownloader.h"
#include "categoriesdownloader.h"


RandomNoise::RandomNoise()
    : m_trackSelector{m_randomNoises}
    , m_position{0}
    , m_trackPosition{0}
    , m_status{}
    , m_tracks{nullptr}
    , m_categories{new CategoriesDownloader(m_randomNoises)}
{
    connect(m_categories, &CategoriesDownloader::error,
            this, [&](QString what) {
                status(std::move(what));
            });
    connect(m_categories, &CategoriesDownloader::success,
            this, [&]() {
                delete m_categories;
                m_categories = nullptr;
                randomNoise("");
            });
}

void RandomNoise::randomNoise(QString)
{
    if (m_categories)
    {
        status("Fetching the category list...");
        m_categories->download();
    }
    else if (!m_randomNoises.empty())
    {
        m_position = QRandomGenerator::global()->bounded(0u, m_randomNoises.size());
        m_trackSelector.reset(m_position);

        status("");
        emit randomNoiseChanged();

        fetchTrackList();
    }
    else
    {
        status("No categories found");
    }
}

void RandomNoise::status(QString data)
{
    if (m_status != data)
    {
        m_status = data;
        emit statusChanged();
    }
}

bool RandomNoise::fetchTrackList()
{
    if (m_randomNoises.empty())
    {
        m_trackPosition = UINT32_MAX;
        randomNoise("");
        return false;
    }
    else if (!m_tracks && m_randomNoises[m_position].tracks.empty())
    {
        status("Downloading " + m_randomNoises[m_position].genre + " track list");
        m_trackPosition = 0;
        m_tracks = new TrackDownloader(m_randomNoises[m_position].tracks,
                                       m_randomNoises[m_position].playlist,
                                       m_randomNoises[m_position].ref);
        connect(m_tracks, &TrackDownloader::error,
                this, [&](QString what) {
                    status(std::move(what));
                    delete m_tracks;
                    m_tracks = nullptr;
                });
        connect(m_tracks, &TrackDownloader::success,
                this, [&]() {
                    status("Downloaded " + QString::number(m_randomNoises[m_position].tracks.size()) + " tracks");
                    m_trackSelector.reset(m_position);
                    openSpotify();
                    delete m_tracks;
                    m_tracks = nullptr;
                });
        m_tracks->download();
        return false;
    }
    return !m_randomNoises[m_position].tracks.empty();
}

void RandomNoise::openSpotify()
{
    if (m_position < m_randomNoises.size() && !m_randomNoises[m_position].playlist.isEmpty())
    {
        QDesktopServices::openUrl(QUrl("spotify:playlist/" + m_randomNoises[m_position].playlist, QUrl::TolerantMode));
    }
}
