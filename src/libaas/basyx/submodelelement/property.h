#pragma once

#include <basyx/enums/DataTypeDefinition.h>

#include <basyx/langstringset.h>
#include <basyx/modeltype.h>
#include <basyx/serialization/serializable.h>
#include <basyx/submodelelement/dataelement.h>

#include <basyx/util/string_view/string_view.hpp>

#include <sstream>
#include <string>
#include <sstream>
#include <type_traits>

namespace basyx {

template<typename T>
struct property_string_helper
{
    static std::string to_string(const T& t) { return std::to_string(t); };
};

template<>
struct property_string_helper<std::string> {
    static const std::string& to_string(const std::string& s) { return s; };
};



class property_value_base
{
public:
    virtual std::string get_value_string() const = 0;
    virtual DataTypeDefinition get_value_type() const = 0;
    virtual std::unique_ptr<property_value_base> copy() const = 0;
};

template<DataTypeDefinition DataType>
class property_value_impl : public property_value_base 
{
public:
    using value_t = typename basyx::detail::data_type_def_map<DataType>::type_t;
public:
    value_t value;
public:
    property_value_impl() : value({}) {};
    property_value_impl(value_t val) : value(std::move(val)) {};

    property_value_impl(const property_value_impl&) = default;
    property_value_impl& operator=(const property_value_impl&) = default;
    
    property_value_impl(property_value_impl&&) noexcept = default;
    property_value_impl& operator=(property_value_impl&&) noexcept = default;
public:
    std::string get_value_string() const override { 
        return property_string_helper<value_t>::to_string(value);
    };

    DataTypeDefinition get_value_type() const override { return DataType; };
public:
    const value_t& get_value() const { return value; };
public:
    std::unique_ptr<property_value_base> copy() const override {
        return std::make_unique<property_value_impl>(*this); 
    };
};

class Property : 
    public DataElement,
    private ModelType<ModelTypes::Property>,
    private serialization::Serializable<Property>,
    private Referable::Copyable<Property> 
{
public:
    using value_holder_t = std::unique_ptr<property_value_base>;
public:
    using ModelType::get_model_type;
private:
    value_holder_t value;
public:
    util::optional<Reference> valueId;

private:
    template<typename T>
    static value_holder_t make_value_holder(T t) {
        return std::make_unique<property_value_impl<basyx::detail::data_type_def_map_base_type<T>::dataType>>(std::move(t));
    };

    template<DataTypeDefinition DataType>
    static property_value_impl<DataType>* value_cast(property_value_base* base) {
        return static_cast<property_value_impl<DataType>*>(base);
    };
public:
    Property(util::string_view idShort)
        : DataElement(idShort) {};

    template<typename T>
    explicit Property(util::string_view idShort, T&& t)
        : DataElement(idShort)
    {
        this->assign(std::forward<T>(t));
    };



    Property(const Property& prop)
        : DataElement(*prop.getIdShort())
        , valueId(prop.valueId)
    {
        if (prop.has_value())
            this->value = prop.value->copy();
    };


    Property& operator=(const Property& prop) {
        this->setIdShort(*prop.getIdShort());
        this->valueId = prop.valueId;

        if(prop.has_value())
            this->value = prop.value->copy();

        return *this;
    };

    Property(Property&&) = default;
    Property& operator=(Property&&) = default;

    ~Property() = default;
public:
    bool has_value() const { return this->value != nullptr; };
public:
    //void assign(float f);
    void assign(util::string_view sv);
    void assign(const char* c_str) { this->assign(util::string_view(c_str)); };
public:
    DataTypeDefinition get_value_type() const { return this->value->get_value_type(); };

    std::string get_value_string() const;

    template<DataTypeDefinition DataType>
    auto get_as() const -> typename basyx::detail::data_type_def_map<DataType>::type_t
    {
        auto typed_value = Property::value_cast<DataType>(this->value.get());
        return typed_value->get_value();
    };

public:
    template<typename T>
    void assign(T t) {
        this->value = Property::make_value_holder<T>(std::move(t));
    };
};

}