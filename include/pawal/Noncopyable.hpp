#pragma once
#ifndef _PAWAL_NONCOPYABLE_HPP
#define _PAWAL_NONCOPYABLE_HPP

namespace pawal
{
    class Noncopyable
    {
    private:
        using Self = Noncopyable;
    
    public:
    
        Noncopyable() noexcept = default;
    
        Noncopyable(Self &&other) noexcept = default;

        Self &operator=(Self &&other) noexcept = default;
    
        ~Noncopyable() noexcept = default;
    
        inline const Self &Const() const noexcept
        {
            return *this;
        }
    };   
}

#endif