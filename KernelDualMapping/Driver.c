#include <ntddk.h>
#include <wdf.h>
#include "IO.h"

//globals
UNICODE_STRING dev, dos;
PDEVICE_OBJECT pDeviceObject;

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT pDriverObject, _In_ PUNICODE_STRING pRegistryPath)
{
	NTSTATUS status = 0;

	RtlInitUnicodeString(&dev, L"\\Device\\KernelDualMapping");
	RtlInitUnicodeString(&dos, L"\\DosDevice\\KernelDualMapping");

	status = IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);

	status = IoCreateSymbolicLink(&dos, &dev);

	pDriverObject->DriverUnload = DriverUnload;
	pDriverObject->MajorFunction[IRP_MJ_CREATE] = IOCreateCall;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = IOCloseCall;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IOControlCall;

	DbgPrint("DualMapper Driver Loaded\n");
}

NTSTATUS DriverUnload(PDRIVER_OBJECT pDriverObject)
{

	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(pDriverObject->DeviceObject);

	DbgPrint("DualMapper Driver Unloaded\n");
}