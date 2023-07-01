#pragma once

#include <vector>
#include <QString>


struct RandomTrackElement
{
    QString spotifyKey;
    QString author;
    QString title;
    QString previewLink;
};


struct RandomNoiseElement
{
    QString ref;
    QString genre;
    QString playlist;
    std::vector<RandomTrackElement> tracks;
};

