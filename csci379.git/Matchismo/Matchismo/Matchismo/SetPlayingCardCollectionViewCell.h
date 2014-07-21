//
//  SetPlayingCardCollectionViewCell.h
//  Matchismo
//
//  Created by Lorenzo O. Espares on 3/18/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
//  A cell in the collection view that holds a SetPlayingCardView in the
//  SetCardGameViewController to handle the displaying of SetPlayingCards.

#import <UIKit/UIKit.h>
#import "SetPlayingCardView.h"

@interface SetPlayingCardCollectionViewCell : UICollectionViewCell
@property (weak, nonatomic) IBOutlet SetPlayingCardView *setplayingCardView;
@end
