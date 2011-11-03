#import <Cocoa/Cocoa.h>

static inline todo(const char *msg) {
	printf("TODO: %s [%s, %d]\n", msg, __FILE__, __LINE__);
}

static inline RangeToNSRange(range rng) {
	return NSMakeRange(rng.location, rng.length);
}
static inline NSRangeToRange(NSRange rng) {
	return range(rng.location, rng.length);
}


@implementation CHMulticursorController

- (NSLayoutManager *)layoutManager {
	return [view layoutManager];
}
// Perform a text view action (select word right, etc) multiple times in the mulctx
- (BOOL)performTextViewActionInContext:(SEL)action argument:(id)argument {
	
	// Basically
	//  1. For each range, set it as the selection
	//  2. Do the action
	//  3. Get the new range
	//  4. Modify the ranges
	
	disableSelectedRange++;
	
	mulctx.performAction(^range (range rng, bool* shouldDelete) {
		
		[view setSelectedRange:RangeToNSRange(rng)];
		
		[view performSelector:action withObject:argument];
		
		range rng = NSRangeToRange([view selectedRange]);
		
		return rng;
	});
	
	[view setSelectedRange:RangeToNSRange(mulctx.primaryRange())];
	
	disableSelectedRange--;
}
- (void)setSelectedRange:(NSRange)sel {
	
	if (disableSelectedRange > 0) {
		[view super_setSelectedRange:sel];
	}
	
	multctx.setRangeAtIndex(multctx.primaryRangeIndex(), RangeFromNSRange(sel));
}
- (NSRange)selectedRange {
	
	if (disableSelectedRange > 0)
		return [view super_selectedRange];
	
	return RangeToNSRange(mulctx.primaryRange());
}
- (void)insertText:(NSString *)text {
	
	mulctx.performAction(^range (range rng, bool* shouldDelete) {
		
		[view setSelectedRange:RangeToNSRange(rng)];
		
		[view insertText:text];
		
		range rng = NSRangeToRange([view selectedRange]);
		
		return rng;
	});
	
}
- (void)textDidChangeInRange:(NSRange)range newLength:(NSInteger)newLength {
	
	
	
}

// Return NO if the event was not handled
- (BOOL)handleEvent:(NSEvent *)event {
	
	// cmd-esc					decohere
	// alt-click				add new cursor		(alt-click)
	// alt-click*				add	new range		(alt-click then release alt and drag)
	// alt-drag					create new block of selections, replace current state
	// cmd-alt-drag				create new block of selections, adding to current selection
	// alt-{right|ctrl}-click	remove selection
	// alt-double-click			focus selection
	// alt-double-click			unfocus selection
	// alt-drag					move selection endpoint
	// alt-drag					move selection
	
	// Undo/redo
	
	NSEventType type = [event type];
	
	if (type == NSRightMouseUp || (type == NSLeftMouseUp && ([event modifierFlags] & NSControlKeyMask)) {
		[self removeSelectionForEvent:event];
	}
	if (type == NSKeyDown && ([event modifierFlags] & NSCommandKeyMask) && [event keyCode] == 53) { /* 53 == escape */
		[self decohere];
	}
	if (type == NSLeftMouseDown && ([event modifierFlags] & NSAlternateKeyMask)) {
		return [self altMouseDown:event];
	}
	if (type == NSLeftMouseDragged && ([event modifierFlags] & NSAlternateKeyMask)) {
		return [self altMouseDragged:event];
	}
	if (type == NSLeftMouseUp && ([event modifierFlags] & NSAlternateKeyMask)) {
		return [self altMouseUp:event];
	}
	
}
- (void)removeSelectionForEvent:(NSEvent *)event {
	
	NSInteger clickPoint = [self rangeLocationForEvent:event];
	
	range rng = 
	mulctx.performAction(^range (range rng, bool* shouldDelete) {
		
		
		// Find the distance to this range
		
		return rng;
	});

	
}
- (BOOL)altMouseDown:(NSEvent *)event {
	startPoint = [self rangeLocationForEvent:event];
	
	
	
	
}
- (BOOL)altMouseDragged:(NSEvent *)event {
	NSInteger dragPoint = [self rangeLocationForEvent:event];
	
	// Is alt still down?
	BOOL hasAlt = [event modifierFlags] & NSAlternateKeyMask;
	
	
}
- (BOOL)altMouseUp:(NSEvent *)event {
	NSInteger endPoint = [self rangeLocationForEvent:event];
	
	BOOL hasAlt = [event modifierFlags] & NSAlternateKeyMask;
	BOOL isDoubleClick = ([event clickCount] == 2);
	
	if (isDoubleClick) {
		// Focus or unfocus endPoint
		todo("focusing/unfocusing");
		return;
	}
	
	if (endPoint == startPoint) {
		// Add a cursor		
		mulctx.addRange(range(startPoint, 0));
	}
	else if (hasAlt) {
		// Blockedit
		todo("blockedit");
	}
	else {
		// Contiguous
		if (startPoint < endPoint)
			mulctx.addRange(range(startPoint, endPoint - startPoint));
		else
			mulctx.addRange(range(endPoint, startPoint - endPoint));
	}
}


#pragma mark Actions

- (IBAction)decohere {
	mulctx.decohere();
}

- (NSInteger)rangeLocationForEvent:(NSEvent*)event {
	todo("rangeLocationForEvent");
}
- (IBAction)addRangeAction:(NSEvent*)event {
	
	NSRange rng = NSMakeRange([self rangeLocationForEvent:event], 0);
	
}

@end
