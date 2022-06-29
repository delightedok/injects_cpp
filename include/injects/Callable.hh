/**
 * @file Callable.hh
 * @author mGitsun (jieshentan@outlook.com)
 * @brief
 * @version 0.1
 * @date 2022-06-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once


namespace Injects {


template < typename T>
class Callable
{
public:
    virtual T call(void) = 0;
};


}
