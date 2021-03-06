/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _aadcd4c0_06e4_4f4b_a971_84a27d60375c
#define _aadcd4c0_06e4_4f4b_a971_84a27d60375c

#include <string>
#include <memory>

namespace dicomifier
{
    
/**
 * @brief Base class for all dicomifier object
 */
class Object
{
public:
    typedef Object Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /// Create pointer to new instance of Object
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of Object
    virtual ~Object() {}
    
    /**
     * Get this class name
     * @return this class name
     */
    static std::string get_class_name() { return "Object"; }
    
protected:
    /// Create an instance of Object
    Object() {}

private:
    Object(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
    
};
    
} // namespace dicomifier

#endif // _aadcd4c0_06e4_4f4b_a971_84a27d60375c
