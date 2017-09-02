// license:BSD-3-Clause
// copyright-holders:Vas Crabb
//============================================================
//
//  debugwindowhandler.m - MacOS X Cocoa debug window handling
//
//============================================================

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#import "debugwindowhandler.h"

#import "debugconsole.h"
#import "debugcommandhistory.h"
#import "debugview.h"

<<<<<<< HEAD
=======
#include "debugger.h"

#include "util/xmlfile.h"

>>>>>>> upstream/master

//============================================================
//  NOTIFICATIONS
//============================================================

NSString *const MAMEHideDebuggerNotification = @"MAMEHideDebuggerNotification";
NSString *const MAMEShowDebuggerNotification = @"MAMEShowDebuggerNotification";
NSString *const MAMEAuxiliaryDebugWindowWillCloseNotification = @"MAMEAuxiliaryDebugWindowWillCloseNotification";
<<<<<<< HEAD
=======
NSString *const MAMESaveDebuggerConfigurationNotification = @"MAMESaveDebuggerConfigurationNotification";
>>>>>>> upstream/master


//============================================================
//  MAMEDebugWindowHandler class
//============================================================

@implementation MAMEDebugWindowHandler

+ (void)addCommonActionItems:(NSMenu *)menu {
<<<<<<< HEAD
=======
	[menu addItemWithTitle:@"Break"
					action:@selector(debugBreak:)
			 keyEquivalent:@""];

>>>>>>> upstream/master
	NSMenuItem *runParentItem = [menu addItemWithTitle:@"Run"
												action:@selector(debugRun:)
										 keyEquivalent:[NSString stringWithFormat:@"%C", (short)NSF5FunctionKey]];
	NSMenu *runMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"Run"];
	[runParentItem setSubmenu:runMenu];
	[runMenu release];
	[runParentItem setKeyEquivalentModifierMask:0];
	[[runMenu addItemWithTitle:@"and Hide Debugger"
						action:@selector(debugRunAndHide:)
				 keyEquivalent:[NSString stringWithFormat:@"%C", (short)NSF12FunctionKey]]
	 setKeyEquivalentModifierMask:0];
	[[runMenu addItemWithTitle:@"to Next CPU"
						action:@selector(debugRunToNextCPU:)
				 keyEquivalent:[NSString stringWithFormat:@"%C", (short)NSF6FunctionKey]]
	 setKeyEquivalentModifierMask:0];
	[[runMenu addItemWithTitle:@"until Next Interrupt on Current CPU"
						action:@selector(debugRunToNextInterrupt:)
				 keyEquivalent:[NSString stringWithFormat:@"%C", (short)NSF7FunctionKey]]
	 setKeyEquivalentModifierMask:0];
	[[runMenu addItemWithTitle:@"until Next VBLANK"
						action:@selector(debugRunToNextVBLANK:)
				 keyEquivalent:[NSString stringWithFormat:@"%C", (short)NSF8FunctionKey]]
	 setKeyEquivalentModifierMask:0];

	NSMenuItem *stepParentItem = [menu addItemWithTitle:@"Step" action:NULL keyEquivalent:@""];
	NSMenu *stepMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"Step"];
	[stepParentItem setSubmenu:stepMenu];
	[stepMenu release];
	[[stepMenu addItemWithTitle:@"Into"
						 action:@selector(debugStepInto:)
				  keyEquivalent:[NSString stringWithFormat:@"%C", (short)NSF11FunctionKey]]
	 setKeyEquivalentModifierMask:0];
	[[stepMenu addItemWithTitle:@"Over"
						 action:@selector(debugStepOver:)
				  keyEquivalent:[NSString stringWithFormat:@"%C", (short)NSF10FunctionKey]]
	 setKeyEquivalentModifierMask:0];
	[[stepMenu addItemWithTitle:@"Out"
						 action:@selector(debugStepOut:)
				  keyEquivalent:[NSString stringWithFormat:@"%C", (short)NSF10FunctionKey]]
	 setKeyEquivalentModifierMask:NSShiftKeyMask];

	NSMenuItem *resetParentItem = [menu addItemWithTitle:@"Reset" action:NULL keyEquivalent:@""];
	NSMenu *resetMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"Reset"];
	[resetParentItem setSubmenu:resetMenu];
	[resetMenu release];
	[[resetMenu addItemWithTitle:@"Soft"
						  action:@selector(debugSoftReset:)
				   keyEquivalent:[NSString stringWithFormat:@"%C", (short)NSF3FunctionKey]]
	 setKeyEquivalentModifierMask:0];
	[[resetMenu addItemWithTitle:@"Hard"
						  action:@selector(debugHardReset:)
				   keyEquivalent:[NSString stringWithFormat:@"%C", (short)NSF3FunctionKey]]
	 setKeyEquivalentModifierMask:NSShiftKeyMask];

	[menu addItem:[NSMenuItem separatorItem]];

	NSMenuItem *newParentItem = [menu addItemWithTitle:@"New" action:NULL keyEquivalent:@""];
	NSMenu *newMenu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"New"];
	[newParentItem setSubmenu:newMenu];
	[newMenu release];
	[newMenu addItemWithTitle:@"Memory Window"
					   action:@selector(debugNewMemoryWindow:)
				keyEquivalent:@"d"];
	[newMenu addItemWithTitle:@"Disassembly Window"
					   action:@selector(debugNewDisassemblyWindow:)
				keyEquivalent:@"a"];
	[newMenu addItemWithTitle:@"Error Log Window"
					   action:@selector(debugNewErrorLogWindow:)
				keyEquivalent:@"l"];
	[newMenu addItemWithTitle:@"(Break|Watch)points Window"
					   action:@selector(debugNewPointsWindow:)
				keyEquivalent:@"b"];
	[newMenu addItemWithTitle:@"Devices Window"
					   action:@selector(debugNewDevicesWindow:)
				keyEquivalent:@"D"];

	[menu addItem:[NSMenuItem separatorItem]];

	[menu addItemWithTitle:@"Close Window" action:@selector(performClose:) keyEquivalent:@"w"];
	[menu addItemWithTitle:@"Quit" action:@selector(debugExit:) keyEquivalent:@"q"];
}


+ (NSPopUpButton *)newActionButtonWithFrame:(NSRect)frame {
	NSPopUpButton *actionButton = [[NSPopUpButton alloc] initWithFrame:frame pullsDown:YES];
	[actionButton setTitle:@""];
	[actionButton addItemWithTitle:@""];
	[actionButton setBezelStyle:NSShadowlessSquareBezelStyle];
	[actionButton setFocusRingType:NSFocusRingTypeNone];
	[[actionButton cell] setArrowPosition:NSPopUpArrowAtCenter];
	[[self class] addCommonActionItems:[actionButton menu]];
	return actionButton;
}


+ (device_debug::breakpoint *)findBreakpointAtAddress:(offs_t)address forDevice:(device_t &)device {
	device_debug *const cpuinfo = device.debug();
	device_debug::breakpoint *bp = cpuinfo->breakpoint_first();
<<<<<<< HEAD
	while ((bp != NULL) && (address != bp->address())) bp = bp->next();
=======
	while ((bp != nullptr) && (address != bp->address())) bp = bp->next();
>>>>>>> upstream/master
	return bp;
}


- (id)initWithMachine:(running_machine &)m title:(NSString *)t {
	if (!(self = [super init]))
		return nil;

	window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 320, 240)
										 styleMask:(NSTitledWindowMask |
													NSClosableWindowMask |
													NSMiniaturizableWindowMask |
													NSResizableWindowMask)
										   backing:NSBackingStoreBuffered
											 defer:YES];
	[window setReleasedWhenClosed:NO];
	[window setDelegate:self];
	[window setTitle:t];
	[window setContentMinSize:NSMakeSize(320, 240)];

	[[NSNotificationCenter defaultCenter] addObserver:self
<<<<<<< HEAD
=======
											 selector:@selector(saveConfig:)
												 name:MAMESaveDebuggerConfigurationNotification
											   object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self
>>>>>>> upstream/master
											 selector:@selector(showDebugger:)
												 name:MAMEShowDebuggerNotification
											   object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(hideDebugger:)
												 name:MAMEHideDebuggerNotification
											   object:nil];

	machine = &m;

	return self;
}


- (void)dealloc {
	[[NSNotificationCenter defaultCenter] removeObserver:self];

	if (window != nil)
	{
		[window orderOut:self];
		[window release];
	}

	[super dealloc];
}


- (void)activate {
	[window makeKeyAndOrderFront:self];
}


<<<<<<< HEAD
- (IBAction)debugRun:(id)sender {
	debug_cpu_get_visible_cpu(*machine)->debug()->go();
=======
- (IBAction)debugBreak:(id)sender {
	if (machine->debug_flags & DEBUG_FLAG_ENABLED)
		machine->debugger().cpu().get_visible_cpu()->debug()->halt_on_next_instruction("User-initiated break\n");
}


- (IBAction)debugRun:(id)sender {
	machine->debugger().cpu().get_visible_cpu()->debug()->go();
>>>>>>> upstream/master
}


- (IBAction)debugRunAndHide:(id)sender {
<<<<<<< HEAD
	[[NSNotificationCenter defaultCenter] postNotificationName:MAMEHideDebuggerNotification object:self];
	debug_cpu_get_visible_cpu(*machine)->debug()->go();
=======
	[[NSNotificationCenter defaultCenter] postNotificationName:MAMEHideDebuggerNotification
														object:self
													  userInfo:[NSDictionary dictionaryWithObject:[NSValue valueWithPointer:machine]
																						   forKey:@"MAMEDebugMachine"]];
	machine->debugger().cpu().get_visible_cpu()->debug()->go();
>>>>>>> upstream/master
}


- (IBAction)debugRunToNextCPU:(id)sender {
<<<<<<< HEAD
	debug_cpu_get_visible_cpu(*machine)->debug()->go_next_device();
=======
	machine->debugger().cpu().get_visible_cpu()->debug()->go_next_device();
>>>>>>> upstream/master
}


- (IBAction)debugRunToNextInterrupt:(id)sender {
<<<<<<< HEAD
	debug_cpu_get_visible_cpu(*machine)->debug()->go_interrupt();
=======
	machine->debugger().cpu().get_visible_cpu()->debug()->go_interrupt();
>>>>>>> upstream/master
}


- (IBAction)debugRunToNextVBLANK:(id)sender {
<<<<<<< HEAD
	debug_cpu_get_visible_cpu(*machine)->debug()->go_vblank();
=======
	machine->debugger().cpu().get_visible_cpu()->debug()->go_vblank();
>>>>>>> upstream/master
}


- (IBAction)debugStepInto:(id)sender {
<<<<<<< HEAD
	debug_cpu_get_visible_cpu(*machine)->debug()->single_step();
=======
	machine->debugger().cpu().get_visible_cpu()->debug()->single_step();
>>>>>>> upstream/master
}


- (IBAction)debugStepOver:(id)sender {
<<<<<<< HEAD
	debug_cpu_get_visible_cpu(*machine)->debug()->single_step_over();
=======
	machine->debugger().cpu().get_visible_cpu()->debug()->single_step_over();
>>>>>>> upstream/master
}


- (IBAction)debugStepOut:(id)sender {
<<<<<<< HEAD
	debug_cpu_get_visible_cpu(*machine)->debug()->single_step_out();
=======
	machine->debugger().cpu().get_visible_cpu()->debug()->single_step_out();
>>>>>>> upstream/master
}


- (IBAction)debugSoftReset:(id)sender {
	machine->schedule_soft_reset();
<<<<<<< HEAD
	debug_cpu_get_visible_cpu(*machine)->debug()->go();
=======
	machine->debugger().cpu().get_visible_cpu()->debug()->go();
>>>>>>> upstream/master
}


- (IBAction)debugHardReset:(id)sender {
	machine->schedule_hard_reset();
}


- (IBAction)debugExit:(id)sender {
	machine->schedule_exit();
}


- (void)showDebugger:(NSNotification *)notification {
	running_machine *m = (running_machine *)[[[notification userInfo] objectForKey:@"MAMEDebugMachine"] pointerValue];
	if (m == machine)
	{
		if (![window isVisible] && ![window isMiniaturized])
			[window orderFront:self];
	}
}


- (void)hideDebugger:(NSNotification *)notification {
	running_machine *m = (running_machine *)[[[notification userInfo] objectForKey:@"MAMEDebugMachine"] pointerValue];
	if (m == machine)
		[window orderOut:self];
}

<<<<<<< HEAD
=======

- (void)saveConfig:(NSNotification *)notification {
	running_machine *m = (running_machine *)[[[notification userInfo] objectForKey:@"MAMEDebugMachine"] pointerValue];
	if (m == machine)
	{
		util::xml::data_node *parentnode = (util::xml::data_node *)[[[notification userInfo] objectForKey:@"MAMEDebugParentNode"] pointerValue];
		util::xml::data_node *node = parentnode->add_child("window", nullptr);
		if (node)
			[self saveConfigurationToNode:node];
	}
}


- (void)saveConfigurationToNode:(util::xml::data_node *)node {
	NSRect frame = [window frame];
	node->set_attribute_float("position_x", frame.origin.x);
	node->set_attribute_float("position_y", frame.origin.y);
	node->set_attribute_float("size_x", frame.size.width);
	node->set_attribute_float("size_y", frame.size.height);
}


- (void)restoreConfigurationFromNode:(util::xml::data_node const *)node {
	NSRect frame = [window frame];
	frame.origin.x = node->get_attribute_float("position_x", frame.origin.x);
	frame.origin.y = node->get_attribute_float("position_y", frame.origin.y);
	frame.size.width = node->get_attribute_float("size_x", frame.size.width);
	frame.size.height = node->get_attribute_float("size_y", frame.size.height);

	NSSize min = [window minSize];
	frame.size.width = std::max(frame.size.width, min.width);
	frame.size.height = std::max(frame.size.height, min.height);

	NSSize max = [window maxSize];
	frame.size.width = std::min(frame.size.width, max.width);
	frame.size.height = std::min(frame.size.height, max.height);

	[window setFrame:frame display:YES];
}

>>>>>>> upstream/master
@end


//============================================================
//  MAMEAuxiliaryDebugWindowHandler class
//============================================================

@implementation MAMEAuxiliaryDebugWindowHandler

+ (void)cascadeWindow:(NSWindow *)window {
	static NSPoint lastPosition = { 0, 0 };
	if (NSEqualPoints(lastPosition, NSZeroPoint)) {
		NSRect available = [[NSScreen mainScreen] visibleFrame];
		lastPosition = NSMakePoint(available.origin.x + 12, available.origin.y + available.size.height - 8);
	}
	lastPosition = [window cascadeTopLeftFromPoint:lastPosition];
}


- (id)initWithMachine:(running_machine &)m title:(NSString *)t console:(MAMEDebugConsole *)c {
	if (!(self = [super initWithMachine:m title:t]))
		return nil;
	console = c;
	return self;
}


- (void)dealloc {
	[super dealloc];
}


- (IBAction)debugNewMemoryWindow:(id)sender {
	[console debugNewMemoryWindow:sender];
}


- (IBAction)debugNewDisassemblyWindow:(id)sender {
	[console debugNewDisassemblyWindow:sender];
}


- (IBAction)debugNewErrorLogWindow:(id)sender {
	[console debugNewErrorLogWindow:sender];
}


- (IBAction)debugNewPointsWindow:(id)sender {
	[console debugNewPointsWindow:sender];
}


- (IBAction)debugNewDevicesWindow:(id)sender {
	[console debugNewDevicesWindow:sender];
}


- (void)windowWillClose:(NSNotification *)notification {
	[[NSNotificationCenter defaultCenter] postNotificationName:MAMEAuxiliaryDebugWindowWillCloseNotification
														object:self];
}

- (void)cascadeWindowWithDesiredSize:(NSSize)desired forView:(NSView *)view {
	// convert desired size to an adjustment and apply it to the current window frame
	NSSize const current = [view frame].size;
	desired.width -= current.width;
	desired.height -= current.height;
	NSRect windowFrame = [window frame];
	windowFrame.size.width += desired.width;
	windowFrame.size.height += desired.height;

	// limit the size to the minimum size
	NSSize const minimum = [window minSize];
<<<<<<< HEAD
	windowFrame.size.width = MAX(windowFrame.size.width, minimum.width);
	windowFrame.size.height = MAX(windowFrame.size.height, minimum.height);

	// limit the size to the main screen size
	NSRect const available = [[NSScreen mainScreen] visibleFrame];
	windowFrame.size.width = MIN(windowFrame.size.width, available.size.width);
	windowFrame.size.height = MIN(windowFrame.size.height, available.size.height);

	// arbitrary additional height limit
	windowFrame.size.height = MIN(windowFrame.size.height, 320);
=======
	windowFrame.size.width = std::max(windowFrame.size.width, minimum.width);
	windowFrame.size.height = std::max(windowFrame.size.height, minimum.height);

	// limit the size to the main screen size
	NSRect const available = [[NSScreen mainScreen] visibleFrame];
	windowFrame.size.width = std::min(windowFrame.size.width, available.size.width);
	windowFrame.size.height = std::min(windowFrame.size.height, available.size.height);

	// arbitrary additional height limit
	windowFrame.size.height = std::min(windowFrame.size.height, CGFloat(320));
>>>>>>> upstream/master

	// place it in the bottom right corner and apply
	windowFrame.origin.x = available.origin.x + available.size.width - windowFrame.size.width;
	windowFrame.origin.y = available.origin.y;
	[window setFrame:windowFrame display:YES];
	[[self class] cascadeWindow:window];
}

@end


//============================================================
//  MAMEExpreesionAuxiliaryDebugWindowHandler class
//============================================================

@implementation MAMEExpressionAuxiliaryDebugWindowHandler

- (id)initWithMachine:(running_machine &)m title:(NSString *)t console:(MAMEDebugConsole *)c {
	if (!(self = [super initWithMachine:m title:t console:c]))
		return nil;
	history = [[MAMEDebugCommandHistory alloc] init];
	return self;
}


- (void)dealloc {
	if (history != nil)
		[history release];
	[super dealloc];
}


- (id <MAMEDebugViewExpressionSupport>)documentView {
	return nil;
}


- (NSString *)expression {
	return [[self documentView] expression];
}

- (void)setExpression:(NSString *)expression {
	[history add:expression];
	[[self documentView] setExpression:expression];
	[expressionField setStringValue:expression];
	[expressionField selectText:self];
}


- (IBAction)doExpression:(id)sender {
	NSString *expr = [sender stringValue];
	if ([expr length] > 0) {
		[history add:expr];
		[[self documentView] setExpression:expr];
	} else {
		[sender setStringValue:[[self documentView] expression]];
		[history reset];
	}
	[sender selectText:self];
}


- (BOOL)control:(NSControl *)control textShouldBeginEditing:(NSText *)fieldEditor
{
	if (control == expressionField)
		[history edit];

	return YES;
}


- (BOOL)control:(NSControl *)control textView:(NSTextView *)textView doCommandBySelector:(SEL)command {
	if (control == expressionField) {
		if (command == @selector(cancelOperation:)) {
			[history reset];
			[expressionField setStringValue:[[self documentView] expression]];
			[expressionField selectText:self];
			return YES;
		} else if (command == @selector(moveUp:)) {
			NSString *hist = [history previous:[expressionField stringValue]];
			if (hist != nil) {
				[expressionField setStringValue:hist];
				[expressionField selectText:self];
			}
			return YES;
		} else if (command == @selector(moveDown:)) {
			NSString *hist = [history next:[expressionField stringValue]];
			if (hist != nil) {
				[expressionField setStringValue:hist];
				[expressionField selectText:self];
			}
			return YES;
		}
<<<<<<< HEAD
    }
	return NO;
}

=======
	}
	return NO;
}


- (void)saveConfigurationToNode:(util::xml::data_node *)node {
	[super saveConfigurationToNode:node];
	node->add_child("expression", util::xml::normalize_string([[self expression] UTF8String]));
}


- (void)restoreConfigurationFromNode:(util::xml::data_node const *)node {
	[super restoreConfigurationFromNode:node];
	util::xml::data_node const *const expr = node->get_child("expression");
	if (expr && expr->get_value())
		[self setExpression:[NSString stringWithUTF8String:expr->get_value()]];
}

>>>>>>> upstream/master
@end
