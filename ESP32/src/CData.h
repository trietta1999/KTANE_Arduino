/**
 * @brief Common data class
 */

#ifndef _CDATA_H
#define _CDATA_H

template<class T>
class CData
{
private:
    T value;
    T oldValue;
    bool state;

public:
    CData()
    {
        this->state = false;
    }

    ~CData() = default;

    T GetValue()
    {
        return this->value;
    }

    void SetValue(T value)
    {
        if (value != this->value)
        {
            this->oldValue = this->value;
            this->value = value;
            this->state = true;
        }
    }

    bool GetState()
    {
        return this->state;
    }

    void ResetState()
    {
        if (this->state)
        {
            this->oldValue = this->value;
            this->state = false;
        }
    }
};

#endif // !_CDATA_H
