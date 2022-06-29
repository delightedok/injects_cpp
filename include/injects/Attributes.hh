/**
 * @file Attributes.hh
 * @author TamGitsun (jieshentan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2022-06-25
 *
 * @copyright Copyright (c) 2022
 **/

#pragma once


namespace Injects {


enum class Attribute: int
{
    SINGLE = 0x01,
    SINGLETON = 0x02,
};

int operator&(Attribute attr, int attrs)
{
    return static_cast<int>(attr) & attrs;
}

int operator&(int attrs, Attribute attr)
{
    return attr & attrs;
}

int operator|(Attribute attr, int attrs)
{
    return static_cast<int>(attr) | attrs;
}

int operator|(int attrs, Attribute attr)
{
    return attr | attrs;
}


}
