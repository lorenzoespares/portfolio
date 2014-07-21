//
//  GenericViewController_Protected.h
//  Matchismo
//
//  Protected header file that only allows access to view controllers that
//  inherit from and are subclasses of GenericViewController.

#import "CardGameViewController.h"
#import "CardMatchingGame.h"

@interface GenericViewController ()

@property (nonatomic, readonly) NSUInteger startingCardCount; // abstract
@property (strong, nonatomic) CardMatchingGame *game;
- (Deck *)createDeck;	// abstract
- (void)updateCell:(UICollectionViewCell *)cell usingCard:(Card *)card; // abstract
- (void)startNewGame;

@end
