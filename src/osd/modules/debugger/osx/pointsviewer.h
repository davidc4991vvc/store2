// license:BSD-3-Clause
// copyright-holders:Vas Crabb
//============================================================
//
//  pointsviewer.h - MacOS X Cocoa debug window handling
//
//============================================================

#import "debugosx.h"

#import "debugwindowhandler.h"

<<<<<<< HEAD
#include "emu.h"
=======
>>>>>>> upstream/master

#import <Cocoa/Cocoa.h>


@class MAMEDebugConsole;

@interface MAMEPointsViewer : MAMEAuxiliaryDebugWindowHandler
{
<<<<<<< HEAD
	NSTabView   *tabs;
=======
	NSTabView       *tabs;
	NSPopUpButton   *subviewButton;
>>>>>>> upstream/master
}

- (id)initWithMachine:(running_machine &)m console:(MAMEDebugConsole *)c;

- (IBAction)changeSubview:(id)sender;

<<<<<<< HEAD
=======
- (void)saveConfigurationToNode:(util::xml::data_node *)node;
- (void)restoreConfigurationFromNode:(util::xml::data_node const *)node;

>>>>>>> upstream/master
@end
