#ifndef VIVO_ARRAY_INL_H
#define VIVO_ARRAY_INL_H

namespace vivo
{
    template <class T>
    inline T ObjectArray<T>::at(uint32_t idx)
    {
        if(!IsValid(idx)) {
            ABORT();
            return reinterpret_cast<T>(0);
        }
        else
            return reinterpret_cast<T>(first_element_ + sizeof(T)*idx);
    }

    template <class T>
    inline void ObjectArray<T>::set(uint32_t idx, T data)
    {
        if(!IsValid(idx)) {
            ABORT();
            return;
        }
        *(reinterpret_cast<T*>(first_element_ + sizeof(T)*idx)) = data;
        return;
    }

    inline bool Array::IsValid(uint32_t idx)
    {
        return idx < size_;
    }
    inline void Array::setLength(uint32_t compontLength)
    {
       size_ = compontLength; 
    }
}

#endif
