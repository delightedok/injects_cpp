/**
 * @file injects.hh
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "types.hh"
#include "Attributes.hh"
#include "PolicyManager.hh"
#include <string>
#include <map>
#include <typeinfo>
#include <iostream>
#include <memory>


namespace Injects {


#define EVAL(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL5(...) __VA_ARGS__

#define EXPAND_(...) __VA_ARGS__
#define EXPAND(...) EXPAND_(__VA_ARGS__)

#define SECOND(a1, a2, ...) a2
#define CHECK(...) SECOND(__VA_ARGS__, 0)

#define PROBE(x) x, 1

#define EMPTY()
#define DEFER(x) x EMPTY()

#define CONCAT_(A, B) A##B
#define CONCAT(A, B) CONCAT_(A, B)

#define IS_EMPTY_I(x, ...) CHECK(CONCAT(CONCAT_(IS_EMPTY_, x), 0))
#define IS_EMPTY(x, ...) IS_EMPTY_I(x, ##__VA_ARGS__)
#define IS_EMPTY_0 PROBE(1)

#define FIRST_ARG(__Arg, ...) __Arg
#define DEL_FIRST_ARG(__Arg, ...) __VA_ARGS__

#define FOR_EACH(target, x, ...) CONCAT(FOR_EACH_, IS_EMPTY(__VA_ARGS__)) (target, x, __VA_ARGS__)
#define FOR_EACH_0(target, x, ...) target(x, __VA_ARGS__) DEFER(FOR_EACH_I)() (target, __VA_ARGS__)
#define FOR_EACH_1(target, x, ...) target(x, __VA_ARGS__)
#define FOR_EACH_I() FOR_EACH

#define TYPE_HAVE_MORE_1
#define TYPE_HAVE_MORE_0 ,

#define INJECT_PARAM(t) t##_
#define INJECT_PARAM_TYPE(t) SP<t>

#define EMPTY_PARAM_1(t)
#define EMPTY_PARAM_0(t) INJECT_PARAM_TYPE(t) INJECT_PARAM(t)
#define TYPES_2_PARAMS_FOR_EACH_TARGET(t, ...) \
    CONCAT(EMPTY_PARAM_, IS_EMPTY(t))(t) CONCAT(TYPE_HAVE_MORE_, IS_EMPTY(__VA_ARGS__))
#define TYPES_2_PARAMS(...) EVAL(FOR_EACH(TYPES_2_PARAMS_FOR_EACH_TARGET, __VA_ARGS__))
#define EMPTY_ARG_1(t)
#define EMPTY_ARG_0(t) INJECT_PARAM(t)
#define TYPES_2_ARGS_FOR_EACH_TARGET(t, ...) \
    CONCAT(EMPTY_ARG_, IS_EMPTY(t))(t) CONCAT(TYPE_HAVE_MORE_, IS_EMPTY(__VA_ARGS__))
#define TYPES_2_ARGS(...) EVAL(FOR_EACH(TYPES_2_ARGS_FOR_EACH_TARGET, __VA_ARGS__))

#define GET_INSTANCE_1(t)
#define GET_INSTANCE_0(t) t::InjectBuilder::get()
#define GET_INSTANCES_FOR_EACH_TARGET(t, ...) \
    CONCAT(GET_INSTANCE_, IS_EMPTY(t))(t) CONCAT(TYPE_HAVE_MORE_, IS_EMPTY(__VA_ARGS__))
#define GET_INSTANCES(...) EVAL(FOR_EACH(GET_INSTANCES_FOR_EACH_TARGET, __VA_ARGS__))

#define INJECTOR_CLASS(__class_name, __attrs, ...) \
    class InjectBuilder \
    { \
    private: \
        class Builder: public Callable<SP<__class_name> > \
        { \
            SP<__class_name> call(void) \
            { \
                return std::make_shared<__class_name>(GET_INSTANCES(__VA_ARGS__)); \
            } \
        }; \
    public: \
        static SP<__class_name> get(void) \
        { \
            return PolicyManager::get( \
                __attrs | Attribute::SINGLE, \
                Builder()); \
        } \
    }

#define INJECT_CONSTRUCTOR(__class_name, attrs, ...) \
    INJECTOR_CLASS(__class_name, attrs, ##__VA_ARGS__); \
    __class_name(TYPES_2_PARAMS(__VA_ARGS__))
    
#define PROVIDES_CLASS(__class_name, __attrs, ...) \
    class InjectBuilder \
    { \
    private: \
        class Builder: public Callable<SP<__class_name> > \
        { \
            SP<__class_name> call(void) \
            { \
                return std::make_shared<__class_name>(GET_INSTANCES(__VA_ARGS__)); \
            } \
        }; \
    public: \
        static SP<__class_name> get(void) \
        { \
            return PolicyManager::get(static_cast<int>(__attrs), Builder()); \
        } \
    }

#define PROVIDES_CONSTRUCTOR(__class_name, attrs, ...) \
    PROVIDES_CLASS(__class_name, attrs, ##__VA_ARGS__); \
    __class_name(TYPES_2_PARAMS(__VA_ARGS__))
    
#define GET_CLASS_1(t)
#define GET_CLASS_0(t) \
    static SP<t> get_##t(void) \
    { \
        return t::InjectBuilder::get(); \
    }
#define GET_CLASSES_FOR_EACH_TARGET(t, ...) CONCAT(GET_CLASS_, IS_EMPTY(t))(t)
#define GET_CLASSES(...) EVAL(FOR_EACH(GET_CLASSES_FOR_EACH_TARGET, __VA_ARGS__))

#define COMPONENT_CLASS(__class_name, ...) \
    class __class_name##Component \
    { \
    public: \
        GET_CLASSES(__VA_ARGS__) \
    }; \
    class __class_name: public __class_name##Component {}
    
template <typename T>
class Provider
{
    public: SP<T> get(void)
    {
        return T::InjectBuilder::get();
    }
};


}
