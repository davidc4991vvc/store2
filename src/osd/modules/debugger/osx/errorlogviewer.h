// license:BSD-3-Clause
// copyright-holders:Vas Crabb
//============================================================
//
//  errorlogviewer.h - MacOS X Cocoa debug window handling
//
//============================================================

#import "debugosx.h"

#import "debugwindowhandler.h"

<<<<<<< HEAD
#include "emu.h"
=======
>>>>>>> upstream/master

#import <Cocoa/Cocoa.h>


@class MAMEDebugConsole, MAMEErrorLogView;

@interface MAMEErrorLogViewer : MAMEAuxiliaryDebugWindowHandler
{
	MAMEErrorLogView    *logView;
}

- (id)initWithMachine:(running_machine &)m console:(MAMEDebugConsole *)c;

<<<<<<< HEAD
=======
- (void)saveConfigurationToNode:(util::xml::data_node *)node;

>>>>>>> upstream/master
@end
