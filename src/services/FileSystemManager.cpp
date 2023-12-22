#include "FileSystemManager.h"

FileSystemManager::FileSystemManager() : flash(&flashTransport)
{
    // Constructor
}

bool FileSystemManager::begin()
{
    if (!flash.begin())
    {
        Serial.println(F("Error, failed to initialize flash chip!"));
        return false;
    }
    else
    {
        Serial.println(F("Flash chip ID: "));
        Serial.println(flash.getJEDECID(), HEX);
    }

    if (!fatfs.begin(&flash))
    {
        Serial.println(F("Error, failed to mount filesystem!"));
        return false;
    }
    else
    {
        Serial.println(F("Mounted filesystem!"));
    }

    return true;
}

void FileSystemManager::ls()
{
    fatfs.ls();
}

bool FileSystemManager::writeFile(const String &path, const String &data)
{
    File file = fatfs.open(path.c_str(), FILE_WRITE);
    if (!file)
    {
        return false;
    }

    size_t bytesWritten = file.print(data);
    file.close();
    return bytesWritten == data.length();
}

String FileSystemManager::readFile(const String &path)
{
    File file = fatfs.open(path.c_str(), FILE_READ);
    if (!file)
    {
        return String();
    }

    String data;
    while (file.available())
    {
        data += (char)file.read();
    }

    file.close();
    return data;
}

bool FileSystemManager::writeBinaryFile(const String &path, const uint8_t *data, size_t length)
{
    File file = fatfs.open(path.c_str(), FILE_WRITE | O_TRUNC | O_CREAT);
    if (!file)
        return false;

    file.seek(0);
    size_t bytesWritten = file.write(data, length);
    file.flush();
    file.sync();
    file.close();

    bool success = bytesWritten == length;
    if (success)
        Serial.println("Wrote " + String(bytesWritten) + " bytes to " + path);
    else
        Serial.println("Failed to write " + String(length) + " bytes to " + path);

    return success;
}

bool FileSystemManager::readBinaryFile(const String &path, uint8_t *buffer, size_t length)
{
    File file = fatfs.open(path.c_str(), FILE_READ);
    if (!file)
        return false;

    size_t bytesRead = file.read(buffer, length);
    file.close();

    bool success = bytesRead == length;
    if (success)
        Serial.println("Read " + String(bytesRead) + " bytes from " + path);
    else
        Serial.println("Failed to read " + String(length) + " bytes from " + path);

    return success;
}

bool FileSystemManager::exists(const String &path)
{
    return fatfs.exists(path.c_str());
}

bool FileSystemManager::remove(const String &path)
{
    return fatfs.remove(path.c_str());
}

bool FileSystemManager::mkdir(const String &path)
{
    return fatfs.mkdir(path.c_str());
}

bool FileSystemManager::rmdir(const String &path)
{
    return fatfs.rmdir(path.c_str());
}