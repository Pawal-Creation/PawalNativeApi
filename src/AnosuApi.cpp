#include <pawal/AnosuApi.hpp>

#include <new>
#include <cstdio>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>

pawal::AnosuApi::AnosuApi()
    :anosuClient_()
    ,path_("/pixiv/direct?r18=1")
    ,redirectMap_()
{
    this->anosuClient_.reset(new (std::nothrow) httplib::Client{"https://image.anosu.top"});
    if(!this->anosuClient_)
    {
        throw std::bad_alloc{};
    }
}

pawal::AnosuApi &pawal::AnosuApi::operator=(Self &&other) noexcept
{
    if(this != std::addressof(other))
    {
        this->anosuClient_ = std::move(other.anosuClient_);
        this->path_ = std::move(other.path_);
        this->redirectMap_ = std::move(other.redirectMap_);
    }
    return *this;
}

httplib::Client &pawal::AnosuApi::GetRequiredClient(const std::string &domain)
{
    assert(!domain.empty());
    auto ite = this->redirectMap_.find(domain);
    if(ite != this->redirectMap_.end())
    {
        return *ite->second;
    }
    httplib::Client *rawClient{new (std::nothrow) httplib::Client{domain}};
    if(!rawClient)
    {
        throw std::bad_alloc{};
    }
    std::unique_ptr<httplib::Client> client{rawClient};
    this->redirectMap_.emplace(domain,std::move(client));
    return *rawClient;
}

std::vector<char> pawal::AnosuApi::LookupImage(const std::string &keyword)
{
    assert(this->anosuClient_);
    assert(!this->path_.empty());
    std::size_t pathSize{this->path_.size()};
    char keywordArg[] = "&keyword=";
    if(!keyword.empty())
    {
        pathSize += sizeof(keywordArg) - 1 + keyword.size();
    }
    std::string realPath;
    realPath.resize(pathSize);
    std::memcpy(const_cast<char *>(realPath.data()),this->path_.data(),this->path_.size());
    if(!keyword.empty())
    {
        std::memcpy(const_cast<char *>(realPath.data()) + this->path_.size(),keywordArg,sizeof(keywordArg) - 1);
        std::memcpy(const_cast<char *>(realPath.data()) + this->path_.size() + sizeof(keywordArg) - 1,keyword.data(),keyword.size());
    }
    std::vector<char> image;
    httplib::Result result{this->anosuClient_->Get(realPath)};
    if(!result)
    {
        throw pawal::ApiError{"Fail to invoke anosu restful api"};
    }
    if(result->status == 200)
    {
        return image;
    }
    if(result->status != 302)
    {
        throw pawal::ApiError{"Should redirect to a new host, but not"};
    }
    static const std::string locationHeader{"Location"};
    static const std::string contentTypeHeader{"Content-Type"};
    if (!result->has_header(locationHeader))
    {
        throw pawal::ApiError{"Should redirect to a new host, but not"};
    }
    const std::string &location{result->get_header_value(locationHeader)};
    std::string domain{pawal::StringTool::GetHttpDomainFromUrl(location)};
    httplib::Client &client{this->GetRequiredClient(domain)};
    std::string format{domain};
    format.append("%s");
    std::string path;
    path.resize(location.size() - domain.size());
    if(std::sscanf(location.data(),format.data(),const_cast<char*>(path.data())) != 1)
    {
        throw pawal::ApiError{"Fail to get path from url"};
    }
    result = client.Get(path);
    if(!result)
    {
        throw pawal::ApiError{"Fail to invoke anosu restful api"};
    }
    if(result->status != 200)
    {
        throw pawal::ApiError{"Unexcepted status code"};
    }
    if(!result->has_header(contentTypeHeader))
    {
        throw pawal::ApiError{"Cannot get Content-Type header"};
    }
    const std::string &contentType{result->get_header_value(contentTypeHeader)};
    if(pawal::StringTool::StartWith(contentType,"image"))
    {
        image.assign(result->body.begin(),result->body.end());
        return image;   
    }
    return image;
}