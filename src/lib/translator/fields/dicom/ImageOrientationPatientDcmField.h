/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _4364dec2_af5c_4c9f_94ad_45e86d4e4bc8
#define _4364dec2_af5c_4c9f_94ad_45e86d4e4bc8

#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class ImageOrientationPatientDcmField : public SubTag<VR>
{
public:
    typedef ImageOrientationPatientDcmField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of ImageOrientationPatientDcmField
    static Pointer New();
    
    virtual ~ImageOrientationPatientDcmField();
                     
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmDataset* dataset);
    
    virtual ClassType get_class_type() const 
            { return ECT_ImageOrientationPatientDcmField; }

protected:
    ImageOrientationPatientDcmField();

private:

};
    
} // namespace translator
    
} // namespace dicomifier

#include "ImageOrientationPatientDcmField.txx"

#endif // _4364dec2_af5c_4c9f_94ad_45e86d4e4bc8