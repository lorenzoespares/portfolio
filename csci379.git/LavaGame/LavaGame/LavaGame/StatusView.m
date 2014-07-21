//
//  StatusView.m
//  LavaGame
//
//  Created by Lorenzo O. Espares on 5/6/14.
//  Copyright (c) 2014 bucknell.edu. All rights reserved.
//

#import "StatusView.h"

static const CGFloat defaultStatusScaleFactor = 1.0;

@interface StatusView ()
@property (nonatomic) CGFloat StatusScaleFactor;
@end

@implementation StatusView

//
// Initializes the view.
//
- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    _StatusScaleFactor = defaultStatusScaleFactor;
    return self;
}

//
// Initializes the view.  awakeFromNib gets called after the view and its
// subviews were allocated and initialized. It is guaranteed that the view will
// have all its outlet instance variables set.  Use KVO to watch instance
// variables for changes.
//
- (void)awakeFromNib {
    _StatusScaleFactor = defaultStatusScaleFactor;
    [self addObserver:self forKeyPath:@"self.status" options:0 context:NULL];
    [self addObserver:self forKeyPath:@"self.faceCardScaleFactor" options:0
              context:NULL];
    self.status = @"gameover";
}

//
// Requests a refresh whenever an instance variable changes.
//
- (void)observeValueForKeyPath:(NSString *)keyPath
                      ofObject:(id)object
                        change:(NSDictionary *)change
                       context:(void *)context
{
    [self setNeedsDisplay];
}

//
// Draws the view to be displayed.
//
- (void)drawRect:(CGRect)rect {
    [self drawStatus];
}

//
// Draws the view. The view can either be a "win" or "death" view. The main menu
// also uses a status view, but instead displays main.jpg to the user.
//
- (void)drawStatus {
    NSString *imageName = [NSString stringWithFormat:@"%@.jpg",
                           self.status];
    NSLog(@"%@", self.status);
    UIImage *faceImage = [UIImage imageNamed:imageName];
    if (faceImage != nil) {
        CGRect imageRect = CGRectInset(self.bounds,
                                       self.bounds.size.width *
                                       (1.0 - self.StatusScaleFactor),
                                       self.bounds.size.height *
                                       (1.0 - self.StatusScaleFactor));
        [faceImage drawInRect:imageRect];
    }
}

@end
