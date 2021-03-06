/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "bruker/converters/pixel_data_converter.h"

#include <fstream>
#include <string>

#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/registry.h>

#include <boost/filesystem.hpp>

#include "bruker/Dataset.h"
#include "core/DicomifierException.h"
#include "core/Endian.h"

namespace dicomifier
{

namespace bruker
{

pixel_data_converter
::pixel_data_converter()
: _filename(""), _rescaleintercept(0), _rescaleslope(1)
{
    // Nothing else
}

pixel_data_converter
::~pixel_data_converter()
{
    // Nothing to do.
}

void
pixel_data_converter
::operator()(unsigned int frame_size, unsigned int frame_index,
             std::string const & filename, std::string const & word_type,
             std::string const & file_byte_order,
             dcmtkpp::DataSet & dicom_data_set)
{
    this->_set_data_set(filename, word_type, file_byte_order);

    dcmtkpp::Value::Binary pixel_data;

    if (word_type == "_32BIT_SGN_INT")
    {
        pixel_data = this->_read_pixel_data<int32_t>(frame_size, frame_index);
    }
    else if (word_type == "_16BIT_SGN_INT")
    {
        pixel_data = this->_read_pixel_data<int16_t>(frame_size, frame_index);
    }
    else if (word_type == "_8BIT_UNSGN_INT")
    {
        pixel_data = this->_read_pixel_data<uint8_t>(frame_size, frame_index);
    }
    else if (word_type == "_32BIT_FLOAT")
    {
        pixel_data = this->_read_pixel_data<float>(frame_size, frame_index);
    }
    else
    {
        throw DicomifierException("Unknown value for field VisuCoreWordType");
    }

    dicom_data_set.add(dcmtkpp::registry::PixelData,
                       pixel_data, dcmtkpp::VR::OW);
}

double
pixel_data_converter
::get_rescaleintercept() const
{
    return this->_rescaleintercept;
}

double
pixel_data_converter
::get_rescaleslope() const
{
    return this->_rescaleslope;
}

void
pixel_data_converter
::_set_data_set(std::string const & filename,
                std::string const & word_type,
                std::string const & file_byte_order)
{
    if(filename != this->_filename)
    {
        if (!boost::filesystem::is_regular_file(filename))
        {
            std::stringstream error;
            error << "Could not open file: " << filename;
            throw DicomifierException(error.str());
        }

        // read pixel data
        std::ifstream stream(filename, std::ifstream::binary);
        stream.seekg(0, stream.end);
        auto const size = stream.tellg();
        stream.seekg(0, stream.beg);

        this->_pixel_data.resize(size);
        stream.read((char*)(&this->_pixel_data[0]), size);

        auto const file_is_big_endian = (file_byte_order == "bigEndian");
        auto const system_is_big_endian = dicomifier::endian::is_big_endian();
        if(system_is_big_endian != file_is_big_endian)
        {
            // Flip to native order
            if (word_type == "_32BIT_SGN_INT")
            {
                this->_flip<int32_t>();
            }
            else if (word_type == "_16BIT_SGN_INT")
            {
                this->_flip<int16_t>();
            }
            else if (word_type == "_8BIT_UNSGN_INT")
            {
                this->_flip<uint8_t>();
            }
            else if (word_type == "_32BIT_FLOAT")
            {
                this->_flip<float>();
            }
        }

        if (word_type == "_32BIT_SGN_INT")
        {
            this->_update_min_max<int32_t>();

            this->_rescaleintercept = this->_min;
            this->_rescaleslope = double(this->_max-this->_min) / exp2(16.0);
        }
        else if (word_type == "_16BIT_SGN_INT")
        {
            this->_update_min_max<int16_t>();

            this->_rescaleintercept = -exp2(15);
            this->_rescaleslope     = 1;
        }
        else if (word_type == "_8BIT_UNSGN_INT")
        {
            this->_update_min_max<uint8_t>();

            this->_rescaleintercept = 0;
            this->_rescaleslope     = 1;
        }
        else if (word_type == "_32BIT_FLOAT")
        {
            this->_update_min_max<float>();

            this->_rescaleintercept = (double)this->_min;
            this->_rescaleslope     = (this->_max-this->_min) / exp2(16.0);
        }

        this->_filename = filename;
    }
}

} // namespace bruker

} // namespace dicomifier
