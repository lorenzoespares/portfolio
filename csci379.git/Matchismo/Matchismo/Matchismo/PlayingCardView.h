//
//  PlayingCardView.h
//  SuperCard
//
//  Created by Lorenzo O. Espares on 3/18/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
//  This view will show either side of a playing card.  If the card is face
//  down, it displays the card back.  If the card is face up, display either
//  an image for a face card, or pips for all others.

#import <UIKit/UIKit.h>

@interface PlayingCardView : UIView

@property (nonatomic) NSUInteger rank;
@property (nonatomic, strong) NSString *suit;
@property (nonatomic, getter = isFaceUp) BOOL faceUp;

@end
