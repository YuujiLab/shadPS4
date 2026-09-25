// SPDX-FileCopyrightText: Copyright 2024 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "common/logging/log.h"
#include "core/libraries/libs.h"
#include "core/libraries/system/usbstoragedialog.h"

namespace Libraries::UsbStorageDialog {

using CommonDialog::Error;
using CommonDialog::Result;
using CommonDialog::Status;

static auto g_status = Status::NONE;

Error PS4_SYSV_ABI sceUsbStorageDialogInitialize() {
    LOG_DEBUG(Lib_CommonDlg, "called");
    if (!CommonDialog::g_isInitialized) {
        return Error::NOT_SYSTEM_INITIALIZED;
    }
    if (g_status != Status::NONE) {
        return Error::ALREADY_INITIALIZED;
    }
    if (CommonDialog::g_isUsed) {
        return Error::BUSY;
    }
    g_status = Status::INITIALIZED;
    CommonDialog::g_isUsed = true;
    return Error::OK;
}

Error PS4_SYSV_ABI sceUsbStorageDialogOpen(const void* param) {
    LOG_DEBUG(Lib_CommonDlg, "called");
    if (g_status != Status::INITIALIZED && g_status != Status::FINISHED) {
        return Error::INVALID_STATE;
    }
    if (param == nullptr) {
        return Error::ARG_NULL;
    }
    g_status = Status::FINISHED;
    return Error::OK;
}

Status PS4_SYSV_ABI sceUsbStorageDialogUpdateStatus() {
    LOG_TRACE(Lib_CommonDlg, "called");
    return g_status;
}

Status PS4_SYSV_ABI sceUsbStorageDialogGetStatus() {
    LOG_TRACE(Lib_CommonDlg, "called");
    return g_status;
}

Error PS4_SYSV_ABI sceUsbStorageDialogGetResult(void* result) {
    LOG_DEBUG(Lib_CommonDlg, "called");
    if (g_status != Status::FINISHED) {
        return Error::NOT_FINISHED;
    }
    if (result == nullptr) {
        return Error::ARG_NULL;
    }

    *(s32*)((u8*)result + 8) = 0;
    *(u32*)((u8*)result + 12) = 0;

    return Error::OK;
}

Error PS4_SYSV_ABI sceUsbStorageDialogClose() {
    LOG_DEBUG(Lib_CommonDlg, "called");
    return Error::OK;
}

Error PS4_SYSV_ABI sceUsbStorageDialogTerminate() {
    LOG_DEBUG(Lib_CommonDlg, "called");
    if (g_status == Status::NONE) {
        return Error::NOT_INITIALIZED;
    }
    g_status = Status::NONE;
    CommonDialog::g_isUsed = false;
    return Error::OK;
}

void RegisterLib(Core::Loader::SymbolsResolver* sym) {
    LIB_FUNCTION("IX49aL2rOGU", "libSceUsbStorageDialog", 1, "libSceUsbStorageDialog",
                 sceUsbStorageDialogInitialize);
    LIB_FUNCTION("ClBMa8CWKkM", "libSceUsbStorageDialog", 1, "libSceUsbStorageDialog",
                 sceUsbStorageDialogOpen);
    LIB_FUNCTION("MpXK+QLRpwU", "libSceUsbStorageDialog", 1, "libSceUsbStorageDialog",
                 sceUsbStorageDialogUpdateStatus);
    LIB_FUNCTION("zI+X8+h6dL8", "libSceUsbStorageDialog", 1, "libSceUsbStorageDialog",
                 sceUsbStorageDialogGetStatus);
    LIB_FUNCTION("ul-kdmwPExY", "libSceUsbStorageDialog", 1, "libSceUsbStorageDialog",
                 sceUsbStorageDialogGetResult);
    LIB_FUNCTION("K7Vb-7JGXVc", "libSceUsbStorageDialog", 1, "libSceUsbStorageDialog",
                 sceUsbStorageDialogClose);
    LIB_FUNCTION("O2rgVi8YyOg", "libSceUsbStorageDialog", 1, "libSceUsbStorageDialog",
                 sceUsbStorageDialogTerminate);
}

} // namespace Libraries::UsbStorageDialog
