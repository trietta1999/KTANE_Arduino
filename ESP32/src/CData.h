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
    CData() = default;
    ~CData() = default;

    T GetValue();
    void SetValue(T);
    bool GetState();
    void ResetState();
};

#endif // !_CDATA_H
