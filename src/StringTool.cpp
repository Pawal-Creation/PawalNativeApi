#include <pawal/StringTool.hpp>

#include <cstdio>

bool pawal::StringTool::StartWith(const std::string &thiz,const std::string &str) noexcept
{
    if(thiz.size() < str.size())
    {
        return false;
    }
    bool result{true};
    for(std::size_t i = 0;i != str.size();++i)
    {
        if(thiz[i] != str[i])
        {
            result = false;
            break;
        }   
    }
    return result;
}

std::string pawal::StringTool::GetHttpDomainFromUrl(const std::string &url)
{
    if(url.empty())
    {
        throw std::invalid_argument{"string is not a http(s) url"};
    }
    if(!pawal::StringTool::StartWith(url,"http://") && !pawal::StringTool::StartWith(url,"https://"))
    {
        throw std::invalid_argument{"string is not a http(s) url"};
    }
    std::size_t index{0};
    std::size_t count{0};
    for(std::size_t i = 0;i != url.size();++i)
    {
        if(url[i] == '/')
        {
            count += 1;
            if(count == 3)
            {
                index = i;
                break;
            }
        }   
    }
    if(!index)
    {
        throw std::invalid_argument{"string is not a http(s) url"};
    }
    std::string domain;
    domain.resize(index);
    std::memcpy(const_cast<char*>(domain.data()),url.data(),index);
    return domain;
}