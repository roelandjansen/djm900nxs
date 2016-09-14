/*
 * Copyright (c) 1998-2008 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#include "AppleUSBAudioPlugin.h"
#include "AppleUSBAudioEngine.h"

#include <IOKit/IOLib.h>

#define super IOService

OSDefineMetaClassAndStructors (DJM01AudioPlugin, IOService)

OSMetaClassDefineReservedUsed(DJM01AudioPlugin, 0);
OSMetaClassDefineReservedUsed(DJM01AudioPlugin, 1);

OSMetaClassDefineReservedUnused(DJM01AudioPlugin, 2);
OSMetaClassDefineReservedUnused(DJM01AudioPlugin, 3);
OSMetaClassDefineReservedUnused(DJM01AudioPlugin, 4);
OSMetaClassDefineReservedUnused(DJM01AudioPlugin, 5);
OSMetaClassDefineReservedUnused(DJM01AudioPlugin, 6);
OSMetaClassDefineReservedUnused(DJM01AudioPlugin, 7);
OSMetaClassDefineReservedUnused(DJM01AudioPlugin, 8);
OSMetaClassDefineReservedUnused(DJM01AudioPlugin, 9);
OSMetaClassDefineReservedUnused(DJM01AudioPlugin, 10);
OSMetaClassDefineReservedUnused(DJM01AudioPlugin, 11);
OSMetaClassDefineReservedUnused(DJM01AudioPlugin, 12);
OSMetaClassDefineReservedUnused(DJM01AudioPlugin, 13);
OSMetaClassDefineReservedUnused(DJM01AudioPlugin, 14);
OSMetaClassDefineReservedUnused(DJM01AudioPlugin, 15);

// Standard IOService.h function methods
bool DJM01AudioPlugin::start (IOService * provider) {
	if (!super::start (provider)) 
	{
		return FALSE;
	}

	reserved = (ExpansionData *)IOMalloc (sizeof(struct ExpansionData));
	if (!reserved) {
		return FALSE;
	}

	reserved->streamProvider = OSDynamicCast (DJM01AudioStream, provider);
	
	if (reserved->streamProvider)
	{
		// Tell DJM01AudioStream that we're loaded
		reserved->streamProvider->registerPlugin (this);
	}
	else
	{
		mOurProvider = OSDynamicCast (DJM01AudioEngine, provider);

		if (mOurProvider)
		{
			// Tell DJM01AudioEngine that we're loaded
			mOurProvider->registerPlugin (this);
		}
	}
	
	return TRUE;
}

void DJM01AudioPlugin::stop (IOService * provider) {
	// Tell the system that we're not an available resource anymore
	publishResource ("DJM01AudioPlugin", NULL);

	if (reserved) {
		IOFree (reserved, sizeof(struct ExpansionData));
	}

	super::stop (provider);
}

IOReturn DJM01AudioPlugin::pluginDeviceRequest (IOUSBDevRequest * request, IOUSBCompletion * completion) {
	IOReturn						result;

	result = kIOReturnError;
	if (reserved && reserved->streamProvider)
	{
		result = reserved->streamProvider->pluginDeviceRequest (request, completion);
	}
	else if (mOurProvider) 
	{
		result = mOurProvider->pluginDeviceRequest (request, completion);
	}

	return result;
}

void DJM01AudioPlugin::pluginSetConfigurationApp (const char * bundleID) {
	if (reserved && reserved->streamProvider)
	{
		reserved->streamProvider->pluginSetConfigurationApp (bundleID);
	}
	else if (mOurProvider) 
	{
		mOurProvider->pluginSetConfigurationApp (bundleID);
	}
}

// Methods that the plugin will override
IOReturn DJM01AudioPlugin::pluginInit (IOService * provider, UInt16 vendorID, UInt16 modelID) {
	return kIOReturnSuccess;
}

// OSMetaClassDefineReservedUsed(DJM01AudioPlugin, 1);
IOReturn DJM01AudioPlugin::pluginSetDirection (IOAudioStreamDirection direction) {
	return kIOReturnSuccess;
}

IOReturn DJM01AudioPlugin::pluginStart () {
	return kIOReturnSuccess;
}

IOReturn DJM01AudioPlugin::pluginSetFormat (const IOAudioStreamFormat * const newFormat, const IOAudioSampleRate * const newSampleRate) {
	return kIOReturnSuccess;
}

IOReturn DJM01AudioPlugin::pluginReset () {
	return kIOReturnSuccess;
}

IOReturn DJM01AudioPlugin::pluginProcess (float * mixBuf, UInt32 numSampleFrames, UInt32 numChannels) {
	return kIOReturnSuccess;
}

// OSMetaClassDefineReservedUsed(DJM01AudioPlugin, 0);
IOReturn DJM01AudioPlugin::pluginProcessInput (float * destBuf, UInt32 numSampleFrames, UInt32 numChannels) {
	return kIOReturnSuccess;
}

IOReturn DJM01AudioPlugin::pluginStop () {
	return kIOReturnSuccess;
}
