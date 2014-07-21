//
//  PlayingCardDeck.m
//  Matchismo
//
//  Created by Lorenzo O. Espares on 1/29/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "PlayingCardDeck.h"
#import "PlayingCard.h"

@implementation PlayingCardDeck

//
// Initializes the card deck so that there is one card from each suit and rank
// for a total of 52 cards.
//

- (instancetype)init {
    self = [super init];
    if (self != nil) {
        for (NSString *suit in [PlayingCard validSuits]) {
            for (NSUInteger rank = 1; rank <= [PlayingCard maxRank]; rank++) {
                PlayingCard *card = [[PlayingCard alloc] init];
                card.rank = rank;
                card.suit = suit;
                [self addCard:card atTop:YES];
            }
        }
    }
    return self;
}

@end
