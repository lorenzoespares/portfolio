//
//  SetPlayingCardDeck.m
//  Matchismo
//
//  Created by Lorenzo O. Espares on 2/19/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "SetPlayingCardDeck.h"
#import "SetPlayingCard.h"

@implementation SetPlayingCardDeck

//
// Initializes the card deck so that there is one card from each pattern, rank,
// shade, and color for a total of 81 cards. We will only be using 24 cards
// for the actual game.

- (instancetype)init {
    self = [super init];
    if (self != nil) {
        for (NSString *pattern in [SetPlayingCard validPatterns]) {
            for (NSString *shade in [SetPlayingCard validShading]) {
                for (NSString *color in [SetPlayingCard validColors]) {
                    for (NSUInteger rank = 1;
                    rank < [[SetPlayingCard validRanks] count] + 1; rank++) {
                        SetPlayingCard *card = [[SetPlayingCard alloc] init];
                        card.rank = rank;
                        card.pattern = pattern;
                        card.shade = shade;
                        card.color = color;
                        [self addCard:card atTop:YES];
                    }
                }
            }
        }
    }
    return self;
}

@end
