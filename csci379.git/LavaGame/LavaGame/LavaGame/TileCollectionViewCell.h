//
//  TileCollectionViewCell.h
//  LavaGame
//
//  Created by Lorenzo O. Espares on 5/5/14.
//  Copyright (c) 2014 bucknell.edu. All rights reserved.
//
//  A collectionview cell that specifically handles the display of the tile.

#import <UIKit/UIKit.h>
#import "TileView.h"

@interface TileCollectionViewCell : UICollectionViewCell
@property (weak, nonatomic) IBOutlet TileView *tileview;

@end
