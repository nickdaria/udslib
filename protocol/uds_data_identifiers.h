#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Data Identifiers for 0x22 Read Data By Identifier
 *  https://piembsystech.com/data-identifiers-did-of-uds-protocol-iso-14229/
 * 
 */
typedef enum {
    /* 0x0000 - 0x00FF: ISO SAE Reserved */

    /* 0x0100 - 0xA5FF: Vehicle Manufacturer Specific */

    /* 0xA600 - 0xA7FF: Reserved for Legislative Use */

    /* 0xA800 - 0xACFF: Vehicle Manufacturer Specific */

    /* 0xAD00 - 0xAFFF: Reserved for Legislative Use */

    /* 0xB000 - 0xB1FF: Vehicle Manufacturer Specific */

    /* 0xB200 - 0xBFFF: Reserved for Legislative Use */

    /* 0xC000 - 0xC2FF: Vehicle Manufacturer Specific */

    /* 0xC300 - 0xCEFF: Reserved for Legislative Use */

    /* 0xCF00 - 0xEFFF: Vehicle Manufacturer Specific */

    /* 0xF000 - 0xF00F: Network Configuration Data For Tractor Trailer Application */

    /* 0xF010 - 0xF0FF: Vehicle Manufacturer Specific */

    /* 
      0xF100 - 0xF17F: 
      Identification Option Vehicle Manufacturer Specific 
    */
    UDS_DID_BOOT_SOFTWARE_ID = 0xF180, /* Boot Software Identification Data Identifier */
    UDS_DID_APP_SOFTWARE_ID = 0xF181, /* Application Software Identification Data Identifier */
    UDS_DID_APP_DATA_ID = 0xF182, /* Application Data Identification Data Identifier */
    UDS_DID_BOOT_SW_FINGERPRINT = 0xF183, /* Boot Software Finger-print Data Identifier */
    UDS_DID_APP_SW_FINGERPRINT = 0xF184, /* Application Software Fingerprint Data Identifier */
    UDS_DID_APP_DATA_FINGERPRINT = 0xF185, /* Application Data Fingerprint Data Identifier */
    UDS_DID_ACTIVE_DIAG_SESSION = 0xF186, /* Active Diagnostic Session Data Identifier */
    UDS_DID_SPARE_PART_NUMBER = 0xF187, /* Vehicle Manufacturer Spare Part Number Data Identifier */
    UDS_DID_ECU_SW_NUMBER = 0xF188, /* Vehicle Manufacturer ECU Software Number Data Identifier */
    UDS_DID_ECU_SW_VERSION = 0xF189, /* Vehicle Manufacturer ECU Software Version Number Data Identifier */
    UDS_DID_SYSTEM_SUPPLIER_ID = 0xF18A, /* System Supplier Identifier Data Identifier */
    UDS_DID_ECU_MANUFACTURING_DATE = 0xF18B, /* ECU Manufacturing Date Data Identifier */
    UDS_DID_ECU_SERIAL_NUMBER = 0xF18C, /* ECU Serial Number Data Identifier */
    UDS_DID_SUPPORTED_FUNCTIONAL_UNITS = 0xF18D, /* Supported Functional Units Data Identifier */
    UDS_DID_KIT_ASSEMBLY_PART_NUMBER = 0xF18E, /* Vehicle Manufacturer Kit Assembly Part Number Data Identifier */
    
    /*  0xF18F:  ISO SAE Reserved Standardized  */
      
    UDS_DID_VIN_DATA = 0xF190, /* VIN Data Identifier */
    UDS_DID_ECU_HW_NUMBER = 0xF191, /* Vehicle Manufacturer ECU Hardware Number Data Identifier */
    UDS_DID_SYS_SUPPLIER_HW_NUMBER = 0xF192, /* System Supplier ECU Hardware Number Data Identifier */
    UDS_DID_SYS_SUPPLIER_HW_VERSION = 0xF193, /* System Supplier ECU Hardware Version Number Data Identifier */
    UDS_DID_SYS_SUPPLIER_SW_NUMBER = 0xF194, /* System Supplier ECU Software Number Data Identifier */
    UDS_DID_SYS_SUPPLIER_SW_VERSION = 0xF195, /* System Supplier ECU Software Version Number Data Identifier */
    UDS_DID_EXHAUST_REGULATION = 0xF196, /* Exhaust Regulation Or Type Approval Number Data Identifier */
    UDS_DID_SYSTEM_NAME_ENGINE_TYPE = 0xF197, /* System Name Or Engine Type Data Identifier */
    UDS_DID_REPAIR_SHOP_CODE = 0xF198, /* Repair Shop Code Or Tester Serial Number Data Identifier */
    UDS_DID_PROGRAMMING_DATE = 0xF199, /* Programming Date Data Identifier */
    UDS_DID_CALIB_REPAIR_SHOP_CODE = 0xF19A, /* Calibration Repair Shop Code Or Calibration Equipment Serial Number */
    UDS_DID_CALIBRATION_DATE = 0xF19B, /* Calibration Date Data Identifier */
    UDS_DID_CALIB_EQUIPMENT_SW_NUMBER = 0xF19C, /* Calibration Equipment Software Number Data Identifier */
    UDS_DID_ECU_INSTALLATION_DATE = 0xF19D, /* ECU Installation Date Data Identifier */
    UDS_DID_ODX_FILE = 0xF19E, /* ODX File Data Identifier */
    UDS_DID_ENTITY = 0xF19F, /* Entity Data Identifier */

    /* 0xF1A0 - 0xF1EF: Identification Option Vehicle Manufacturer Specific */

    /* 0xF1F0 - 0xF1FF: Identification Option System Supplier Specific */

    /* 0xF200 - 0xF2FF: Periodic Data Identifier */

    /* 0xF300 - 0xF3FF: Dynamically Defined Data Identifier */

    /* 0xF400 - 0xF4FF: OBD Data Identifier */

    /* 0xF500 - 0xF5FF: OBD Data Identifier */

    /* 0xF600 - 0xF6FF: OBD Monitor Data Identifier */

    /* 0xF700 - 0xF7FF: OBD Monitor Data Identifier */

    /* 0xF800 - 0xF8FF: OBD Info Type Data Identifier */

    /* 0xF900 - 0xF9FF: Tachograph Data Identifier */

    /* 0xFA00 - 0xFA0F: Airbag Deployment Data Identifier */

    /* 0xFA10 - 0xFA18: Event Data Recorder (EDR) Identifiers */
    UDS_DID_NUMBER_OF_EDR_DEVICES = 0xFA10, /* Number Of EDR Devices */
    UDS_DID_EDR_IDENTIFICATION = 0xFA11, /* EDR Identification */
    UDS_DID_EDR_DEVICE_ADDRESS_INFO = 0xFA12, /* EDR Device Address Information */

    // EDR Entry List
    UDS_DID_EDR_ENTRY_LATEST = 0xFA13, /* Latest EDR Entry */
    UDS_DID_EDR_ENTRY_OLDEST = 0xFA18, /* Oldest EDR Entry */

    /* 0xFA19 - 0xFAFF: Safety System Data Identifier */

    /* 0xFB00 - 0xFCFF: Reserved For Future Legislative Requirements */

    /* 0xFD00 - 0xFEFF: System Supplier Specific */

    /* 0xFF00: UDS Version Data Identifier */
    UDS_DID_UDS_VERSION = 0xFF00, /* UDS Version Data Identifier */

    /* 0xFF01 - 0xFFFF: ISO SAE Reserved */
} uds_protocol_dataIdentifier_t;

#ifdef __cplusplus
}
#endif