//
//  PlayingCardView.m
//  SuperCard
//
//  Created by Lorenzo O. Espares on 3/18/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "PlayingCardView.h"

static const CGFloat cornerRadius = 12.0;
static const CGFloat fontSizeAsFractionOfCardWidth = 0.20;
static const CGFloat cornerOffset = 2.0;
static const CGFloat pipFontScaleFactor = 0.2;
static const CGFloat defaultFaceCardScaleFactor = 0.9;
static const CGFloat pipHoffsetFraction = 0.165;
static const CGFloat pipVoffset1Fraction = 0.09;
static const CGFloat pipVoffset2Fraction = 0.175;
static const CGFloat pipVoffset3Fraction = 0.27;

@interface PlayingCardView ()
@property (nonatomic) CGFloat faceCardScaleFactor;
@end

@implementation PlayingCardView

//
// Initializes the view.
//
- (void)setup {
    _faceCardScaleFactor = defaultFaceCardScaleFactor;
}

//
// Initializes the view.  awakeFromNib gets called after the view and its
// subviews were allocated and initialized. It is guaranteed that the view will
// have all its outlet instance variables set.  Use KVO to watch instance
// variables for changes.  Installs a pinch gesture recognizer.
//
- (void)awakeFromNib {
    [self setup];
    [self addObserver:self forKeyPath:@"self.rank" options:0 context:NULL];
    [self addObserver:self forKeyPath:@"self.suit" options:0 context:NULL];
    [self addObserver:self forKeyPath:@"self.faceUp" options:0 context:NULL];
    [self addObserver:self forKeyPath:@"self.faceCardScaleFactor" options:0
              context:NULL];
    UIPinchGestureRecognizer *pinchRecognizer =
    [[UIPinchGestureRecognizer alloc] initWithTarget:self
                                              action:@selector(pinch:)];
    [self addGestureRecognizer:pinchRecognizer];
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
// Initializes the view.
//
- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    [self setup];
    return self;
}



#pragma mark - Drawing

//
// Recognizes a pinch gesture and sets adjusts the scale factor of the card
// accordingly.
//
- (void)pinch:(UIPinchGestureRecognizer *)recognizer {
    if (recognizer.state == UIGestureRecognizerStateChanged ||
        recognizer.state == UIGestureRecognizerStateEnded) {
        self.faceCardScaleFactor *= recognizer.scale;
        recognizer.scale = 1.0;
    }
}

//
// Draws the face of the card.  If there's no image for this rank, draw pips
// instead.
//
- (void)drawCardFace {
    NSString *imageName = [NSString stringWithFormat:@"%@%@.jpg",
                           [self rankAsString], self.suit];
    UIImage *faceImage = [UIImage imageNamed:imageName];
    if (faceImage != nil) {
        CGRect imageRect = CGRectInset(self.bounds,
                                       self.bounds.size.width *
                                       (1.0 - self.faceCardScaleFactor),
                                       self.bounds.size.height *
                                       (1.0 - self.faceCardScaleFactor));
        [faceImage drawInRect:imageRect];
        
    } else
        [self drawPips];
    [self drawCorners];
}

//
// Draws the white background and border of the card.
//
- (void)drawCardBackground {
    UIBezierPath *roundedRect = [UIBezierPath bezierPathWithRoundedRect:
                                 self.bounds
                                cornerRadius:cornerRadius];
    [roundedRect addClip];
    [[UIColor whiteColor] setFill];
    UIRectFill(self.bounds);
    [[UIColor blackColor] setStroke];
    [roundedRect stroke];
}

//
// Draws the back of the playing card.
//
- (void)drawRect:(CGRect)rect {
    [self drawCardBackground];
    if (self.isFaceUp)
        [self drawCardFace];
    else
        [self drawCardBack];
}

//
// Draws the back of the card.
//
- (void)drawCardBack {
    [[UIImage imageNamed:@"doge.jpg"] drawInRect:self.bounds];
}

//
// Converts the card rank to a string.
//
- (NSString *)rankAsString {
    return @[@"?", @"A", @"2", @"3", @"4", @"5", @"6", @"7", @"8", @"9", @"10",
             @"J", @"Q", @"K"][self.rank];
}

//
// Draws the corners of the card.
//
- (void)drawCorners {
    NSMutableParagraphStyle *paragraphStyle =
                                [[NSMutableParagraphStyle alloc] init];
    paragraphStyle.alignment = NSTextAlignmentCenter;
    UIFont *cornerFont = [UIFont systemFontOfSize:self.bounds.size.width *
                          fontSizeAsFractionOfCardWidth];
    NSString *text = [NSString stringWithFormat:@"%@\n%@", [self rankAsString],
                      self.suit];
    NSDictionary *attributes = @{ NSParagraphStyleAttributeName: paragraphStyle,
                                  NSFontAttributeName : cornerFont };
    NSAttributedString *cornerText = [[NSAttributedString alloc]
                                      initWithString:text
                                      attributes:attributes];
    CGRect textBounds;
    textBounds.origin = CGPointMake(cornerOffset, cornerOffset);
    textBounds.size = [cornerText size];
    [cornerText drawInRect:textBounds];
    [self saveContextAndRotateUpsideDown];
    [cornerText drawInRect:textBounds];
    [self restoreContext];
}

//
// Saves the current graphics context and sets the current transformation matrix
// so that we are drawing upside down in the lower right of the card.
//
- (void)saveContextAndRotateUpsideDown {
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSaveGState(context);
    CGContextTranslateCTM(context, self.bounds.size.width,
                          self.bounds.size.height);
    CGContextRotateCTM(context, M_PI);
}

//
// Restores the graphics context.
//
- (void)restoreContext {
    CGContextRestoreGState(UIGraphicsGetCurrentContext());
}

#pragma mark - Draw Pips

//
// Draws the pips on a card.  If the card is a face card, this does nothing.
// Row 0 is at the center of the card, row 1 is above that.  Row 3 is the top
// row of pips, which is aligned with the suit in the corner of the card.
//
- (void)drawPips {
    if ([self cardHasOnePipInRowZero])
        [self drawOnePipInRow:0];
    else if ([self cardHasTwoPipsInRowZero])
        [self drawTwoPipsInRow:0];
    if ([self cardHasTwoPipsInRowOne])
        [self drawTwoPipsInRow:1];
    if ([self cardHasOnePipInRowTwo])
        [self drawOnePipInRow:2];
    if ([self cardHasTwoPipsInRowThree])
        [self drawTwoPipsInRow:3];
}

//
// Determines if a card has one pip in row zero.
//
- (BOOL)cardHasOnePipInRowZero {
    return self.rank == 1 || self.rank == 3 || self.rank == 5 || self.rank == 9;
}

//
// Determines if a card has two pips in row zero.
//
- (BOOL)cardHasTwoPipsInRowZero {
    return self.rank == 6 || self.rank == 7 || self.rank == 8;
}

//
// Determines if a card has two pips in row one.
//
- (BOOL)cardHasTwoPipsInRowOne {
    return self.rank == 9 || self.rank == 10;
}

//
// Determines if a card has one pip in row two.
//
- (BOOL)cardHasOnePipInRowTwo {
    return self.rank == 2 || self.rank == 3 || self.rank == 7 || self.rank == 8
    || self.rank == 10;
}

//
// Determines if a card has two pips in row three.
//
- (BOOL)cardHasTwoPipsInRowThree {
    return self.rank == 4 || self.rank == 5 || self.rank == 6 || self.rank == 7
    || self.rank == 8 || self.rank == 9 || self.rank == 10;
}

//
// Draws a single pip in row.  The pip is mirrored unless it is in row 0 or if
// the rank is seven.  Setting the horizontal offset to 0 causes just one pip to
// be drawn.
//
- (void)drawOnePipInRow:(NSUInteger)row {
    if (row == 0)
        [self drawPipsWithHorizontalOffset:0
                            verticalOffset:0
                        mirroredVertically:NO];
    else if (row == 2)
        [self drawPipsWithHorizontalOffset:0
                            verticalOffset:pipVoffset2Fraction
                        mirroredVertically:(self.rank != 7)];
}

//
// Draws two pips in a row.  All pips are mirrored unless they are in row zero.
//
- (void)drawTwoPipsInRow:(NSUInteger)row {
    if (row == 0)
        [self drawPipsWithHorizontalOffset:pipHoffsetFraction
                            verticalOffset:0
                        mirroredVertically:NO];
    else if (row == 1)
        [self drawPipsWithHorizontalOffset:pipHoffsetFraction
                            verticalOffset:pipVoffset1Fraction
                        mirroredVertically:YES];
    else if (row == 3)
        [self drawPipsWithHorizontalOffset:pipHoffsetFraction
                            verticalOffset:pipVoffset3Fraction
                        mirroredVertically:YES];
}

//
// Draws pips at the given horizontal and vertical offset from the center of the
// card.  The offsets are a fraction of the card size.  upsideDown indicates
// whether we are drawing the pips inverted.  If the horizontal offset is
// nonzero, two pips are drawn on either side of the vertical axis.
//
- (void)drawPipsWithHorizontalOffset:(CGFloat)hoffset
                      verticalOffset:(CGFloat)voffset
                          upsideDown:(BOOL)isUpsideDown
{
    if (isUpsideDown)
        [self saveContextAndRotateUpsideDown];
    CGPoint middle = CGPointMake(self.bounds.size.width / 2.0,
                                 self.bounds.size.height / 2.0);
    UIFont *pipFont = [UIFont systemFontOfSize:self.bounds.size.width *
                       pipFontScaleFactor];
    NSAttributedString *attributedSuit = [[NSAttributedString alloc]
                                          initWithString:self.suit
                                          attributes:@{ NSFontAttributeName:
                                                            pipFont }];
    CGSize pipSize = [attributedSuit size];
    CGPoint pipOrigin = CGPointMake(middle.x - pipSize.width / 2.0 -
                                    hoffset * self.bounds.size.width,
                                    middle.y - pipSize.height / 2.0 -
                                    voffset * self.bounds.size.height);
    [attributedSuit drawAtPoint:pipOrigin];
    if (hoffset != 0.0) {
        pipOrigin.x += hoffset * 2.0 * self.bounds.size.width;
        [attributedSuit drawAtPoint:pipOrigin];
    }
    if (isUpsideDown)
        [self restoreContext];
}

//
// Draws pips with given horizontal and vertical offsets.  If the horizontal
// offset is nonzero, then two pips are drawn at the given vertical offset,
// on either side of the vertical axis.  This pips will be mirrored vertically
// if mirroredVertically is true.
//
- (void)drawPipsWithHorizontalOffset:(CGFloat)hoffset
                      verticalOffset:(CGFloat)voffset
                  mirroredVertically:(BOOL)mirroredVertically
{
    [self drawPipsWithHorizontalOffset:hoffset
                        verticalOffset:voffset
                            upsideDown:NO];
    if (mirroredVertically)
        [self drawPipsWithHorizontalOffset:hoffset
                            verticalOffset:voffset
                                upsideDown:YES];
}

@end
