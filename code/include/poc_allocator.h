//==================================================================================================
//  File:
//      poc_allocator.h
//
//  Summary:
//      Defines the poc_allocator<T> class template (relocatable heap experimental allocator).
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#ifndef POC_ALLOCATOR_H_DEFINED
#define POC_ALLOCATOR_H_DEFINED

#include <type_traits>
#include <memory>

//--------------------------------------------------------------------------------------------------
//  Class Template:
//      poc_allocator<T, POCCA, POCMA, POCS, EQ>
//
//  Summary:
//      This class template implements a standard-conforming allocator that uses the pointer
//      interface and allocation strategy expressed by its second template parameter to allocate
//      memory for representing objects of type T.
//--------------------------------------------------------------------------------------------------
//
template<class T, class POCCA, class POCMA, class POCS, bool EQ>
class poc_allocator
{
  public:
    using propagate_on_container_copy_assignment = POCCA;
    using propagate_on_container_move_assignment = POCMA;
    using propagate_on_container_swap            = POCS;

    using difference_type       = std::ptrdiff_t;
    using size_type             = std::size_t;
    using void_pointer          = void*;
    using const_void_pointer    = void const*;
    using pointer               = T*;
    using const_pointer         = T const*;
    using reference             = T&;
    using const_reference       = T const&;
    using value_type            = T;
    using element_type          = T;

    template<class U>
    struct rebind
    {
        using other = poc_allocator<U, POCCA, POCMA, POCS, EQ>;
    };

  public:
    poc_allocator();
    poc_allocator(poc_allocator&& src) noexcept;
    poc_allocator(const poc_allocator& src) noexcept;
    template<class U>
    poc_allocator(const poc_allocator<U, POCCA, POCMA, POCS, EQ>& src) noexcept;
    ~poc_allocator();

    poc_allocator&  operator =(poc_allocator&& vRhs) noexcept;
    poc_allocator&  operator =(const poc_allocator& vRhs) noexcept;

    T*          address(reference t) const noexcept;
    T const*    address(const_reference t) const noexcept;

    pointer     allocate(size_type n);
    pointer     allocate(size_type n, const_void_pointer p);
    void        deallocate(pointer p, size_type n);

    template<class U, class... Args>
    void        construct(U* p, Args&&... args);

    template<class U>
    void        destroy(U* p);

    std::allocator<T>   m_heap;
};


//--------------------------------------------------------------------------------------------------
//  Class Template:
//      poc_allocator<void>
//
//  Summary:
//      This class is a partial specialization poc_allocator for type T=void.
//--------------------------------------------------------------------------------------------------
//
template<class POCCA, class POCMA, class POCS, bool EQ>
class poc_allocator<void, POCCA, POCMA, POCS, EQ>
{
  public:
    using propagate_on_container_copy_assignment = POCCA;
    using propagate_on_container_move_assignment = POCMA;
    using propagate_on_container_swap            = POCS;

    using difference_type       = std::ptrdiff_t;
    using size_type             = std::size_t;
    using void_pointer          = void*;
    using const_void_pointer    = void const*;

    template<class U>
    struct rebind
    {
        using other = poc_allocator<U, POCCA, POCMA, POCS, EQ>;
    };

};


//--------------------------------------------------------------------------------------------------
//  Facility:   poc_allocator<T>
//--------------------------------------------------------------------------------------------------
//
template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
poc_allocator<T, POCCA, POCMA, POCS, EQ>::poc_allocator()
:   m_heap()
{}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
poc_allocator<T, POCCA, POCMA, POCS, EQ>::poc_allocator(poc_allocator&& src) noexcept
:   m_heap(std::move(src.m_heap))
{}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
poc_allocator<T, POCCA, POCMA, POCS, EQ>::poc_allocator(const poc_allocator& src) noexcept
:   m_heap(src.m_heap)
{}

template<class T, class POCCA, class POCMA, class POCS, bool EQ>
template<class U> inline
poc_allocator<T, POCCA, POCMA, POCS, EQ>::poc_allocator(const poc_allocator<U, POCCA, POCMA, POCS, EQ>& src) noexcept
:   m_heap(src.m_heap)
{}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
poc_allocator<T, POCCA, POCMA, POCS, EQ>::~poc_allocator()
{}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
poc_allocator<T, POCCA, POCMA, POCS, EQ>&
poc_allocator<T, POCCA, POCMA, POCS, EQ>::operator =(poc_allocator&& vRhs) noexcept
{
    m_heap = std::move(vRhs.m_heap);
    return *this;
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
poc_allocator<T, POCCA, POCMA, POCS, EQ>&
poc_allocator<T, POCCA, POCMA, POCS, EQ>::operator =(const poc_allocator& vRhs) noexcept
{
    if (&vRhs != this)
    {
        m_heap = vRhs.m_heap;
    }
    return *this;
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
T*
poc_allocator<T, POCCA, POCMA, POCS, EQ>::address(reference t) const noexcept
{
    return &t;
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
T const*
poc_allocator<T, POCCA, POCMA, POCS, EQ>::address(const_reference t) const noexcept
{
    return &t;
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
typename poc_allocator<T, POCCA, POCMA, POCS, EQ>::pointer
poc_allocator<T, POCCA, POCMA, POCS, EQ>::allocate(size_type n)
{
    return m_heap.allocate(n);
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
typename poc_allocator<T, POCCA, POCMA, POCS, EQ>::pointer
poc_allocator<T, POCCA, POCMA, POCS, EQ>::allocate(size_type n, const_void_pointer)
{
    return m_heap.allocate(n);
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
void
poc_allocator<T, POCCA, POCMA, POCS, EQ>::deallocate(pointer p, size_type n)
{
    m_heap.deallocate(p, n);
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ>
template<class U, class... Args> inline
void
poc_allocator<T, POCCA, POCMA, POCS, EQ>::construct(U* p, Args&&... args)
{
    ::new ((void*) p) U(std::forward<Args>(args)...);
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ>
template<class U> inline
void
poc_allocator<T, POCCA, POCMA, POCS, EQ>::destroy(U* p)
{
    p->~U();
}


//--------------------------------------------------------------------------------------------------
//  Facility:   poc_allocator<T> Comparison Operators
//--------------------------------------------------------------------------------------------------
//
template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline bool
operator ==(const poc_allocator<T, POCCA, POCMA, POCS, EQ>&, const poc_allocator<T, POCCA, POCMA, POCS, EQ>&)
{
    return EQ;
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline bool
operator !=(const poc_allocator<T, POCCA, POCMA, POCS, EQ>&, const poc_allocator<T, POCCA, POCMA, POCS, EQ>&)
{
    return !EQ;
}

//--------------------------------------------------------------------------------------------------
//  Class Template:
//      syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>
//
//  Summary:
//      This class template implements a standard-conforming allocator that uses the pointer
//      interface and allocation strategy expressed by its second template parameter to allocate
//      memory for representing objects of type T.
//--------------------------------------------------------------------------------------------------
//
template<class T, class POCCA, class POCMA, class POCS, bool EQ>
class syn_poc_allocator
{
  public:
    using propagate_on_container_copy_assignment = POCCA;
    using propagate_on_container_move_assignment = POCMA;
    using propagate_on_container_swap            = POCS;

    using difference_type       = std::ptrdiff_t;
    using size_type             = std::size_t;
    using void_pointer          = syn_ptr<void, wrapper_addressing_model>;
    using const_void_pointer    = syn_ptr<void const*, wrapper_addressing_model>;
    using pointer               = syn_ptr<T, wrapper_addressing_model>;
    using const_pointer         = syn_ptr<T const, wrapper_addressing_model>;
    using reference             = T&;
    using const_reference       = T const&;
    using value_type            = T;
    using element_type          = T;

    template<class U>
    struct rebind
    {
        using other = syn_poc_allocator<U, POCCA, POCMA, POCS, EQ>;
    };

  public:
    syn_poc_allocator();
    syn_poc_allocator(syn_poc_allocator&& src) noexcept;
    syn_poc_allocator(const syn_poc_allocator& src) noexcept;
    template<class U>
    syn_poc_allocator(const syn_poc_allocator<U, POCCA, POCMA, POCS, EQ>& src) noexcept;
    ~syn_poc_allocator();

    syn_poc_allocator&  operator =(syn_poc_allocator&& vRhs) noexcept;
    syn_poc_allocator&  operator =(const syn_poc_allocator& vRhs) noexcept;

    T*          address(reference t) const noexcept;
    T const*    address(const_reference t) const noexcept;

    pointer     allocate(size_type n);
    pointer     allocate(size_type n, const_void_pointer p);
    void        deallocate(pointer p, size_type n);

    template<class U, class... Args>
    void        construct(U* p, Args&&... args);

    template<class U>
    void        destroy(U* p);

    std::allocator<T>   m_heap;
};


//--------------------------------------------------------------------------------------------------
//  Class Template:
//      syn_poc_allocator<void>
//
//  Summary:
//      This class is a partial specialization syn_poc_allocator for type T=void.
//--------------------------------------------------------------------------------------------------
//
template<class POCCA, class POCMA, class POCS, bool EQ>
class syn_poc_allocator<void, POCCA, POCMA, POCS, EQ>
{
  public:
    using propagate_on_container_copy_assignment = POCCA;
    using propagate_on_container_move_assignment = POCMA;
    using propagate_on_container_swap            = POCS;

    using difference_type       = std::ptrdiff_t;
    using size_type             = std::size_t;
    using void_pointer          = syn_ptr<void, wrapper_addressing_model>;
    using const_void_pointer    = syn_ptr<void const*, wrapper_addressing_model>;

    template<class U>
    struct rebind
    {
        using other = syn_poc_allocator<U, POCCA, POCMA, POCS, EQ>;
    };

};


//--------------------------------------------------------------------------------------------------
//  Facility:   syn_poc_allocator<T>
//--------------------------------------------------------------------------------------------------
//
template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::syn_poc_allocator()
:   m_heap()
{}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::syn_poc_allocator(syn_poc_allocator&& src) noexcept
:   m_heap(std::move(src.m_heap))
{}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::syn_poc_allocator(const syn_poc_allocator& src) noexcept
:   m_heap(src.m_heap)
{}

template<class T, class POCCA, class POCMA, class POCS, bool EQ>
template<class U> inline
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::syn_poc_allocator(const syn_poc_allocator<U, POCCA, POCMA, POCS, EQ>& src) noexcept
:   m_heap(src.m_heap)
{}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::~syn_poc_allocator()
{}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>&
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::operator =(syn_poc_allocator&& vRhs) noexcept
{
    m_heap = std::move(vRhs.m_heap);
    return *this;
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>&
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::operator =(const syn_poc_allocator& vRhs) noexcept
{
    if (&vRhs != this)
    {
        m_heap = vRhs.m_heap;
    }
    return *this;
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
T*
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::address(reference t) const noexcept
{
    return &t;
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
T const*
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::address(const_reference t) const noexcept
{
    return &t;
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
typename syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::pointer
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::allocate(size_type n)
{
    return m_heap.allocate(n);
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
typename syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::pointer
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::allocate(size_type n, const_void_pointer)
{
    return m_heap.allocate(n);
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline
void
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::deallocate(pointer p, size_type n)
{
    m_heap.deallocate(p, n);
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ>
template<class U, class... Args> inline
void
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::construct(U* p, Args&&... args)
{
    ::new ((void*) p) U(std::forward<Args>(args)...);
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ>
template<class U> inline
void
syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>::destroy(U* p)
{
    p->~U();
}


//--------------------------------------------------------------------------------------------------
//  Facility:   syn_poc_allocator<T> Comparison Operators
//--------------------------------------------------------------------------------------------------
//
template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline bool
operator ==(const syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>&, const syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>&)
{
    return EQ;
}

template<class T, class POCCA, class POCMA, class POCS, bool EQ> inline bool
operator !=(const syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>&, const syn_poc_allocator<T, POCCA, POCMA, POCS, EQ>&)
{
    return !EQ;
}

#endif  //-  POC_ALLOCATOR_H_DEFINED
