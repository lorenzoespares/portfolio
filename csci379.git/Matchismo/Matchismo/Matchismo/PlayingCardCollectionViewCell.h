//
//  PlayingCardCollectionViewCell.h
//  Matchismo
//
//  Created by Lorenzo O. Espares on 3/18/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
//  A cell in the collection view that holds a PlayingCardView in the
//  CardGameViewController to handle the displaying of PlayingCards.
//

#import <UIKit/UIKit.h>
#import "PlayingCardView.h"

@interface PlayingCardCollectionViewCell : UICollectionViewCell
@property (weak, nonatomic) IBOutlet PlayingCardView *playingCardView;
@end
