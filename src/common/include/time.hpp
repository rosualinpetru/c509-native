#ifndef __C509_TIME_H
#define __C509_TIME_H

namespace C509
{
    struct Time
    {
        enum class Type
        {
            Int,
            Float
        } type;

        union
        {
            uint32_t intTime;
            double floatTime;
        };
    };
}

#endif // __C509_TIME_H