/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _cae2b9c2_c9ae_411e_ae03_5e41d3fa55e4
#define _cae2b9c2_c9ae_411e_ae03_5e41d3fa55e4

#include "Factory.h"

#include <memory>

namespace dicomifier
{
    
template<typename T>
unsigned int
Factory
::register_()
{
    this->_creators.insert(std::make_pair(
        T::get_class_name(), [] () { return T::New(); }));
    return this->_creators.size();
}
    
} // namespace dicomifier

#endif // _cae2b9c2_c9ae_411e_ae03_5e41d3fa55e4
