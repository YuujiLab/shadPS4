// SPDX-FileCopyrightText: Copyright 2024 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include <cstring>
#include "common/logging/log.h"
#include "core/libraries/system/usbstorage.h"

namespace Libraries::UsbStorage {

CommonDialog::Error PS4_SYSV_ABI sceUsbStorageInit() {
    return CommonDialog::Error::OK;
}

CommonDialog::Error PS4_SYSV_ABI sceUsbStorageTerm() {
    return CommonDialog::Error::OK;
}

CommonDialog::Error PS4_SYSV_ABI sceUsbStorageGetDeviceList(uint32_t* deviceIds, int* numDevices) {
    if (deviceIds && numDevices) {
        deviceIds[0] = 1; // Fake device ID
        *numDevices = 1;
    }
    return CommonDialog::Error::OK;
}

CommonDialog::Error PS4_SYSV_ABI sceUsbStorageGetDeviceInfo(uint32_t deviceId, void* deviceInfo) {
    if (deviceInfo) {
        std::memset(deviceInfo, 0, 824); // Zero out the struct
    }
    return CommonDialog::Error::OK;
}

CommonDialog::Error PS4_SYSV_ABI sceUsbStorageIsExist(uint32_t deviceId, const char* directory,
                                                      bool* out_exists) {
    if (out_exists) {
        *out_exists = true; // Pretend it exists
    }
    return CommonDialog::Error::OK;
}

CommonDialog::Error PS4_SYSV_ABI sceUsbStorageRequestMap(uint32_t deviceId, const char* directory,
                                                         int lockType, uint64_t optionFlags,
                                                         char* mountPoint,
                                                         uint64_t* additionalFeatureFlags,
                                                         const void* dbgData, size_t dbgDataSize) {
    if (mountPoint) {
        std::strcpy(mountPoint, "/usb0"); // Return the mounted path
    }
    return CommonDialog::Error::OK;
}

CommonDialog::Error PS4_SYSV_ABI sceUsbStorageRequestUnmap(uint32_t deviceId,
                                                           const char* directory) {
    return CommonDialog::Error::OK;
}

void RegisterLib(Core::Loader::SymbolsResolver* sym) {
    LIB_FUNCTION("BDDZwF5kuTc", "libSceUsbStorage", 1, "libSceUsbStorage", sceUsbStorageInit);
    LIB_FUNCTION("Wp8zHTocS5E", "libSceUsbStorage", 1, "libSceUsbStorage", sceUsbStorageTerm);
    LIB_FUNCTION("mryrNITeYvI", "libSceUsbStorage", 1, "libSceUsbStorage",
                 sceUsbStorageGetDeviceList);
    LIB_FUNCTION("-GvBqz54ssU", "libSceUsbStorage", 1, "libSceUsbStorage",
                 sceUsbStorageGetDeviceInfo);
    LIB_FUNCTION("tO8DvyElInw", "libSceUsbStorage", 1, "libSceUsbStorage", sceUsbStorageIsExist);
    LIB_FUNCTION("IDYJZSeBgDs", "libSceUsbStorage", 1, "libSceUsbStorage", sceUsbStorageRequestMap);
    LIB_FUNCTION("fl3roYs7F9U", "libSceUsbStorage", 1, "libSceUsbStorage",
                 sceUsbStorageRequestUnmap);
}

} // namespace Libraries::UsbStorage
