/**
 * @brief Common data class
 */

#include "CData.h"

template<class T>
T CData<T>::GetValue()
{
    return this->value;
}

template<class T>
bool CData<T>::GetState()
{
    return this->state;
}

template<class T>
void CData<T>::SetValue(T value)
{
    if (value != this->value)
    {
        this->oldValue = this->value;
        this->value = value;
        this->state = true;
    }
}

template<class T>
void CData<T>::ResetState()
{
    oldValue = value;
    state = false;
}
