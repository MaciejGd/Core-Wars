#pragma once

#include <string_view>
#include <memory>

///
/// Enumeration type representing all
/// possible modifiers accessible in 
/// RedCode language
///
enum ModifierType {
    A,
    B,
    AB,
    BA,
    I,
    F,
    X,
    DEFAULT
};


/// Class implementing logic of setting default modifier for 
/// operations, based on parameters they interact with
class IDefaultModSetter {
public:
    IDefaultModSetter() = default;
    IDefaultModSetter(const IDefaultModSetter& other) = default;

    /// @brief Virtual function to be implemented in derived classes. 
    /// Responsible for deducing default modifier based on parameters type
    /// @param a_param_type string representing A parameter's type
    /// @param b_param_type string representing B parameter's type
    /// @return 
    virtual ModifierType DeduceDefaultModSetter(std::string_view a_param_type, std::string_view b_param_type) = 0;
    virtual std::unique_ptr<IDefaultModSetter> clone() const = 0;
};