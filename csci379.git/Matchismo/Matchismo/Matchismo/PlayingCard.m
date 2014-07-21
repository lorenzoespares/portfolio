//
//  PlayingCard.m
//  Matchismo
//
//  Created by Lorenzo O. Espares on 1/29/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "PlayingCard.h"

static NSArray *rankStrings;
static NSArray *validSuits;
static NSUInteger maxRank;

@implementation PlayingCard

//
// Initializes the class before any methods are called.
//
+ (void)initialize {
    if (self == [PlayingCard class]) {
        rankStrings = @[@"?", @"A", @"2", @"3", @"4", @"5", @"6", @"7", @"8",
                        @"9", @"10", @"J", @"Q", @"K"];
        validSuits = @[@"♥", @"♦", @"♠", @"♣"];
        maxRank = [rankStrings count] - 1;
    }
}

//
// Returns an array of strings representing valid suits.
//
+ (NSArray *)validSuits {
    return validSuits;
}

//
// Returns the maximum rank a playing card may have.
//
+ (NSUInteger)maxRank {
    return maxRank;
}

//
// Returns a string representing this card.
//
- (NSString *)contents {
    return [rankStrings[self.rank] stringByAppendingString:self.suit];
}

//
// Sets the suit for a playing card. If the parameter is invalid, set it to
// a question mark.
//

- (void)setSuit:(NSString *)suit {
    if ([validSuits containsObject:suit])
        _suit  = suit;
    else
        _suit = @"?";
}

//
// Sets the rank for a card. If the parameters has an invalid value, use 0. //
- (void)setRank:(NSUInteger)rank {
    if (rank <= [PlayingCard maxRank])
        _rank = rank;
    else
        _rank = 0;
}

//
// Determines the match score when compared to the single card that is in
// otherCards.  If the suits match, the score is 1.  If the ranks match, the
// score is 4.  Otherwise, the score is 0. This method is also fitted for
// three card matching, comparing the ranks and suits of three cards
// to return the proper score. All ranks match = 8, two ranks match = 4,
// all suits match = 2, two suits match =1.
//
- (NSUInteger)match:(NSArray *)otherCards {
    NSUInteger score = 0;
    if ([otherCards count] == 1) {
        PlayingCard *otherCard = [otherCards lastObject];
        if ([otherCard.suit isEqualToString:self.suit])
            score = 1;
        else if (otherCard.rank == self.rank)
            score = 4;
    } else if ([otherCards count] == 2){
        PlayingCard *firstotherCard = [otherCards firstObject];
        PlayingCard *secondotherCard = [otherCards lastObject];
        if ((firstotherCard.rank == self.rank) &
            (secondotherCard.rank == self.rank))
            score = 8;
        else if ((firstotherCard.rank == self.rank) |
                 (secondotherCard.rank == self.rank) |
                 (firstotherCard.rank == secondotherCard.rank))
            score = 4;
        else if ([firstotherCard.suit isEqualToString:self.suit] &
                 [secondotherCard.suit isEqualToString:self.suit])
            score = 2;
        else if ([firstotherCard.suit isEqualToString:self.suit] |
            [secondotherCard.suit isEqualToString:self.suit] |
            [firstotherCard.suit isEqualToString:secondotherCard.suit])
            score = 1;

    }
    return score;
}


@end
