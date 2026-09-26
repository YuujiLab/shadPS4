#pragma once

#include "common/types.h"
#include "core/libraries/system/commondialog.h"

namespace Libraries::UsbStorage {

CommonDialog::Error PS4_SYSV_ABI sceUsbStorageInit();
CommonDialog::Error PS4_SYSV_ABI sceUsbStorageTerm();
CommonDialog::Error PS4_SYSV_ABI sceUsbStorageGetDeviceList(uint32_t* deviceIds, int* numDevices);
CommonDialog::Error PS4_SYSV_ABI sceUsbStorageGetDeviceInfo(uint32_t deviceId, void* deviceInfo);
CommonDialog::Error PS4_SYSV_ABI sceUsbStorageIsExist(uint32_t deviceId, const char* directory,
                                                      bool* out_exists);
CommonDialog::Error PS4_SYSV_ABI sceUsbStorageRequestMap(uint32_t deviceId, const char* directory,
                                                         int lockType, uint64_t optionFlags,
                                                         char* mountPoint,
                                                         uint64_t* additionalFeatureFlags,
                                                         const void* dbgData, size_t dbgDataSize);
CommonDialog::Error PS4_SYSV_ABI sceUsbStorageRequestUnmap(uint32_t deviceId, const char* directory);

void RegisterLib(Core::Loader::SymbolsResolver* sym);

} // namespace Libraries::UsbStorage
