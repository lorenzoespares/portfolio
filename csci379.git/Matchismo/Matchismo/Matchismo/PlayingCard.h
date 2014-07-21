//
//  PlayingCard.h
//  Matchismo
//
//  Created by Lorenzo O. Espares on 1/29/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
// A playing card is a card that has a rank and a suit.

#import "Card.h"

@interface PlayingCard : Card

@property (strong , nonatomic) NSString *suit;
@property (nonatomic) NSUInteger rank;

+ (NSArray *)validSuits;
+ (NSUInteger)maxRank;


@end
