#pragma once
#ifndef _PAWAL_STRINGTOOL_HPP
#define _PAWAL_STRINGTOOL_HPP

#include <string>
#include <stdexcept>

namespace pawal
{
    class StringTool
    {
    private:
        using Self = pawal::StringTool;
    protected:
    public:
    
        StringTool() noexcept = default;
    
        StringTool(const Self &other) noexcept = default;
    
        StringTool(Self &&other) noexcept = default;
    
        Self &operator=(const Self &other) noexcept = default;
    
        Self &operator=(Self &&other) noexcept = default;
    
        ~StringTool() noexcept = default;
    
        inline const Self &Const() const noexcept
        {
            return *this;
        }

        static bool StartWith(const std::string &thiz,const std::string &str) noexcept;

        static std::string GetHttpDomainFromUrl(const std::string &url);
    };   
}

#endif