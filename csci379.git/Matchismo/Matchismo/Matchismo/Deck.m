//
//  Deck.m
//  Matchismo
//
//  Created by Lorenzo O. Espares on 1/29/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//


#import "Deck.h"

@interface Deck()
@property (strong, nonatomic) NSMutableArray *cards;
@end

@implementation Deck

//
// Initializes the class.
//
- (instancetype)init {
    self = [super init];
    if (self != nil) {
        _cards = [[NSMutableArray alloc] init];
    }
    return self;
}

//
// Adds a card to the deck. If atTop is YES, add the card to the top of the
// deck. Otherwise, add it to the bottom.
//
- (void)addCard:(Card *)card atTop:(BOOL)atTop {
    if (card == nil)
    return;
    if (atTop)
        [self.cards insertObject:card atIndex:0];
    else
        [self.cards addObject:card];
}

//
// Draws a random card from the deck. If the deck is empty, return nil.
//
- (Card *)drawRandomCard { Card *randomCard = nil;
    if ([self.cards count] != 0) {
        NSUInteger index = arc4random() % [self.cards count];
        randomCard = self.cards[index];
        [self.cards removeObjectAtIndex:index];
    }
    return randomCard;
}


@end
