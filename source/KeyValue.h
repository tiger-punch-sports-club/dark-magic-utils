#pragma once

namespace DarkMagic
{
    // ********************************
    // Key-Value single linked list
    // ******************************** 
    template <typename K, typename V>
    struct FKeyValue
    {
        K Key;
        V Value;
        FKeyValue<K, V>* Next;

        V* GetValue(const K& Key);
        void Delete();
    };

    template <typename K, typename V>
    V* FKeyValue<K, V>::GetValue(const K& Key)
    {
        if(this->Key == Key)
        {
            return &Value;
        }

        if(Next)
        {
            return Next->GetValue(Key);
        }

        return nullptr;
    }

    template <typename K, typename V>
    void FKeyValue<K, V>::Delete()
    {
        if(Next)
        {
            Next->Delete();
        }

        delete Next;
    }
}
