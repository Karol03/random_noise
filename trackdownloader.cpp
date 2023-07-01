#include "trackdownloader.h"


TrackDownloader::TrackDownloader(std::vector<RandomTrackElement>& output,
                                 QString& playlistLink,
                                 QString reflink)
    : m_manager{nullptr}
    , m_request{}
    , m_output{output}
    , m_playlistLink{playlistLink}
    , m_isOngoing{false}
{
    m_request.setUrl(QUrl("https://everynoise.com/" + reflink));
}

void TrackDownloader::download()
{
    if (m_output.empty() && !m_isOngoing.exchange(true))
    {
        m_manager = new QNetworkAccessManager();
        QObject::connect(m_manager, &QNetworkAccessManager::finished,
                         this, [=](QNetworkReply *reply) {
                             if (reply->error())
                             {
                                 emit error("[ERR] Tracks: " + QString::number(reply->error()) + ": " + reply->errorString());
                             }
                             else
                             {
                                 parse(reply->readAll());
                             }
                         });
        m_manager->get(m_request);
    }
}

void TrackDownloader::parse(QString reply)
{
    constexpr const char* ITEM_BEGIN = "<div id=item";
    constexpr const char* BEGIN_DELIM = "preview_url=\"";
    constexpr const char* END_DELIM = "\"";

    m_output.clear();
    for (const auto& line : reply.split("\n"))
    {
        if (line.startsWith(ITEM_BEGIN))
        {
            auto list = line.split("&quot;");
            if (list.size() > 5)
            {
                auto begPos = list[list.size() - 1].indexOf(BEGIN_DELIM) + strlen(BEGIN_DELIM);
                auto endPos = list[list.size() - 1].indexOf(END_DELIM, begPos);

                if (m_playlistLink.isEmpty())
                {
                    auto bIdx = reply.indexOf("com/playlist/");
                    if (bIdx != -1)
                    {
                        bIdx += strlen("com/playlist/");
                        auto eIdx = reply.indexOf("\"", bIdx);
                        if (eIdx != -1)
                            m_playlistLink = reply.mid(bIdx, eIdx - bIdx);
                    }
                }

                m_output.push_back(
                    RandomTrackElement{list[1],
                                       getRidOfHtmlSymbols(list[3]),
                                       getRidOfHtmlSymbols(list[5]),
                                       list[0].mid(begPos, endPos - begPos)});
            }
        }
    }

    if (m_output.size()) {
        emit success();
    } else {
        emit error("No tracks found");
    }
}

QString TrackDownloader::getRidOfHtmlSymbols(QString value)
{
    return value.replace("&lt;", "<")
        .replace("&gt;", ">")
        .replace("&amp;", "&")
        .replace("&apos;", "'");
}
