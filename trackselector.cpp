#include "trackselector.h"

#include <QRandomGenerator>


TrackSelector::TrackSelector(std::vector<RandomNoiseElement>& randomNoises)
    : m_randomNoises{randomNoises}
    , m_tracklist{}
    , m_currentCategory{}
    , m_currentTrack{}
{}

void TrackSelector::reset(uint32_t category)
{
    m_tracklist.clear();
    m_currentCategory = category;
    m_currentTrack = 0;
}

uint32_t TrackSelector::current()
{
    if (m_tracklist.empty())
        return next();

    m_tracklist.resize(m_currentTrack);
    return m_tracklist.back().second;
}

uint32_t TrackSelector::next()
{
    if (m_currentCategory >= m_randomNoises.size() ||
        m_randomNoises[m_currentCategory].tracks.size() <= 0)
        return 0;

    auto nextTrackId = QRandomGenerator::global()->bounded(0u, m_randomNoises[m_currentCategory].tracks.size());
    m_tracklist.resize(m_currentTrack);
    m_tracklist.push_back({m_currentCategory, nextTrackId});
    m_currentTrack = m_tracklist.size();
    return nextTrackId;
}

uint32_t TrackSelector::previous()
{
    if (m_tracklist.size() < m_currentTrack)
        return UINT32_MAX;

    if (m_currentTrack > 1)
        --m_currentTrack;

    return m_tracklist[m_currentTrack - 1].second;
}
