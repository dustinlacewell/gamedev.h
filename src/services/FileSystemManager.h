#pragma once

#include <Adafruit_SPIFlash.h>
#include <SdFat.h>
#include <SPI.h>

class FileSystemManager
{
public:
    FileSystemManager();
    bool begin();
    void ls();
    bool writeFile(const String &path, const String &data);
    String readFile(const String &path);
    bool writeBinaryFile(const String &path, const uint8_t *data, size_t length);
    bool readBinaryFile(const String &path, uint8_t *buffer, size_t length);
    bool exists(const String &path);
    bool remove(const String &path);
    bool mkdir(const String &path);
    bool rmdir(const String &path);

private:
    Adafruit_FlashTransport_QSPI flashTransport;
    Adafruit_SPIFlash flash;
    FatFileSystem fatfs;
};