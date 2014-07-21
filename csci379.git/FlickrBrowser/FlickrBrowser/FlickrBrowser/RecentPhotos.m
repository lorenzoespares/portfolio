//
//  RecentPhotos.m
//  FlickrBrowser
//
//  Created by Lorenzo O. Espares on 3/26/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "RecentPhotos.h"
#import "FlickrFetcher.h"

@implementation RecentPhotos

//
//  Gets the most recent photos that are saved into userdefaults.
//
+ (NSArray *)getRecentPhotos
{
    return [[NSUserDefaults standardUserDefaults] objectForKey:@"RecentPhotos"];
}

//
//  Adds a photo to userdefaults. If the photo is already present, it removes
//  the photo and adds it at the beginning of the array of photos.
//
+ (void)addPhoto:(NSDictionary *)photo
{
    NSUserDefaults *userdefaults = [NSUserDefaults standardUserDefaults];
    NSMutableArray *photos = [[userdefaults objectForKey:@"RecentPhotos"] mutableCopy];
    
    if (!photos) photos = [NSMutableArray array];
    NSUInteger key = [photos indexOfObject:photo];
    if (key != NSNotFound) [photos removeObjectAtIndex:key];
    [photos insertObject:photo atIndex:0];
    while ([photos count] > 20) {
        [photos removeLastObject];
    }
    
    [userdefaults setObject:photos forKey:@"RecentPhotos"];
}


@end
