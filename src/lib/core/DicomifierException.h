/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7e73d887_9f2a_46ba_a4bd_049bb2aebd97
#define _7e73d887_9f2a_46ba_a4bd_049bb2aebd97

#include <exception>
#include <string>

namespace dicomifier
{
    
/**
 * \class BrukerException
 * \brief Generic exception
 */
class DicomifierException: public std::exception
{
public:
    DicomifierException(const std::string& message):
        m_message(message) {}

    ~DicomifierException() throw() {}
    
    virtual const char* what() const throw() {
        return m_message.c_str();
    }
    
protected:
   std::string m_message;

private:

};

} // namespace dicomifier

#endif // _7e73d887_9f2a_46ba_a4bd_049bb2aebd97
