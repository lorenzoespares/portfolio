//
//  SetPlayingCard.h
//  Matchismo
//
//  Created by Lorenzo O. Espares on 2/19/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
//  A set playing card is a card that has a pattern, rank, shade, and color

#import "Card.h"

@interface SetPlayingCard : Card

@property (strong , nonatomic) NSString *pattern;
@property (nonatomic) NSUInteger rank;
@property (strong , nonatomic) NSString *shade;
@property (strong , nonatomic) NSString *color;

- (NSUInteger)matchset:(NSArray *)otherCards;

- (NSString*)description;
+ (NSArray *)validPatterns;
+ (NSArray *)validShading;
+ (NSArray *)validColors;
+ (NSArray *)validRanks;


@end
