#include "categoriesdownloader.h"


CategoriesDownloader::CategoriesDownloader(std::vector<RandomNoiseElement>& output)
    : m_manager{nullptr}
    , m_request{}
    , m_output{output}
    , m_isOngoing{false}
{
    m_request.setUrl(QUrl("https://everynoise.com/"));
}

void CategoriesDownloader::download()
{
    if (m_output.empty() && !m_isOngoing.exchange(true))
    {
        m_manager = new QNetworkAccessManager();
        QObject::connect(m_manager, &QNetworkAccessManager::finished,
                         this, [=](QNetworkReply *reply) {
                             if (reply->error())
                             {
                                 m_isOngoing = false;
                                 emit error("[ERR] Categories: " + QString::number(reply->error()) + ": " + reply->errorString());
                             }
                             else
                             {
                                 parse(reply->readAll());
                             }
                         });
        m_manager->get(m_request);
    }
}

void CategoriesDownloader::parse(QString reply)
{
    constexpr const char* ITEM_BEGIN = "<div id=item";
    constexpr const char* BEGIN_DELIM = "href=\"";
    constexpr const char* END_DELIM = "\"";

    m_output.clear();
    for (const auto& line : reply.split("\n"))
    {
        if (line.startsWith(ITEM_BEGIN))
        {
            auto list = line.split("&quot;");
            if (list.size() > 4)
            {
                auto begPos = list[list.size() - 1].indexOf(BEGIN_DELIM) + strlen(BEGIN_DELIM);
                auto endPos = list[list.size() - 1].indexOf(END_DELIM, begPos);

                m_output.push_back(
                    RandomNoiseElement{list[list.size() - 1].mid(begPos, endPos - begPos),
                                       getRidOfHtmlSymbols(list[3])});
            }
        }
    }

    if (m_output.size()) {
        emit success();
    } else {
        m_isOngoing = false;
        emit error("Nothing found");
    }
}

QString CategoriesDownloader::getRidOfHtmlSymbols(QString value)
{
    return value.replace("&lt;", "<")
        .replace("&gt;", ">")
        .replace("&amp;", "&")
        .replace("&apos;", "'");
}
