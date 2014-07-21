//
//  SetPlayingCard.m
//  Matchismo
//
//  Created by Lorenzo O. Espares on 2/19/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "SetPlayingCard.h"

static NSArray *validPatterns;
static NSArray *validRanks;
static NSArray *validShading;
static NSArray *validColors;

@interface SetPlayingCard()
@property(readwrite, nonatomic) NSAttributedString *SetCardcontents;
@end

@implementation SetPlayingCard


//
// Initializes the class before any methods are called.
//
+ (void)initialize {
    if (self == [SetPlayingCard class]) {
        validRanks = @[@"1", @"2", @"3"];
        validPatterns = @[@"▲", @"■", @"●"];
        validShading = @[@"N", @"S", @"F"];
        validColors = @[@"R", @"G", @"B"];
    }
}


//
// Returns a string that describes this object.
//
- (NSString*)description {
    NSArray *myStrings = [[NSArray alloc] initWithObjects:[validRanks[self.rank - 1]
            stringByAppendingString:self.pattern], self.shade, self.color, nil];
    return [myStrings componentsJoinedByString:@""];
}

//
// Returns an array of strings representing valid suits.
//
+ (NSArray *)validPatterns {
    return validPatterns;
}

//
// Returns an array of strings representing valid suits.
//
+ (NSArray *)validShading {
    return validShading;
}

//
// Returns an array of strings representing valid suits.
//
+ (NSArray *)validColors {
    return validColors;
}

+ (NSArray *)validRanks {
    return validRanks;
}


//
// Sets the pattern for a playing card. If the parameter is invalid, set it to
// a question mark.
//
- (void)setPattern:(NSString *)pattern {
    if([validPatterns containsObject:pattern])
        _pattern = pattern;
    else
        _pattern = @"?";
}

//
// Sets the rank for a playing card. If the parameter is invalid, set it to
// 0.
//
- (void)setRank:(NSUInteger)rank {
    if(rank < [validRanks count] + 1)
        _rank = rank;
    else
        _rank = 0;
}

//
// Sets the shade for a playing card. If the parameter is invalid, set it to
// a question mark.
//
- (void)setShade:(NSString *)shade{
    if([validShading containsObject:shade])
        _shade = shade;
    else
        _shade = @"?";
}

//
// Sets the color for a playing card. If the parameter is invalid, set it to
// a question mark.
//
- (void)setColor:(NSString *)color{
    if([validColors containsObject:color])
        _color = color;
    else
        _color = @"?";
}

//
// Intermediate method used to compare two set playing cards. ie, if A = B
// and B = C, then and B = C and A = C, then A = B = C in terms of similarities
// and differences in satisfying the logic for the match game.
//
- (NSUInteger)matchtwo:(SetPlayingCard *)first
         withothercard:(SetPlayingCard *)second{
    NSUInteger mismatch = 0;
    // rank pattern shade color
    
    if (first.rank != second.rank) {
        mismatch += 1;
    }
    if ([first.pattern isEqualToString:second.pattern] == false) {
        mismatch += 2;
    }
    if ([first.shade isEqualToString:second.shade] == false) {
        mismatch += 3;
    }
    if ([first.color isEqualToString:second.color] == false) {
        mismatch += 4;
    }
    
    return mismatch;
}

//
// Determines if the three set playing cards match correctly. If the three cards
// make a set (following the logic presented in the matchtwo method), then
// change score to 1 and return score.
//
- (NSUInteger)matchset:(NSArray *)otherCards {
    NSUInteger score = 0;
    if ([otherCards count] == 2){
        SetPlayingCard *firstotherCard = [otherCards firstObject];
        SetPlayingCard *secondotherCard = [otherCards lastObject];
        
        
        if (([self matchtwo:self withothercard:firstotherCard] ==
             [self matchtwo:firstotherCard withothercard:secondotherCard]) &&
            ([self matchtwo:firstotherCard withothercard:secondotherCard] ==
             [self matchtwo:self withothercard:secondotherCard])) {
                score = 1;
            }
    }
    return score;
}



@end
