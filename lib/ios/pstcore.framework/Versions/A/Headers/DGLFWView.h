#import <UIKit/UIKit.h>
#import "DGLFWCreateWindowCallback.h"

#pragma mark - DGLFWView

@interface DGLFWView : UIView

+ (void)setCreateWindowCallback:(id<DGLFWCreateWindowCallback>)callback;
- (instancetype)initWithFrame:(CGRect)frame window_ptr:(void*)window_ptr;

@property(nonatomic, assign) void *window_ptr;

@end

