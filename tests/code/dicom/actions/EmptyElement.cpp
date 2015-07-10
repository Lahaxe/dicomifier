/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <memory>

#define BOOST_TEST_MODULE ModuleEmptyElement
#include <boost/test/unit_test.hpp>

#include <dcmtk/dcmdata/dctk.h>

#include "dicom/actions/EmptyElement.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(Constructor)
{
    auto emptyelt = dicomifier::actions::EmptyElement::New();
    BOOST_REQUIRE(emptyelt != NULL);
    
    emptyelt = dicomifier::actions::EmptyElement::New(NULL, {});
    BOOST_REQUIRE(emptyelt != NULL);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Get/Set
 */
BOOST_AUTO_TEST_CASE(Accessors)
{
    auto emptyelt = dicomifier::actions::EmptyElement::New();
    
    DcmDataset dataset;
    emptyelt->set_dataset(&dataset);
    BOOST_CHECK(emptyelt->get_dataset() != NULL);
    
    emptyelt->set_tags({dicomifier::TagAndRange()});
    BOOST_CHECK_EQUAL(emptyelt->get_tags().size(), 1);
    
    emptyelt =
            dicomifier::actions::EmptyElement::New(&dataset,
                                                   {dicomifier::TagAndRange()});
    BOOST_CHECK(emptyelt->get_dataset() != NULL);
    BOOST_CHECK_EQUAL(emptyelt->get_tags().size(), 1);
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run
 */
struct TestDataOK03
{
    DcmDataset dataset;
    std::vector<dicomifier::TagAndRange> vect;
 
    TestDataOK03()
    {
        // Test VR = AE
        OFCondition condition =
                dataset.putAndInsertOFStringArray(DCM_PerformedStationAETitle,
                                                  OFString("ABCD"), true);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = AS
        condition = dataset.putAndInsertOFStringArray(DCM_PatientAge,
                                                      OFString("20Y"), true);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = AT => Not implemented
        
        // Test VR = CS
        condition = dataset.putAndInsertOFStringArray(DCM_PatientSex,
                                                      OFString("M"), true);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = DA
        condition = dataset.putAndInsertOFStringArray(DCM_StudyDate,
                                                      OFString("02052014"),
                                                      true);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = DS
        condition = dataset.putAndInsertOFStringArray(DCM_PatientWeight,
                                                      "60.5", true);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = DT
        condition =
                dataset.putAndInsertOFStringArray(DCM_AcquisitionDateTime,
                                                  OFString("02153202062013"),
                                                  true);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = FL
        condition = dataset.putAndInsertFloat32(DCM_StimulusArea, (Float32)15.2);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = FD
        condition = dataset.putAndInsertFloat64(DCM_PupilSize, 42.5);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = IS
        condition = dataset.putAndInsertOFStringArray(DCM_StageNumber,
                                                      "12", true);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = LO
        condition = dataset.putAndInsertOFStringArray(DCM_Manufacturer,
                                                      OFString("Machine1"),
                                                      true);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = LT
        condition =
                dataset.putAndInsertOFStringArray(DCM_AdditionalPatientHistory,
                                                  OFString("abc"), true);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = OB => Not implemented
        // Test VR = OD => Not implemented
        // Test VR = OF => Not implemented
        // Test VR = OW => Not implemented
        
        // Test VR = PN
        condition = dataset.putAndInsertOFStringArray(DCM_PatientName,
                                                      OFString("John"), true);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = SH
        condition = dataset.putAndInsertOFStringArray(DCM_AccessionNumber,
                                                      OFString("1234"), true);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = SL
        condition = dataset.putAndInsertSint32(DCM_ReferencePixelX0, 123);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = SQ
        DcmItem* item = new DcmItem(DCM_OtherPatientIDsSequence);
        item->putAndInsertOFStringArray(DCM_PatientID, "123");
        condition = dataset.insertSequenceItem(DCM_OtherPatientIDsSequence,
                                               item);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = SS
        condition = dataset.putAndInsertSint16(DCM_TagAngleSecondAxis, 123);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = ST
        condition = dataset.putAndInsertOFStringArray(DCM_InstitutionAddress,
                                                      OFString("ABC"), true);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = TM
        condition = dataset.putAndInsertOFStringArray(DCM_StudyTime,
                                                      OFString("012345"), true);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = UI
        condition = dataset.putAndInsertOFStringArray(DCM_SOPClassUID,
                                                      OFString("12345678"),
                                                      true);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = UL
        condition = dataset.putAndInsertUint32(DCM_RegionFlags, 123);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = UN => Not implemented
        
        // Test VR = US
        condition = dataset.putAndInsertUint16(DCM_FailureReason, 123);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = UT
        OFString name("myUnlimitedText");
        condition = dataset.putAndInsertOFStringArray(DCM_PixelDataProviderURL,
                                                      name, true);
        BOOST_REQUIRE(condition.good());
    }
 
    ~TestDataOK03()
    {
        // Nothing to do
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK03)
{
    dicomifier::actions::EmptyElement::Pointer testempty = NULL;
    
    // Test VR = AE
    BOOST_CHECK(dataset.tagExists(DCM_PerformedStationAETitle));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PerformedStationAETitle, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_PerformedStationAETitle));
    
    // Test VR = AS
    BOOST_CHECK(dataset.tagExists(DCM_PatientAge));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientAge, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_PatientAge));
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    BOOST_CHECK(dataset.tagExists(DCM_PatientSex));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientSex, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_PatientSex));
    
    // Test VR = DA
    BOOST_CHECK(dataset.tagExists(DCM_StudyDate));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_StudyDate, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_StudyDate));
    
    // Test VR = DS
    BOOST_CHECK(dataset.tagExists(DCM_PatientWeight));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientWeight, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_PatientWeight));
    
    // Test VR = DT
    BOOST_CHECK(dataset.tagExists(DCM_AcquisitionDateTime));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_AcquisitionDateTime, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_AcquisitionDateTime));
    
    // Test VR = FL
    BOOST_CHECK(dataset.tagExists(DCM_StimulusArea));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_StimulusArea, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_StimulusArea));
    
    // Test VR = FD
    BOOST_CHECK(dataset.tagExists(DCM_PupilSize));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PupilSize, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_PupilSize));
    
    // Test VR = IS
    BOOST_CHECK(dataset.tagExists(DCM_StageNumber));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_StageNumber, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_StageNumber));
    
    // Test VR = LO
    BOOST_CHECK(dataset.tagExists(DCM_Manufacturer));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_Manufacturer, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_Manufacturer));
    
    // Test VR = LT
    BOOST_CHECK(dataset.tagExists(DCM_AdditionalPatientHistory));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_AdditionalPatientHistory, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_AdditionalPatientHistory));
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    BOOST_CHECK(dataset.tagExists(DCM_PatientName));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientName, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_PatientName));
    
    // Test VR = SH
    BOOST_CHECK(dataset.tagExists(DCM_AccessionNumber));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_AccessionNumber, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_AccessionNumber));
    
    // Test VR = SL
    BOOST_CHECK(dataset.tagExists(DCM_ReferencePixelX0));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_ReferencePixelX0, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_ReferencePixelX0));
    
    // Test VR = SQ
    BOOST_CHECK(dataset.tagExists(DCM_OtherPatientIDsSequence));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_OtherPatientIDsSequence, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_OtherPatientIDsSequence));
    
    // Test VR = SS
    BOOST_CHECK(dataset.tagExists(DCM_TagAngleSecondAxis));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_TagAngleSecondAxis, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_TagAngleSecondAxis));
    
    // Test VR = ST
    BOOST_CHECK(dataset.tagExists(DCM_InstitutionAddress));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_InstitutionAddress, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_InstitutionAddress));
    
    // Test VR = TM
    BOOST_CHECK(dataset.tagExists(DCM_StudyTime));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_StudyTime, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_StudyTime));
    
    // Test VR = UI
    BOOST_CHECK(dataset.tagExists(DCM_SOPClassUID));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_SOPClassUID, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_SOPClassUID));
    
    // Test VR = UL
    BOOST_CHECK(dataset.tagExists(DCM_RegionFlags));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_RegionFlags, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_RegionFlags));
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    BOOST_CHECK(dataset.tagExists(DCM_FailureReason));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_FailureReason, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_FailureReason));
    
    // Test VR = UT
    BOOST_CHECK(dataset.tagExists(DCM_PixelDataProviderURL));
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PixelDataProviderURL, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    BOOST_CHECK(dataset.tagExists(DCM_PixelDataProviderURL));
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Empty public attribut (not in sequence)
 */
struct TestDataOK04
{
    DcmDataset dataset;
 
    TestDataOK04()
    {
        // Insert testing value
        OFCondition condition = dataset.putAndInsertOFStringArray(
                        DCM_Modality, "value1\\value2\\value3\\value4");
        BOOST_REQUIRE(condition.good());

        DcmItem* item = new DcmItem(DCM_OtherPatientIDsSequence);
        item->putAndInsertOFStringArray(DCM_PatientID, "123\\456\\789");
        condition = dataset.insertSequenceItem(DCM_OtherPatientIDsSequence,
                                               item);
        BOOST_REQUIRE(condition.good());
    }
 
    ~TestDataOK04()
    {
        // Nothing to do
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_04, TestDataOK04)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_Modality,
                                           dicomifier::Range(0,1)));
    
    auto testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
        
    DcmElement * element = NULL;
    OFCondition condition = dataset.findAndGetElement(DCM_Modality,
                                                      element);
    BOOST_CHECK(condition.good());
    BOOST_CHECK(element != NULL);
    
    OFString str;
    condition = dataset.findAndGetOFStringArray(DCM_Modality, str);
    BOOST_CHECK(condition.good());
    
    BOOST_CHECK_EQUAL(str, "");
}

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: Empty public attribut (in sequence)
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_05, TestDataOK04)
{
    // check DCM_Modality in dataset
    BOOST_CHECK(dataset.tagExists(DCM_PatientID, OFTrue));
    
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(
                       DCM_OtherPatientIDsSequence, dicomifier::Range(0,1)));
    vect.push_back(dicomifier::TagAndRange(
                       DCM_PatientID,
                       dicomifier::Range(0,std::numeric_limits<int>::max())));
    
    auto testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    
    testempty->run();
        
    // check DCM_Modality delete
    BOOST_CHECK(dataset.tagExists(DCM_PatientID, OFTrue));
    
    OFString str;
    OFCondition condition = dataset.findAndGetOFStringArray(DCM_PatientID,
                                                            str, true);
    BOOST_CHECK(condition.good());
    
    BOOST_CHECK_EQUAL(str, "");
}

/*************************** TEST OK 06 *******************************/
/**
 * Nominal test case: Add public attribut
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_06, TestDataOK04)
{
    BOOST_REQUIRE(!dataset.tagExists(DCM_PatientName));
                      
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_PatientName, 
                   dicomifier::Range(0,1)));
    auto testempty = dicomifier::actions::EmptyElement::New(&dataset, vect);
    testempty->run();
    
    BOOST_CHECK(dataset.tagExists(DCM_PatientName));
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Empty dataset
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    auto testempty = dicomifier::actions::EmptyElement::New();
        
    BOOST_REQUIRE_THROW(testempty->run(), dicomifier::DicomifierException);
}
