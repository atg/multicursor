#import <Cocoa/Cocoa.h>

@interface CHMulticursorController : NSObject {
    
    NSTextView *view;
    multicursor::context mulctx;
}

- (NSLayoutManager *)layoutManager;
- (void)performTextViewActionInContext:(SEL)action argument:(id)argument; // Perform a text view action (select word right, etc) multiple times in the mulctx

- (void)insertText:(NSString *)text view:(NSTextView *)view;
- (void)textDidChangeInRange:(NSRange)range newLength:(NSInteger)newLength;

- (BOOL)handleEvent:(NSEvent *)event; // Return NO if the event was not handled

@end
