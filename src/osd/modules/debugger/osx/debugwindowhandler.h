// license:BSD-3-Clause
// copyright-holders:Vas Crabb
//============================================================
//
//  debugwindowhandler.h - MacOS X Cocoa debug window handling
//
//============================================================

#import "debugosx.h"

<<<<<<< HEAD
#include "emu.h"
=======
>>>>>>> upstream/master
#include "debug/debugcpu.h"

#import <Cocoa/Cocoa.h>


@protocol MAMEDebugViewExpressionSupport;
@class MAMEDebugCommandHistory, MAMEDebugConsole;


extern NSString *const MAMEHideDebuggerNotification;
extern NSString *const MAMEShowDebuggerNotification;
extern NSString *const MAMEAuxiliaryDebugWindowWillCloseNotification;
<<<<<<< HEAD
=======
extern NSString *const MAMESaveDebuggerConfigurationNotification;


// for compatibility with the Qt debugger
enum
{
	MAME_DEBUGGER_WINDOW_TYPE_CONSOLE = 1,
	MAME_DEBUGGER_WINDOW_TYPE_MEMORY_VIEWER,
	MAME_DEBUGGER_WINDOW_TYPE_DISASSEMBLY_VIEWER,
	MAME_DEBUGGER_WINDOW_TYPE_ERROR_LOG_VIEWER,
	MAME_DEBUGGER_WINDOW_TYPE_POINTS_VIEWER,
	MAME_DEBUGGER_WINDOW_TYPE_DEVICES_VIEWER,
	MAME_DEBUGGER_WINDOW_TYPE_DEVICE_INFO_VIEWER
};
>>>>>>> upstream/master


@interface MAMEDebugWindowHandler : NSObject <NSWindowDelegate>
{
	NSWindow        *window;
	running_machine *machine;
}

+ (void)addCommonActionItems:(NSMenu *)menu;
+ (NSPopUpButton *)newActionButtonWithFrame:(NSRect)frame;

+ (device_debug::breakpoint *)findBreakpointAtAddress:(offs_t)address forDevice:(device_t &)device;

- (id)initWithMachine:(running_machine &)m title:(NSString *)t;

- (void)activate;

<<<<<<< HEAD
=======
- (IBAction)debugBreak:(id)sender;
>>>>>>> upstream/master
- (IBAction)debugRun:(id)sender;
- (IBAction)debugRunAndHide:(id)sender;
- (IBAction)debugRunToNextCPU:(id)sender;
- (IBAction)debugRunToNextInterrupt:(id)sender;
- (IBAction)debugRunToNextVBLANK:(id)sender;

- (IBAction)debugStepInto:(id)sender;
- (IBAction)debugStepOver:(id)sender;
- (IBAction)debugStepOut:(id)sender;

- (IBAction)debugSoftReset:(id)sender;
- (IBAction)debugHardReset:(id)sender;

- (IBAction)debugExit:(id)sender;

- (void)showDebugger:(NSNotification *)notification;
- (void)hideDebugger:(NSNotification *)notification;
<<<<<<< HEAD
=======
- (void)saveConfig:(NSNotification *)notification;

- (void)saveConfigurationToNode:(util::xml::data_node *)node;
- (void)restoreConfigurationFromNode:(util::xml::data_node const *)node;
>>>>>>> upstream/master

@end


@interface MAMEAuxiliaryDebugWindowHandler : MAMEDebugWindowHandler
{
	MAMEDebugConsole    *console;
}

+ (void)cascadeWindow:(NSWindow *)window;

- (id)initWithMachine:(running_machine &)m title:(NSString *)t console:(MAMEDebugConsole *)c;

- (IBAction)debugNewMemoryWindow:(id)sender;
- (IBAction)debugNewDisassemblyWindow:(id)sender;
- (IBAction)debugNewErrorLogWindow:(id)sender;
- (IBAction)debugNewPointsWindow:(id)sender;
- (IBAction)debugNewDevicesWindow:(id)sender;

- (void)windowWillClose:(NSNotification *)notification;

- (void)cascadeWindowWithDesiredSize:(NSSize)desired forView:(NSView *)view;

@end


@interface MAMEExpressionAuxiliaryDebugWindowHandler : MAMEAuxiliaryDebugWindowHandler <NSTextFieldDelegate>
{
	MAMEDebugCommandHistory *history;
	NSTextField             *expressionField;
}

- (id)initWithMachine:(running_machine &)m title:(NSString *)t console:(MAMEDebugConsole *)c;

- (id <MAMEDebugViewExpressionSupport>)documentView;

- (NSString *)expression;
- (void)setExpression:(NSString *)expression;

- (IBAction)doExpression:(id)sender;

- (BOOL)control:(NSControl *)control textShouldBeginEditing:(NSText *)fieldEditor;
- (BOOL)control:(NSControl *)control textView:(NSTextView *)textView doCommandBySelector:(SEL)command;

<<<<<<< HEAD
=======
- (void)saveConfigurationToNode:(util::xml::data_node *)node;
- (void)restoreConfigurationFromNode:(util::xml::data_node const *)node;

>>>>>>> upstream/master
@end
