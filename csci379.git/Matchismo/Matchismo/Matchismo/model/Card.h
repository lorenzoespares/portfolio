//
//  Card.h
//  Matchismo
//
//  Created by Lorenzo O. Espares on 1/29/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
// This class represents a generic card. It is an abstract class.

#import <Foundation/Foundation.h>

@interface Card : NSObject

@property(nonatomic, readonly) NSString *contents;
@property (nonatomic, getter = isFaceUp) BOOL faceUp;
@property (nonatomic, getter = isUnplayable) BOOL unplayable;

- (NSUInteger)match:(NSArray *)otherCards;

@end
