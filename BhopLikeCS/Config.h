#pragma once

class Config
{
public:
    static Config& GetInstance();

    Config(const Config& config) = delete;
    Config& operator=(const Config& config) = delete;

    void Init();
    json& Data();
    bool Save();
private:
    const char* FILE_NAME = "config.json";

    static json staticGetDefaultConfig();
private:
    bool isInitialized = false;
    json jsonData;

    Config();
    ~Config();
};
