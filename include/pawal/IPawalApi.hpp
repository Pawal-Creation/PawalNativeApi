#pragma once
#ifndef _PAWAL_IPAWALAPI_HPP
#define _PAWAL_IPAWALAPI_HPP

#include <vector>
#include <string>

#include "ApiError.hpp"

namespace pawal
{
    class IPawalApi
    {
    private:
        using Self = pawal::IPawalApi;
    protected:
    public:
    
        IPawalApi() noexcept = default;
    
        IPawalApi(const Self &other) noexcept = default;
    
        IPawalApi(Self &&other) noexcept = default;
    
        Self &operator=(const Self &other) noexcept = default;
    
        Self &operator=(Self &&other) noexcept = default;
    
        virtual ~IPawalApi() noexcept = default;
    
        inline const Self &Const() const noexcept
        {
            return *this;
        }

        virtual std::vector<char> LookupImage(const std::string &keyword) = 0;
    };
}

#endif