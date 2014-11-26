/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7c03e687_e027_4fe3_afcf_f662183ce97e
#define _7c03e687_e027_4fe3_afcf_f662183ce97e

#include "translator/filters/PatientSexFilter.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The PatientSexFilterCreator class
 */
class PatientSexFilterCreator : public TranslationCreatorBase
{
public:
    typedef PatientSexFilterCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of PatientSexFilterCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of PatientSexFilterCreator
    virtual ~PatientSexFilterCreator();

    /**
     * @brief Create Pointer to class PatientSexFilter
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new PatientSexFilter
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return PatientSexFilter
     */
    static std::string get_class_name() { return "PatientSexFilter"; }
    
protected:
    /// Create an instance of PatientSexFilterCreator
    PatientSexFilterCreator();

private:
    PatientSexFilterCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorPatientSexFilterCreator
    {
        std::vector<dicomifier::translator::Tag::Pointer> pttag;
        mutable dicomifier::translator::Tag::Pointer patientsexfilter;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory

} // namespace translator

} // namespace dicomifier

#endif // _7c03e687_e027_4fe3_afcf_f662183ce97e

