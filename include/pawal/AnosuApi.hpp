#pragma once
#ifndef _PAWAL_ANOSUAPI_HPP
#define _PAWAL_ANOSUAPI_HPP

#include <memory>
#include <cassert>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <string>
#include <map>

#include "IPawalApi.hpp"
#include "Noncopyable.hpp"
#include "StringTool.hpp"

namespace httplib
{
    class Client;
}

namespace pawal
{
    class AnosuApi:public pawal::IPawalApi,public pawal::Noncopyable
    {
    private:
        using Self = pawal::AnosuApi;
        using Client = httplib::Client;

        std::unique_ptr<Client> anosuClient_;
        std::string path_;
        std::map<std::string,std::unique_ptr<Client>> redirectMap_;

        Client &GetRequiredClient(const std::string &domain);
    public:
    
        AnosuApi();
    
        AnosuApi(Self &&other) noexcept = default;
    
        Self &operator=(Self &&other) noexcept;
    
        virtual ~AnosuApi() noexcept = default;
    
        inline const Self &Const() const noexcept
        {
            return *this;
        }

        virtual std::vector<char> LookupImage(const std::string &keyword) override;
    };   
}

#endif