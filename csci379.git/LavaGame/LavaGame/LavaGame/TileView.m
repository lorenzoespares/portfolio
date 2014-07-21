//
//  TileView.m
//  LavaGame
//
//  Created by Lorenzo O. Espares on 5/5/14.
//  Copyright (c) 2014 bucknell.edu. All rights reserved.
//

#import "TileView.h"

static const CGFloat defaultTileScaleFactor = 1.0;

@interface TileView ()
@property (nonatomic) CGFloat TileScaleFactor;
@end

@implementation TileView

//
// Initializes the view.
//
- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    _TileScaleFactor = defaultTileScaleFactor;
    return self;
}

//
// Initializes the view.  awakeFromNib gets called after the view and its
// subviews were allocated and initialized. It is guaranteed that the view will
// have all its outlet instance variables set.  Use KVO to watch instance
// variables for changes.
//
- (void)awakeFromNib {
    _TileScaleFactor = defaultTileScaleFactor;
    [self addObserver:self forKeyPath:@"self.tiletype" options:0 context:NULL];
    [self addObserver:self forKeyPath:@"self.faceCardScaleFactor" options:0
              context:NULL];
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
// Draws the tile
//
- (void)drawRect:(CGRect)rect {
    [self drawTile];
}

//
// Draws the face of the tile. The tile can either be floor or lava.
//
- (void)drawTile {
    NSString *imageName = [NSString stringWithFormat:@"%@.jpg",
                           self.tiletype];
    UIImage *faceImage = [UIImage imageNamed:imageName];
    if (faceImage != nil) {
        CGRect imageRect = CGRectInset(self.bounds,
                                       self.bounds.size.width *
                                       (1.0 - self.TileScaleFactor),
                                       self.bounds.size.height *
                                       (1.0 - self.TileScaleFactor));
        [faceImage drawInRect:imageRect];
    }
}

@end
