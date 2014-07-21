//
//  SetGameViewController.m
//  Matchismo
//
//  Created by Lorenzo O. Espares on 2/19/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "SetGameViewController.h"
#import "SetPlayingCardDeck.h"
#import "SetPlayingCard.h"
#import "SetMatchingGame.h"
#import "SetPlayingCardCollectionViewCell.h"
#import "CardGameViewController_Protected.h"


@interface SetGameViewController ()
@property (weak, nonatomic) IBOutlet UILabel *scoreLabel;
@property (weak, nonatomic) IBOutlet UILabel *statusLabel;

@end

@implementation SetGameViewController

//
// Initializes the model.
//
- (void)viewDidLoad {
    [super viewDidLoad];
    self.statusLabel.text = [NSString stringWithFormat:
                             @"Welcome to SET."];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

//
// Returns the number of cards in the game.
//
- (NSUInteger)startingCardCount {
    return 12;
}

//
// Creates a new deck of cards.
//
- (Deck *)createDeck {
    return [[SetPlayingCardDeck alloc] init];
}


//
// Updates the cell with the current properties of the playing card.
//
- (void)updateCell:(UICollectionViewCell *)cell usingCard:(Card *)card {
    SetPlayingCardView *setplayingCardView =
                ((SetPlayingCardCollectionViewCell *)cell).setplayingCardView;
    SetPlayingCard *playingCard = (SetPlayingCard *)card;
    setplayingCardView.rank = playingCard.rank;
    setplayingCardView.pattern = playingCard.pattern;
    setplayingCardView.color = playingCard.color;
    setplayingCardView.shade = playingCard.shade;
    
    
    setplayingCardView.faceUp = playingCard.isFaceUp;
    setplayingCardView.alpha = playingCard.isUnplayable ? 0.3 : 1.0;
}

//
// Updates the view with the current properties of the playing card.
//
- (void)updateView:(UIView *)view usingCard:(Card *)card {
    SetPlayingCardView *setplayingCardView = (SetPlayingCardView *)view;
    SetPlayingCard *playingCard = (SetPlayingCard *)card;
    setplayingCardView.rank = playingCard.rank;
    setplayingCardView.pattern = playingCard.pattern;
    setplayingCardView.color = playingCard.color;
    setplayingCardView.shade = playingCard.shade;
    
    
    setplayingCardView.faceUp = playingCard.isFaceUp;
}

//
// Creates a cell for the specified index path and updates it.
//
- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView
                  cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    UICollectionViewCell *cell = [collectionView
                        dequeueReusableCellWithReuseIdentifier:@"SetPlayingCard"
                                                forIndexPath:indexPath];
    Card *card = [self.game cardAtIndex:indexPath.item];
    [self updateCell:cell usingCard:card];
    return cell;
}


//
// Starts a new game by dealing the cards, setting the flip count to 0 and
// updating the UI.
//
- (void)startNewGame {
    self.game = [[SetMatchingGame alloc] initWithCardCount:self.startingCardCount
                                                  usingDeck:[self createDeck]];
    [super startNewGame];
}


@end
