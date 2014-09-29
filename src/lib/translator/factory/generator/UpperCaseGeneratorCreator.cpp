/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>

#include "UpperCaseGeneratorCreator.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration = TranslatorFactory::get_instance().register_<UpperCaseGeneratorCreator>(); 

UpperCaseGeneratorCreator
::UpperCaseGeneratorCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

UpperCaseGeneratorCreator
::~UpperCaseGeneratorCreator()
{
    // Nothing to do
}

Tag::Pointer 
UpperCaseGeneratorCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    std::vector<dicomifier::translator::Tag::Pointer> pttag;
    BOOST_FOREACH(boost::property_tree::ptree::value_type &child, value.second)
    {
        if (dicomifier::translator::
                TranslatorFactory::get_instance().can_create(child.first.data()))
        {
            pttag.push_back(dicomifier::translator::
                    TranslatorFactory::get_instance().create(child,
                                                             dataset,
                                                             evr));
        }
    }
    
    TranslatorUpperCaseGeneratorCreator action;
    action.pttag = pttag;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.uppercasegenerator;
}

template<>
void 
UpperCaseGeneratorCreator::TranslatorUpperCaseGeneratorCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Create SQ Element");
}

template<DcmEVR VR> 
void 
UpperCaseGeneratorCreator::TranslatorUpperCaseGeneratorCreator
::run() const
{
    uppercasegenerator = 
        dicomifier::translator::UpperCaseGenerator<VR>::New(pttag[0]);
}
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
    


