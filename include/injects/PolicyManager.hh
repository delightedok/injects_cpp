/**
 * @file PolicyManager.hh
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "types.hh"
#include "Attributes.hh"
#include "Callable.hh"


namespace Injects {


class PolicyManager
{
public:
    template <typename T>
    static SP<T> get(int attrs, Callable<SP<T> > && callable)
    {
        if (attrs & Attribute::SINGLE)
        {
            static WP<T> w_instance;
            SP<T> instance_ = w_instance.lock();
            if (nullptr == instance_)
            {
                instance_ = callable.call();
                w_instance = instance_;
            }
            return instance_;
        } else if (attrs & Attribute::SINGLETON)
        {
            static SP<T> s_instance;
            s_instance = callable.call();
            return s_instance;
        } else
        {
            return callable.call();
        }
    }
};


}
