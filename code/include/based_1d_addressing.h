//==================================================================================================
//  File:
//      based_1d_addressing.h
//
//  Summary:
//      Defines a simple one-dimensional based addressing model as a class template.
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#ifndef BASED_1D_ADDRESSING_H_DEFINED
#define BASED_1D_ADDRESSING_H_DEFINED

#include <cstddef>
#include <cstdint>

//--------------------------------------------------------------------------------------------------
//  Class:
//      based_1d_addressing_model
//
//  Summary:
//      This class implements a based (base + offset) addressing model.  The offset is stored
//      as a 64-bit integer, and the base address is provided by a segment address from an 
//      instance of the template argument SM.
//
//      Note that the comparison helper functions include several that define the "greater_than"
//      relationship.  They are included because they are trivial, and make the code for any
//      synthetic pointer wrapper class comparison operators easier to implement and read.
//--------------------------------------------------------------------------------------------------
//
template<typename SM>
class based_1d_addressing_model
{
  public:
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

  public:
    ~based_1d_addressing_model() = default;

    based_1d_addressing_model() noexcept = default;
    based_1d_addressing_model(based_1d_addressing_model&&) noexcept = default;
    based_1d_addressing_model(based_1d_addressing_model const&) noexcept = default;
    based_1d_addressing_model(std::nullptr_t) noexcept;
    based_1d_addressing_model(size_type offset) noexcept;

    based_1d_addressing_model&  operator =(based_1d_addressing_model&&) noexcept = default;
    based_1d_addressing_model&  operator =(based_1d_addressing_model const&) noexcept = default;
    based_1d_addressing_model&  operator =(std::nullptr_t) noexcept;

    void*       address() const noexcept;
    size_type   offset() const noexcept;

    bool        equals(std::nullptr_t) const noexcept;
    bool        equals(void const* p) const noexcept;
    bool        equals(based_1d_addressing_model const& other) const noexcept;

    bool        greater_than(std::nullptr_t) const noexcept;
    bool        greater_than(void const* p) const noexcept;
    bool        greater_than(based_1d_addressing_model const& other) const noexcept;

    bool        less_than(std::nullptr_t) const noexcept;
    bool        less_than(void const* p) const noexcept;
    bool        less_than(based_1d_addressing_model const& other) const noexcept;

    void        assign_from(void const* p);

    void        decrement(difference_type dec) noexcept;
    void        increment(difference_type inc) noexcept;

  private:
    static  int const   null_offset = -1;

    int64_t     m_offset;
};

//------
//
template<typename SM> inline
based_1d_addressing_model<SM>::based_1d_addressing_model(std::nullptr_t) noexcept
:   m_offset{null_offset}
{}

template<typename SM> inline
based_1d_addressing_model<SM>::based_1d_addressing_model(size_type off) noexcept
:   m_offset{static_cast<int64_t>(off)}
{}

template<typename SM> inline
based_1d_addressing_model<SM>&
based_1d_addressing_model<SM>::operator =(std::nullptr_t) noexcept
{
    m_offset = null_offset;
    return *this;
}

//------
//
template<typename SM> inline
void*
based_1d_addressing_model<SM>::address() const noexcept
{
    return (m_offset == null_offset) ? nullptr : SM::first_segment_address() + m_offset;
}

template<typename SM> inline
typename based_1d_addressing_model<SM>::size_type
based_1d_addressing_model<SM>::offset() const noexcept
{
    return m_offset;
}

//------
//
template<typename SM> inline
bool
based_1d_addressing_model<SM>::equals(std::nullptr_t) const noexcept
{
    return m_offset == null_offset;
}

template<typename SM> inline
bool
based_1d_addressing_model<SM>::equals(void const* p) const noexcept
{
    return address() == p;
}

template<typename SM> inline
bool
based_1d_addressing_model<SM>::equals(based_1d_addressing_model const& other) const noexcept
{
    return address() == other.address();
}

//------
//
template<typename SM> inline
bool
based_1d_addressing_model<SM>::greater_than(std::nullptr_t) const noexcept
{
    return address() != nullptr;
}

template<typename SM> inline
bool
based_1d_addressing_model<SM>::greater_than(void const* p) const noexcept
{
    return address() > p;
}

template<typename SM> inline
bool
based_1d_addressing_model<SM>::greater_than(based_1d_addressing_model const& other) const noexcept
{
    return address() > other.address();
}

//------
//
template<typename SM> inline
bool
based_1d_addressing_model<SM>::less_than(std::nullptr_t) const noexcept
{
    return false;
}

template<typename SM> inline
bool
based_1d_addressing_model<SM>::less_than(void const* p) const noexcept
{
    return address() < p;
}

template<typename SM> inline
bool
based_1d_addressing_model<SM>::less_than(based_1d_addressing_model const& other) const noexcept
{
    return address() < other.address();
}

//------
//
template<typename SM>
void
based_1d_addressing_model<SM>::assign_from(void const* p) 
{
    char const*     p_data  = static_cast<char const*>(p);
    char const*     p_lower = SM::first_segment_address();

    m_offset = p_data - p_lower;
}

//------
//
template<typename SM> inline
void
based_1d_addressing_model<SM>::decrement(difference_type dec) noexcept
{
    m_offset -= dec;
}

template<typename SM> inline
void
based_1d_addressing_model<SM>::increment(difference_type inc) noexcept
{
    m_offset += inc;
}

#endif  //- 1D_ADDRESSING_H_DEFINED
