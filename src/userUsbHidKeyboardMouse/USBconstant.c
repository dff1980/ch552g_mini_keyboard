#include "USBconstant.h"

// Device descriptor
__code USB_Descriptor_Device_t DeviceDescriptor = {
    .Header = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

    .USBSpecification = VERSION_BCD(1, 1, 0),
    .Class = 0x00,
    .SubClass = 0x00,
    .Protocol = 0x00,

    .Endpoint0Size = DEFAULT_ENDP0_SIZE,

    .VendorID = 0x1209,
    .ProductID = 0xc55D,
    .ReleaseNumber = VERSION_BCD(1, 0, 0),

    .ManufacturerStrIndex = 1,
    .ProductStrIndex = 2,
    .SerialNumStrIndex = 3,

    .NumberOfConfigurations = 1};

/** Configuration descriptor structure. This descriptor, located in FLASH
 * memory, describes the usage of the device in one of its supported
 * configurations, including information about any device interfaces and
 * endpoints. The descriptor is read out by the USB host during the enumeration
 * process when selecting a configuration so that the host may correctly
 * communicate with the USB device.
 */
__code USB_Descriptor_Configuration_t ConfigurationDescriptor = {
    .Config = {.Header = {.Size = sizeof(USB_Descriptor_Configuration_Header_t),
                          .Type = DTYPE_Configuration},

               .TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
               .TotalInterfaces = 1,

               .ConfigurationNumber = 1,
               .ConfigurationStrIndex = NO_DESCRIPTOR,

               .ConfigAttributes = (USB_CONFIG_ATTR_RESERVED),

               .MaxPowerConsumption = USB_CONFIG_POWER_MA(200)},

    .HID_Interface = {.Header = {.Size = sizeof(USB_Descriptor_Interface_t),
                                   .Type = DTYPE_Interface},

                      .InterfaceNumber = 0,
                      .AlternateSetting = 0x00,

                      .TotalEndpoints = 2,

                      .Class = HID_CSCP_HIDClass,
                      .SubClass = HID_CSCP_BootSubclass,
                      .Protocol = HID_CSCP_KeyboardBootProtocol,

                      .InterfaceStrIndex = NO_DESCRIPTOR},

    .HID_KeyboardHID = {.Header = {.Size = sizeof(USB_HID_Descriptor_HID_t),
                                     .Type = HID_DTYPE_HID},

                        .HIDSpec = VERSION_BCD(1, 1, 0),
                        .CountryCode = 0x00,
                        .TotalReportDescriptors = 1,
                        .HIDReportType = HID_DTYPE_Report,
                        .HIDReportLength = sizeof(ReportDescriptor)},

    .HID_ReportINEndpoint = {.Header = {.Size =
                                            sizeof(USB_Descriptor_Endpoint_t),
                                        .Type = DTYPE_Endpoint},

                             .EndpointAddress = KEYBOARD_EPADDR,
                             .Attributes =
                                 (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC |
                                  ENDPOINT_USAGE_DATA),
                             .EndpointSize = KEYBOARD_MOUSE_EPSIZE,
                             .PollingIntervalMS = 10},

    .HID_ReportOUTEndpoint = {.Header = {.Size =
                                              sizeof(USB_Descriptor_Endpoint_t),
                                          .Type = DTYPE_Endpoint},

                              .EndpointAddress = KEYBOARD_LED_EPADDR,
                              .Attributes =
                                  (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC |
                                   ENDPOINT_USAGE_DATA),
                              .EndpointSize = KEYBOARD_MOUSE_EPSIZE,
                              .PollingIntervalMS = 10},
};

__code uint8_t ReportDescriptor[] = {

    // ===========================================================
    /* DUPLICATE REMOVED */
    // ============================================================

    0x05, 0x01,
    0x09, 0x06,
    0xA1, 0x01,
    0x85, 0x01,

    0x05, 0x07,
    0x19, 0xE0,
    0x29, 0xE7,
    0x15, 0x00,
    0x25, 0x01,
    0x95, 0x08,
    0x75, 0x01,
    0x81, 0x02,

    0x95, 0x01,
    0x75, 0x08,
    0x81, 0x03,

    0x95, 0x06,
    0x75, 0x08,
    0x15, 0x00,
    0x26, 0xFF, 0x00,
    0x05, 0x07,
    0x19, 0x00,
    0x29, 0xE7,
    0x81, 0x00,

    0x05, 0x08,
    0x19, 0x01,
    0x29, 0x05,
    0x15, 0x00,
    0x25, 0x01,
    0x95, 0x05,
    0x75, 0x01,
    0x91, 0x02,

    0x95, 0x01,
    0x75, 0x03,
    0x91, 0x03,

    0xC0,


    // ===========================================================
    // Mouse - Report ID 2
    // ============================================================

    0x05, 0x01,
    0x09, 0x02,
    0xA1, 0x01,

    0x09, 0x01,
    0xA1, 0x00,

    0x85, 0x02,

    0x05, 0x09,
    0x19, 0x01,
    0x29, 0x03,
    0x15, 0x00,
    0x25, 0x01,

    0x95, 0x03,
    0x75, 0x01,
    0x81, 0x02,

    0x95, 0x01,
    0x75, 0x05,
    0x81, 0x03,

    0x05, 0x01,
    0x09, 0x30,
    0x09, 0x31,
    0x09, 0x38,

    0x15, 0x81,
    0x25, 0x7F,

    0x75, 0x08,
    0x95, 0x03,
    0x81, 0x06,

    0xC0,
    0xC0,


    // ===========================================================
    // Consumer Control - Report ID 3
    // ============================================================

    0x05, 0x0C,
    0x09, 0x01,
    0xA1, 0x01,
    0x85, 0x03,

    0x15, 0x00,
    0x26, 0xFF, 0x03,

    0x19, 0x00,
    0x2A, 0xFF, 0x03,

    0x75, 0x10,
    0x95, 0x01,
    0x81, 0x00,

    0xC0,


    // ===========================================================
    // System Microphone Mute - Report ID 4
    // HUTRR110
    // ============================================================

    0x05, 0x01,       // Usage Page: Generic Desktop
    0x09, 0x80,       // Usage: System Control
    0xA1, 0x01,       // Application Collection

    0x85, 0x04,       // Report ID 4

    // Input: System Microphone Mute
    0x09, 0xA9,       // Usage: System Microphone Mute
    0x15, 0x00,       // Logical Minimum
    0x25, 0x01,       // Logical Maximum
    0x95, 0x01,       // Report Count = 1
    0x75, 0x01,       // Report Size = 1 bit
    0x81, 0x06,       // Input: Data, Variable, Relative

    // Input padding
    0x95, 0x01,
    0x75, 0x07,
    0x81, 0x03,

    // Output: System Microphone Mute LED
    0x05, 0x08,       // Usage Page: LEDs
    0x09, 0x57,       // Usage: System Microphone Mute
    0x15, 0x00,
    0x25, 0x01,
    0x95, 0x01,
    0x75, 0x01,
    0x91, 0x06,       // Output: Data, Variable, Relative

    // Output padding
    0x95, 0x01,
    0x75, 0x07,
    0x91, 0x03,

    0xC0
};

// String Descriptors
__code uint8_t LanguageDescriptor[] = {
    0x04, 0x03, 0x09, 0x04
};

__code uint16_t SerialDescriptor[] = {
    (((13 + 1) * 2) | (DTYPE_String << 8)),
    'C',
    'H',
    '5',
    '5',
    'x',
    ' ',
    'k',
    'b',
    'd',
    ' ',
    'm',
    'o',
    's',
};

__code uint16_t ProductDescriptor[] = {
    (((10 + 1) * 2) | (DTYPE_String << 8)),
    'C',
    'H',
    '5',
    '5',
    'x',
    'd',
    'u',
    'i',
    'n',
    'o',
};

__code uint16_t ManufacturerDescriptor[] = {
    (((6 + 1) * 2) | (DTYPE_String << 8)),
    'D',
    'e',
    'q',
    'i',
    'n',
    'g',
};