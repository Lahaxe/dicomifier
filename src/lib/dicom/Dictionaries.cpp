/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <dcmtkpp/registry.h>

#include "Dictionaries.h"

namespace dicomifier
{
    
Dictionaries * Dictionaries::_instance = NULL;

Dictionaries::Dictionaries()
{
    // Create public dictionary
    this->AddPublicDictionary();
}

Dictionaries::~Dictionaries()
{
    // Nothing to do
}

Dictionaries& 
Dictionaries
::get_instance()
{
    if (Dictionaries::_instance == NULL)
    {
        Dictionaries::_instance = new Dictionaries();
    }
    return *Dictionaries::_instance;
}

void
Dictionaries
::delete_instance()
{
    if (Dictionaries::_instance != NULL)
    {
        delete Dictionaries::_instance;
        Dictionaries::_instance = NULL;
    }
}

void 
Dictionaries
::ParsePrivateDictionary(std::string const & filename)
{
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml(filename, pt);
    
    // Get Dictionary Title
    std::string title = pt.get<std::string>("book.title");
    
    // Create pointer
    auto publicdict = Dictionary::New();
    
    // Get private Tag
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
            pt.get_child("book.chapter.table.tbody"))
    {
        std::vector<std::string> values = { title };
        
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v2, 
                      v.second.equal_range("td"))
        {
            values.push_back(v2.second.get<std::string>("para"));
        }
        
        std::string tagkey = values[1].substr(1,9);
        
        std::string groupstr = values[1].substr(1,4);
        Uint16 group = std::strtol(groupstr.c_str(), NULL, 16);
        
        std::string elementstr = values[1].substr(8,2);
        Uint16 element = std::strtol(elementstr.c_str(), NULL, 16);

        std::vector<std::string> splitvalues;
        boost::split(splitvalues, values[5], boost::is_any_of("-"));
        
        int vmMin = std::atoi(splitvalues[0].c_str());
        
        int vmMax = vmMin;
        if (splitvalues.size() == 2)
        {
            if (splitvalues[1] == "n")
                vmMax = DcmVariableVM;
            else
            {
                vmMax = std::atoi(splitvalues[1].c_str());
            }
        }
        
        DcmDictEntry* dictentry = 
            new DcmDictEntry(group, element,
                             DcmVR(values[4].c_str()),
                             values[3].c_str(),
                             vmMin, vmMax,
                             NULL, OFTrue,
                             values[0].c_str());
                                       
        publicdict->AddDictEntry(dictentry, values[3], tagkey);
    }
    
    // Add into map
    this->_dictionaries.insert(
                std::pair<std::string, Dictionary::Pointer>(title, publicdict));
}

void 
Dictionaries
::AddPublicDictionary()
{
    // Create pointer
    auto publicdict = Dictionary::New();

    for(auto it = dcmtkpp::registry::public_dictionary.begin();
        it != dcmtkpp::registry::public_dictionary.end(); ++it)
    {
        std::vector<std::string> splitvalues;
        boost::split(splitvalues, it->second.vm, boost::is_any_of("-"));

        int vmMin = std::atoi(splitvalues[0].c_str());

        int vmMax = vmMin;
        if (splitvalues.size() == 2)
        {
            if (splitvalues[1] == "n")
                vmMax = DcmVariableVM;
            else
            {
                vmMax = std::atoi(splitvalues[1].c_str());
            }
        }

        DcmDictEntry * entry = new DcmDictEntry(it->first.group,
                                                it->first.element,
                                                DcmVR(it->second.vr.c_str()),
                                                it->second.keyword.c_str(),
                                                vmMin, vmMax,
                                                NULL, OFTrue,
                                                NULL);

        publicdict->AddDictEntry(entry);
    }

    // Add into map
    this->_dictionaries.insert(
                std::pair<std::string, Dictionary::Pointer>("public",
                                                            publicdict));
}

DcmTag 
Dictionaries
::GetTagFromName(std::string const & name,
                 std::string const & dict, bool & finalypublic)
{
    if (this->_dictionaries.find(dict) == this->_dictionaries.end())
    {
        throw DicomifierException("Unknown private dictionary : " + dict);
    }
    Dictionary::Pointer dico = this->_dictionaries[dict];
    
    finalypublic = false;
    DcmDictEntry* entry = NULL;
    try
    {
        // Look in the given dictionary
        entry = dico->GetEntryFromName(name);
    }
    catch (DicomifierException const & exc)
    {
        // not find, try in the public dictionary
        dico = this->_dictionaries["public"];
        entry = dico->GetEntryFromName(name);
        
        finalypublic = true;
    }
    
    DcmTag tag(*entry);
    tag.setVR(entry->getVR());
    if (dict != "public" && !finalypublic) tag.setPrivateCreator(dict.c_str());
    
    return tag;
}

DcmTag 
Dictionaries
::GetTagFromKey(std::string const & key,
                std::string const & dict, bool & finalypublic)
{
    if (this->_dictionaries.find(dict) == this->_dictionaries.end())
    {
        throw DicomifierException("Unknown private dictionary : " + dict);
    }
    Dictionary::Pointer dico = this->_dictionaries[dict];
    
    finalypublic = false;
    DcmDictEntry* entry = NULL;
    try
    {
        // Look in the given dictionary
        entry = dico->GetEntryFromKey(key);
    }
    catch (DicomifierException const & exc)
    {
        // not find, try in the public dictionary
        dico = this->_dictionaries["public"];
        entry = dico->GetEntryFromKey(key);
        
        finalypublic = true;
    }
    
    DcmTag tag(*entry, entry->getVR());
    if (dict != "public" && !finalypublic) tag.setPrivateCreator(dict.c_str());
    
    return tag;
}

Uint16 
Dictionaries
::FindCreatorElementNumber(std::string const & privatecreator, 
                           DcmDataset* dataset)
{
    if (dataset == NULL || privatecreator == "public")
    {
        return 0x00FF;
    }
    
    Uint16 group = this->_dictionaries[privatecreator]->get_privateGroup();
    
    Uint16 firstfree = 0x000F;
    Uint16 current = 0x000F;
    while (current < 0x00FF)
    {
        current++;
        OFString result;
        OFCondition condition =
                dataset->findAndGetOFString(DcmTagKey(group, current), result);
        if (condition.good())
        {
            if (result.c_str() == privatecreator)
            {
                return current;
            }
        }
        else if (firstfree == 0x000F)
        {
            firstfree = current;
        }
    }
    
    // insert private dictionary name
    dataset->putAndInsertString(DcmTag(group, firstfree),
                                privatecreator.c_str());
    
    return firstfree;
}

std::string
Dictionaries
::public_dictionary_as_json()
{
    std::stringstream stream;
    stream << "{";

    bool first = true;
    for(auto it = dcmtkpp::registry::public_dictionary.begin();
        it != dcmtkpp::registry::public_dictionary.end(); ++it)
    {
        if (!first)
        {
            stream << ",";
        }
        first = false;

        stream << "\"" << it->second.keyword
               << "\": [\"" << it->second.vr
               << "\",\"" << std::string(it->first) << "\"]";
    }

    stream << "}";

    return stream.str();
}

} // namespace dicomifier
