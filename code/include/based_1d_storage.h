//==================================================================================================
//  File:
//      based_1d_storage.h
//
//  Summary:
//      Defines a simple storage model that uses the wrapper addressing model.
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#ifndef BASED_1D_STORAGE_H_DEFINED
#define BASED_1D_STORAGE_H_DEFINED

#include "storage_base.h"
#include "based_1d_addressing.h"

//--------------------------------------------------------------------------------------------------
//  Class:
//      based_1d_storage_model
//
//  Summary:
//      This base class implements a based 1D storage model using the facilities provided by
//      the "storage_model_base" base class.  For this model, all allocations occur from the
//      first segment, making it appear as if there is only one segment.
//--------------------------------------------------------------------------------------------------
//
class based_1d_storage_model : public storage_model_base
{
  public:
    using addressing_model = based_1d_addressing_model<based_1d_storage_model>;

    static  addressing_model    segment_pointer(size_type, size_type offset);
};

//------
//
inline based_1d_storage_model::addressing_model
based_1d_storage_model::segment_pointer(size_type, size_type offset) 
{
    return addressing_model{offset};
}

#endif  //- BASED_1D_STORAGE_H_DEFINED
