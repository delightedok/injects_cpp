/**
 * @file types.hh
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#pragma once

#include <memory>


namespace Injects {


template <typename T>
using SP = std::shared_ptr<T>;

template <typename T>
using WP = std::weak_ptr<T>;


}
