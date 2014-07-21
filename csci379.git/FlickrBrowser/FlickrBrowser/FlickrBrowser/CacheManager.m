//
//  CacheManager.m
//  FlickrBrowser
//
//  Created by Lorenzo O. Espares on 4/8/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "CacheManager.h"

static CacheManager *sharedInstance = nil;

@implementation CacheManager

//
//  Initializes the instance if it is uninitialized, otherwise returns the
//  already existing instance.
//
+(CacheManager *)sharedInstance {
    if (sharedInstance == nil) {
        sharedInstance = [[CacheManager alloc] init];
        sharedInstance.cache = [[NSCache alloc] init];
    }
    return sharedInstance;
}

//
//  Stores an object in the cache with the corresponding key.
//
-(void)setCache:(id)obj forKey:(NSString *)key {
    [self.cache setObject:obj forKey:key];
}

//  Gets an object from the cache with the corresponding key.
-(id)getCacheForKey:(NSString *)key {
    return [self.cache objectForKey:key];
}
@end
