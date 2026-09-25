// SPDX-FileCopyrightText: Copyright 2024 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common/types.h"
#include "core/libraries/system/commondialog.h"

namespace Core::Loader {
class SymbolsResolver;
}

namespace Libraries::UsbStorageDialog {

CommonDialog::Error PS4_SYSV_ABI sceUsbStorageDialogInitialize();
CommonDialog::Error PS4_SYSV_ABI sceUsbStorageDialogOpen(const void* param);
CommonDialog::Status PS4_SYSV_ABI sceUsbStorageDialogUpdateStatus();
CommonDialog::Status PS4_SYSV_ABI sceUsbStorageDialogGetStatus();
CommonDialog::Error PS4_SYSV_ABI sceUsbStorageDialogGetResult(void* result);
CommonDialog::Error PS4_SYSV_ABI sceUsbStorageDialogClose();
CommonDialog::Error PS4_SYSV_ABI sceUsbStorageDialogTerminate();

void RegisterLib(Core::Loader::SymbolsResolver* sym);

} // namespace Libraries::UsbStorageDialog
