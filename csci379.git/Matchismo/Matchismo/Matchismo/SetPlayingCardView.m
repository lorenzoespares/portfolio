//
//  SetPlayingCardView.m
//  Matchismo
//
//  Created by Lorenzo O. Espares on 3/18/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "SetPlayingCardView.h"

static const CGFloat cornerRadius = 12.0;
static const CGFloat fontSizeAsFractionOfCardWidth = 0.20;
static const CGFloat cornerOffset = 2.0;
static const CGFloat shapeOffset = 0.2;
static const CGFloat defaultFaceCardScaleFactor = 0.9;
static const CGFloat linethickness = 0.02;
static const CGFloat shapewidth = 0.15;
static const CGFloat shapeheight = 0.4;
static const CGFloat squiggle = 0.9;
static const CGFloat stripeOffset = 0.06;
static const CGFloat stripeangle = 5;


@interface SetPlayingCardView ()
@property (nonatomic) CGFloat faceCardScaleFactor;
@end

@implementation SetPlayingCardView

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
    [self addObserver:self forKeyPath:@"self.pattern" options:0 context:NULL];
    [self addObserver:self forKeyPath:@"self.color" options:0 context:NULL];
    [self addObserver:self forKeyPath:@"self.shade" options:0 context:NULL];
    [self addObserver:self forKeyPath:@"self.faceUp" options:0 context:NULL];
    [self addObserver:self forKeyPath:@"self.faceCardScaleFactor" options:0
                                                        context:NULL];
    UIPinchGestureRecognizer *pinchRecognizer = [[UIPinchGestureRecognizer alloc]
                                                 initWithTarget:self
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
    [[self SetColor] setStroke];
    CGPoint point = CGPointMake(self.bounds.size.width/2,
                                self.bounds.size.height/2);
    if (self.rank == 1) {
        [self drawShape:point];
    }
    CGFloat offset = self.bounds.size.width * shapeOffset;
    if (self.rank == 2) {
        [self drawShape:CGPointMake(point.x - offset / 2, point.y)];
        [self drawShape:CGPointMake(point.x + offset / 2, point.y)];
    }
    if (self.rank == 3) {
        [self drawShape:point];
        [self drawShape:CGPointMake(point.x - offset, point.y)];
        [self drawShape:CGPointMake(point.x + offset, point.y)];
    }
}

//
// Sets the color to be used depending on the color representation of the
// SetPlayingCard.
//
- (UIColor *)SetColor
{
    if ([self.color isEqualToString:@"R"])
        return [UIColor redColor];
    if ([self.color isEqualToString:@"G"])
        return [UIColor greenColor];
    if ([self.color isEqualToString:@"B"])
        return [UIColor blueColor];
    return nil;
}

//
// Calls the proper method depending on the pattern representation of the
// SetPlayingCard.
//
- (void)drawShape:(CGPoint)point
{
    if ([self.pattern isEqualToString:@"●"]) {
        [self drawOval:point];
    } else if ([self.pattern isEqualToString:@"■"]) {
        [self drawSquiggle:point];
    }else if ([self.pattern isEqualToString:@"▲"]) {
        [self drawDiamond:point];
    }
}

//
// Draws an Oval Shape
//
- (void)drawOval:(CGPoint)point;
{
    CGFloat offsetx = self.bounds.size.width * shapewidth / 2;
    CGFloat offsety = self.bounds.size.height * shapeheight / 2;
    
    UIBezierPath *path = [UIBezierPath bezierPathWithRoundedRect:
                          CGRectMake(point.x - offsetx, point.y - offsety,
                                     2 * offsetx, 2 * offsety)
                          cornerRadius:offsetx];
    
    path.lineWidth = self.bounds.size.width * linethickness;
    [self shadeShape:path];
    [path stroke];
}

//
// Draws a Squiggle Shape
//
- (void)drawSquiggle:(CGPoint)point;
{
    CGFloat offsetx = self.bounds.size.width * shapewidth / 2;
    CGFloat offsety = self.bounds.size.height * shapeheight / 3;
    CGFloat squiggle_x = offsetx * squiggle;
    CGFloat squiggle_y = offsety * squiggle;
    
    UIBezierPath *path = [[UIBezierPath alloc] init];
    [path moveToPoint:CGPointMake(point.x - offsetx, point.y - offsety)];
    [path addQuadCurveToPoint:CGPointMake(point.x + offsetx, point.y - offsety)
                 controlPoint:CGPointMake(point.x - squiggle_x, point.y -
                                          offsety - squiggle_y)];
    [path addCurveToPoint:CGPointMake(point.x + offsetx, point.y + offsety)
            controlPoint1:CGPointMake(point.x + offsetx + squiggle_x, point.y -
                                      offsety + squiggle_y)
            controlPoint2:CGPointMake(point.x + offsetx - squiggle_x, point.y +
                                      offsety - squiggle_y)];
    [path addQuadCurveToPoint:CGPointMake(point.x - offsetx, point.y + offsety)
                 controlPoint:CGPointMake(point.x + squiggle_x, point.y +
                                          offsety + squiggle_y)];
    [path addCurveToPoint:CGPointMake(point.x - offsetx, point.y - offsety)
            controlPoint1:CGPointMake(point.x - offsetx - squiggle_x, point.y +
                                      offsety - squiggle_y)
            controlPoint2:CGPointMake(point.x - offsetx + squiggle_x, point.y -
                                      offsety + squiggle_y)];
    
    path.lineWidth = self.bounds.size.width * linethickness;
    [self shadeShape:path];
    [path stroke];
}

//
// Draws a Diamond Shape.
//
- (void)drawDiamond:(CGPoint)point;
{
    CGFloat offsetx = self.bounds.size.width * shapewidth / 2;
    CGFloat offsety = self.bounds.size.height * shapeheight / 2;
    
    UIBezierPath *path = [[UIBezierPath alloc] init];
    [path moveToPoint:CGPointMake(point.x, point.y - offsety)];
    [path addLineToPoint:CGPointMake(point.x + offsetx, point.y)];
    [path addLineToPoint:CGPointMake(point.x, point.y + offsety)];
    [path addLineToPoint:CGPointMake(point.x - offsetx, point.y)];
    [path closePath];
    
    path.lineWidth = self.bounds.size.width * linethickness;
    [self shadeShape:path];
    [path stroke];
}


//
// Draws the stripes inside the shape.
//
- (void)shadeShape:(UIBezierPath *)path
{
    if ([self.shade isEqualToString:@"F"]) {
        [[self SetColor] setFill];
        [path fill];
    } else if ([self.shade isEqualToString:@"S"]) {
        CGContextRef context = UIGraphicsGetCurrentContext();
        CGContextSaveGState(context);
        
        [path addClip];
        UIBezierPath *stripes = [[UIBezierPath alloc] init];
        CGPoint start = self.bounds.origin;
        CGPoint end = start;
        CGFloat offset = self.bounds.size.height * stripeOffset;
        end.x += self.bounds.size.width;
        start.y += offset * stripeangle;
        for (int i = 0; i < 1 / stripeOffset; i++) {
            [stripes moveToPoint:start];
            [stripes addLineToPoint:end];
            start.y += offset;
            end.y += offset;
        }
        
        stripes.lineWidth = self.bounds.size.width / 2 * linethickness;
        [stripes stroke];
        [self restoreContext];
    } else if ([self.shade isEqualToString:@"N"]) {
        [[UIColor clearColor] setFill];
    }
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
    [self drawCardFace];
    if (self.isFaceUp)
        [self setAlpha:0.6];
}

//
// Restores the graphics context.
//
- (void)restoreContext {
    CGContextRestoreGState(UIGraphicsGetCurrentContext());
}

@end

