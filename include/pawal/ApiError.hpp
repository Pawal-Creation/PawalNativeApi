#pragma once
#ifndef _PAWAL_APIERROR_HPP
#define _PAWAL_APIERROR_HPP

#include <exception>

namespace pawal
{
    template<typename _Exception,bool _IsEmpty>
    class InternalApiError:public _Exception
    {
    private:
    
        using Self = pawal::InternalApiError<_Exception,_IsEmpty>;
    
        const char *msg_;
    public:
        InternalApiError() noexcept = default;
    
        explicit InternalApiError(const char *msg)
            :msg_(msg)
        {}
    
        InternalApiError(const Self &other) noexcept = default;
    
        InternalApiError(Self &&other) noexcept = default;
    
        ~InternalApiError() noexcept = default;
    
        Self &operator=(const Self &other) noexcept = default;
    
        Self &operator=(Self &&other) noexcept = default;
    
        virtual const char *what() const noexcept override
        {
            return this->msg_;
        }
    };
    
    //msvc exception
    template<typename _Exception>
    class InternalApiError<_Exception,false>:public _Exception
    {
    private:
    
        using Self = pawal::InternalApiError<_Exception,false>;
        using Base = _Exception;
    public:
        InternalApiError() noexcept = default;
    
        explicit InternalApiError(const char *msg) noexcept
            :Base(msg)
        {}
    
        InternalApiError(const Self &other) noexcept = default;
    
        InternalApiError(Self &&other) noexcept = default;
    
        ~InternalApiError() noexcept = default;
    
        Self &operator=(const Self &other) noexcept = default;
    
        Self &operator=(Self &&other) noexcept = default;
    };
    
    //if sizeof(std::exception) == sizeof(void*),std::exception is a interface class
    //exception class defination
    class ApiError:public pawal::InternalApiError<std::exception,sizeof(std::exception) == sizeof(void*)>
    {
    private:
        using Self = pawal::ApiError;
        using Base = pawal::InternalApiError<std::exception,sizeof(std::exception) == sizeof(void*)>;
    public:
        ApiError() noexcept = default;
    
        explicit ApiError(const char *msg) noexcept
            :Base(msg)
        {}
    
        ApiError(const Self &other) noexcept = default;
    
        ApiError(Self &&other) noexcept = default;
    
        ~ApiError() noexcept = default;
    
        Self &operator=(const Self &other) noexcept = default;
    
        Self &operator=(Self &&other) noexcept = default;
    };
}

#endif