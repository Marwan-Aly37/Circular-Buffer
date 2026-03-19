#ifndef CONFIG_H
#define CONFIG_H

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"

#if defined(_WIN32) || defined(__linux__) || defined(__APPLE__)

#ifndef PLATFORM_PC
#define PLATFORM_PC
#endif

#endif

#ifndef ENABLE_LOGGING
#define ENABLE_LOGGING 1
#endif

#if ENABLE_LOGGING

#ifdef PLATFORM_PC
    #include<stdio.h>
    #define LOG_DEBUG(fmt, ...) printf(YELLOW fmt ,__VA_ARGS__)
    #define LOG_INFO(fmt, ...) printf(GREEN"[INFO] " fmt "\n",__VA_ARGS__)
    #define LOG_WARN(msg) printf(RED"[WARNING] %s\n",msg)

    #else
    #define LOG_INFO(msg) 
                    uart_send([INFO])
                    uart_send(msg)
                    uart_send(\n)
    #define LOG_WARN(msg) 
                    uart_send([WARNING])
                    uart_send(msg)
                    uart_send(\n)
    #define LOG_DEBUG(msg)
                    uart_send([DEBUG])
                    uart_send(msg)

#endif

#else
    #define LOG_INFO(fmt, ...)
    #define LOG_WARN(msg)
    #define LOG_DEBUG(fmt, ...)
#endif

#endif
