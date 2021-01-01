#pragma once
#include <string>
#include <sstream> 

// Source: https://stackoverflow.com/questions/8001207/compile-time-typeid-without-rtti-with-gcc

typedef void* FTypeId;
template <class T>
FTypeId TypeId() //this function is instantiated for every different type
{
    //WARNING: works only inside one module: same type coming from different module will have different value!
    static T* TypeUniqueMarker = nullptr; //thus this static variable will be created for each TypeIdNoRTTI<T> separately
    return &TypeUniqueMarker; //it's address is unique identifier of TypeIdNoRTTI<T> type
}

inline const char* TypeIdToString(FTypeId TypeId)
{
    std::stringstream StringStream;
    StringStream << TypeId;
    return StringStream.str().c_str();
}
