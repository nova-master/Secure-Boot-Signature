#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Guid/ImageAuthentication.h> // Include the ImageAuthentication GUID
#include <Library/MemoryAllocationLib.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>
#include <Library/FileHandleLib.h>
#include <Library/DevicePathLib.h>
#include <Library/BaseMemoryLib.h> 
#include <Guid/SmBios.h>
#include <Protocol/Smbios.h>
#include <Library/DebugLib.h>
#include <Protocol/Runtime.h>
#include <Protocol/Security.h>
#include <Guid/FileInfo.h>
#include <Library/FileHandleLib.h>

EFI_STATUS
EFIAPI
UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS Status;
  UINT8 SecureBoot;
  UINTN DataSize = sizeof(SecureBoot);
 
  // Retrieve the SecureBoot variable 0 means disable 1 means enable
  Status = SystemTable->RuntimeServices->GetVariable(
    L"SecureBoot",
    &gEfiGlobalVariableGuid,
    NULL,
    &DataSize,
    &SecureBoot
  );

  if (EFI_ERROR(Status)) {
    Print(L"Failed to retrieve the SecureBoot variable: %r\n", Status);
    gBS->Stall(5000000);

    return Status;
  }

  // Check the secure boot state
  if (SecureBoot == 1) {
    Print(L"Platform firmware is operating in secure boot mode\n");
    gBS->Stall(5000000);

  } else {
    Print(L"Platform firmware is not operating in secure boot mode\n");
    gBS->Stall(5000000);

  }
  
  //####################################################################################
 // Retrieve the dbDefault variable
 UINTN VariableSize = 0;
  UINT8 *DbDefaultData = NULL;
  
  Status = SystemTable->RuntimeServices->GetVariable(
    L"dbDefault",
    &gEfiGlobalVariableGuid,
    NULL,
    &VariableSize,
    NULL
  );

  if (Status != EFI_BUFFER_TOO_SMALL) {
    Print(L"Failed to retrieve the size of the dbDefault variable: %r\n", Status);
    gBS->Stall(5000000);
    return Status;
  }

  // Allocate memory for the DbDefault variable
  DbDefaultData = AllocatePool(VariableSize);
  if (DbDefaultData == NULL) {
    Print(L"Failed to allocate memory for the dbDefault variable\n");
    gBS->Stall(5000000);
    return EFI_OUT_OF_RESOURCES;
  }

  // Retrieve the content of the DbDefault variable
 Status = SystemTable->RuntimeServices->GetVariable(
    L"dbDefault",
    &gEfiGlobalVariableGuid,
    NULL,
    &VariableSize,
    DbDefaultData
  );

  if (EFI_ERROR(Status)) {
    Print(L"Failed to retrieve the dbDefault variable: %r\n", Status);
    gBS->Stall(5000000);
    FreePool(DbDefaultData);
    return Status;
  }
/*
 // Print the content of the DbDefault variable as hexadecimal values and ASCII representation
  Print(L"DbDefault variable content:\n");

  for (UINTN i = 0; i < VariableSize; i++) {
    // Print hexadecimal value
    Print(L"%02X ", DbDefaultData[i]);

    // Print ASCII representation after 16 bytes
    if ((i + 1) % 16 == 0) {
      Print(L"   ");
      for (UINTN j = i - 15; j <= i; j++) {
        if (DbDefaultData[j] >= 0x20 && DbDefaultData[j] <= 0x7E) {
          Print(L"%c", DbDefaultData[j]);
        } else {
          Print(L".");
        }
      }
      Print(L"\n");
      // Insert a 1-second delay (1000000 microseconds) after each line
      //gBS->Stall(500000);
    }
  }

  // Print the remaining ASCII representation
  if (VariableSize % 16 != 0) {
    UINTN remainingBytes = 16 - (VariableSize % 16);
    for (UINTN i = 0; i < remainingBytes; i++) {
      Print(L"   ");
    }
    for (UINTN i = VariableSize - (VariableSize % 16); i < VariableSize; i++) {
      if (DbDefaultData[i] >= 0x20 && DbDefaultData[i] <= 0x7E) {
        Print(L"%c", DbDefaultData[i]);
      } else {
        Print(L".");
      }
    }
  }

  Print(L"\n");
  // Free the allocated memory
  FreePool(DbDefaultData);
   // Print the dbDefault value

  gBS->Stall(5000000);
  */
 //##################################################################### 
      EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *Volume;
    EFI_FILE_PROTOCOL *RootFs;
    EFI_FILE_PROTOCOL *File;
  // Get the handle and protocol for the loaded image
    Status = gBS->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, (VOID**)&LoadedImage);
    if (EFI_ERROR(Status)) {
        Print(L"Failed to get the loaded image handle: %r\n", Status);
gBS->Stall(5000000);
        return Status;
    }

    // Open the root file system
    Status = gBS->OpenProtocol(LoadedImage->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid,
                               (VOID**)&Volume, ImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(Status)) {
        Print(L"Failed to open the file system protocol: %r\n", Status);
gBS->Stall(5000000);
        return Status;
    }

    // Open the root directory
    Status = Volume->OpenVolume(Volume, &RootFs);
    if (EFI_ERROR(Status)) {
        Print(L"Failed to open the root directory: %r\n", Status);
        return Status;
    }
 Print(L"Platform firmware is not operating in secure boot mode3\n");
    // Open the "hello-y.efi" file
    Status = RootFs->Open(RootFs, &File, L"\\EFI\\boot\\hex_export.txt",
                          EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, EFI_FILE_READ_ONLY);
    if (EFI_ERROR(Status)) {
        Print(L"Failed to open the hello-y.efi file: %r\n", Status);
gBS->Stall(5000000);
        return Status;
    }

 Print(L"Platform firmware is not operating in secure boot mode4\n"); 
    
Status = File->Write(File, &VariableSize, DbDefaultData);
if (EFI_ERROR(Status)) {
  Print(L"Failed to write to the file: %r\n", Status);
  gBS->Stall(5000000);
  File->Close(File);
  FreePool(DbDefaultData);
  return Status;
} else {
  Print(L"Successfully written to the file.\n");
}

// Flush the file to ensure the data is written immediately
Status = File->Flush(File);
if (EFI_ERROR(Status)) {
  Print(L"Failed to flush the file: %r\n", Status);
  gBS->Stall(5000000);
  File->Close(File);
  FreePool(DbDefaultData);
  return Status;
}
  Print(L"Successfully flus to the file.\n");
File->Close(File);
FreePool(DbDefaultData);
  
  
 //##################################################################################### 
  
  UINT8 NewSecureBootValue = 1;  // Set the desired value of SecureBoot

Status = SystemTable->RuntimeServices->SetVariable(
  L"SecureBoot",
  &gEfiGlobalVariableGuid,
  EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
  sizeof(NewSecureBootValue),
  &NewSecureBootValue
);

if (EFI_ERROR(Status)) {
  Print(L"Failed to set the SecureBoot variable: %r\n", Status);
  gBS->Stall(5000000);
  return Status;
} else {
  Print(L"SecureBoot variable set successfully.\n");
  gBS->Stall(5000000);
}
// Check the secure boot state
  if (SecureBoot == 1) {
    Print(L"Platform firmware is operating in secure boot mode\n");
    gBS->Stall(5000000);

  } else {
    Print(L"Platform firmware is not operating in secure boot mode\n");
    gBS->Stall(5000000);

  }


gBS->Stall(15000000);
  return EFI_SUCCESS;
}
