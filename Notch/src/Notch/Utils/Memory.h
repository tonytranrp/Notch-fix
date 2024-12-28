#pragma once
#include <windows.h>
#include <iostream>
#include <algorithm>
#include <execution>
#include <string>
#include <cstdarg>
#include <cstdint>
#include <string_view>
#include <psapi.h>
#include "TimeUtil.h"
#include "../Libraries/Libraries.h"
#include "../Libraries/Libs/libhat/libhat.hpp"
#include "Logger.h"
#include "StringUtil.h"
#include <vector>


class AddressLogger {
public:
    void log(size_t name, uintptr_t address) {
        logs.push_back(std::to_string(name) + ": " + std::to_string(address));
    }

    // Change the return type to return the logs
    std::vector<std::string> printLogs() const {
        return logs;  // Return the vector of logs
    }

private:
    std::vector<std::string> logs;  // Changed access to private
};




template<typename Ret, typename Type>
Ret& direct_access(Type* type, size_t offset) {
    union {
        size_t raw;
        Type* source;
        Ret* target;
    } u;
    u.source = type;
    u.raw += offset;
    AddressLogger addressLogger;
    // Log the access
    addressLogger.log(offset, reinterpret_cast<uintptr_t>(u.target));

    return *u.target;
}

#define AS_FIELD(type, name, fn) __declspec(property(get = fn, put = set##name)) type name
#define FAKE_FIELD(type, name)       \
    AS_FIELD(type, name, get##name); \
    type get##name()
#define BUILD_ACCESS(ptr, type, name, offset)                           \
    AS_FIELD(type, name, get##name);                                    \
    type get##name() const { return direct_access<type>(ptr, offset); } \
    void set##name(type v) const { direct_access<type>(ptr, offset) = v; }
namespace Memory {
    template <typename R, typename... Args>
    R CallFunc(void* func, Args... args)
    {
        return ((R(*)(Args...))func)(args...);
    }

    static uintptr_t ResolveRef(uintptr_t ptr, int offset = 1) {
        if (!ptr)
            return 0;

        uintptr_t newAddr = ptr + *reinterpret_cast<int*>(ptr + offset) + (offset + 4);
        return newAddr;
    }
    template <typename TRet, typename... TArgs>
    extern TRet CallVFunc(void* thisptr, size_t index, TArgs... argList) {
        using TFunc = TRet(__fastcall*)(void*, TArgs...);
        TFunc* vtable = *reinterpret_cast<TFunc**>(thisptr);
        return vtable[index](thisptr, argList...);
    }
    template <typename R, typename... Args>
    auto GetFunc(void* func) -> R(*)(Args...) {
        return reinterpret_cast<R(*)(Args...)>(func);
    }

    

    template <typename ret>
    auto FuncFromSigOffset(uintptr_t sig, int offset) -> ret {
        if (sig != 0x0) {
            sig += offset + 4 + *reinterpret_cast<int*>(sig + offset);
        }
        return reinterpret_cast<ret>(sig);
    }

    static const uintptr_t range_start = reinterpret_cast<uintptr_t>(GetModuleHandleA("Minecraft.Windows.exe"));

    template <typename T>
    bool CreateHook(void* pTarget, T pDetour, void* pOriginal, const char* sigId)
    {
        if ((uintptr_t)pTarget == 0u) 
            return false;
        if (MH_CreateHook(pTarget, pDetour, (LPVOID*)pOriginal) != MH_OK)
        {
            logF(StringUtil::combine("[", pTarget, ",", sigId, "] Failed to create hook").c_str(), "FAIL");
            return false;
        }

        if (MH_EnableHook(pTarget) != MH_OK)
        {
            logF(StringUtil::combine("[", pTarget, ",", sigId, "] Failed to enable hook").c_str(), "FAIL");
            return false;
        }

        std::stringstream ss;
        ss << "Minecraft.Windows.exe+" << std::hex << (uintptr_t)pTarget - range_start;

        logF(StringUtil::combine("[", ss.str().c_str(), ",", sigId, "] Successfully Hooked").c_str(), "OKAY");

        return true;
    }

#define INRANGE(x, a, b) (x >= a && x <= b)
#define GET_BYTE(x) ((GET_BITS(x[0]) << 4) | GET_BITS(x[1]))
#define GET_BITS(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? (x - '0') : 0))
    inline uintptr_t findSignature(const char* szSignature) {
        std::string_view signature(szSignature);

        const auto parsed = hat::parse_signature(signature);
        if (!parsed.has_value()) {
            //logF(std::format("[ Runtime Scanner ] Failed to parse signature: ", std::string(signature)), "INFO");
            return 0u;
        }

        const auto result = hat::find_pattern(parsed.value());

        if (!result.has_result()) {
            //logF(std::format("[ Runtime Scanner ] Failed to find signature: ", std::string(signature)), "INFO");
            return 0u;
        }

        return reinterpret_cast<uintptr_t>(result.get());
        /*const char* pattern = szSignature;
        uintptr_t firstMatch = 0;
        static const auto rangeStart = (uintptr_t)GetModuleHandleA("Minecraft.Windows.exe");
        static MODULEINFO miModInfo;
        static bool init = false;
        if (!init) {
            init = true;
            GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
        }
        static const uintptr_t rangeEnd = rangeStart + miModInfo.SizeOfImage;

        BYTE patByte = GET_BYTE(pattern);
        const char* oldPat = pattern;

        for (uintptr_t pCur = rangeStart; pCur < rangeEnd; pCur++) {
            if (!*pattern)
                return firstMatch;

            while (*(PBYTE)pattern == ' ')
                pattern++;

            if (!*pattern)
                return firstMatch;

            if (oldPat != pattern) {
                oldPat = pattern;
                if (*(PBYTE)pattern != '\?')
                    patByte = GET_BYTE(pattern);
            }

            if (*(PBYTE)pattern == '\?' || *(BYTE*)pCur == patByte) {
                if (!firstMatch)
                    firstMatch = pCur;

                if (!pattern[2] || !pattern[1])
                    return firstMatch;
                
                pattern += 2;
            }
            else {
                pattern = szSignature;
                firstMatch = 0;
            }
        }
        return 0u;*/
    }
    static void* addSignature(const char* sig) {
        return (void*)findSignature(sig);
    }
    static char* findString(std::string_view find, const char* module) {
        auto gameModule = reinterpret_cast<uintptr_t>(GetModuleHandleA(module));
        auto* const scanBytes = reinterpret_cast<uint8_t*>(gameModule);
        auto* const dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(gameModule);
        auto* const ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(scanBytes + dosHeader->e_lfanew);
        const auto sizeOfCode = ntHeaders->OptionalHeader.SizeOfImage;

        const auto end = scanBytes + sizeOfCode;

        auto it = std::search(std::execution::par, scanBytes, end, find.cbegin(), find.cend());

        auto ret = it != end ? reinterpret_cast<char*>(it) : 0ull;
        return ret;
    }
}