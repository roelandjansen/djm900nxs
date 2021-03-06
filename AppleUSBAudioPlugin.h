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

#ifndef __DJM01AudioPLUGIN__
#define __DJM01AudioPLUGIN__

#include <IOKit/IOService.h>
#include <IOKit/audio/IOAudioStream.h>
#include <IOKit/usb/USB.h>

class DJM01AudioEngine;
class DJM01AudioStream;

class DJM01AudioPlugin : public IOService {

	OSDeclareDefaultStructors (DJM01AudioPlugin)

private:
	DJM01AudioEngine *			mOurProvider;

protected:
	struct ExpansionData { 
		DJM01AudioStream *	streamProvider;
	};

	ExpansionData *reserved;

public:
	// OSMetaClassDeclareReservedUsed (DJM01AudioPlugin, 0);
	virtual IOReturn	pluginProcessInput (float * destBuf, UInt32 numSampleFrames, UInt32 numChannels);
	// OSMetaClassDeclareReservedUsed (DJM01AudioPlugin, 1);
	virtual IOReturn	pluginSetDirection (IOAudioStreamDirection direction);

private:
	OSMetaClassDeclareReservedUsed (DJM01AudioPlugin, 0);
	OSMetaClassDeclareReservedUsed (DJM01AudioPlugin, 1);

	OSMetaClassDeclareReservedUnused (DJM01AudioPlugin, 2);
	OSMetaClassDeclareReservedUnused (DJM01AudioPlugin, 3);
	OSMetaClassDeclareReservedUnused (DJM01AudioPlugin, 4);
	OSMetaClassDeclareReservedUnused (DJM01AudioPlugin, 5);
	OSMetaClassDeclareReservedUnused (DJM01AudioPlugin, 6);
	OSMetaClassDeclareReservedUnused (DJM01AudioPlugin, 7);
	OSMetaClassDeclareReservedUnused (DJM01AudioPlugin, 8);
	OSMetaClassDeclareReservedUnused (DJM01AudioPlugin, 9);
	OSMetaClassDeclareReservedUnused (DJM01AudioPlugin, 10);
	OSMetaClassDeclareReservedUnused (DJM01AudioPlugin, 11);
	OSMetaClassDeclareReservedUnused (DJM01AudioPlugin, 12);
	OSMetaClassDeclareReservedUnused (DJM01AudioPlugin, 13);
	OSMetaClassDeclareReservedUnused (DJM01AudioPlugin, 14);
	OSMetaClassDeclareReservedUnused (DJM01AudioPlugin, 15);

public:
	virtual	bool		start (IOService * provider);
	virtual	void		stop (IOService * provider);

	IOReturn			pluginDeviceRequest (IOUSBDevRequest * request, IOUSBCompletion * completion = NULL);
	void				pluginSetConfigurationApp (const char * bundleID);

	virtual	IOReturn	pluginInit (IOService * provider, UInt16 vendorID, UInt16 modelID);
	virtual	IOReturn	pluginStart ();
	virtual	IOReturn	pluginReset ();
	virtual	IOReturn	pluginSetFormat (const IOAudioStreamFormat * const newFormat, const IOAudioSampleRate * const newSampleRate);
	virtual	IOReturn	pluginProcess (float * mixBuf, UInt32 numSampleFrames, UInt32 numChannels);
	virtual	IOReturn	pluginStop ();
};

#endif
