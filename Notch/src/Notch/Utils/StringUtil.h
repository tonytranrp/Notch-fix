#pragma once

#include <string>
#include <sstream>
class StringUtil {
public:
    template <typename T> // not related to memory LOL
    static std::string combine(T t)
    {
        std::stringstream ss;
        ss << t;
        return ss.str();
    }

    template <typename T, typename... Args> // not related to memory LOL
    static std::string combine(T t, Args... args)
    {
        std::stringstream ss;
        ss << t << combine(args...);
        return ss.str();
    }

    static std::wstring StrToWStr(std::string const& s) {
        int slength = static_cast<int>(s.length()) + 1;
        int len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), slength, 0, 0);
        wchar_t* buf = new wchar_t[len];
        MultiByteToWideChar(CP_UTF8, 0, s.c_str(), slength, buf, len);
        std::wstring r(buf);
        delete[] buf;
        return r;
    }

    static std::string WStrToStr(std::wstring const& ws) {
        std::string ret;
        int len = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), static_cast<int>(ws.size()), NULL, 0, NULL, NULL);
        if (len > 0) {
            ret.resize(len);
            WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), static_cast<int>(ws.size()), &ret[0], len, NULL, NULL);
        }
        return ret;
    }

    static bool startsWith(std::string str, std::string start) {
        return str.starts_with(start);
    }

    static std::string join(const std::vector<std::string>& vec, const std::string& delimiter) {
        if (vec.empty()) return "";
        std::ostringstream oss;
        for (size_t i = 0; i < vec.size() - 1; ++i) {
            oss << vec[i] << delimiter;
        }
        oss << vec.back();
        return oss.str();
    }
    static std::string join(const std::vector<int>& vec, const std::string& delimiter) {
        if (vec.empty()) return "";
        std::ostringstream oss;
        for (size_t i = 0; i < vec.size() - 1; ++i) {
            oss << vec[i] << delimiter;
        }
        oss << vec.back();
        return oss.str();
    }
    static std::string join(const std::set<std::string>& vec, const std::string& delimiter) {
        if (vec.empty()) return "";
        std::ostringstream oss;
        auto it = vec.begin();
        while (std::next(it) != vec.end()) {
            oss << *it << delimiter;
            ++it;
        }
        oss << *it;
        return oss.str();
    }

    static std::string join(const std::set<int>& vec, const std::string& delimiter) {
        if (vec.empty()) return "";
        std::ostringstream oss;
        auto it = vec.begin();
        while (std::next(it) != vec.end()) {
            oss << *it << delimiter;
            ++it;
        }
        oss << *it;
        return oss.str();
    }
};