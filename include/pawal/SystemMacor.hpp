#pragma once
#ifndef _PAWAL_SYSTEMMACOR_HPP
#define _PAWAL_SYSTEMMACOR_HPP

#if (defined (_WIN32)) || (defined (_WIN64))
#define PAWAL_IS_WIN
#define WIN32_LEAN_AND_MEAN
#elif (defined (_linux)) || (defined (_linux_)) || (defined (__linux__))
#define PAWAL_IS_LINUX
#define PAWAL_IS_NIX
#elif (defined (_unix)) || (defined (_unix_))
#define PAWAL_IS_UNIX
#define PAWAL_IS_NIX
#endif

#endif