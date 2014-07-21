//
//  SetPlayingCardView.h
//  Matchismo
//
//  Created by Lorenzo O. Espares on 3/18/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
//  This view will show either side of a SetPlayingCard. Since the pattern on a
//  Set Card is visible from both sides, this view does not draw the back of the
//  card. This class takes care of drawing the ovals, diamonds, and squiggle
//  patterns to give a Set Card feel.

#import <UIKit/UIKit.h>

@interface SetPlayingCardView : UIView

@property (nonatomic, getter = isFaceUp) BOOL faceUp;

@property (strong , nonatomic) NSString *pattern;
@property (nonatomic) NSUInteger rank;
@property (strong , nonatomic) NSString *shade;
@property (strong , nonatomic) NSString *color;

@end
