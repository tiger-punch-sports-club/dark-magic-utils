#include <cstdint>
#include <stdio.h>
#include <string>


#include "KeyValue.h"
#include "LinearAllocator.h"
#include "ScopedPointer.h"
#include "ServiceLocator.h"
#include "Singleton.h"
#include "TypeName.h"

using namespace DarkMagic;

namespace
{
    struct MyService
    {
        void DoStuff()
        {
            printf("MyService doing stuff!\n");
        }
    };

    struct MySingleton final : TSingleton<MySingleton>
    {
        float MyStuff;

        MySingleton()
            : MyStuff(123.0f)
        {
        }
    };

    struct MyStruct
    {
        void SayHello()
        {
            printf("Hello\n");
        }

        ~MyStruct()
        {
            printf("Oh no!\n");
        }
    };
}

void main()
{
    // ********************************
    // Linked list
    // ******************************** 
    FKeyValue<uint32_t, std::string> Head = { 0, "Head" };
    FKeyValue<uint32_t, std::string> Child = { 1, "Child" };
    FKeyValue<uint32_t, std::string> Child2 = { 4, "Child 2" };

    Head.Next = &Child;
    Child.Next = &Child2;

    auto* Chain = &Head;
    while(Chain)
    {
        printf("%d, %s \n", Chain->Key, Chain->Value.c_str());
        Chain = Chain->Next;
    }

    const uint32_t Key = 4;
    printf("Get Value: %d, %s \n", Key, Head.GetValue(Key)->c_str());

    // ********************************
    // Linear allocator
    // ******************************** 
    TLinearAllocator<uint32_t> UintAllocator;
    UintAllocator.Init(10);

    for(uint32_t I = 0; I < 10; I++)
    {
        auto& Number = *UintAllocator.Alloc();
        Number = I;
    }

    for(uint32_t I = 0; I < 10; I++)
    {
        const auto Array = static_cast<uint32_t*>(UintAllocator.Allocator.Memory);
        printf("[%d] = %d\n", I, Array[I]);
    }

    UintAllocator.Reset();

    for(uint32_t I = 0; I < 10; I++)
    {
        auto& Number = *UintAllocator.Alloc();
        Number = I * I;
    }

    for(uint32_t I = 0; I < 10; I++)
    {
        const auto Array = static_cast<uint32_t*>(UintAllocator.Allocator.Memory);
        printf("[%d] = %d\n", I, Array[I]);
    }

    // ********************************
    // Compile time type information
    // ******************************** 
    constexpr auto Type = TypeName<int32_t>().data();
    printf("Compile time type info: %s \n", Type);

    // ********************************
    // ServiceLocator
    // ******************************** 
    MyService MyService{};

    FServiceLocator ServiceLocator{};
    ServiceLocator.Set<struct MyService>(&MyService);

    auto& MyRetrievedService = *ServiceLocator.Get<struct MyService>();
    MyRetrievedService.DoStuff();

    ServiceLocator.Remove<struct MyService>();

    assert(ServiceLocator.Get<struct MyService>() == nullptr && "Did not remove the service!");

    // ********************************
    // Hash
    // ********************************

    const std::string DynamicHashString = "Dynamic hash";
    auto DynamicHash = HashData(DynamicHashString.c_str());

    constexpr auto CompileTimeHash = HashData("Compile time hash");

    // ********************************
    // Singleton
    // ********************************
    MySingleton* MySingletonInstance = MySingleton::GetInstance();
    printf("%f\n", MySingletonInstance->MyStuff);
    MySingleton::GetInstance()->MyStuff = 999.0f;
    printf("%f\n", MySingletonInstance->MyStuff);

    // ********************************
    // Scoped Pointer
    // ********************************
    {
        auto ScopedPointer = TScopedPointer<MyStruct>(new MyStruct());
        ScopedPointer->SayHello();
    }

    // ********************************
    // Negative index
    // -1 remaps to start at 0
    // ********************************
    {
        int32_t Index = -1;
        // int32_t NegativeIndex = (-1 -Index);
        int32_t NegativeIndex = ~Index;
        printf("%d => %d\n", Index, NegativeIndex);
    }
}
