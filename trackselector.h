#pragma once

#include <QObject>
#include <vector>

#include "randomnoiseelement.h"


class TrackSelector
{
public:
    TrackSelector(std::vector<RandomNoiseElement>& randomNoises);

    void reset(uint32_t category);
    uint32_t current();
    uint32_t next();
    uint32_t previous();

private:
    std::vector<RandomNoiseElement>& m_randomNoises;
    std::vector<std::pair<uint32_t, uint32_t>> m_tracklist;
    uint32_t m_currentCategory;
    uint32_t m_currentTrack;
};
