//==================================================================================================
//  File:
//      based_2d_storage.h
//
//  Summary:
//      Defines a simple two-dimensional based addressing model as a class template.
//
//  Copyright (c) 2017 Bob Steagall, KEWB Computing
//==================================================================================================
//
#include "based_1d_storage.h"
#include "based_2d_storage.h"
#include "wrapper_storage.h"
#include "leaky_allocation_strategy.h"

template class leaky_allocation_strategy<based_1d_storage_model>;
template class leaky_allocation_strategy<based_2d_storage_model>;
template class leaky_allocation_strategy<wrapper_storage_model>;
