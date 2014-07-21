//
//  Card.m
//  Matchismo
//
//  Created by Lorenzo O. Espares on 1/29/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "Card.h"

@implementation Card

//
// Returns a string that describes this object.
//
- (NSString *)description {
    return self.contents; }

//
// Determins how well self matches the cards in an array of cards. If there is
// an exact match, return 1, otherwise return 0. Returns an integer because we
// may want to change this to indicate the strength of the match.
//

- (NSUInteger) match:(NSArray *)otherCards {
    NSUInteger score = 0;
    for (Card *card in otherCards) {
        if ([card.contents isEqualToString:self.contents]) {
            score = 1;
            break;
        }
    }
    return score;
}

@end
