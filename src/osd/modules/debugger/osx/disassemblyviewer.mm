// license:BSD-3-Clause
// copyright-holders:Vas Crabb
//============================================================
//
//  disassemblyviewer.m - MacOS X Cocoa debug window handling
//
//============================================================

<<<<<<< HEAD
=======
#include "emu.h"
>>>>>>> upstream/master
#import "disassemblyviewer.h"

#import "debugconsole.h"
#import "debugview.h"
#import "disassemblyview.h"

#include "debugger.h"
#include "debug/debugcon.h"
#include "debug/debugcpu.h"

<<<<<<< HEAD
=======
#include "util/xmlfile.h"

>>>>>>> upstream/master

@implementation MAMEDisassemblyViewer

- (id)initWithMachine:(running_machine &)m console:(MAMEDebugConsole *)c {
<<<<<<< HEAD
	NSScrollView	*dasmScroll;
	NSView			*expressionContainer;
	NSPopUpButton	*actionButton;
	NSRect			expressionFrame;
=======
	NSScrollView    *dasmScroll;
	NSView          *expressionContainer;
	NSPopUpButton   *actionButton;
	NSRect          expressionFrame;
>>>>>>> upstream/master

	if (!(self = [super initWithMachine:m title:@"Disassembly" console:c]))
		return nil;
	NSRect const contentBounds = [[window contentView] bounds];
	NSFont *const defaultFont = [[MAMEDebugView class] defaultFontForMachine:m];

	// create the expression field
	expressionField = [[NSTextField alloc] initWithFrame:NSMakeRect(0, 0, 100, 19)];
	[expressionField setAutoresizingMask:(NSViewWidthSizable | NSViewMaxXMargin | NSViewMinYMargin)];
	[expressionField setFont:defaultFont];
	[expressionField setFocusRingType:NSFocusRingTypeNone];
	[expressionField setTarget:self];
	[expressionField setAction:@selector(doExpression:)];
	[expressionField setDelegate:self];
	[expressionField sizeToFit];

	// create the subview popup
	subviewButton = [[NSPopUpButton alloc] initWithFrame:NSOffsetRect(expressionFrame,
																	  expressionFrame.size.width,
																	  0)];
	[subviewButton setAutoresizingMask:(NSViewWidthSizable | NSViewMinXMargin | NSViewMinYMargin)];
	[subviewButton setBezelStyle:NSShadowlessSquareBezelStyle];
	[subviewButton setFocusRingType:NSFocusRingTypeNone];
	[subviewButton setFont:defaultFont];
	[subviewButton setTarget:self];
	[subviewButton setAction:@selector(changeSubview:)];
	[[subviewButton cell] setArrowPosition:NSPopUpArrowAtBottom];
	[subviewButton sizeToFit];

	// adjust sizes to make it fit nicely
	expressionFrame = [expressionField frame];
<<<<<<< HEAD
	expressionFrame.size.height = MAX(expressionFrame.size.height, [subviewButton frame].size.height);
=======
	expressionFrame.size.height = std::max(expressionFrame.size.height, [subviewButton frame].size.height);
>>>>>>> upstream/master
	expressionFrame.size.width = (contentBounds.size.width - expressionFrame.size.height) / 2;
	[expressionField setFrame:expressionFrame];
	expressionFrame.origin.x = expressionFrame.size.width;
	expressionFrame.size.width = contentBounds.size.width - expressionFrame.size.height - expressionFrame.origin.x;
	[subviewButton setFrame:expressionFrame];

	// create a container for the expression field and subview popup
	expressionFrame = NSMakeRect(expressionFrame.size.height,
								 contentBounds.size.height - expressionFrame.size.height,
								 contentBounds.size.width - expressionFrame.size.height,
								 expressionFrame.size.height);
	expressionContainer = [[NSView alloc] initWithFrame:expressionFrame];
	[expressionContainer setAutoresizingMask:(NSViewWidthSizable | NSViewMinYMargin)];
	[expressionContainer addSubview:expressionField];
	[expressionField release];
	[expressionContainer addSubview:subviewButton];
	[subviewButton release];
	[[window contentView] addSubview:expressionContainer];
	[expressionContainer release];

	// create the disassembly view
	dasmView = [[MAMEDisassemblyView alloc] initWithFrame:NSMakeRect(0, 0, 100, 100) machine:*machine];
	[dasmView insertSubviewItemsInMenu:[subviewButton menu] atIndex:0];
	dasmScroll = [[NSScrollView alloc] initWithFrame:NSMakeRect(0,
																0,
																contentBounds.size.width,
																expressionFrame.origin.y)];
	[dasmScroll setAutoresizingMask:(NSViewWidthSizable | NSViewHeightSizable)];
	[dasmScroll setHasHorizontalScroller:YES];
	[dasmScroll setHasVerticalScroller:YES];
	[dasmScroll setAutohidesScrollers:YES];
	[dasmScroll setBorderType:NSNoBorder];
<<<<<<< HEAD
=======
	[dasmScroll setDrawsBackground:NO];
>>>>>>> upstream/master
	[dasmScroll setDocumentView:dasmView];
	[dasmView release];
	[[window contentView] addSubview:dasmScroll];
	[dasmScroll release];

	// create the action popup
	actionButton = [[self class] newActionButtonWithFrame:NSMakeRect(0,
																	 expressionFrame.origin.y,
																	 expressionFrame.size.height,
																	 expressionFrame.size.height)];
	[actionButton setAutoresizingMask:(NSViewMaxXMargin | NSViewMinYMargin)];
	[actionButton setFont:[NSFont systemFontOfSize:[defaultFont pointSize]]];
	[dasmView insertActionItemsInMenu:[actionButton menu] atIndex:1];
	[[window contentView] addSubview:actionButton];
	[actionButton release];

	// set default state
<<<<<<< HEAD
	[dasmView selectSubviewForDevice:debug_cpu_get_visible_cpu(*machine)];
=======
	[dasmView selectSubviewForDevice:machine->debugger().cpu().get_visible_cpu()];
>>>>>>> upstream/master
	[dasmView setExpression:@"curpc"];
	[expressionField setStringValue:@"curpc"];
	[expressionField selectText:self];
	[subviewButton selectItemAtIndex:[subviewButton indexOfItemWithTag:[dasmView selectedSubviewIndex]]];
	[window makeFirstResponder:expressionField];
	[window setTitle:[NSString stringWithFormat:@"Disassembly: %@", [dasmView selectedSubviewName]]];

	// calculate the optimal size for everything
	NSSize const desired = [NSScrollView frameSizeForContentSize:[dasmView maximumFrameSize]
										   hasHorizontalScroller:YES
											 hasVerticalScroller:YES
													  borderType:[dasmScroll borderType]];
	[self cascadeWindowWithDesiredSize:desired forView:dasmScroll];

	// don't forget the result
	return self;
}


- (void)dealloc {
	[super dealloc];
}


- (id <MAMEDebugViewExpressionSupport>)documentView {
	return dasmView;
}


- (IBAction)debugNewMemoryWindow:(id)sender {
	debug_view_disasm_source const *source = [dasmView source];
	[console debugNewMemoryWindowForSpace:&source->space()
<<<<<<< HEAD
								   device:&source->device()
=======
								   device:source->device()
>>>>>>> upstream/master
							   expression:nil];
}


- (IBAction)debugNewDisassemblyWindow:(id)sender {
	debug_view_disasm_source const *source = [dasmView source];
	[console debugNewDisassemblyWindowForSpace:&source->space()
<<<<<<< HEAD
										device:&source->device()
=======
										device:source->device()
>>>>>>> upstream/master
									expression:[dasmView expression]];
}


- (BOOL)selectSubviewForDevice:(device_t *)device {
	BOOL const result = [dasmView selectSubviewForDevice:device];
	[subviewButton selectItemAtIndex:[subviewButton indexOfItemWithTag:[dasmView selectedSubviewIndex]]];
	[window setTitle:[NSString stringWithFormat:@"Disassembly: %@", [dasmView selectedSubviewName]]];
	return result;
}


- (BOOL)selectSubviewForSpace:(address_space *)space {
	BOOL const result = [dasmView selectSubviewForSpace:space];
	[subviewButton selectItemAtIndex:[subviewButton indexOfItemWithTag:[dasmView selectedSubviewIndex]]];
	[window setTitle:[NSString stringWithFormat:@"Disassembly: %@", [dasmView selectedSubviewName]]];
	return result;
}


- (IBAction)debugToggleBreakpoint:(id)sender {
	if ([dasmView cursorVisible])
	{
<<<<<<< HEAD
		device_t &device = [dasmView source]->device();
=======
		device_t &device = *[dasmView source]->device();
>>>>>>> upstream/master
		offs_t const address = [dasmView selectedAddress];
		device_debug::breakpoint *bp = [[self class] findBreakpointAtAddress:address forDevice:device];

		// if it doesn't exist, add a new one
<<<<<<< HEAD
		if (bp == NULL)
		{
			UINT32 const bpnum = device.debug()->breakpoint_set(address, NULL, NULL);
			debug_console_printf(*machine, "Breakpoint %X set\n", bpnum);
=======
		if (bp == nullptr)
		{
			uint32_t const bpnum = device.debug()->breakpoint_set(address, nullptr, nullptr);
			machine->debugger().console().printf("Breakpoint %X set\n", bpnum);
>>>>>>> upstream/master
		}
		else
		{
			int const bpnum = bp->index();
			device.debug()->breakpoint_clear(bpnum);
<<<<<<< HEAD
			debug_console_printf(*machine, "Breakpoint %X cleared\n", (UINT32)bpnum);
=======
			machine->debugger().console().printf("Breakpoint %X cleared\n", (uint32_t)bpnum);
>>>>>>> upstream/master
		}

		// fail to do this and the display doesn't update
		machine->debug_view().update_all();
<<<<<<< HEAD
		debugger_refresh_display(*machine);
=======
		machine->debugger().refresh_display();
>>>>>>> upstream/master
	}
}


- (IBAction)debugToggleBreakpointEnable:(id)sender {
	if ([dasmView cursorVisible])
	{
<<<<<<< HEAD
		device_t &device = [dasmView source]->device();
		offs_t const address = [dasmView selectedAddress];
		device_debug::breakpoint *bp = [[self class] findBreakpointAtAddress:address forDevice:device];
		if (bp != NULL)
		{
			device.debug()->breakpoint_enable(bp->index(), !bp->enabled());
			debug_console_printf(*machine,
								 "Breakpoint %X %s\n",
								 (UINT32)bp->index(),
								 bp->enabled() ? "enabled" : "disabled");
			machine->debug_view().update_all();
			debugger_refresh_display(*machine);
=======
		device_t &device = *[dasmView source]->device();
		offs_t const address = [dasmView selectedAddress];
		device_debug::breakpoint *bp = [[self class] findBreakpointAtAddress:address forDevice:device];
		if (bp != nullptr)
		{
			device.debug()->breakpoint_enable(bp->index(), !bp->enabled());
			machine->debugger().console().printf("Breakpoint %X %s\n",
												 (uint32_t)bp->index(),
												 bp->enabled() ? "enabled" : "disabled");
			machine->debug_view().update_all();
			machine->debugger().refresh_display();
>>>>>>> upstream/master
		}
	}
}


- (IBAction)debugRunToCursor:(id)sender {
	if ([dasmView cursorVisible])
<<<<<<< HEAD
		[dasmView source]->device().debug()->go([dasmView selectedAddress]);
=======
		[dasmView source]->device()->debug()->go([dasmView selectedAddress]);
>>>>>>> upstream/master
}


- (IBAction)changeSubview:(id)sender {
	[dasmView selectSubviewAtIndex:[[sender selectedItem] tag]];
	[window setTitle:[NSString stringWithFormat:@"Disassembly: %@", [dasmView selectedSubviewName]]];
}


<<<<<<< HEAD
=======
- (void)saveConfigurationToNode:(util::xml::data_node *)node {
	[super saveConfigurationToNode:node];
	node->set_attribute_int("type", MAME_DEBUGGER_WINDOW_TYPE_DISASSEMBLY_VIEWER);
	node->set_attribute_int("cpu", [dasmView selectedSubviewIndex]);
	[dasmView saveConfigurationToNode:node];
}


- (void)restoreConfigurationFromNode:(util::xml::data_node const *)node {
	[super restoreConfigurationFromNode:node];
	int const region = node->get_attribute_int("cpu", [dasmView selectedSubviewIndex]);
	[dasmView selectSubviewAtIndex:region];
	[subviewButton selectItemAtIndex:[subviewButton indexOfItemWithTag:[dasmView selectedSubviewIndex]]];
	[dasmView restoreConfigurationFromNode:node];
}


>>>>>>> upstream/master
- (BOOL)validateMenuItem:(NSMenuItem *)item {
	SEL const action = [item action];
	BOOL const inContextMenu = ([item menu] == [dasmView menu]);
	BOOL const haveCursor = [dasmView cursorVisible];

<<<<<<< HEAD
	device_debug::breakpoint *breakpoint = NULL;
	if (haveCursor)
	{
		breakpoint = [[self class] findBreakpointAtAddress:[dasmView selectedAddress]
												 forDevice:[dasmView source]->device()];
=======
	device_debug::breakpoint *breakpoint = nullptr;
	if (haveCursor)
	{
		breakpoint = [[self class] findBreakpointAtAddress:[dasmView selectedAddress]
												 forDevice:*[dasmView source]->device()];
>>>>>>> upstream/master
	}

	if (action == @selector(debugToggleBreakpoint:))
	{
		if (haveCursor)
		{
<<<<<<< HEAD
			if (breakpoint != NULL)
=======
			if (breakpoint != nullptr)
>>>>>>> upstream/master
			{
				if (inContextMenu)
					[item setTitle:@"Clear Breakpoint"];
				else
					[item setTitle:@"Clear Breakpoint at Cursor"];
			}
			else
			{
				if (inContextMenu)
					[item setTitle:@"Set Breakpoint"];
				else
					[item setTitle:@"Set Breakpoint at Cursor"];
			}
		}
		else
		{
			if (inContextMenu)
				[item setTitle:@"Toggle Breakpoint"];
			else
				[item setTitle:@"Toggle Breakpoint at Cursor"];
		}
		return haveCursor;
	}
	else if (action == @selector(debugToggleBreakpointEnable:))
	{
<<<<<<< HEAD
		if ((breakpoint != NULL) && !breakpoint->enabled())
=======
		if ((breakpoint != nullptr) && !breakpoint->enabled())
>>>>>>> upstream/master
		{
			if (inContextMenu)
				[item setTitle:@"Enable Breakpoint"];
			else
				[item setTitle:@"Enable Breakpoint at Cursor"];
		}
		else
		{
			if (inContextMenu)
				[item setTitle:@"Disable Breakpoint"];
			else
				[item setTitle:@"Disable Breakpoint at Cursor"];
		}
<<<<<<< HEAD
		return breakpoint != NULL;
=======
		return breakpoint != nullptr;
>>>>>>> upstream/master
	}
	else
	{
		return YES;
	}
}

@end
