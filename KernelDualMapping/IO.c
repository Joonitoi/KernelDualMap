#include "IO.h"



NTSTATUS IOCreateCall(PDEVICE_OBJECT pDeviceObject, PIRP IRP)
{
	IRP->IoStatus.Status = STATUS_SUCCESS;
	IRP->IoStatus.Information = 0;

	IoCompleteRequest(IRP, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS IOCloseCall(PDEVICE_OBJECT pDeviceObject, PIRP IRP)
{
	IRP->IoStatus.Status = STATUS_SUCCESS;
	IRP->IoStatus.Information = 0;

	IoCompleteRequest(IRP, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS IOControlCall(PDEVICE_OBJECT pDeviceObject, PIRP IRP)
{
	PIO_STACK_LOCATION pIOStackLocation = IoGetCurrentIrpStackLocation(IRP);
	ULONG CTL = pIOStackLocation->Parameters.DeviceIoControl.IoControlCode;

	if (CTL == IO_DUALMAP_REQUEST)
	{
		DbgPrint("DUALMAP request recived!");
	}

	IRP->IoStatus.Status = STATUS_SUCCESS;
	IRP->IoStatus.Information = 0;

	IoCompleteRequest(IRP, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}
