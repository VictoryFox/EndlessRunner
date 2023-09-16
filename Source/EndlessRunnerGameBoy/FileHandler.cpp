// Fill out your copyright notice in the Description page of Project Settings.


#include "FileHandler.h"

#include "JsonObjectConverter.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"

TSharedPtr<FJsonObject> FileHandler::ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
    FString JsonString = ReadStringFromFile(JsonFilePath, bOutSuccess, OutInfoMessage);
    if (!bOutSuccess)
    {
        return nullptr;
    }

    TSharedPtr<FJsonObject> RetJsonObject;

    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), RetJsonObject))
    {
        bOutSuccess = false;
        OutInfoMessage = ("Could not deserialize file");
        return nullptr;
    }

    bOutSuccess = true;
    OutInfoMessage = ("Read Json sucessfully");
    return  RetJsonObject;
}

void FileHandler::WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject> JsonObject, bool& bOutSuccess, FString& OutInfoMessage)
{
    FString JsonString;

    if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<>::Create(&JsonString, 0)))
    {
        bOutSuccess = false;
        OutInfoMessage = ("could not serialize Json object to string");
        return;
    }

    WriteStringToFile(JsonFilePath, JsonString, bOutSuccess, OutInfoMessage);
    if (!bOutSuccess)
    {
        return;
    }

    bOutSuccess = true;
    OutInfoMessage = ("Write Json Succeeded");
}

FString FileHandler::ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
    {
        bOutSuccess = false;
        OutInfoMessage = ("File not found");
        return "";
    }

    FString RetString = "";

    if (!FFileHelper::LoadFileToString(RetString, *FilePath))
    {
        bOutSuccess = false;
        OutInfoMessage = ("Could not read file");
        return "";
    }

    bOutSuccess = true;
    OutInfoMessage = ("Read file succesfully");
    return  RetString;
}

void FileHandler::WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage)
{
    if (!FFileHelper::SaveStringToFile(String, *FilePath))
    {
        bOutSuccess = false;
        OutInfoMessage = ("could not write to file, is it read only?");
        return;
    }

    bOutSuccess = true;
    OutInfoMessage = ("Write to string sucessfully");
}
